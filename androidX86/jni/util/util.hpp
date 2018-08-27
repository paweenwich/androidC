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
#include <string>
#include <vector>
#include <fstream>
#include <android/log.h>

#ifndef UTIL_HPP
#define UTIL_HPP

std::vector<unsigned char> ReadFile(const char *fileName);
void ReadMaps(int pid,std::vector<std::string> &out);


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
};

#endif /* UTIL_HPP */

