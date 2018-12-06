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
        int memAddr = ParseAddress((char *)vTokens[1].c_str());
        int memSize = ParseAddress((char *)vTokens[2].c_str());
        std::string fileName = vTokens[3];
        sock.printf("%s %08X %08X %s\n",BSC_DUMPMEM,memAddr,memSize,fileName.c_str());
        bool ret = DumpMemory(memAddr,memSize,(char *)fileName.c_str());
        if(ret){
            sock.printf("Success\n");
        }else{
            sock.printf("Fail\n");
        }
        return;
    }
    help(sock);
    return;
    
}


