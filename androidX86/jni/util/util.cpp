#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
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
#include <sstream>
#include <iomanip>
#include <cctype>
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


#define MONO_FUNC(r,n,p)\
    typedef r (* n##_t) p;\
    n##_t n;

MONO_FUNC(void *,mono_domain_get,(void));
MONO_FUNC(void *,mono_image_open_from_data,(unsigned char *data,int size,int num,int *status));
MONO_FUNC(void *,mono_domain_assembly_open,(unsigned int domain, const char *assemblyName));
MONO_FUNC(void *,mono_get_root_domain,(void));
MONO_FUNC(void *,mono_thread_attach,(unsigned int domain));
MONO_FUNC(void *,mono_assembly_load_from_full,(unsigned int image, const char *fname,int *status,int readonly));
MONO_FUNC(void *,mono_assembly_get_image,(unsigned int assembly));
MONO_FUNC(void *,mono_class_from_name,(unsigned int image, const char* name_space, const char *name));
MONO_FUNC(void *,mono_class_get_method_from_name,(unsigned int klass, const char *name, int param_count));
MONO_FUNC(void *,mono_runtime_invoke,(unsigned int method, unsigned int obj, unsigned int params, unsigned int exc));

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
    
#define MONO_LOAD(n)\
    n = (n ## _t)dlsym(handle,#n);\
    LOGD(#n " %08X",(unsigned int) n);
    
    MONO_LOAD(mono_domain_get);
    unsigned int domain = (unsigned int)mono_domain_get();
    LOGD("domain %08X",(unsigned int) domain);
    
    MONO_LOAD(mono_image_open_from_data);
    MONO_LOAD(mono_domain_assembly_open);
    MONO_LOAD(mono_get_root_domain);
    unsigned int rootdomain = (unsigned int)mono_get_root_domain(); 
    LOGD("rootdomain %08X",rootdomain);

    MONO_LOAD(mono_thread_attach);
    mono_thread_attach(rootdomain);
    
    MONO_LOAD(mono_assembly_load_from_full);
    MONO_LOAD(mono_assembly_get_image);
    MONO_LOAD(mono_class_from_name);
    MONO_LOAD(mono_class_get_method_from_name);
    MONO_LOAD(mono_runtime_invoke);
    
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
    char username[64];
    sprintf(cmd,"ps | grep %s",processName);
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
	    // if first one is digit then simple ps
	    if(isdigit(buff[0])){
		sscanf(buff,"%d",&ret);
	    }else{
		sscanf(buff,"%s %d",username,&ret);
	    }
            printf("FindProcessByName: Found pid=%d\n",ret);
	    break;
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

//Support XXXXXX and XX XX XX]
std::vector<unsigned char> hex2bin(std::string const& s)
{
    
    std::vector<unsigned char> ret;
    char *ptr = (char *)s.c_str();
    //printf("%s\n",ptr);
    for(int i=0;i<strlen(ptr);i+=2){
	if(ptr[i]==' '){
	    i++;
	}
	char buf[3];
	strncpy(buf,&ptr[i],2);
	buf[2] = 0;
	int c;
	sscanf(buf,"%x",&c);
	ret.push_back(c);
	//printf("%x\n",c);
    }
    return ret;
}

bool isDirectoryExist(const char* dir){
    struct stat sb;
    if (stat(dir, &sb) == 0 && S_ISDIR(sb.st_mode))
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t GetFilesize(const char* filename) { 
    struct stat st; 
    stat(filename, &st); 
    return st.st_size; 
} 

#include <dirent.h>
std::vector<std::string> DirectoryListFile(std::string& dirName,std::string filter){
    std::vector<std::string> ret;
    //len = strlen(name);
    DIR *dirp = opendir(dirName.c_str());
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL){
	if(filter!=""){
	    if(strstr(dp->d_name,filter.c_str())!=NULL){
		ret.push_back(dp->d_name);
	    }
	}else{
	    ret.push_back(dp->d_name);
	}
	//if (dp->d_namlen == len && !strcmp(dp->d_name, name)) {
		//(void)closedir(dirp);
	//}
	//printf("[%s]\n",dp->d_name);
    }
    closedir(dirp);
    return ret;
}

std::string StringReplaceChar(std::string src,char c1,char c2)
{
    std::string s = src;
    std::replace(s.begin(), s.end(), c1, c2 );
    return s;
}

std::vector<std::string> SplitByChar(std::string src, char c)
{
    std::vector<std::string> result;
    char *str = (char *)src.c_str();
    do
    {
        const char *begin = str;
        while(*str != c && *str)
            str++;

        result.push_back(std::string((char *)begin, str));
    } while (0 != *str++);
    return result;
}

double GetTickCount(void) 
{
  struct timespec now;
  if (clock_gettime(CLOCK_MONOTONIC, &now))
    return 0;
  return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
}

std::vector<std::string> ReadAllLines(char *fileName)
{
    char buffer[2048];
    std::vector<std::string> out;
    FILE *fp = NULL;
    //sprintf(filename, "/proc/%d/maps", pid);
    fp = fopen(fileName, "rt");
    if (fp == NULL) {
        LOGD("ReadAllLines: cannot open %s",fileName);
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
    return out;
}

int GetMyTracerPID()
{
    char fileName[128];
    sprintf(fileName,"/proc/%d/status",getpid());
    std::vector<std::string> lines = ReadAllLines(fileName);
    int tracerID = 0;    
    for(int i=0;i<lines.size();i++){
	char *line = (char *)lines[i].c_str();
	if(strstr(line,"TracerPid:")==line){
	    //printf("%s\n",lines[i].c_str());
	    char key[64];
	    if(sscanf(line,"%s%d",key,&tracerID)==2){
		//printf("TracerPid=%d\n",tracerID);
		break;
	    }
	}
    }
    return tracerID;
}

inline void Panic(const char* fmt, ...) 
{
  va_list args;
  fprintf(stderr, "PANIC: ");
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  exit(1);
}

std::string GetCurrentExecutable() 
{
  char path[PATH_MAX];  
  ssize_t ret = readlink("/proc/self/exe", path, sizeof(path));
  if (ret < 0)
    Panic("Could not read /proc/self/exe: %s\n", strerror(errno));
  return path;
}

// Retrieve current executable directory as a String.
std::string GetCurrentExecutableDirectory() 
{
  std::string path = GetCurrentExecutable();
  // Find basename.
  char* p = reinterpret_cast<char*>(strrchr(path.c_str(), '/'));
  if (p == NULL)
    Panic("Current executable does not have directory root?: %s\n",
          path.c_str());

  int pos = path.find(p);
  //path.Resize(p - path.c_str());
  return path.substr(0,pos);
}

bool IsSelinuxEnabled()
{
  FILE* fp = fopen("/proc/filesystems", "r");
  char* line = (char*) calloc(50, sizeof(char));
  bool result = false;
  while(fgets(line, 50, fp)) {
    if (strstr(line, "selinuxfs")) {
      result = true;
    }
  }
  if (line) {
    free(line);
  }
  fclose(fp);
  return result;
}

void DisableSelinux() {
  FILE* fp = fopen("/proc/mounts", "r");
  char* line = (char*) calloc(1024, sizeof(char));
  while(fgets(line, 1024, fp)) {
    if (strstr(line, "selinuxfs")) {
      strtok(line, " ");
      char* selinux_dir = strtok(NULL, " ");
      char* selinux_path = strcat(selinux_dir, "/enforce");
      FILE* fp_selinux = fopen(selinux_path, "w");
      char* buf = (char*)"0"; // set selinux to permissive
      fwrite(buf, strlen(buf), 1, fp_selinux);
      fclose(fp_selinux);
      break;
    }
  }
  fclose(fp);
  if (line) {
    free(line);
  }
}

unsigned int ParseAddress(char *data)
{
    unsigned int ret=0;
    if(strstr(data,"0x")==data){
        sscanf(data+2,"%x",&ret);
    }else{
        sscanf(data,"%d",&ret);
    }
    return ret;
}

bool IsReadable(unsigned int addr,int size)
{
    int nullfd = open("/dev/random", O_WRONLY);
    if (write(nullfd, (void *)addr, size) < 0)
    {
        return false;
    }
    close(nullfd);
    return true;
}

bool DumpMemory(unsigned int addr,int size,char *fileName)
{
    if(IsReadable(addr,size)){
        int fd = open(fileName, O_WRONLY|O_CREAT, 777);
        if(fd>0){
            if (write(fd, (void *)addr, size) < 0)
            {
                LOGD("DumpMemory: write fail");
                return false;
            }
            close(fd);
        }else{
            LOGD("DumpMemory: open %s fail",fileName);
            return false;
        }
        return true;
    }
    LOGD("DumpMemory: not readable");
    return false;
}

