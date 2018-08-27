#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <pthread.h>
#include <netdb.h>
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
#include <fstream>
#include "../util/logger.h"
#include "../luac/luascript.h"
#include "lua_server.hpp"

#define  LOGD(...)  logger->printf(__VA_ARGS__)
#define  LOGE(...)  logger->printf(__VA_ARGS__)
#define	 LOGHEX(x,y)	logger->logHex((x),(y))

LuaScript *lua;
extern Logger *logger;

char *scriptfile = "/data/local/tmp/cscript.lua";
FILE *currentFile;


void ServerLog(char *str)
{
    fprintf(currentFile,"%s",str);
    fflush(currentFile);
}

void * ServerService(void *arg)
{
    char line[1024];
    FILE *f = (FILE *)arg;
    currentFile = f;
    luaLogger = new Logger();
    luaLogger->fp = f;
    LOGD("ServerService %d",gettid());
    lua->execFile(scriptfile);
    ServerLog(">");
    while(fgets(line,sizeof(line),f)!=NULL){
	line[strlen(line)-2] = 0;
	LOGD("CMD[%d]=[%s]",gettid(),line);
	if(strcmp(line,"QUIT")==0){
	    ServerLog("Goodbye\n");
	    fclose(f);
	    break;
	}
	if(strcmp(line,"RELOAD")==0){
	    lua->execFile(scriptfile);
	}else{
	    lua->execString(line);
	}
	ServerLog(">");
    }
}

void CreateLuaScript()
{
    LOGD("CreateLuaScript");
    lua = new LuaScript(tolua_lua_server_open);
    LOGD("CreateLuaScript %08X",(unsigned int)lua);
    
}
bool ServerStart(int port)
{	
    struct sockaddr_in addr;
    /*--- create lua script ---*/
    
    CreateLuaScript();
    /*--- create socket ---*/
    int sd = socket(PF_INET, SOCK_STREAM, 0);
    if ( sd < 0 ){
	LOGE("socket: %s",strerror(errno));
	return false;
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
	return false;
    }

    /*--- make into listener with 10 slots ---*/
    if ( listen(sd, 10) != 0 ){
	LOGE("listen: %s",strerror(errno));
	return false;
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
	    fp = fdopen(clientSocket, "r+");           /* convert into FILE* */
	    pthread_create(&child, 0, ServerService, (void *)fp);       /* start thread */
	    pthread_detach(child);                      /* don't track it */
	}
    }
}

int main(int argc,char *argv[])
{
    printf("main\n");
    CreateLuaScript();
}