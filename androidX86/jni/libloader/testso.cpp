#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <resolv.h>
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

#include "../util/util.hpp"
#include "../util/logger.h"

#define  LOG_TAG    "testso"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C" {
    void Test1();
};

void Test1()
{
    LOGD("Test1()");
    printf("Test1()\n");
}


void __attribute__ ((constructor)) dll_load()
{
    LOGD("LIBRARY LOADED FROM PID %d", getpid());
    LOGD("THREAD CREATED");
}

void __attribute__ ((destructor)) dll_unload()
{
    LOGD("LIBRARY UNLOADED FROM PID %d", getpid());
}



