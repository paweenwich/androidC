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

#include <../util/util.hpp>
#include <../util/PtraceUtil.hpp>
#include <../util/logger.h>
#include <../util/payload.hpp>
#include <../util/elf_help.h>

#include <../util/SimpleTCPServer.hpp>

#define  LOG_TAG    "loader"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

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

void * ServerService(void *arg)
{
    LOGD("%d Start",gettid());
    char line[1024];
    int socket = (int)arg;
    SimpleSocket sock(socket);
    int count;
    while(!sock.IsClosed()){
    //while((count = sock.hasData())>=0){
	count = sock.hasData();
	LOGD("%d count=[%d]",gettid(),count);
	if(count > 0){
	    FILE *f = fdopen(socket, "r+");
	    if(fgets(line,sizeof(line),f)!=NULL){
		//remove new line
		line[strlen(line)-1]=0;
		LOGD("%d [%s]",gettid(),line);
		if(strcmp(line,"QUIT")==0){
		    sock.Close();
		    break;
		}
		if(!sock.SendLine((char *)"OK")){
		    LOGD("Write fail");
		    sock.Close();
		    break;
		}
	    }
	}
	//sleep(3);
    }
    LOGD("%d End",gettid());
    /*currentFile = f;
    luaLogger = new Logger();
    luaLogger->fp = f;
    LOGD("ServerService %d",gettid());
    lua->execFile(scriptfile);
    ServerLog(">");*/
    /*while(fgets(line,sizeof(line),f)!=NULL){
	line[strlen(line)-2] = 0;
	LOGD("CMD[%d]=[%s]",gettid(),line);
	if(strcmp(line,"QUIT")==0){
	    //ServerLog("Goodbye\n");
	    fclose(f);
	    break;
	}
	if(strcmp(line,"RELOAD")==0){
	    //lua->execFile(scriptfile);
	}else{
	    //lua->execString(line);
	}
	//ServerLog(">");
    }*/
}


void *ServerStart(void *)
{
    SimpleTCPServer server;
    server.Start(1414,(void *)ServerService);
}

void __attribute__ ((constructor)) armhlp_load()
{
    LOGD("LIBRARY LOADED FROM PID %d.", getpid());

    pthread_t t;
    pthread_create(&t, NULL, ServerStart,NULL);
    
}


void __attribute__ ((destructor)) armhlp_unload()
{
    LOGD("LIBRARY UNLOADED FROM PID %d.", getpid());
}