/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PtraceUtil.hpp
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
#include <cctype>
#include <vector>
#include "logger.h"
#ifndef PTRACEUTIL_HPP
#define PTRACEUTIL_HPP

#define MEMORY_BACKUP_SIZE  1024
class MemoryBackup
{
public:
    unsigned int targetAddr;
    unsigned char data[MEMORY_BACKUP_SIZE];
    int size;
};

class PtraceUtil {
public:
    Logger logger;
    int pid;
    std::vector<MemoryBackup> vMemoryBackup;
    PtraceUtil();
    virtual ~PtraceUtil();
    MemoryBackup* FindBackupMemory(unsigned int targetAddr);
    void DumpHex(unsigned int addr,int size);
    bool ReadProcessMemory(unsigned int addr, unsigned char *buf, int blen);
    bool WriteProcessMemory(unsigned int addr, unsigned char *buf, int blen);
    int  wordAlignSize(int size);
    bool BackupMemory(unsigned int targetAddr,int size);
    bool RestoreMemory(unsigned int targetAddr);
    int PokeText(unsigned int addr,size_t value);
    int PeekText(unsigned int addr,size_t *value);
    long Attach(int _pid);
    long Detach();
    long Continue();
    int waitForStop();
    int GetRegs(pt_regs *reg);
    int SetRegs(pt_regs *reg);
    unsigned int GetReturnValue(pt_regs *reg);
    unsigned int GetIP(pt_regs *reg);
    int Push(unsigned int value,pt_regs *reg);
    long Call(uint32_t addr, long *params, uint32_t num_params,  struct pt_regs *regs);
private:

};

#endif /* PTRACEUTIL_HPP */

