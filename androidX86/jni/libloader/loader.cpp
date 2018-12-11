#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/mman.h>
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

#include "../util/util.hpp"
#include "../util/PtraceUtil.hpp"
#include "../util/logger.h"
#include "../util/payload.hpp"
#include "../util/elf_help.h"

#include "../util/SimpleTCPServer.hpp"

#define  LOG_TAG    "loader"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#include "BaseCommandService.h"


extern "C" {
    void ThreadLoadManageLibrary();
};

void *LoadManagedLibrary(void *)
{
    //MonoLoadAndInvokeAssembly("/data/local/tmp/SimpleClass.dll", "SimpleClass","Main", "Start");
    LOGD("LoadManagedLibrary called %d", getpid());
}

void ThreadLoadManageLibrary()
{
    pthread_t t;
    pthread_create(&t, NULL, LoadManagedLibrary, NULL);
}

void * ServerService(SimpleTCPServerParam *arg)
{
    //BaseCommanService *service = (BaseCommanService *)arg;
    SimpleTCPServerParam *sp = /*(SimpleTCPServerParam *)*/arg;
    LOGD("%d Start",gettid());
    int socket = sp->clientSocket;
    BaseCommandService *service = (BaseCommandService *)sp->service;
    SimpleSocket sock(socket);
    int count;
    while(!sock.IsClosed()){
        //char line[1024];
    	count = sock.hasData();
	LOGD("%d count=[%d]",gettid(),count);
	if(count > 0){
            std::string sline = sock.ReadLine();
            //sprintf("%s")
	    //FILE *f = fdopen(socket, "r+");
	    //if(fgets(line,sizeof(line),f)!=NULL){
		//remove new line
		//line[strlen(line)-1]=0;
		LOGD("%d [%s]",gettid(),sline.c_str());
                // hard code QUIT
		if(strcmp(sline.c_str(),"QUIT")==0){
                    sock.SendLine((char *)"BYE\nOK");
		    sock.Close();
		    break;
		}
                if(service!=NULL){
                    service->doLine(sock,(char *)sline.c_str());
                }
                //Always answer back
                sock.SendLine((char *)"OK");                
	    //}
	}
	//sleep(3);
    }
    LOGD("%d End",gettid());
}


void *ServerStart(void *param)
{

    std::string exeName = GetCurrentExecutable();
    LOGD("EXENAME %s",exeName.c_str());
    SimpleTCPServer server;    
    if(strstr(exeName.c_str(),"tracer")!=NULL){
	server.Start(1415,(void *)ServerService,param);
    }else{
	server.Start(1414,(void *)ServerService,param);
    }
}

void __attribute__ ((constructor)) armhlp_load()
{
    LOGD("LIBRARY LOADED FROM PID %d", getpid());

    pthread_t t;
    pthread_create(&t, NULL, ServerStart,new BaseCommandService());
    LOGD("THREAD CREATED");
}


void __attribute__ ((destructor)) armhlp_unload()
{
    LOGD("LIBRARY UNLOADED FROM PID %d", getpid());
}