/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimpleTCPServer.cpp
 * Author: kwang
 * 
 * Created on December 3, 2018, 2:40 PM
 */
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <resolv.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <dlfcn.h>
#include <stdarg.h>
#include <string>
#include <vector>
#include <cctype>
#include <dirent.h>
#include <pthread.h>
#include <netdb.h>
#include <netinet/in.h>


#include <../util/util.hpp>
#include <../util/PtraceUtil.hpp>
#include <../util/logger.h>
#include <../util/payload.hpp>
#include <../util/elf_help.h>


#define  LOG_TAG    "SimpleTCPServer"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#include "SimpleTCPServer.hpp"

SimpleTCPServer::SimpleTCPServer() {
}

SimpleTCPServer::SimpleTCPServer(const SimpleTCPServer& orig) {
}

SimpleTCPServer::~SimpleTCPServer() {
}

void SimpleTCPServer::Start(int port,void *threadServiceFunc, void *param)
{
    LOGE("ServerStart %d",port);
    struct sockaddr_in addr;
    /*--- create lua script ---*/
    
    //CreateLuaScript();
    /*--- create socket ---*/
    int sd = socket(PF_INET, SOCK_STREAM, 0);
    if ( sd < 0 ){
	LOGE("socket: %s",strerror(errno));
	return;
    }
    
    int enable = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0){
	LOGE("setsockopt(SO_REUSEADDR) failed");
    }

    /*--- bind port/address to socket ---*/
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;                   /* any interface */
    if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 ){
	LOGE("bind: %s",strerror(errno));
	return;
    }

    /*--- make into listener with 10 slots ---*/
    if ( listen(sd, 10) != 0 ){
	LOGE("listen: %s",strerror(errno));
	return;
    }
    /*--- begin waiting for connections ---*/
    else
    {	
	LOGD("C Server startd %d",port);
	while (1)                         /* process all incoming clients */
	{
	    pthread_t child;
	    FILE *fp;

	    int clientSocket = accept(sd, 0, 0);	     /* accept connection */
	    LOGD("Client connect");
            SimpleTCPServerParam *sp = new SimpleTCPServerParam();
            sp->clientSocket = clientSocket;
            sp->service = param;
	    pthread_create(&child, 0, (void * (*)(void *))threadServiceFunc, (void *)sp);       /* start thread */
	    pthread_detach(child);                      /* don't track it */
	}
    }
    return;
}


SimpleTCPClient::SimpleTCPClient(int port)
{
    this->port = port;
}
bool SimpleTCPClient::ConnectLocal()
{
   struct sockaddr_in serv_addr;
   int sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      LOGE("ERROR opening socket");
      return false;
   }

   struct hostent *server = gethostbyname("127.0.0.1");
   
   if (server == NULL) {
      LOGE("ERROR, no such host");
      return false;
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(port);
   
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      LOGE("ERROR connecting");
      return false;
   }

   sock = SimpleSocket(sockfd);
   return true;
}


SimpleSocket::SimpleSocket(int socket)
{
    sock = socket;
    //NonBlocking();
}

void SimpleSocket::NonBlocking()
{
    int flags;
    flags = fcntl(sock,F_GETFL,0);
    //assert(flags != -1);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

bool SimpleSocket::printf(const char *format, ...)
{
    char buff[2048];
    va_list args;
    va_start(args, format);
    vsprintf(buff,format, args);
    va_end(args);
    return SendString(buff);
}


bool SimpleSocket::SendString(char *mesg)
{
    int ret = send(sock, mesg, strlen(mesg), MSG_NOSIGNAL);
    if(ret==-1){
	return false;
    }else{
	LOGD("SendString %s %d",mesg,ret);
    }
    return true;
}

bool SimpleSocket::SendLine(char *mesg)
{
    char buf[strlen(mesg)+20];
    sprintf(buf,"%s\n",mesg);
    return(SendString(buf));
}

std::string SimpleSocket::ReadLine()
{
    char c = '0';
    int status = 0;
    int i = 0;
    std::string ret;
    while(true)
    {
        if(IsClosed()){
            break;
        }
        status = recv(sock,&c, 1,0);
        //LOGD("readline recv %d",status);
        if(status <=0){
            return ret;
        }
        else if(status > 0)
        {
            if(c == '\n' || c == '\r')
            {
                break;
            }
            ret += c;            
        }
    }
    return ret;
}

std::vector<std::string> SimpleSocket::ReadUntil(char *str)
{
    std::vector<std::string> ret;
    std::string line;
    while(line!=str){
	line = ReadLine();
	if(line!=""){
	    //printf("%s\n",ret.c_str());fflush(stdout);
	    ret.push_back(line);
	}
    }    
    return ret;
}

void SimpleSocket::Close()
{
    close(sock);
}

bool SimpleSocket::IsClosed()
{
    fd_set rfd;
    FD_ZERO(&rfd);
    FD_SET(sock, &rfd);
    timeval tv = { 0 };
    select(sock+1, &rfd, 0, 0, &tv);
    if (!FD_ISSET(sock, &rfd))
      return false;
    int n = 0;
    ioctl(sock, FIONREAD, &n);
    return n == 0;
}

int SimpleSocket::hasData()
{
    //int on=1;
    struct timeval t;
    t.tv_usec=0;
    t.tv_sec=15;

    fd_set readset,writeset,exceptionset;
    FD_ZERO(&readset);
    FD_SET(sock,&readset);
    
    FD_ZERO(&writeset);
    FD_SET(sock,&writeset);
    
    FD_ZERO(&exceptionset);
    FD_SET(sock,&exceptionset);
    
    //ioctl(sock, FIONBIO, (char *)&on);

    int retval=select(sock+1,&readset,NULL,NULL,&t);
    LOGD("retval return %d",retval);
    if(retval==0){
	// timeout
	LOGD("hasData timeout");
	// check if it closed or not 
	return -1;
    }
    if(retval<0){
	// error 
	//LOGD("hasData timeout");
	return -1;
    }

    if(FD_ISSET(sock, &readset)) {
	//int ret1;
	//char buffer[32];
	//ret1 = recv(sock, buffer, 32, MSG_PEEK | MSG_DONTWAIT);
	//LOGD("recv return %d",ret1);
	int count=0;
	ioctl(sock, FIONREAD, &count);
	return count;
    }
    //if(FD_ISSET(sock, &exceptionset)) {
//	LOGD("EXCEPTION");
    //}
    //LOGD("hasData %d",count);
    return 0;
}
