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
#include <algorithm>
#include <cctype>
#include <dirent.h>
#include <pthread.h>
#include <stdint.h>
#include <elf.h>

#include <../util/util.hpp>
#include <../util/AndroidLogger.h>


#include "DLHook.h"
#include "elf_hook.h"
#include "Slua.h"

// Unity mono compatible 
//https://github.com/0xd4d/dnSpy-Unity-mono

#define  LOG_TAG    "Hook"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define	MonoAssembly	void
#define MonoImage   void
#define MonoImageOpenStatus void
#define mono_bool bool
#define gboolean bool
#define guint32 unsigned int
#define MonoAssemblyName char*
#define MonoDebugFormat int
#define MonoDomain void
#define MonoObject void
#define MonoMethod void
#define MonoArray void

//#define lua_State void

#define HOOKFUNCORG(r,n,p)  r (* original_ ## n) p
#define HOOKFUNCDEF(r,n,p)  r hooked_ ## n p
#define ORG(n)	original_ ## n

#define HOOKFUNCPROT(r,n,p) \
    HOOKFUNCORG(r,n,p);	\
    HOOKFUNCDEF(r,n,p)

#define HOOKFUNC(n) \
	if(strcmp(#n,symbol)==0){\
	    LOGD("hooked it");\
	    unsigned int *ptr = (unsigned int *)&original_ ## n;\
	    *ptr = UINT(dlsym_ret);\
	    dlsym_ret = (void *) hooked_ ## n;\
	    return dlsym_ret;\
	}

HOOKFUNCORG(char *,mono_method_get_name,(MonoMethod *));

/*
 * MONO
 */
HOOKFUNCPROT(MonoAssembly*,mono_assembly_load_from,(MonoImage *image, char *fname,MonoImageOpenStatus *status))
{
    if(ORG(mono_assembly_load_from)!=NULL){
	LOGD("hooked mono_assembly_load_from %08X %s %08X",UINT(image),fname,UINT(status));
	MonoAssembly* ret = ORG(mono_assembly_load_from)(image,fname,status);
	return ret;
    }else{
	LOGD("WARNING: original mono_assembly_load_from not set");
	return NULL;
    }
}

HOOKFUNCPROT(MonoAssembly*,mono_assembly_load_from_full,(MonoImage *image, char *fname,MonoImageOpenStatus *status,mono_bool refonly))
{
    if(ORG(mono_assembly_load_from_full)!=NULL){
	LOGD("hooked mono_assembly_load_from_full %08X %s %08X %d",UINT(image),fname,UINT(status),refonly);
	MonoAssembly* ret = ORG(mono_assembly_load_from_full)(image,fname,status,refonly);
	return ret;
    }else{
	LOGD("WARNING: original mono_assembly_load_from_full not set");
	return NULL;
    }
    
}

HOOKFUNCPROT(MonoAssembly *,mono_assembly_open,(const char *filename,MonoImageOpenStatus *status))
{
    if(ORG(mono_assembly_open)!=NULL){
	LOGD("hooked mono_assembly_open %s %08X",filename,UINT(status));
	MonoAssembly* ret = ORG(mono_assembly_open)(filename,status);
	return ret;
    }else{
	LOGD("WARNING: original mono_assembly_open not set");
	return NULL;
    }
}

HOOKFUNCPROT(MonoImage *, mono_image_open_from_data_full, (char *data, guint32 data_len, gboolean need_copy,MonoImageOpenStatus *status, gboolean refonly))
{
    if(ORG(mono_image_open_from_data_full)!=NULL){
	LOGD("hooked mono_image_open_from_data_full %08X %d %d %08X %d",UINT(data),data_len,need_copy,UINT(status),refonly);
	MonoImage* ret = ORG(mono_image_open_from_data_full)(data,data_len,need_copy,status,refonly);
	return ret;
    }else{
	LOGD("WARNING: original mono_image_open_from_data_full not set");
	return NULL;
    }
    
}

HOOKFUNCPROT(MonoImage *,mono_image_open_from_data_with_name, (char *data, guint32 data_len, gboolean need_copy,MonoImageOpenStatus *status, gboolean refonly, char *name))
{
    if(ORG(mono_image_open_from_data_with_name)!=NULL){
	LOGD("hooked mono_image_open_from_data_with_name %08X %d %d %08X %d %s",UINT(data),data_len,need_copy,UINT(status),refonly,name);
	MonoImage* ret = ORG(mono_image_open_from_data_with_name)(data,data_len,need_copy,status,refonly,name);
	return ret;
    }else{
	LOGD("WARNING: original mono_image_open_from_data_with_name not set");
	return NULL;
    }
    
}

HOOKFUNCPROT(gboolean, mono_is_debugger_attached, (void))
{
    if(ORG(mono_is_debugger_attached)!=NULL){
	LOGD("hooked mono_is_debugger_attached()");
	gboolean ret = ORG(mono_is_debugger_attached)();
	return ret;
    }else{
	LOGD("WARNING: original mono_is_debugger_attached not set");
	return 0;
    }
}

HOOKFUNCPROT(void,mono_debug_init, (MonoDebugFormat format))
{
    if(ORG(mono_debug_init)!=NULL){
	LOGD("hooked mono_debug_init %d",format);
	ORG(mono_debug_init)(format);
    }else{
	LOGD("WARNING: original mono_debug_init not set");
    }
}

HOOKFUNCPROT(void,mono_debug_open_image_from_memory,(MonoImage *image, char *raw_contents, int size))
{
    if(ORG(mono_debug_open_image_from_memory)!=NULL){
	LOGD("hooked mono_debug_open_image_from_memory %08X %08X %d",UINT(image),UINT(raw_contents),size);
	ORG(mono_debug_open_image_from_memory)(image,raw_contents,size);
    }else{
	LOGD("WARNING: mono_debug_open_image_from_memory not set");
    }
}

HOOKFUNCPROT(MonoDomain *,mono_domain_get,(void))
{
    if(ORG(mono_domain_get)!=NULL){
	LOGD("hooked mono_domain_get()");
	MonoDomain *ret = ORG(mono_domain_get)();
	return ret;
    }else{
	LOGD("WARNING: original mono_domain_get not set");
	return NULL;
    }

}


HOOKFUNCPROT(MonoDomain *,mono_get_root_domain,(void))
{
    if(ORG(mono_get_root_domain)!=NULL){
	LOGD("hooked mono_get_root_domain()");
	MonoDomain *ret = ORG(mono_get_root_domain)();
	return ret;
    }else{
	LOGD("WARNING: original mono_get_root_domain not set");
	return NULL;
    }
}

HOOKFUNCPROT(void,mono_runtime_object_init,(MonoObject *this_obj))
{
    if(ORG(mono_runtime_object_init)!=NULL){
	LOGD("hooked mono_runtime_object_init %08X",UINT(this_obj));
	ORG(mono_runtime_object_init)(this_obj);
    }else{
	LOGD("WARNING: original mono_runtime_object_init not set");
    }
}

HOOKFUNCPROT(MonoObject*, mono_runtime_invoke,(MonoMethod *method, void *obj, void **params, MonoObject **exc))
{
    if(ORG(mono_runtime_invoke)!=NULL){
        if(ORG(mono_method_get_name)!=NULL){
            LOGD("hooked mono_runtime_invoke method=%s obj=%08X param=%08X exec=%08X",ORG(mono_method_get_name)(method),UINT(obj),UINT(params),UINT(exc));
        }else{
            LOGD("hooked mono_runtime_invoke method=%08X obj=%08X param=%08X exec=%08X",UINT(method),UINT(obj),UINT(params),UINT(exc));
        }
	MonoObject *ret = ORG(mono_runtime_invoke)(method,obj,params,exc);
	return ret;
    }else{
	LOGD("WARNING: original mono_runtime_invoke not set");
	return NULL;
    }
}

HOOKFUNCPROT(MonoObject*, mono_runtime_invoke_array, (MonoMethod *method, void *obj, MonoArray *params,MonoObject **exc))
{
    if(ORG(mono_runtime_invoke_array)!=NULL){
	LOGD("hooked mono_runtime_invoke_array %08X %08X %08X %08X",UINT(method),UINT(obj),UINT(params),UINT(exc));
	MonoObject *ret = ORG(mono_runtime_invoke_array)(method,obj,params,exc);
	return ret;
    }else{
	LOGD("WARNING: original mono_runtime_invoke_array not set");
	return NULL;
    }
    
}

HOOKFUNCPROT(int, mono_runtime_exec_main, (MonoMethod *method, MonoArray *args, MonoObject **exc))
{
    if(ORG(mono_runtime_exec_main)!=NULL){
	LOGD("hooked mono_runtime_exec_main %08X %08X %08X",UINT(method),UINT(args),UINT(exc));
	int ret = ORG(mono_runtime_exec_main)(method,args,exc);
	return ret;
    }else{
	LOGD("WARNING: original mono_runtime_exec_main not set");
	return 0;
    }
    
}

/*
 * Lua
 * http://pgl.yoyo.org/luai/i/luaL_ref
 * https://www.lua.org/manual/5.3/manual.html#luaL_loadbufferx
*/
HOOKFUNCPROT(lua_State *,luaL_newstate, (void))
{
    if(ORG(luaL_newstate)!=NULL){
	LOGD("hooked luaL_newstate()");
	lua_State *ret = ORG(luaL_newstate)();
	return ret;
    }else{
	LOGD("WARNING: original luaL_newstate not set");
	return NULL;
    }
}

HOOKFUNCPROT(void,luaL_openlibs,(lua_State *L))
{
   if(ORG(luaL_openlibs)!=NULL){
	LOGD("hooked luaL_openlibs %08X",UINT(L));
	ORG(luaL_openlibs)(L);
    }else{
	LOGD("WARNING: original luaL_openlibs not set");
    }    
}

HOOKFUNCPROT(int, luaL_ref, (lua_State *L, int t))
{
    if(ORG(luaL_ref)!=NULL){
	LOGD("hooked luaL_ref %08X %d",UINT(L),t);
	int ret = ORG(luaL_ref)(L,t);
	return ret;
    }else{
	LOGD("WARNING: original luaL_ref not set");
	return 0;
    }
}

HOOKFUNCPROT(void,luaL_unref,(lua_State *L, int t, int ref))
{
    if(ORG(luaL_unref)!=NULL){
	LOGD("hooked luaL_unref %08X %d %d",UINT(L),t,ref);
	ORG(luaL_unref)(L,t,ref);
    }else{
	LOGD("WARNING: original luaL_unref not set");
    }    
    
}

HOOKFUNCPROT(int, luaL_loadstring, (lua_State *L, char *s))
{
    if(ORG(luaL_loadstring)!=NULL){
	LOGD("hooked luaL_loadstring %08X %s",UINT(L),s);
	int ret = ORG(luaL_loadstring)(L,s);
	return ret;
    }else{
	LOGD("WARNING: original luaL_loadstring not set");
	return 0;
    }
    
}
/*
HOOKFUNCPROT(int, luaL_loadbufferx, (lua_State *L, char *buff,size_t sz, char *name, char *mode))
{
    if(ORG(luaL_loadbufferx)!=NULL){
	LOGD("hooked luaL_loadbufferx %08X %08X %d %s %s",UINT(L),UINT(buff),sz,name,mode);
	int ret = ORG(luaL_loadbufferx)(L,buff,sz,name,mode);
	return ret;
    }else{
	LOGD("WARNING: original luaL_loadbufferx not set");
	return 0;
    }
    
}
*/ 

HOOKFUNCPROT(int, luaL_loadbufferx, (lua_State *L, char *buff,size_t sz, char *name, char *mode))
{
    if(ORG(luaL_loadbufferx)!=NULL){
	LOGD("hooked luaL_loadbufferx %08X %08X %d %s %s",UINT(L),UINT(buff),sz,name,mode);
        char cleanName[128];
        if(strcmp(name,"temp buffer")==0){
            sprintf(cleanName,"temp_buffer_%08X",sz);
        }else{
            strcpy(cleanName,name);
            for(int i=0;i<strlen(cleanName);i++){
                if(cleanName[i] == '@') {cleanName[i] = 'A';continue;}
                if(cleanName[i] == '/') {cleanName[i] = '_';continue;}
                if(cleanName[i] == ' ') {cleanName[i] = '_';continue;}
            }
        }
        // check @Script/Refactory/Game/GameLauncher
        // load my script at this point
        if(strcmp(name,"@Script/Refactory/Game/GameLauncher")==0){
            Slua slua;
            if(slua.Init("libslua.so")){
                if(slua.DoFile(L,"/data/local/tmp/script/rom.lua")){
                    LOGD("slua.DoFile rom.lua success");
                }else{
                    LOGD("slua.DoFile rom.lua fail");
                }
            }else{
                LOGD("slua.Init rom.lua fail");
            }
        }
        char outFileName[256];
        sprintf(outFileName,"/data/local/tmp/loadbufferx/%s",cleanName);
        if(DumpMemory(UINT(buff),sz,outFileName)){
            LOGD("Save %s success",outFileName);
        }else{
            LOGD("Save %s fail",outFileName);
        }

        char customFileName[256];
        sprintf(customFileName,"/data/local/tmp/script/%s.lua",cleanName);        
        //LOGD("[%s]",customFileName);
        if(isFileExist(customFileName)){
            LOGD("Custom file found %s use it",customFileName);
            std::vector<unsigned char> buffer = ReadFile(customFileName);
            int ret = ORG(luaL_loadbufferx)(L,(char *)&buffer[0],buffer.size(),name,mode);
            return ret;
        }else{
            int ret = ORG(luaL_loadbufferx)(L,buff,sz,name,mode);
            return ret;
        }
    }else{
	LOGD("WARNING: original luaL_loadbufferx not set");
	return 0;
    }
    
}

HOOKFUNCPROT(lua_CFunction, lua_atpanic, (lua_State *L, lua_CFunction panicf))
{
    if(ORG(lua_atpanic)!=NULL){
	LOGD("hooked lua_atpanic %08X %08X",UINT(L),UINT(panicf));
	lua_CFunction ret = ORG(lua_atpanic)(L,panicf);
	return ret;
    }else{
	LOGD("WARNING: original lua_atpanic not set");
	return NULL;
    }
    
}

HOOKFUNCPROT(int, lua_pcallk, (lua_State *L,int nargs,int nresults,int msgh,lua_KContext ctx,lua_KFunction k))
{
    if(ORG(lua_pcallk)!=NULL){
	LOGD("hooked lua_pcallk %08X %d %d %d %08X %08X",UINT(L),nargs,nresults,msgh,UINT(ctx),UINT(k));
	int ret = ORG(lua_pcallk)(L,nargs,nresults,msgh,ctx,k);
	return ret;
    }else{
	LOGD("WARNING: original lua_pcallk not set");
	return 0;
    }
}


/*
 LD
 */
HOOKFUNCPROT(void*,dlsym,(void *handle, const char *symbol))
{
    //LOGD("hooked_dlsym(%08X,%s)",UINT(handle),symbol);
    if(original_dlsym!=NULL){
	void *dlsym_ret = original_dlsym(handle,symbol);
	// ignore all not found 
	if(UINT(dlsym_ret) == 0){
	    return dlsym_ret;
	}
        if(ORG(mono_method_get_name)==NULL){
            if(strstr(symbol,"mono_")!=NULL){
                unsigned int *ptr = (unsigned int *)&ORG(mono_method_get_name);
                *ptr = UINT(original_dlsym(handle,"mono_method_get_name"));
                LOGD("hooked_dlsym set mono_method_get_name");
            }
        }

	LOGD("hooked_dlsym(%08X,%s) return %08X",UINT(handle),symbol,UINT(dlsym_ret));
	//HOOKFUNC(mono_assembly_load_from);
	//HOOKFUNC(mono_assembly_load_from_full);
	//HOOKFUNC(mono_assembly_open);
	//HOOKFUNC(mono_image_open_from_data_full);
	//HOOKFUNC(mono_image_open_from_data_with_name);
	//HOOKFUNC(mono_debug_init);
	//HOOKFUNC(mono_debug_open_image_from_memory);
	//HOOKFUNC(mono_is_debugger_attached);
	//HOOKFUNC(mono_domain_get);
	//HOOKFUNC(mono_get_root_domain);
	//HOOKFUNC(mono_runtime_object_init);
	//HOOKFUNC(mono_runtime_invoke);
	//HOOKFUNC(mono_runtime_invoke_array);
	//HOOKFUNC(mono_runtime_exec_main);
	//HOOKFUNC(luaL_newstate);
	//HOOKFUNC(luaL_openlibs);
	//HOOKFUNC(luaL_ref);
	//HOOKFUNC(luaL_unref);
	HOOKFUNC(luaL_loadstring);
	HOOKFUNC(luaL_loadbufferx);
	//HOOKFUNC(lua_atpanic);	
        //HOOKFUNC(lua_pcallk);
	return dlsym_ret;
    }else{
	LOGD("WARNING: original_dlsym not set");
	return NULL;
    }
    
}

//void* (*original_dlopen)(char *filename, int flag);
//void* hooked_dlopen(char *filename, int flag)
HOOKFUNCPROT(void*,dlopen,(char *filename, int flag))
{
    //LOGD("hooked_dlopen(%s,%08X)",filename,flag);  
    if(original_dlopen!=NULL){
	void *dlopen_ret = original_dlopen(filename,flag);
	//LOGD("hooked_dlopen wsize=%d %d",DLHook::vWatchlibrary.size(),DLHook::vHookData.size());    	
	LOGD("hooked_dlopen(%s,%08X) return %08X",filename,flag,UINT(dlopen_ret)); 
	// check if is in my watch list
	if(filename!=NULL){
	    if(DLHook::IsWatched(filename)){
		LOGD("IsWatched");
		DLHook::ReHook(filename);
	    }
	}
	return dlopen_ret;
    }else{
	LOGD("WARNING: original_dlopen not set");
	return NULL;
    }
}


#define	ADDHOOK(n)  \
    {\
	HookData h = { #n, (void *)hooked_ ## n, (unsigned int *)&original_ ## n}; \
        ret.push_back(h);\
    }

std::vector<HookData> DLHook::GetDLHookData()
{
    std::vector<HookData> ret;
    ADDHOOK(dlsym);
    ADDHOOK(dlopen);
    return ret;
}

std::vector<std::string> DLHook::GetWatchlibrary()
{
    std::vector<std::string> ret;
    ret.push_back(std::string("/libunity.so"));
    return ret;
}

bool DLHook::IsWatched(char *name)
{
    //LOGD("IsWatched %s wsize=%d",name,vWatchlibrary.size());
    std::vector<std::string> vWatchlibrary = GetWatchlibrary();
    for(int i=0;i<vWatchlibrary.size();i++){
	if(strstr(name,vWatchlibrary[i].c_str())!=NULL){
	    return true;
	}
    }
    return false;
}


void DLHook::ReHook(char *libname)
{
    LOGD("ReHook %s",libname);
    ELFHook elfHook;
    if(elfHook.Open(libname)){
	printf("Open %s success\n",libname);	 
	static std::vector<HookData> vHookData = GetDLHookData();
	for(int j=0;j<vHookData.size();j++){
	    unsigned int originalAddr=0;
	    if(elfHook.Hook(vHookData[j].name, vHookData[j].hookAddr,&originalAddr)){
		printf("Hook [%s] [%s] original1=%08X\n",libname,vHookData[j].name,originalAddr); 		
		*(vHookData[j].originalAddr) = originalAddr;
	    }
	}
    }
}

