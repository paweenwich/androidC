/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   util.hpp
 * Author: kwang
 *
 * Created on August 3, 2016, 9:26 AM
 */
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
#include <fcntl.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <android/log.h>


#ifndef UTIL_HPP
#define UTIL_HPP

std::vector<unsigned char> ReadFile(const char *fileName);
void ReadMaps(int pid,std::vector<std::string> &out);
std::string bin2hex(std::string const &s);
std::vector<unsigned char> hex2bin(std::string const& s);
std::vector<std::string> DirectoryListFile(std::string& dirName,std::string filter = "");
std::string StringReplaceChar(std::string src,char c1,char c2);
std::vector<std::string> SplitByChar(std::string src, char c = ' ');
std::vector<std::string> ReadAllLines(char *fileName);
std::string GetCurrentExecutable();
std::string GetCurrentExecutableDirectory();
std::string StringPrintf(const char* fmt, ...);

// interface for unity
extern "C" {
    unsigned int GetFuncAddress(const char* libname, const char* funcName);
    unsigned int GetFuncOffset(const char* libname, const char* funcName);
    unsigned int FindBaseLibrary( const char *library, int pid);
    unsigned int FindBaseLibraryFromAddress(unsigned int address, int pid);
    char *GetBaseLibraryNameFromAddress(unsigned int address, int pid);
    void FindLibraryPath(const char* libname,char *path,int len);
    void FindLibraryPathEx(const char* libname,char *path,unsigned int *baseAddr,unsigned int *libSize);
    void MonoLoadAndInvokeAssembly(const char* fileName,const char* name_space,char *className,const char* methodName);
    void Test();
    int FindProcessByName(char *processName,char *filter);
    unsigned int FinddlopenAddress(int pid);
    unsigned int FindwriteAddress(int pid);
    unsigned int GetBaseLibraryTextSize(const char* libname,int pid);
    bool isDirectoryExist(const char* dir);
    size_t GetFilesize(const char* filename); 
    double GetTickCount(void); 
    int GetMyTracerPID();
    void Panic(const char* fmt, ...);
    void DisableSelinux();
    bool IsSelinuxEnabled();
    unsigned int ParseAddress(char *);
    bool IsReadable(unsigned int addr,int size);
    bool DumpMemory(unsigned int addr,int size,char *fileName);
    bool MightContainPE(unsigned int startAddr,unsigned int endAddr);
};

class FileMap
{
public:
    std::string fileName;
    size_t filesize;
    int fd;
    void *buf;
    FileMap(){
	buf = NULL;
    }
    ~FileMap(){
	unMap();
    }
    void* map(std::string fileName){
	this->fileName = fileName;
	filesize = GetFilesize(fileName.c_str()); 
	if(filesize > 0){
	    fd = open(fileName.c_str(), O_RDONLY, 0); 
	    if(fd > 0 ){
		//Execute mmap 
		buf = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0); 
		if(buf != MAP_FAILED){
		    //printf("FileMap:map %s %d\n",fileName.c_str(),filesize);
		    return buf;
		}
	    }
	    close(fd);
	}
	return(NULL);
    }
    void unMap(){
	if(buf!=NULL){
	    int rc = munmap(buf, filesize); 
	    //printf("FileMap:unmap %d\n",filesize);
	    close(fd); 
	}
    }

};

class TempDirectory {
 public:
  TempDirectory() {
    snprintf(path_, sizeof path_, "/data/local/tmp/temp-XXXXXX");
    if (!mktemp(path_))
      Panic("Could not create temporary directory name: %s\n", strerror(errno));
    if (mkdir(path_, 0700) < 0)
      Panic("Could not create temporary directory %s: %s\n", strerror(errno));
  }

  ~TempDirectory() {
    // Remove any file in this directory.
    DIR* d = opendir(path_);
    if (!d)
      Panic("Could not open directory %s: %s\n", strerror(errno));

    struct dirent* entry;
    while ((entry = readdir(d)) != NULL) {
      if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
        continue;
      char file_path[PATH_MAX*2];
      //String file_path;
      //file_path.Format("%s/%s", path_, entry->d_name);
      sprintf(file_path,"%s/%s", path_, entry->d_name);
      if (unlink(file_path) < 0)
        Panic("Could not remove %s: %s\n", file_path, strerror(errno));
    }
    closedir(d);

    if (rmdir(path_) < 0)
      Panic("Could not remove dir %s: %s\n", path_, strerror(errno));
  }

  const char* path() const { return path_; }

 private:
  char path_[PATH_MAX];
};


typedef enum {
	MONO_IMAGE_OK,
	MONO_IMAGE_ERROR_ERRNO,
	MONO_IMAGE_MISSING_ASSEMBLYREF,
	MONO_IMAGE_IMAGE_INVALID
} MonoImageOpenStatus;



#endif /* UTIL_HPP */

