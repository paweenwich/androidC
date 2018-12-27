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
#include <elf.h>

#include "../util/util.hpp"
#include "../util/PtraceUtil.hpp"
#include "../util/logger.h"
#include "../util/payload.hpp"
//#include "../util/elf_help.h"
#include "../util/elf_hook.h"
#include "../util/DLHook.h"


#include "../util/SimpleTCPServer.hpp"

#define  LOG_TAG    "Hook"
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

void Hook()
{
    ELFHook::ShowMap();
    //DLHook::AddWatch("/libunity.so");
    std::vector<HookData> vHook = DLHook::GetDLHookData();
    //DLHook::vHookData.insert(DLHook::vHookData.end(), vHook.begin(), vHook.end());    
    
    char *libNames[] = {
	"/libmono.so",
//	"/libunity.so",
	"/libmain.so",
	0
    };
    for(int i=0;libNames[i]!=NULL;i++){
        ELFHook elfHook;
        if(elfHook.Open(libNames[i])){
	    LOGD("Open %s success",libNames[i]);	    
	    for(int j=0;j<vHook.size();j++){
		unsigned int originalAddr=0;
		if(elfHook.Hook(vHook[j].name, vHook[j].hookAddr,&originalAddr)){
		    LOGD("Hook [%s] [%s] original1=%08X",libNames[i],vHook[j].name,originalAddr); 		
		    *(vHook[j].originalAddr) = originalAddr;
		}
	    }
	}
	
    }
}


void *ServerStart(void *param)
{
    //LOGD("S wsize=%d %d",DLHook::vWatchlibrary.size(),DLHook::vHookData.size());    
    //LOGD("S %08X\n",UINT(&DLHook::vWatchlibrary));
    //LOGD("S wsize=%d %d",DLHook::vWatchlibrary.size(),DLHook::vHookData.size());
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
    Hook();        
    //LOGD("H1 wsize=%d %d",DLHook::vWatchlibrary.size(),DLHook::vHookData.size());
    //LOGD("H1 %08X\n",UINT(&DLHook::vWatchlibrary));
    
    pthread_t t;
    pthread_create(&t, NULL, ServerStart,new BaseCommandService());
    sleep(2);
    //LOGD("H2 wsize=%d %d",DLHook::vWatchlibrary.size(),DLHook::vHookData.size());
    //LOGD("H2 %08X\n",UINT(&DLHook::vWatchlibrary));
    LOGD("THREAD CREATED");
}


void __attribute__ ((destructor)) armhlp_unload()
{
    LOGD("LIBRARY UNLOADED FROM PID %d", getpid());
}