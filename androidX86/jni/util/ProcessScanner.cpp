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
	return false;
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

std::vector<ProcMapData> ProcessScanner::getHeap()
{
    std::vector<ProcMapData> ret;
    for(int i=0;i<vProcMap.size();i++){
	if(strcmp(vProcMap[i].desc,"[heap]")==0){
	    ret.push_back(vProcMap[i]);
	}
    }
    return ret;
}

std::vector<ProcMapData> ProcessScanner::getWriteable()
{
    std::vector<ProcMapData> ret;
    for(int i=0;i<vProcMap.size();i++){
	if(strcmp(vProcMap[i].protection,"rw-p")==0){
	    ret.push_back(vProcMap[i]);
	}
    }
    return ret;
}

std::vector<ProcMapData> ProcessScanner::getNotExecute()
{
    std::vector<ProcMapData> ret;
    for(int i=0;i<vProcMap.size();i++){
	if(strcmp(vProcMap[i].protection,"r--p")==0){
	    ret.push_back(vProcMap[i]);
	}
    }
    return ret;
}

std::vector<ProcMapData> ProcessScanner::getAll()
{
    std::vector<ProcMapData> ret;
    for(int i=0;i<vProcMap.size();i++){
	ret.push_back(vProcMap[i]);
    }
    return ret;
}

bool ProcessScanner::buffToFile(unsigned int bufferAddr,int size,char *fileName)
{
    FILE *f = fopen(fileName,"wb");
    if(f!=NULL){
	int numWrite = fwrite((void *)bufferAddr,size,1,f);
	fclose(f);
	return numWrite > 0;
    }
    return false;
}


std::vector<SnapShotResult> SnapShotData::findInt32(unsigned int data)
{
    std::vector<SnapShotResult> ret;
    unsigned int *iptr = (unsigned int *)buf;
    for(int i=0;i<size/4;i++){
	if(iptr[i] == data){
	    SnapShotResult r;
	    r.addr = startAddr + (i*4);
	    memcpy(r.data,&iptr[i],sizeof(int));
	    ret.push_back(r);
	}
    }
    return ret;
}

std::vector<SnapShotResult> SnapShot::findInt32(unsigned int data)
{
    std::vector<SnapShotResult> ret;
    for(int i=0;i<vData.size();i++){
	std::vector<SnapShotResult> tmp = vData[i].findInt32(data);
	ret.insert(ret.end(),tmp.begin(),tmp.end());
    }
    return ret;
}

std::vector<SnapShotResult> SnapShotData::findBinary(std::vector<unsigned char> data)
{
    //printf("SnapShotData::findBinary %d %d %08X\n",data.size(),size,(unsigned int)buf);
    std::vector<SnapShotResult> ret;
    unsigned char *ptr = (unsigned char *)buf;
    for(int i=0;i<size - data.size();i++){
	//printf("%d\n",i);
	if(ptr[i] == data[0]){
	    if(memcmp(&ptr[i],data.begin(),data.size())==0){
		SnapShotResult r;
    		r.addr = startAddr + i;
		ret.push_back(r);
	    }
	}
    }
    return ret;
}

std::vector<SnapShotResult> SnapShot::findBinary(std::vector<unsigned char> data)
{
    std::vector<SnapShotResult> ret;
    for(int i=0;i<vData.size();i++){
	std::vector<SnapShotResult> tmp = vData[i].findBinary(data);
	ret.insert(ret.end(),tmp.begin(),tmp.end());
    }
    return ret;
}

std::vector<SnapShotResult> SnapShot::readFromFile(char *fileName)
{
    std::vector<SnapShotResult> ret;
    FILE *f = fopen(fileName,"rb");
    if(f!=NULL){
	SnapShotResult data;
	while(fread(&data,sizeof(SnapShotResult),1,f)>0){
	    ret.push_back(data);
	}
	fclose(f);
    }
    return ret;
}

bool ascendingAddr(const SnapShotResult& guy1, const SnapShotResult& guy2) {
  return guy1.addr < guy2.addr;
}

