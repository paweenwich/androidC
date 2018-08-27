/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProcessScanner.cpp
 * Author: kwang
 * 
 * Created on August 25, 2016, 8:25 AM
 */
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/uio.h>
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
#include "logger.h"
#include "util.hpp"
#include "ProcessScanner.hpp"


ProcessScanner::ProcessScanner() {
    logger = new Logger(NULL,0);
    f = NULL;
}


ProcessScanner::~ProcessScanner() {
    close();
    //delete(logger);
    
}

void ProcessScanner::openFile()
{
    close();
    char fileName[128];
    sprintf(fileName,"/proc/%d/mem",pid);
    f = fopen(fileName,"rw");
}

bool ProcessScanner::open(int _pid)
{
    pid = _pid;
    readMap();
    openFile();
    return (f != NULL);
}

void ProcessScanner::close()
{
    if(f!=NULL){
	fclose(f);
	f = NULL;
    }
}

void ProcessScanner::readMap()
{
    
    std::vector<std::string> lines;
    ReadMaps(pid,lines);
    
    vProcMap.clear();
    
    for(int i=0;i<lines.size();i++){
	ProcMapData map;
	char addr[64];
	char perms[64];
	char unk[64];
	char unk2[64] = {0};
	char unk3[64] = {0};
	char unk4[512] = {0};
	sscanf(lines[i].c_str(),"%s %s %s %s %s %s",addr, perms, unk,unk2,unk3,unk4);
	std::string strAddr = addr;
	std::replace( strAddr.begin(), strAddr.end(), '-', ' ');
	unsigned int from;
	unsigned int to;
	sscanf(strAddr.c_str(),"%x %x",&from,&to);
	//printf("%08X %08X %s %s %s %s %s\n",from,to,perms,unk,unk2,unk3,unk4);
	strcpy(map.desc,unk4);
	strcpy(map.protection,perms);
	map.startAddr = from;
	map.endAddr = to;
	vProcMap.push_back(map);
    }
    
}

void ProcessScanner::scanAll(unsigned int dataAddr,int dataSize,std::vector<ScanResult> &result,bool writeAble)
{
    scanRange(0,0xFFFFFFFF,dataAddr,dataSize,result,writeAble);
}

void ProcessScanner::scanRange(unsigned int startRange,unsigned int endRange,unsigned int dataAddr,int dataSize,std::vector<ScanResult> &result,bool writeAble)
{
    std::vector<ScanData> vData;
    ScanData sd;
    memcpy(sd.data,(void *)dataAddr,dataSize);
    sd.size = dataSize;
    scanRange(startRange,endRange,vData,result,1,writeAble);
}

void ProcessScanner::scanRange(unsigned int startRange,unsigned int endRange,std::vector<ScanData> &vData,std::vector<ScanResult> &result,int step, bool writeAble)
{
    //PtraceUtil ptraceUtil;
    //ptraceUtil.Attach(pid);
    //ptraceUtil.waitForStop();    
    
    for(int i=0;i<vProcMap.size();i++){
	ProcMapData *p = &vProcMap[i];
	if(writeAble && (!p->isCanWrite())){
	    continue;
	}
	if(p->startAddr < startRange){
	    continue;
	}
	if(p->endAddr > endRange){
	    continue;
	}

	unsigned int memSize = p->size();
	unsigned char *buffer = (unsigned char*)malloc(memSize);
	if(buffer!=NULL){
	    read(p->startAddr,memSize,(unsigned int)buffer);
	    for(int j=0;j<vData.size();j++){
		ScanData sd = vData[j];
		std::vector<ScanResult> sresult;		
		memScan((unsigned int)sd.data,sd.size,(unsigned int)buffer,memSize,sresult,step);
		for(int i=0;i<sresult.size();i++){
		    ScanResult res;
		    printf("Found at = %08X\n",p->startAddr + sresult[i].addr);
		    res.addr = p->startAddr + sresult[i].addr;
		    result.push_back(res);
		}
	    }
	    free(buffer);
	}else{
	    printf("scanAll: malloc can not alocate %d\n",memSize);
	}
    }    
    
    //ptraceUtil.Detach();
}

bool ProcessScanner::read(unsigned int targetAddr,int size,unsigned int bufferAddr)
{
    if(fseek(f,targetAddr,SEEK_SET)!=0){
	printf("seek %08X fail: %s\n",targetAddr,strerror(errno));
	return false;
    }
    if(fread((void *)bufferAddr,size,1,f)!=1){
	printf("read %08X for %d fail: %s\n",targetAddr,size,strerror(errno));
    }
    return true;
}

bool ProcessScanner::writeAll(std::vector<WriteData> &vData)
{
    PtraceUtil ptraceUtil;
    ptraceUtil.Attach(pid);
    ptraceUtil.waitForStop();
    for(int i=0;i<vData.size();i++){
	WriteData wd = vData[i];
	if(!ptraceUtil.WriteProcessMemory(wd.addr,(unsigned char *)wd.data,wd.size)){
	    printf("write %08X for %d fail: %s\n",wd.addr,wd.size,strerror(errno));
	}
    }
    ptraceUtil.Detach();
    // reopen file
    openFile();
}

bool ProcessScanner::write(unsigned int targetAddr,int size,unsigned int bufferAddr)
{
    PtraceUtil ptraceUtil;
    ptraceUtil.Attach(pid);
    ptraceUtil.waitForStop();
    if(!ptraceUtil.WriteProcessMemory(targetAddr,(unsigned char *)bufferAddr,size)){
	printf("write %08X for %d fail: %s\n",targetAddr,size,strerror(errno));
    }
    ptraceUtil.Detach();
    // reopen file
    openFile();
}

void ProcessScanner::memScan(unsigned int dataAddr,int dataSize,unsigned int memAddr,int memSize,std::vector<ScanResult> &result,int step)
{
    for(unsigned int i=0;i<memSize - dataSize;i+=step){
	if(memcmp((void *)dataAddr,(void *)(memAddr + i),dataSize)==0){
	    ScanResult res;
	    //printf("memScan found\n");
	    res.addr = i;
	    result.push_back(res);
	}
    }
}

void ProcessScanner::dump(unsigned int targetAddr,int size)
{
    unsigned char *buffer = (unsigned char *)malloc(size);
    read(targetAddr,size,(unsigned int)buffer);
    logger->logHex(buffer,size);
    free(buffer);
}