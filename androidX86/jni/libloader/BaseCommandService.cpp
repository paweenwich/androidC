/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseCommandService.cpp
 * Author: Administrator
 * 
 * Created on December 5, 2018, 10:42 AM
 */
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
#include <iterator>
#include <sstream>
#include <dirent.h>
#include <pthread.h>

#include "../util/util.hpp"
#include "../util/PtraceUtil.hpp"
#include "../util/logger.h"
#include "../util/payload.hpp"
#include "../util/elf_help.h"
#include "../util/ProcessScanner.hpp"

#include "../util/SimpleTCPServer.hpp"

#define  LOG_TAG    "BaseCommandService"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#include "BaseCommandService.h"

BaseCommandService::BaseCommandService() {
}

BaseCommandService::BaseCommandService(const BaseCommandService& orig) {
}

BaseCommandService::~BaseCommandService() {
}

void BaseCommandService::help(SimpleSocket &sock)
{
    sock.SendLine((char *)"Version 1.0");
    sock.SendLine((char *)BSC_HELP);
    sock.SendLine((char *)BSC_DUMPMEM);
    sock.SendLine((char *)BSC_DUMPALL);
}

void BaseCommandService::dumpmem(SimpleSocket &sock,std::string sstart,std::string ssize,std::string sfileName)
{
    int memAddr = ParseAddress((char *)sstart.c_str());
    int memSize = ParseAddress((char *)ssize.c_str());
    std::string fileName = sfileName;
    sock.printf("%s %08X %08X %s\n",BSC_DUMPMEM,memAddr,memSize,fileName.c_str());
    bool ret = DumpMemory(memAddr,memSize,(char *)fileName.c_str());
    if(ret){
	sock.printf("Success\n");
    }else{
	sock.printf("Fail\n");
    }
}

void BaseCommandService::dump(SimpleSocket &sock,std::string mode)
{
    ProcessScanner pscan;
    int pid = getpid();
    pscan.open(pid);
    std::vector<ProcMapData> ret;
    if((mode=="")||(mode=="A"))ret = pscan.getAll();
    if(mode=="H")ret = pscan.getHeap();
    if(mode=="W")ret = pscan.getWriteable();
    if(mode=="N")ret = pscan.getNotExecute();
    if(ret.size() == 0){
	sock.printf("Fail mode=[%s]\n",(char *)mode.c_str());
	return;
    }
    for(int i=0;i<ret.size();i++){
	ProcMapData *p = &ret[i];
	char dumpDir[128];
	char dumpFileName[128];
	sprintf(dumpDir,"/data/local/tmp/%d",pid);
	mkdir(dumpDir,0777);
	sprintf(dumpFileName,"/data/local/tmp/%d/%08X-%08X.dump",pid,p->startAddr,p->endAddr);
	bool ret = DumpMemory(p->startAddr,p->size(),(char *)dumpFileName);
	if(!ret){
	    sock.printf("Fail [%s]\n",dumpFileName);
	}else{
	    sock.printf("Success [%s]\n",dumpFileName);
	}
    }
}

void BaseCommandService::doLine(SimpleSocket &sock,char *data){
    LOGD("doLine %s",data);
    std::string text = data;
    std::istringstream iss(text);
    std::vector<std::string> vTokens((std::istream_iterator<std::string>(iss)),std::istream_iterator<std::string>());
    int numTok = vTokens.size();
    LOGD("tokensize=%d",numTok);
    if(numTok<=0){
        return;
    }
    for(int i=0;i<numTok;i++){
        LOGD("[%s]",vTokens[i].c_str());
    }
    std::string cmd = vTokens[0];
    if(cmd == BSC_DUMPMEM){
        if(numTok !=4){
            sock.printf("%s memaddr size filename\n",BSC_DUMPMEM);
            return;
        }
	dumpmem(sock,vTokens[1],vTokens[2],vTokens[3]);
        return;
    }
    if(cmd == BSC_DUMPALL){
	if(numTok < 2){
	    dump(sock,"A");
	}else{
	    dump(sock,vTokens[1]);
	}
	return;
    }
    help(sock);
    return;
    
}


