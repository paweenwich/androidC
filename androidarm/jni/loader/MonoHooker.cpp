/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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
#include <fstream>
#include <pthread.h>
#include "../util/logger.h"
#include "../util/payload.hpp"
#include "MonoHooker.hpp"

extern Logger *logger;
void FindLibraryPath(const char* libname,char *path,unsigned int *baseAddr,unsigned int *libSize);

#define  LOGD(...)  logger->printf(__VA_ARGS__)
#define  LOGE(...)  logger->printf(__VA_ARGS__)
#define	 LOGHEX(x,y)	logger->logHex((x),(y));

mono_class_get_name_t mono_class_get_name;
mono_class_get_namespace_t mono_class_get_namespace;
mono_method_get_name_t mono_method_get_name;
mono_method_get_class_t mono_method_get_class;
mono_domain_get_t mono_domain_get;
mono_image_open_from_data_t mono_image_open_from_data;
mono_domain_assembly_open_t mono_domain_assembly_open;
mono_get_root_domain_t mono_get_root_domain;
mono_thread_attach_t mono_thread_attach;
mono_assembly_load_from_full_t mono_assembly_load_from_full;
mono_assembly_get_image_t mono_assembly_get_image;
mono_class_from_name_t mono_class_from_name;
mono_class_get_method_from_name_t mono_class_get_method_from_name;
mono_runtime_invoke_t mono_runtime_invoke;
mono_assembly_foreach_t mono_assembly_foreach;
mono_assembly_get_name_t mono_assembly_get_name;
mono_stringify_assembly_name_t mono_stringify_assembly_name;
mono_image_get_table_rows_t mono_image_get_table_rows;
mono_class_get_t mono_class_get;
mono_class_get_fields_t mono_class_get_fields;
mono_field_get_name_t mono_field_get_name;
mono_field_static_set_value_t mono_field_static_set_value;
mono_field_static_get_value_t mono_field_static_get_value;
mono_class_vtable_t mono_class_vtable;
mono_string_new_t mono_string_new;
mono_runtime_class_init_t mono_runtime_class_init;
mono_string_to_utf8_t mono_string_to_utf8;
mono_class_get_field_from_name_t mono_class_get_field_from_name;
mono_property_get_value_t mono_property_get_value;
mono_property_set_value_t mono_property_set_value;
mono_class_get_property_from_name_t mono_class_get_property_from_name;
mono_class_get_parent_t mono_class_get_parent;
mono_field_get_value_t mono_field_get_value;
mono_field_set_value_t mono_field_set_value;



unsigned int libmonoHandle  =0;
unsigned int monoTextSize;
unsigned int monoBaseAddr;


#define	MONO_SET_FUNC( x )    (x)=( x ##_t )dlsym((void *)libmonoHandle,#x);

unsigned int MonoLoad()
{
    //static unsigned int handle = 0;
    if(libmonoHandle!=0){
	return libmonoHandle;
    }
    
    char monoLibraryFile[1024] = {0};
    FindLibraryPath("libmono.so",&monoLibraryFile[0],&monoBaseAddr,&monoTextSize);
    if(strlen(monoLibraryFile)==0){
        LOGD("MonoLoad: libmono.so not found\n");
        return 0;
    }
    LOGD("MonoLoad: found libmono.so [%s]\n",monoLibraryFile);
    libmonoHandle = (unsigned int)dlopen(monoLibraryFile,0);
    LOGD("libMono Handle=%08X",libmonoHandle);
    // function
    MONO_SET_FUNC(mono_class_get_name);	    
    MONO_SET_FUNC(mono_class_get_namespace);
    MONO_SET_FUNC(mono_method_get_name);
    MONO_SET_FUNC(mono_method_get_class);
    MONO_SET_FUNC(mono_domain_get);
    MONO_SET_FUNC(mono_image_open_from_data);
    MONO_SET_FUNC(mono_domain_assembly_open);
    MONO_SET_FUNC(mono_get_root_domain);
    MONO_SET_FUNC(mono_thread_attach);
    MONO_SET_FUNC(mono_assembly_load_from_full);
    MONO_SET_FUNC(mono_assembly_get_image);
    MONO_SET_FUNC(mono_class_from_name);
    MONO_SET_FUNC(mono_class_get_method_from_name);
    MONO_SET_FUNC(mono_runtime_invoke);
    MONO_SET_FUNC(mono_assembly_foreach);
    MONO_SET_FUNC(mono_assembly_get_name);
    MONO_SET_FUNC(mono_stringify_assembly_name);
    MONO_SET_FUNC(mono_image_get_table_rows);
    MONO_SET_FUNC(mono_class_get);
    MONO_SET_FUNC(mono_class_get_fields);
    MONO_SET_FUNC(mono_field_get_name);
    MONO_SET_FUNC(mono_field_static_set_value);
    MONO_SET_FUNC(mono_field_static_get_value);
    MONO_SET_FUNC(mono_class_vtable);
    MONO_SET_FUNC(mono_string_new);
    MONO_SET_FUNC(mono_runtime_class_init);
    MONO_SET_FUNC(mono_string_to_utf8);
    MONO_SET_FUNC(mono_class_get_field_from_name);
    MONO_SET_FUNC(mono_property_get_value);
    MONO_SET_FUNC(mono_property_set_value);
    MONO_SET_FUNC(mono_class_get_property_from_name);
    MONO_SET_FUNC(mono_class_get_parent);
    MONO_SET_FUNC(mono_field_get_value);
    MONO_SET_FUNC(mono_field_set_value);
    
    return libmonoHandle;
}

MonoAssembly* MonoLoadAssembly(const char* fileName)
{
    void *handle = (void *)MonoLoad();
    if((unsigned int)handle == 0){
	LOGD("Cannot load libmono.so");
	LOGD("ERROR: %s",strerror(errno));
	return 0;
    }
    MonoDomain* rootdomain = mono_get_root_domain(); 
    mono_thread_attach(rootdomain);
    //loading file
    std::vector<unsigned char> buffer = _ReadFile(fileName);
    LOGD("MonoLoadAssembly %s size=%d",fileName,buffer.size());
    LOGD("%02X %02X %02X %02X %02X",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
    
    int status = 0;
    MonoImage* raw_image = mono_image_open_from_data(&buffer[0],buffer.size(),1,&status);
    LOGD("raw_image %08X status=%08X",(unsigned int)raw_image,status);
    
    MonoAssembly *assembly = mono_assembly_load_from_full(raw_image,0,&status,0);
    LOGD("assembly %08X",(unsigned int) assembly);
    return assembly;
}



unsigned char* BackupTargetAddress(unsigned int targetAddr)
{
    int cmd_size = GetBranchToAddressCommandSize();
    unsigned char *ret = (unsigned char *)malloc(cmd_size);
    memcpy(ret,(unsigned char*)targetAddr,cmd_size);
    return ret;
}

void InjectJumpCode(unsigned int targetAddr,int jumpToAddr)
{
    unsigned char *branchCommand = CreateBranchToAddressCommand(jumpToAddr);
    int cmd_size = GetBranchToAddressCommandSize();
    LOGD("Before injectCode %08X",targetAddr);
    logger->logHex((unsigned char *)targetAddr,cmd_size);
    memcpy((unsigned char*)targetAddr,branchCommand,cmd_size);
    LOGD("After injectCode %08X",targetAddr);
    logger->logHex((unsigned char *)targetAddr,cmd_size);
}

unsigned int MonoHook(char *monoFunctionName,unsigned int monoHookFuncAddr)
{
    unsigned int handle = MonoLoad();    
    if(handle == 0){
	LOGD("Cannot load libmono.so");
	LOGD("ERROR: %s",strerror(errno));
	return 0;
    }
    unsigned int addr = (unsigned int)dlsym((void *)handle,monoFunctionName);
    if(addr!=0){
	
	unsigned int newHookFunctionSpaceAddr = AllocateExecutableMemory(4096);
	LOGD("%s newHookFunctionSpaceAddr=%08X",monoFunctionName,newHookFunctionSpaceAddr);
	LOGD("mprotect %08X %08X",monoBaseAddr,monoTextSize);
	
	if(mprotect((void *)monoBaseAddr, monoTextSize, PROT_READ | PROT_WRITE | PROT_EXEC)){
	    LOGE("mprotect error %s\n",strerror(errno));
	    return 0;
	}
	
	LOGD("addr = %08X",addr);
	unsigned char *backupCode = BackupTargetAddress(addr);//,newHookFunctionSpaceAddr+CODE_OFFSET);

        unsigned char asmCode[] = {
	    0x0F,0xC0,0xA0,0xE1,    //mov r12,pc         -- copy pc to r3 (r3 => B20 due to prefetch)
	    0x88,0xC0,0x4C,0xE2,    //sub r12,128 + 8    -- point r3 to payload

	    0xFF,0x1F,0x2D,0xE9,    //push {r0-r12}      -- save r0-r8
	    0x04,0xE0,0x2D,0xE5,    //push {lr}         -- save lr   
	    
	    // try call my hookFunc
	    0x00,0x40,0x9C,0xE5,    //ldr r4,[r12]       -- load hookFunc addr
	    0x34,0xFF,0x2F,0xE1,    //blx r4            -- call hookFunc
	    
	    0x04,0xE0,0x9D,0xE4,    //pop  {lr}         -- pop lr
	    0xFF,0x1F,0xBD,0xE8,    //pop  {r0-r12}      -- pop r0-r8
	    
	    //check 

	    //jump to newFreeSpaceCodeAddr which loader create for us
	    //0x68,0x20,0x93,0xE5,    //ldr r2,[r3,64 + (10*4)]    -- addr of newFreeSpaceCodeAddr
	    //0x12,0xFF,0x2F,0xE1,    //bx r2             -- jump to newFreeSpaceCodeAddr

	    //0x1E,0xFF,0x2F,0xE1,    //bx lr

	    0x14,0x14,0x14,0x14,    //backup instruction[3]
	    0x00,0x00,0x00,0x00,
	    0x00,0x00,0x00,0x00,
	    // hope fully above 3 instruction not using r12
	    0x00,0xC0,0x9F,0xE5,    //LDR r12,[pc,0]    ;load 12 from jump addr
	    0x1C,0xFF,0x2F,0xE1,    //BX	r12
	    0x11,0x22,0x33,0x44,    //jump_addr    
	};
	unsigned char backup_pattern[] = {0x14,0x14,0x14,0x14};
	int backupOffset = MemoryFind(asmCode,sizeof(asmCode),backup_pattern,sizeof(backup_pattern));
	*(unsigned int *)((unsigned char*)asmCode + sizeof(asmCode) - 4) = addr+12;
	memcpy((void *)(asmCode + backupOffset),backupCode,12);
	
	LOGD("asm code");
	LOGHEX(asmCode,sizeof(asmCode));
	
	struct _HookFuncPayloadData *pHookFuncPayloadData = (struct _HookFuncPayloadData *)newHookFunctionSpaceAddr;
	pHookFuncPayloadData->hookFunc = (unsigned int)monoHookFuncAddr;
	pHookFuncPayloadData->oldFuncAddr = (unsigned int)newHookFunctionSpaceAddr + CODE_OFFSET + backupOffset;
	LOGD("asm data");
	LOGHEX((unsigned char *)newHookFunctionSpaceAddr,sizeof(struct _HookFuncPayloadData));
	
	memcpy((unsigned char *)(newHookFunctionSpaceAddr+CODE_OFFSET),asmCode,sizeof(asmCode));
	// everything inplace not inject code 
	InjectJumpCode(addr,newHookFunctionSpaceAddr+CODE_OFFSET);
	
	LOGD("Patch %s done",monoFunctionName);
	return newHookFunctionSpaceAddr;
    }
    return 0;
}


void MonoDumpImage(MonoImage* image)
{
    MonoClass *klass;
    int rows = mono_image_get_table_rows (image, MONO_TABLE_TYPEDEF);
    
    /* we start the count from 1 because we skip the special type <Module> */
    LOGD("rows=%d",rows);
    if(rows == 747) return;
    for (int i = 1; i <= rows; ++i) {
        klass = mono_class_get ((MonoImage *)image, i  | MONO_TOKEN_TYPE_DEF);
        LOGD("klass=%08X %d/%d",klass,i,rows);
        LOGD("Class name: %s.%s", mono_class_get_namespace((unsigned int)klass),mono_class_get_name ((unsigned int)klass));
    }
}

void MonoLoadAndInvokeAssembly(const char* fileName,const char* name_space,char *className,const char* methodName)
{
    
    MonoAssembly *assembly = MonoLoadAssembly(fileName);
    LOGD("assembly %08X",(unsigned int) assembly);
    
    MonoImage *image = mono_assembly_get_image(assembly);
    LOGD("image %08X",(unsigned int) image);
    
    LOGD("Namespace=[%s] name=[%s]",name_space,className);
    MonoClass *monoclass = mono_class_from_name(image,name_space,className);
    LOGD("monoclass %08X",(unsigned int) monoclass);
    
    MonoMethod *myMonoMethod = mono_class_get_method_from_name(monoclass,methodName,0);
    LOGD("myMonoMethod %08X",(unsigned int) myMonoMethod);
    
    mono_runtime_invoke(myMonoMethod,0,0,0);
    LOGD("invoke done");
}




