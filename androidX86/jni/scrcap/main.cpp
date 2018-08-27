/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kwang
 *
 * Created on August 22, 2018, 4:42 PM
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
#include <cstdlib>
#include <dirent.h>
#include <../util/util.hpp>
#include <../util/PtraceUtil.hpp>
#include <../util/logger.h>
#include <../util/payload.hpp>

#define stricmp strcasecmp


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    printf("Hello\n");
    return 0;
}

