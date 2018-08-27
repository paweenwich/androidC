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
#include "util.hpp"

#define  LOG_TAG    "utils"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

typedef void* MonoDomain;
typedef void* MonoAssembly;
typedef void* MonoImage;
typedef void* MonoClass;
typedef void* MonoObject;
typedef void* MonoMethodDesc;
typedef void* MonoMethod;
typedef void* MonoString;
typedef int gboolean;
typedef void* gpointer;

/*
MonoDomain *mono_domain_get();
MonoAssembly *mono_domain_assembly_open(MonoDomain *domain, const char *assemblyName);
MonoImage *mono_assembly_get_image(MonoAssembly *assembly);
MonoMethodDesc *mono_method_desc_new(const char *methodString, gboolean useNamespace);
MonoMethodDesc *mono_method_desc_free(MonoMethodDesc *desc);
MonoMethod *mono_method_desc_search_in_image(MonoMethodDesc *methodDesc, MonoImage *image);
MonoObject *mono_runtime_invoke(MonoMethod *method, void *obj, void **params, MonoObject **exc);
MonoClass *mono_class_from_name(MonoImage *image, const char *namespaceString, const char *classnameString);
MonoMethod *mono_class_get_methods(MonoClass*, gpointer* iter);
MonoString *mono_string_new(MonoDomain *domain, const char *text);
char* mono_method_get_name (MonoMethod *method);
*/



typedef void * (*mono_domain_get_t)();
mono_domain_get_t mono_domain_get;

typedef void * (*mono_image_open_from_data_t)(unsigned char *data,int size,int num,int *status);
mono_image_open_from_data_t mono_image_open_from_data;

typedef void * (*mono_domain_assembly_open_t)(unsigned int domain, const char *assemblyName);
mono_domain_assembly_open_t mono_domain_assembly_open;

typedef void * (*mono_get_root_domain_t)();
mono_get_root_domain_t mono_get_root_domain;

typedef void (*mono_thread_attach_t)(unsigned int domain);
mono_thread_attach_t mono_thread_attach;

typedef void* (*mono_assembly_load_from_full_t)(unsigned int image, const char *fname,int *status,int readonly);
mono_assembly_load_from_full_t mono_assembly_load_from_full;

typedef void* (*mono_assembly_get_image_t)(unsigned int assembly);
mono_assembly_get_image_t mono_assembly_get_image;

typedef void* (*mono_class_from_name_t)(unsigned int image, const char* name_space, const char *name);
mono_class_from_name_t mono_class_from_name;

typedef void* (*mono_class_get_method_from_name_t)(unsigned int klass, const char *name, int param_count);
mono_class_get_method_from_name_t mono_class_get_method_from_name;

typedef void* (*mono_runtime_invoke_t)(unsigned int method, unsigned int obj, unsigned int params, unsigned int exc);
mono_runtime_invoke_t mono_runtime_invoke;

void MonoLoadAndInvokeAssembly(const char* fileName,const char* name_space,char *className,const char* methodName)
{
    char monoLibraryFile[1024] = {0};
    FindLibraryPath("libmono.so",&monoLibraryFile[0],sizeof(monoLibraryFile));
    if(strlen(monoLibraryFile)==0){
        LOGD("MonoLoadAndInvokeAssembly: libmono.so not found\n");
        return;
    }
    LOGD("MonoLoadAndInvokeAssembly: found libmono.so [%s]\n",monoLibraryFile);
    void* handle = dlopen(monoLibraryFile,0);
    mono_domain_get = (mono_domain_get_t)dlsym(handle,"mono_domain_get");
    LOGD("mono_domain_get %08X",(unsigned int) mono_domain_get);
    unsigned int domain = (unsigned int)mono_domain_get();
    LOGD("domain %08X",(unsigned int) domain);
    
    mono_image_open_from_data = (mono_image_open_from_data_t)dlsym(handle,"mono_image_open_from_data");
    LOGD("mono_image_open_from_data %08X",(unsigned int) mono_image_open_from_data);

    mono_domain_assembly_open  = (mono_domain_assembly_open_t)dlsym(handle,"mono_domain_assembly_open");
    LOGD("mono_domain_assembly_open %08X",(unsigned int) mono_domain_assembly_open);

    mono_get_root_domain  = (mono_get_root_domain_t)dlsym(handle,"mono_get_root_domain");
    LOGD("mono_get_root_domain %08X",(unsigned int) mono_get_root_domain);
    unsigned int rootdomain = (unsigned int)mono_get_root_domain(); 
    LOGD("rootdomain %08X",rootdomain);

    mono_thread_attach  = (mono_thread_attach_t)dlsym(handle,"mono_thread_attach");
    LOGD("mono_thread_attach %08X",(unsigned int) mono_thread_attach);
    mono_thread_attach(rootdomain);
    
    mono_assembly_load_from_full  = (mono_assembly_load_from_full_t)dlsym(handle,"mono_assembly_load_from_full");
    LOGD("mono_assembly_load_from_full %08X",(unsigned int) mono_assembly_load_from_full);
    
    mono_assembly_get_image  = (mono_assembly_get_image_t)dlsym(handle,"mono_assembly_get_image");
    LOGD("mono_assembly_get_image %08X",(unsigned int) mono_assembly_get_image);
    
    mono_class_from_name  = (mono_class_from_name_t)dlsym(handle,"mono_class_from_name");
    LOGD("mono_class_from_name %08X",(unsigned int) mono_class_from_name);

    mono_class_get_method_from_name  = (mono_class_get_method_from_name_t)dlsym(handle,"mono_class_get_method_from_name");
    LOGD("mono_class_get_method_from_name %08X",(unsigned int) mono_class_get_method_from_name);

    mono_runtime_invoke  = (mono_runtime_invoke_t)dlsym(handle,"mono_runtime_invoke");
    LOGD("mono_runtime_invoke %08X",(unsigned int) mono_runtime_invoke);
    
    
    
    //loading file
    std::vector<unsigned char> buffer = ReadFile(fileName);
    LOGD("buffer size=%d",buffer.size());
    LOGD("%02X %02X %02X %02X %02X",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
    
    int status = 0;
    unsigned int raw_image = (unsigned int)mono_image_open_from_data(&buffer[0],buffer.size(),1,&status);
    LOGD("raw_image %08X status=%08X",raw_image,status);
    
    unsigned int assembly = (unsigned int)mono_assembly_load_from_full(raw_image,0,&status,0);
    LOGD("assembly %08X",(unsigned int) assembly);
    
    unsigned int image = (unsigned int)mono_assembly_get_image(assembly);
    LOGD("image %08X",(unsigned int) image);
    
    LOGD("Namespace=%sd name=%s",name_space,className);
    unsigned int monoclass = (unsigned int)mono_class_from_name(image,name_space,className);
    LOGD("monoclass %08X",(unsigned int) monoclass);
    
    unsigned int method = (unsigned int)mono_class_get_method_from_name(monoclass,methodName,0);
    LOGD("method %08X",(unsigned int) method);
    
    mono_runtime_invoke(method,0,0,0);
    LOGD("invoke done");
}



std::vector<unsigned char> ReadFile(const char *fileName)
{
    
    FILE *f = fopen(fileName, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  //same as rewind(f);

    unsigned char *ptr = (unsigned char *)malloc(fsize);
    fread(ptr, fsize, 1, f);
    fclose(f);

    LOGD("ReadFile %s size=%ld",fileName,fsize);
    
    std::vector<unsigned char> ret;
    for(int i=0;i<fsize;i++){
        ret.push_back(ptr[i]);
    }
    free(ptr);
    return ret;
}

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

void FindLibraryPath(const char* libname,char *path,int len)
{
   std::vector<std::string> lines;
   ReadMaps(0,lines);
   //LOGD("line=%d\n",lines.size());
   for(int i=0;i<lines.size();i++){
       //LOGD("%s %s\n",lines[i].c_str(),libname);
       char *ptr;
       if((ptr=strstr(lines[i].c_str(),libname))){
           LOGD("FindLibraryPath: found %s",lines[i].c_str());
           while(*ptr != ' ') ptr--;
           ptr++;
           strcpy(path,ptr);
           LOGD("FindLibraryPath: found %s",ptr);
           break;
       }
   }
}

unsigned int GetFuncAddress(const char* libname, const char* funcName)
{
    unsigned int ret = 0;
    LOGD("GetFuncAddress: [%s] [%s]",libname,funcName);
    void* handle = dlopen(libname,0);
    if(handle){
        ret = (unsigned int)dlsym(handle,funcName);
        if(ret !=0){
            LOGD("GetFuncAddress: func [%s] at %08X",funcName,ret);
        }else{
            LOGD("GetFuncAddress: func [%s] not found",funcName);
        }
        dlclose(handle);
    }else{
        LOGD("GetFuncAddress: lib [%s] not found",libname);
    }
    return ret;
}

unsigned int GetFuncOffset(const char* libname, const char* funcName)
{
    LOGD("GetFuncOffset: lib [%s] [%s]",libname,funcName);
    unsigned int func_addr = GetFuncAddress(libname,funcName);
    unsigned int base_addr = FindBaseLibraryFromAddress(func_addr,0);
    LOGD("GetFuncOffset: base=%08X func=%08X",base_addr,func_addr);
    return func_addr - base_addr;
}


unsigned int FindBaseLibrary( const char *library, int pid) 
{
    LOGD("FindBaseLibrary: %s %d",library,pid);
    unsigned int address = 0;
    std::vector<std::string> lines;
    ReadMaps(pid,lines);
    for(int i=0;i<lines.size();i++){
        //LOGD("FindBaseLibrary: %s",lines[i].c_str());
        if (strstr(lines[i].c_str(), library)) {
            address = (unsigned int) strtoul(lines[i].c_str(), NULL, 16);
            break;
        }
    }
    return address;
}

unsigned int FindBaseLibraryFromAddress(unsigned int address, int pid)
{
    unsigned int ret = 0;
    std::vector<std::string> lines;
    ReadMaps(pid,lines);
    for(int i=0;i<lines.size();i++){
        std::string line = lines[i];
        std::replace( line.begin(), line.end(), '-', ' ');
        //printf("%s",line.c_str());
        unsigned int from,to;
        sscanf(line.c_str(),"%X%X",&from,&to);
        //printf("%08X %08X\n",from,to);
        if((address >= from)&&(address<to)){
            LOGD("%s",line.c_str());
            ret = from;
            break;
        }
    }
    return ret;
}

unsigned int FinddlopenAddress(int pid)
{
    unsigned int ret = 0;
    
    unsigned int linkerBase = FindBaseLibraryFromAddress((unsigned int)dlopen,0);
    LOGD("linkerBase = %08X\n",linkerBase);
    LOGD("linkername %s\n",GetBaseLibraryNameFromAddress((unsigned int)dlopen,0));
    unsigned int myOffset = (unsigned int)dlopen - linkerBase;
    LOGD("offset dlopen = %08X\n",myOffset);
    
    unsigned int targetLinkerBase = FindBaseLibrary("/system/lib/arm/libdl.so",pid);
    LOGD("targetLinkerBase = %08X\n",targetLinkerBase);
    if(targetLinkerBase == 0){
        //try /system/lib/arm/linker
        targetLinkerBase = FindBaseLibrary("/system/lib/arm/linker",pid);
        LOGD("targetLinkerBase(/system/lib/arm/linker) = %08X\n",targetLinkerBase);
    }
    if(targetLinkerBase!=0){
        ret = targetLinkerBase + myOffset;
        LOGD("target dlopen = %08X\n",ret);
    }else{
        
        LOGD("ERROR: target dlopen notfound\n");
    }
    return ret;
}

unsigned int FindwriteAddress(int pid)
{
    unsigned int ret = 0;    
    unsigned int libcBase = FindBaseLibraryFromAddress((unsigned int)write,0);
    LOGD("libcBase = %08X\n",libcBase);
    LOGD("libcBasename %s\n",GetBaseLibraryNameFromAddress((unsigned int)write,0));
    unsigned int myOffset = (unsigned int)write - libcBase;
    LOGD("offset write = %08X\n",myOffset);
    
    unsigned int targetLinkerBase = FindBaseLibrary("/system/lib/arm/libc_orig.so",pid);
    LOGD("targetLinkerBase = %08X\n",targetLinkerBase);
    if(targetLinkerBase!=0){
        ret = targetLinkerBase + myOffset;
        LOGD("target write = %08X\n",ret);
    }else{
        LOGD("ERROR: target write notfound\n");
    }
    return ret;
}

char *GetBaseLibraryNameFromAddress(unsigned int address, int pid)
{
    static char name[1024] = {0};
    unsigned int ret = 0;
    std::vector<std::string> lines;
    ReadMaps(pid,lines);
    for(int i=0;i<lines.size();i++){
        std::string line = lines[i];
        std::replace( line.begin(), line.end(), '-', ' ');
        //printf("%s",line.c_str());
        unsigned int from,to;
        sscanf(line.c_str(),"%X%X",&from,&to);
        //printf("%08X %08X\n",from,to);
        if((address >= from)&&(address<to)){
            LOGD("%s",line.c_str());
            strcpy(name,line.c_str());
            break;
        }
    }
    return name;    
}

unsigned int GetBaseLibraryTextSize( const char *library, int pid)
{
    LOGD("GetBaseLibraryTextSize: %s %d",library,pid);
    unsigned int address = 0;
    std::vector<std::string> lines;
    ReadMaps(pid,lines);
    for(int i=0;i<lines.size();i++){
        std::string line = lines[i];
        std::replace( line.begin(), line.end(), '-', ' ');
        if (strstr(lines[i].c_str(), library) && strstr(lines[i].c_str(),"xp")) {
             //printf("%s",line.c_str());
             unsigned int from,to;
             if(sscanf(line.c_str(),"%X%X",&from,&to)==2){
                LOGD("GetBaseLibraryTextSize = %08X",to - from);
                return to - from;
             }
        }
    }
    return 0;
}

int FindProcessByName(char *processName,char *filter)
{
    int ret = 0;
    FILE *in;
    char cmd[1024];
    char buff[1024];
    sprintf(cmd,"/system/bin/ps | grep %s",processName);
    if(!(in = popen(cmd, "r"))){
		exit(1);
    }
    while(fgets(buff, sizeof(buff), in)!=NULL){
        if(filter!=NULL){
            if(strstr(buff,filter)==NULL){
                printf("FindProcessByName SKIP %s", buff);
                continue;
            }
        }
	printf("FindProcessByName %s", buff);
        if(ret==0){
	    char users[64];
            sscanf(buff,"%s%d",users,&ret);
	    break;
            //printf("Found pid=%d\n",ret);
        }
    }
    pclose(in);
    return ret;
}

void Test()
{
    //std::vector<unsigned char> data = ReadFile("/data/local/tmp/FantasyWarTactic.dll");
    LOGD("dlopen=%08X",(unsigned int)dlopen);
    LOGD("dlsym=%08X",(unsigned int)dlsym);
    LOGD("pid=%d",getpid());
    LOGD("gettid=%d",gettid());
}

std::string ConcatStrings(std::vector<std::string> &lst,std::string seperator)
{
    std::string ret;
    for(int i=0;i<lst.size();i++){
	if(i!=0){
	    ret += seperator;
	}
	ret+= lst[i];
    }
    return ret;
}

bool StringReplace(std::string& str, const std::string& from, const std::string& to) 
{
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

std::string SaveCString(char *data)
{
    std::string ret(data);
    StringReplace(ret,"\"","\\\"");
    return ret;
}

