/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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
#include <dirent.h>
#include "../util/logger.h"
#include "../util/payload.hpp"


unsigned char _branchToAddressCmd[] = {
        0x00,0xC0,0x9F,0xE5,    //LDR r12,[pc,0]    ;load 12 from jump addr
        0x1C,0xFF,0x2F,0xE1,    //BX	r12
        0x11,0x22,0x33,0x44,    //jump_addr
};

unsigned char * CreateBranchToAddressCommand(unsigned int jumpToAddr)
{
    unsigned char *ret = (unsigned char*)malloc(GetBranchToAddressCommandSize());
    memcpy(ret,_branchToAddressCmd,GetBranchToAddressCommandSize());
    *(unsigned int *)((unsigned char*)ret + 8) = jumpToAddr;
    return ret;
}

int GetBranchToAddressCommandSize()
{
    return sizeof(_branchToAddressCmd);
}

unsigned int AllocateExecutableMemory(unsigned int size)
{
   void * virtualCodeAddress = 0;
   virtualCodeAddress = mmap(
       NULL,
       size,
       PROT_READ | PROT_WRITE | PROT_EXEC,
       MAP_ANONYMOUS | MAP_PRIVATE,
       0,
       0);
   //LOGD("AllocateExecutableMemory: virtualCodeAddress = %p\n", virtualCodeAddress);
    // write some code in
   return (unsigned int)virtualCodeAddress;
}

unsigned int FindFreeSpace(int pid,char *filter)
{
	FILE *fp;
	char filename[30];
	char line[850];
	char addr[128];
        char unk[128];
	char perms[32];
	sprintf(filename, "/proc/%d/maps", pid);
	fp = fopen(filename, "r");
	if(fp == NULL)
		exit(1);
	while(fgets(line, 850, fp) != NULL)
	{
            sscanf(line, "%s %s %s", addr, perms, unk);
            if(strstr(line,"/dev")){
                //printf("SKIP %s\n",line);
                continue;
            }
            //if((strstr(line,"libsqlite.so")==NULL)&&(strstr(line,"liblog.so")==NULL)){
            if(strstr(line,"liblog.so")==NULL){
                //printf("SKIP(2) %s\n",line);
                continue;
            }
            if(filter!=NULL){
                if(strstr(perms, filter)== NULL){
                    continue;
                }
            }
            //if(strstr(perms, "x") != NULL)
            //{
                printf("freespaceaddr: found at\n");
                printf("%s",line);
                break;
            //}
	}
	fclose(fp);
	return (unsigned int)strtoul(addr, NULL, 16);
}

int MemoryFind(unsigned char *data,int data_size, unsigned char* pattern,int pattern_size)
{
    for(int i=0;i<data_size - pattern_size;i++){
        if(memcmp(&data[i],&pattern[0],pattern_size)==0){
            return i;
        }
    }
    return -1;
}

bool WriteAllBytes(char *fileName,unsigned char *data,int size)
{
    FILE *f = fopen(fileName,"wb");
    if(f!=NULL){
        fwrite(data,size,1,f);
        fflush(f);
        fclose(f);
        return true;
    }
    return false;
}

unsigned char *ReadAllBytes(char *fileName,int *size)
{
    FILE *f = fopen(fileName,"rb");
    unsigned int fileSize;
    if(f!=NULL){
        fseek(f, 0L, SEEK_END);
        fileSize = ftell(f);
        *size = fileSize;
        fseek(f, 0L, SEEK_SET);

        unsigned char *ret = (unsigned char*)malloc(fileSize);
        if(ret!=NULL){
            fread(ret,fileSize,1,f);
            fclose(f);
            return ret;
        }
    }
    return NULL;
}

std::vector<unsigned char> _ReadFile(const char *fileName)
{
    
    FILE *f = fopen(fileName, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  //same as rewind(f);

    unsigned char *ptr = (unsigned char *)malloc(fsize);
    fread(ptr, fsize, 1, f);
    fclose(f);

    //LOGD("ReadFile %s size=%ld",fileName,fsize);
    
    std::vector<unsigned char> ret;
    for(int i=0;i<fsize;i++){
        ret.push_back(ptr[i]);
    }
    free(ptr);
    return ret;
}




