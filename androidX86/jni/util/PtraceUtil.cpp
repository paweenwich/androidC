/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PtraceUtil.cpp
 * Author: kwang
 * 
 * Created on August 4, 2016, 8:28 AM
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
#include "util.hpp"
#include "logger.h"
#include "PtraceUtil.hpp"

#define  LOG_TAG    "PtraceUtil"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

PtraceUtil::PtraceUtil() {
}


PtraceUtil::~PtraceUtil() {
}

long PtraceUtil::Attach(int _pid)
{
    pid = _pid;
    errno = 0;
    long ret = ptrace( PTRACE_ATTACH, pid, 0,0 );
    if( ret == -1){
        LOGE("Attach: %s",strerror(errno));
        return -1;
    }
    LOGD("Attach Success");
    return 0;
}

long PtraceUtil::Detach()
{
    errno = 0;
    long ret = ptrace(PTRACE_DETACH, pid, 0,0 );
    if( ret == -1){
        LOGE("Detach: %s",strerror(errno));
        return -1;
    }
    LOGD("Detach Success");
    return 0;
}

long PtraceUtil::Continue()
{
    long ret = ptrace( PTRACE_CONT, pid, 0,0 );
    if( ret == -1){
        LOGE("Continue: %s",strerror(errno));
        return -1;
    }
    LOGD("Continue Success");
    return ret;
}

MemoryBackup* PtraceUtil::FindBackupMemory(unsigned int targetAddr)
{
    for(int i=0;i<vMemoryBackup.size();i++){
        if(vMemoryBackup[i].targetAddr==targetAddr){
            LOGD("FindBackupMemory %08X found",targetAddr);
            return(&vMemoryBackup[i]);
        }
    }
    //LOGD("FindBackupMemory %08X not found",targetAddr);
    return NULL;
}

bool PtraceUtil::BackupMemory(unsigned int targetAddr,int size)
{
    LOGD("BackupMemory %08X %d",targetAddr,size);
    if(size > MEMORY_BACKUP_SIZE){
        LOGE("BackupMemory size %d > maxsize(%d)",size,MEMORY_BACKUP_SIZE);
        return false;
    }
    //printf("Before Backup Dump %08X\n",targetAddr);
    //DumpHex(targetAddr,32);
    // check if we have this before
    MemoryBackup *oldm = FindBackupMemory(targetAddr);
    if(oldm==NULL){
        LOGE("BackupMemory create new");
        MemoryBackup m;
        m.size = size;
        m.targetAddr = targetAddr;
        ReadProcessMemory(targetAddr,&m.data[0],size);
        vMemoryBackup.push_back(m);
        //printf("After Backup Dump backup\n");
        //logger.logHex(&m.data[0],32);
    }else{
        LOGE("BackupMemory reused");
        oldm->size = size;
        ReadProcessMemory(targetAddr,&oldm->data[0],size);
    }
    LOGD("BackupMemory done");
}

bool PtraceUtil::RestoreMemory(unsigned int targetAddr)
{
    LOGD("RestoreMemory %08X",targetAddr);
    //printf("Before restore Dump %08X\n",targetAddr);
    //DumpHex(targetAddr,32);
    MemoryBackup *m = FindBackupMemory(targetAddr);
    if(m!=NULL){
            WriteProcessMemory(targetAddr,&m->data[0],m->size);
            //printf("After restore Dump %08X\n",targetAddr);
            //DumpHex(targetAddr,32);
            LOGD("RestoreMemory done");
            return true;
    }
    LOGE("RestoreMemory of %08X not found",targetAddr);
    return false;
}

bool PtraceUtil::ReadProcessMemory(unsigned int addr, unsigned char *buf, int blen) {
    for (int i = 0; i < blen; i += sizeof (size_t)) {
        size_t value;
        int ret = PeekText(addr + i,&value);
        if (ret == -1) {
            LOGE("ReadProcessMemory %d %08X fail",pid,addr);
            return false;
        }
        memcpy(&buf[i], &value, sizeof (value));
    }
    return true;
}

int PtraceUtil::wordAlignSize(int size)
{
    return (size + size % sizeof (size_t));
}

bool PtraceUtil::WriteProcessMemory(unsigned int addr, unsigned char *buf, int blen) {
    long ret;
    unsigned long size = wordAlignSize(blen);
    // make sure the buffer is word aligned
    char *ptr = (char *) calloc(size, 1);
    memcpy(ptr, buf, blen);

    for (int i = 0; i < size; i += sizeof (size_t)) {
        ret = PokeText(addr + i,*(size_t *) & ptr[i]);
        if (ret == -1) {
            ::free(ptr);
            return false;
        }
    }
    ::free(ptr);
    return true;
}

int PtraceUtil::PeekText(unsigned int addr,size_t *value)
{
    errno = 0;
    long ret = ptrace( PTRACE_PEEKTEXT, pid,addr,0);
    if( ret == -1){
        if(errno){
            LOGE("PeekText: %s",strerror(errno));
            return -1;
        }
    }
    *value = ret;
    return 0;
}

int PtraceUtil::PokeText(unsigned int addr,size_t value)
{
    errno = 0;
    long ret = ptrace( PTRACE_POKETEXT, pid,addr,value);
    if( ret == -1){
        LOGE("PokeText: %s",strerror(errno));        
        return -1;
    }
    return ret;
}

void PtraceUtil::DumpHex(unsigned int addr,int size)
{
    unsigned char *buf = (unsigned char *)malloc(size);
    if(ReadProcessMemory(addr,buf,size)){
        logger.logHex(buf,size);
    }
    free(buf);
}

int PtraceUtil::waitForStop()
{
    LOGD("waitForStop %d",pid);
    while(true){
        int wstatus = 0;
        int ret = waitpid( pid, &wstatus, __WALL );
        LOGD("waitForStop pid=%d ret=%d status=%08X\n",pid, ret,wstatus);
        if(WIFSTOPPED(wstatus)){
            LOGD("WIFSTOPPED");
            break;
        }
        //if(WIFCONTINUED(wstatus)){
        //    printf("WIFCONTINUED\n");
        //    continue;
        //}
        if(WSTOPSIG(wstatus)){
            LOGD("WSTOPSIG");
            continue;
        }
        if(WTERMSIG(wstatus)){
            LOGD("WTERMSIG");
            continue;
        }
        if(WIFSIGNALED(wstatus)){
            LOGD("WIFSIGNALED");
            continue;
        }
        if(WEXITSTATUS(wstatus)){
            LOGD("WEXITSTATUS");
            continue;
        }
        if(WIFEXITED(wstatus)){
            LOGD("WIFEXITED");
            return -1;
        }
    }
    return 0;
}



