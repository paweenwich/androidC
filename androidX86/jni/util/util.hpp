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
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <dlfcn.h>
#include <stdarg.h>
#include <fcntl.h>
#include <string>
#include <vector>
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


// interface for unity
extern "C" {
    unsigned int GetFuncAddress(const char* libname, const char* funcName);
    unsigned int GetFuncOffset(const char* libname, const char* funcName);
    unsigned int FindBaseLibrary( const char *library, int pid);
    unsigned int FindBaseLibraryFromAddress(unsigned int address, int pid);
    char *GetBaseLibraryNameFromAddress(unsigned int address, int pid);
    void FindLibraryPath(const char* libname,char *path,int len);
    void MonoLoadAndInvokeAssembly(const char* fileName,const char* name_space,char *className,const char* methodName);
    void Test();
    int FindProcessByName(char *processName,char *filter);
    unsigned int FinddlopenAddress(int pid);
    unsigned int FindwriteAddress(int pid);
    unsigned int GetBaseLibraryTextSize(const char* libname,int pid);
    bool isDirectoryExist(const char* dir);
    size_t GetFilesize(const char* filename); 
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


#endif /* UTIL_HPP */

