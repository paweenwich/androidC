#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
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
#include <android/log.h>
#include <pthread.h>
#include "../util/logger.h"
#include "../util/payload.hpp"
#include "MonoHooker.hpp"
#include "MonoEval.hpp"
#define TRACE_BIN   "/data/local/tmp/tracer.bin"


Logger *logger;
Mutex mutex;
MonoEval *monoEval;
bool flgLogMonoRuntimeInvoke = false;
bool flgLoadAssemblySuccess = false;

#define  LOGD(...)  logger->printf(__VA_ARGS__)
#define  LOGE(...)  logger->printf(__VA_ARGS__)
#define	 LOGHEX(x,y)	logger->logHex((x),(y));

void kkk(unsigned int freeSpaceAddr);
bool ServerStart(int port);

void ReadMaps(int pid,std::vector<std::string> &out)
{
    char filename[1024] = {0}, buffer[1024] = {0};
    if(pid==0){
         pid = getpid();
    }
    
    FILE *fp = NULL;
    sprintf(filename, "/proc/%d/maps", pid);
    fp = fopen(filename, "rt");
    if (fp == NULL) {
        LOGD("ReadMaps: cannot open %s",filename);
        goto done;
    }
    out.clear();
    while (fgets(buffer, sizeof (buffer), fp)) {
        //printf("[%s] [%s]\n",buffer,library);
        buffer[strlen(buffer)-1] = 0;
        std::string line = buffer;
        out.push_back(line);
    }
done:
    if (fp) {
        fclose(fp);
    }
}

void FindLibraryPath(const char* libname,char *path,unsigned int *baseAddr,unsigned int *libSize)
{
   std::vector<std::string> lines;
   ReadMaps(0,lines);
   LOGD("FindLibraryPath line=%d\n",lines.size());
   for(int i=0;i<lines.size();i++){
	std::string line = lines[i];
	std::replace(line.begin(), line.end(), '-', ' ');
       
	char *ptr;
	if((ptr=strstr(lines[i].c_str(),libname))){
	    LOGD("FindLibraryPath: found %s",lines[i].c_str());
	    while(*ptr != ' ') ptr--;
	    ptr++;
	    strcpy(path,ptr);
	   
	    unsigned int from,to;
	    if(sscanf(line.c_str(),"%X%X",&from,&to)==2){
		
		*baseAddr = from;
		*libSize = to - from;
		LOGD("%s",line.c_str());
		LOGD("%08X %08X",from,to);
		LOGD("%08X %08X",*baseAddr,*libSize);
		return;
	    }
            break;
       }
   }
}

void RestoreData(unsigned int freeSpaceAddr)
{
    int size;
    unsigned char *buf = ReadAllBytes(TRACE_BIN,&size);
    LOGD("Read %s %d bytes",TRACE_BIN,size);
    
    //unsigned int freeSpaceAddr = FindFreeSpace(getpid(),NULL);
    LOGD("Dump freeSpaceAddr=%08X before restore",freeSpaceAddr);
    logger->logHex((unsigned char *)(freeSpaceAddr),32);
    
    memcpy((void *)freeSpaceAddr,(void *)buf,size);
    if(memcmp((void *)freeSpaceAddr,(void *)buf,size)!=0){
	LOGD("ERROR: RestoreData copy fail");
    }
    LOGD("Dump freeSpaceAddr=%08X after restore",freeSpaceAddr);
    logger->logHex((unsigned char *)(freeSpaceAddr),32);

    free(buf);
    // remove restore file 
    remove(TRACE_BIN);
    
}

void Start();
void *threadFunc(void*)
{
    LOGD("threadFunc thread id=%d ",gettid());
    //sleep(10);
    try{
	/*
	monoEval->GetAllAssembly();
	for(int i=0;i<monoEval->vAssembly.size();i++){
	    LOGD("assembly=%08X",(unsigned int)monoEval->vAssembly[i]);
	}
	MonoClass *klass = monoEval->GetClassFromName("","UIManagerScript");
	LOGD("UIManagerScript found %08X",(unsigned int)klass);
	bool bValue = false;
	monoEval->GetField(klass,NULL,"static_bool",bValue);
	LOGD("static_bool=%d",(unsigned int)bValue);
	bValue = false;
	monoEval->SetField(klass,NULL,"static_bool",bValue);
	bValue = true;
	LOGD("static_bool=%d",(int)monoEval->GetFieldAsBool(klass,NULL,"static_bool"));
	LOGD("static_string=%s",monoEval->GetFieldAsString(klass,NULL,"static_string"));
	LOGD("static_int=%d",monoEval->GetFieldAsInt(klass,NULL,"static_int"));
	 */ 
        //MonoDump();
	//MonoLoadAssembly("/data/local/tmp/KopiLua.dll");
	//MonoLoadAssembly("/data/local/tmp/KopiLuaDll.dll");
	//MonoLoadAssembly("/data/local/tmp/KopiLuaInterface.dll");
        
	//MonoLoadAndInvokeAssembly("/data/local/tmp/FantasyWarTactic.dll", "FantasyWarTactic","Main", "Start");
	//mono_runtime_invoke(myMonoMethod,0,0,0);

        
	//MonoLoadAndInvokeAssembly("/data/local/tmp/FantasyWarTactic.dll", "FantasyWarTactic","Main", "Start");
        Start();
	ServerStart(1415);
        
    }catch(...)
    {
	LOGD("EXCEPTION: ");
    }
    LOGD("threadFunc done");
}


void CreateNewPayload()
{
    _PayloadData *pPayloadData;
    unsigned int freeSpaceAddr = FindFreeSpace(getpid(),NULL);
    LOGD("freeSpaceAddr=%08X",freeSpaceAddr);
    pPayloadData = (_PayloadData *)freeSpaceAddr;
    pPayloadData->kkkAddr = (unsigned int)kkk;
    LOGD("kkk=%08X",kkk);
    unsigned int newFreeSpaceAddr = AllocateExecutableMemory(4096);
    LOGD("newFreeSpaceAddr=%08X",newFreeSpaceAddr);
    pPayloadData->newFreeSpaceDataAddr = newFreeSpaceAddr;
    pPayloadData->newFreeSpaceCodeAddr = newFreeSpaceAddr + CODE_OFFSET;
    
    _NewPayloadData *pNewPayloadData;
    pNewPayloadData = (_NewPayloadData *)newFreeSpaceAddr;
    pNewPayloadData->kkkAddr = (unsigned int)kkk;
    pNewPayloadData->funcAddr = pPayloadData->funcAddr;
    LOGD("NewPayloadData");
    logger->logHex((unsigned char *)(pNewPayloadData),sizeof(_NewPayloadData));
    
    unsigned char newAsmCode[] = {
        0x03,0x10,0xA0,0xE1,    //mov r1,r3         -- r1 point to oladpayload data
        0x0F,0x30,0xA0,0xE1,    //mov r3,pc         -- copy pc to r3 (r3 => B20 due to prefetch)
        0x8C,0x30,0x43,0xE2,    //sub r3,128 + 12    -- point r3 to payload data
        
        // save all register
        0xFF,0x01,0x2D,0xE9,    //push {r0-r8}      -- save r0-r8
        0x04,0xE0,0x2D,0xE5,    //push {lr}         -- save lr   
        // try call kkk(freeSpaceAddr)
        0x01,0x00,0xA0,0xE1,    //mov r0,r1
        0x00,0x20,0x93,0xE5,    //ldr r2,[r3]       -- load kkk addr
        0x32,0xFF,0x2F,0xE1,    //blx r2            -- call kkk
        // restore all register
        0x04,0xE0,0x9D,0xE4,    //pop  {lr}         -- pop lr
        0xFF,0x01,0xBD,0xE8,    //pop  {r0-r8}      -- pop r0-r8

        
        // jump back to old function
        0x04,0x20,0x93,0xE5,    //ldr r2,[r3+4]     -- load func addr  
        0x12,0xFF,0x2F,0xE1,    //bx r2             -- jump to funcaddr
    };
    memcpy((void *)(newFreeSpaceAddr + CODE_OFFSET),newAsmCode,sizeof(newAsmCode));
    LOGD("newAsmCode");
    logger->logHex((unsigned char *)(newFreeSpaceAddr + CODE_OFFSET),sizeof(newAsmCode));
    
}


void hook_mono_class_from_name(unsigned int r0,unsigned int r1,unsigned int r2)
{
    MutexLock(&mutex);
    LOGD("mono_class_from_name(%08X,%s,%s)",r0,r1,r2);
    MutexUnlock(&mutex);
}

void hook_mono_class_get_method_from_name(unsigned int r0,unsigned int r1,unsigned int r2)
{
    MutexLock(&mutex);
    //LOGD("hook_mono_class_get_method_from_name(%s,%s,%d)",mono_class_get_name(r0),r1,r2);
    MutexUnlock(&mutex);
}

unsigned int hook_mono_runtime_invoke_data_addr;
void hook_mono_runtime_invoke(unsigned int r0,unsigned int r1,unsigned int r2,unsigned int r3)
{
    MutexLock(&mutex);
    unsigned int monoclass = mono_method_get_class(r0);
    if(monoclass){
	if(flgLogMonoRuntimeInvoke){
	    char className[128];
	    sprintf(className,"%s",mono_class_get_name(monoclass));
	    LOGD("hook_mono_runtime_invoke(%s,%08X,%08X,%08X)",className,r1,r2,r3);
	}
	if(runTimeInvokeQueue!=NULL){
	    if(runTimeInvokeQueue->size()>0){
		
		char className[128];
		sprintf(className,"%s",mono_class_get_name(monoclass));
		LOGD("hook_mono_runtime_invoke(%s,%08X,%08X,%08X)",className,r1,r2,r3);
		
		RunTimeInvokeData invokeData = runTimeInvokeQueue->pop();
		LOGD("RunTimeInvoke %08X",(unsigned int)invokeData.method);
		_HookFuncPayloadData *p = (_HookFuncPayloadData *)hook_mono_runtime_invoke_data_addr;
		LOGD("p->oldFuncAddr = %08X",p->oldFuncAddr);
		mono_runtime_invoke_t my_mono_runtime_invoke = (mono_runtime_invoke_t)p->oldFuncAddr;
		LOGD("domain=%08X",mono_domain_get());
		my_mono_runtime_invoke(invokeData.method,invokeData.obj,invokeData.params,invokeData.exec);
		LOGD("RunTimeInvoke done");
	    }
	}
	//if(strcmp(className,"GameApp")==0){
	    /*if(strcmp(mono_method_get_name(r0),"Update")==0){
		if(myMonoMethod!=0){
		    LOGD("InvokeMe");
		    _HookFuncPayloadData *p = (_HookFuncPayloadData *)hook_mono_runtime_invoke_data_addr;
		    LOGD("p->oldFuncAddr = %08X",p->oldFuncAddr);
		    mono_runtime_invoke_t my_mono_runtime_invoke = (mono_runtime_invoke_t)p->oldFuncAddr;
		    LOGD("domain=%08X",mono_domain_get());
		    void** args = NULL;
		    my_mono_runtime_invoke(myMonoMethod,0,(unsigned int)args,0);
		    //my_mono_runtime_invoke(r0,r1,r2,r3);
		    myMonoMethod = 0;
		    LOGD("my_mono_runtime_invoke done");
		}
		//LOGD("hook_mono_runtime_invoke(%s.%s,%08X,%08X,%08X)",className,mono_method_get_name(r0),r1,r2,r3);
	    }*/
	//}
    }else{
	LOGD("hook_mono_runtime_invoke(%s,%08X,%08X,%08X)",mono_method_get_name(r0),r1,r2,r3);
    }
    MutexUnlock(&mutex);
}

// called from payload
void kkk(unsigned int freeSpaceAddr)
{
    pthread_t t;

    LOGD("kkk(%08X)",freeSpaceAddr);
    RestoreData(freeSpaceAddr);
    //MonoHook("mono_class_from_name",(unsigned int)hook_mono_class_from_name);
    //MonoHook("mono_class_get_method_from_name",(unsigned int)hook_mono_class_get_method_from_name);
    //hook_mono_runtime_invoke_data_addr = MonoHook("mono_runtime_invoke",(unsigned int)hook_mono_runtime_invoke);
    //MonoDump();
    pthread_create(&t, NULL, threadFunc, NULL);
    //MonoLoadAndInvokeAssembly("/data/local/tmp/FantasyWarTactic.dll", "FantasyWarTactic","Main", "Start");
    LOGD("kkk done");
}

void *LoadManagedLibrary(void *)
{
    MonoDomain* rootdomain = mono_get_root_domain(); 
    mono_thread_attach(rootdomain);    
    
    MonoLoadAssembly("/data/local/tmp/KopiLua.dll");
    MonoLoadAssembly("/data/local/tmp/KopiLuaDll.dll");
    MonoLoadAssembly("/data/local/tmp/KopiLuaInterface.dll");
    MonoLoadAssembly("/data/local/tmp/FantasyWarTactic.dll");
    monoEval->GetAllAssembly();
    flgLoadAssemblySuccess = true;
    //MonoLoadAndInvokeAssembly("/data/local/tmp/FantasyWarTactic.dll", "FantasyWarTactic","Main", "Start");
    //MonoLoadAndInvokeAssembly("/data/local/tmp/SimpleClass.dll", "SimpleClass","Main", "Start");
}

void ThreadLoadManageLibrary()
{
    pthread_t t;
    pthread_create(&t, NULL, LoadManagedLibrary, NULL);
}

void *Invoke(void *)
{
    monoEval->InvokeStatic("FantasyWarTactic","Main", "Start",NULL,false);
}

void ThreadInvoke()
{
    pthread_t t;
    pthread_create(&t, NULL, Invoke, NULL);
}


void Start()
{
    flgLoadAssemblySuccess = false;
    while(flgLoadAssemblySuccess==false){
        ThreadLoadManageLibrary();
        sleep(5);
    }
    LOGD("Load success");
    ThreadInvoke();
    
}

void __attribute__ ((constructor)) armhlp_load()
{
    //Can not use gloable
    logger = new Logger("/data/local/tmp/loader.log");
    monoEval = new MonoEval();
    runTimeInvokeQueue = new RunTimeInvokeQueue();
    MutexCreate(&mutex);
    //printf("armhlp_load()\n");
    // can not restore here because we are running in that code
    //RestoreData();
    LOGD("---------LIBRARY LOADED FROM PID %d ------------------", getpid());
    //MonoLoadAndInvokeAssembly("/data/local/tmp/FantasyWarTactic.dll", "FantasyWarTactic","Main", "Start");

    CreateNewPayload();
    LOGD("CreateNewPayload done");
}


void __attribute__ ((destructor)) armhlp_unload()
{
    //LOGD("LIBRARY UNLOADED FROM PID %d.", getpid());
}

