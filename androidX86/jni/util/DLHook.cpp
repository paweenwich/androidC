/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLHook.cpp
 * Author: Administrator
 * 
 * Created on December 23, 2018, 12:55 PM
 */



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
#include <cctype>
#include <dirent.h>
#include <pthread.h>
#include <stdint.h>
#include <elf.h>

#include <../util/util.hpp>
#include <../util/AndroidLogger.h>

#include "DLHook.h"

#define  LOG_TAG    "DLHook"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

std::vector<HookData> DLHook::vHookData;


void* (*original_dlsym)(void *handle, const char *symbol);
void* hooked_dlsym(void *handle, const char *symbol)
{
    LOGD("hooked_dlsym(%08X,%s)",UINT(handle),symbol);
    if(original_dlsym!=NULL){
	return original_dlsym(handle,symbol);
    }else{
	LOGD("WARNING: original_dlsym not set");
	return NULL;
    }
    
}

void* (*original_dlopen)(const char *filename, int flag);
void* hooked_dlopen(const char *filename, int flag)
{
    LOGD("hooked_dlopen(%s,%08X)",filename,flag);  
    if(original_dlopen!=NULL){
	return original_dlopen(filename,flag);
    }else{
	LOGD("WARNING: original_dlopen not set");
	return NULL;
    }
}

std::vector<HookData> DLHook::GetDLHookData()
{
    std::vector<HookData> ret;
    {
	HookData h = { "dlsym", (void *)hooked_dlsym, (unsigned int *)&original_dlsym}; 
        ret.push_back(h);
    }
    {
	HookData h = { "dlopen", (void *)hooked_dlopen, (unsigned int *)&original_dlopen}; 
        ret.push_back(h);
    }
    
    return ret;
}
