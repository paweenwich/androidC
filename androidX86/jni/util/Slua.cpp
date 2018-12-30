/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Slua.cpp
 * Author: Administrator
 * 
 * Created on December 30, 2018, 4:01 PM
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
#include <../util/util.hpp>
#include "Slua.h"

// NEED libslus.so  RagnarokM or in externalLibs
#define  LOG_TAG    "Hook"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define SLUAAPI(n) \
{\
    unsigned int *ptr = (unsigned int *)&this->n;\
    *ptr = UINT(dlsym(handle,#n));\
    if(*ptr == 0){\
        LOGE("ERROR %s not found\n",#n);\
                return false;\
    }\
}


Slua::Slua() {
}

Slua::~Slua() {
}

bool Slua::Init(char *name)
{
    if(name == NULL){
        name = "/data/local/tmp/libslua.so";
    }
    void *handle = dlopen(name, RTLD_NOW); 
    if(handle==NULL){
        lastError = std::string(dlerror());
        LOGE("Slua::Init Fail %s",lastError.c_str());
        return false;
    }    
    SLUAAPI(luaL_newstate);
    SLUAAPI(luaL_loadfilex);
    SLUAAPI(luaL_openlibs);
    SLUAAPI(luaL_tolstring);
    SLUAAPI(lua_gettop);
    SLUAAPI(lua_pcallk);
    SLUAAPI(luaL_loadbufferx);
    return true;
}

bool Slua::DoFile(lua_State *L,char *fileName)
{
    int ret = luaL_loadfilex(L,"/data/local/tmp/script/rom.lua",NULL);
    if(ret !=0){
        lastError = std::string(luaL_tolstring(L, -1,NULL));
        lua_gettop(L);      // get message from stack        
        LOGE("Slua::DoFile Fail load %s",lastError.c_str());
        return false;
    }else{
        ret = lua_pcallk(L,0,0,0,NULL,NULL);
        if(ret !=0){
            lastError = std::string(luaL_tolstring(L, -1,NULL));
            lua_gettop(L);      // get message from stack
            LOGE("Slua::DoFile exec Fail %s",lastError.c_str());
            return false;
        }else{
            lastError = "";
            return true;
        }
    }
    
}

/*
#define lua_State void                 
                MONO_API(handle,lua_State *,luaL_newstate,(void));
                MONO_API(handle,int,luaL_loadfilex,(lua_State *, char *, char *));
                MONO_API(handle,void,luaL_openlibs,(lua_State *));
                MONO_API(handle,char *,luaL_tolstring,(lua_State *, int ,int *));
                //MONO_API(handle,void,lua_pop,(lua_State *, int ));
                MONO_API(handle,void,lua_gettop,(lua_State *));
                MONO_API(handle,int, lua_pcallk,(lua_State *L,int nargs,int nresults,int msgh,void* ctx,void* k));
                lua_State *lState = luaL_newstate();
                printf("%08X\n",UINT(lState));
                luaL_openlibs(lState);
                int ret = luaL_loadfilex(lState,"/data/local/tmp/script/rom.lua",NULL);
                if(ret !=0){
                    printf("error %08X\n",ret);                
                    char tmp[1024]={0};
                    sprintf(tmp, "%s", luaL_tolstring(lState, -1,NULL));
                    lua_gettop(lState);  
                    printf("%s",tmp);
                }else{
                    ret = lua_pcallk(lState,0,-1,0,NULL,NULL);
                    printf("%08X\n",ret);                
                }
                exit(0);
 
 */

