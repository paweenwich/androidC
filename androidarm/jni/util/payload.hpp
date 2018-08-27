/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   payload.hpp
 * Author: Administrator
 *
 * Created on August 6, 2016, 11:05 AM
 */

#ifndef PAYLOAD_HPP
#define PAYLOAD_HPP
#define CODE_OFFSET     128
struct _PayloadData {
    char libName[64];
    unsigned int dlopenAddr;
    unsigned int funcAddr;
    unsigned int freeSpaceAddr;
    unsigned int libcAddr;
    unsigned int backupInstruction[3];
    unsigned int dlsymAddr;
    unsigned int kkkAddr;
    unsigned int newFreeSpaceDataAddr;
    unsigned int newFreeSpaceCodeAddr;
};

struct _NewPayloadData {
    unsigned int kkkAddr;
    unsigned int funcAddr;
};

struct _HookFuncPayloadData {
    unsigned int hookFunc;
    unsigned int oldFuncAddr;	    //used to call old function
};

unsigned int AllocateExecutableMemory(unsigned int size);
unsigned int FindFreeSpace(int pid,char *filter);
int MemoryFind(unsigned char *data,int data_size, unsigned char* pattern,int pattern_size);
bool WriteAllBytes(char *fileName,unsigned char *data,int size);
unsigned char *ReadAllBytes(char *fileName,int *size);
std::vector<unsigned char> _ReadFile(const char *fileName);
unsigned char * CreateBranchToAddressCommand(unsigned int jumpToAddr);
int GetBranchToAddressCommandSize();

#endif /* PAYLOAD_HPP */

