/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProcessScanner.hpp
 * Author: kwang
 *
 * Created on August 25, 2016, 8:25 AM
 */

#include "PtraceUtil.hpp"

#ifndef PROCESSSCANNER_HPP
#define PROCESSSCANNER_HPP

class ProcMapData {
public:
    unsigned int startAddr;
    unsigned int endAddr;
    char protection[8];
    char desc[256];
    unsigned int size(){
	return (endAddr - startAddr);
    }
    bool isCanWrite(){
	return strstr(protection,"w")!=NULL;
    }
    void show(){
	printf("%08X %08X %s %s\n",startAddr,endAddr,protection,desc);
    }
};

class ScanResult {
public:
    unsigned int addr;
    void show(){
	printf("%08X\n",addr);
    }
};

class ScanData {
public:
    unsigned char data[64];
    int size;
};

class WriteData {
public:
    unsigned int addr;
    unsigned char data[512];
    int size;
    void load(unsigned int address,unsigned char * pdata,int dataSize){
	addr = address;
	memcpy(data,pdata,dataSize);
	size = dataSize;
    }
};

class ProcessScanner {
public:
    Logger *logger;
    //PtraceUtil ptraceUtil;
    int pid;
    FILE *f;
    std::vector<ProcMapData> vProcMap;
    ProcessScanner();
    virtual ~ProcessScanner();
    bool open(int _pid);
    void openFile();
    void close();
    void readMap();
    void scanAll(unsigned int dataAddr,int dataSize,std::vector<ScanResult> &result,bool writeAble);
    void scanRange(unsigned int startRange,unsigned int endRange,unsigned int dataAddr,int dataSize,std::vector<ScanResult> &result,bool writeAble);
    void scanRange(unsigned int startRange,unsigned int endRange,std::vector<ScanData> &vData,std::vector<ScanResult> &result,int step,bool writeAble);
    bool read(unsigned int targetAddr,int size,unsigned int bufferAddr);
    bool write(unsigned int targetAddr,int size,unsigned int bufferAddr);
    bool writeAll(std::vector<WriteData> &vData);
    void dump(unsigned int targetAddr,int size);
    static void memScan(unsigned int dataAddr,int dataSize,unsigned int memAddr,int memSize,std::vector<ScanResult> &result,int step);
private:

};

#endif /* PROCESSSCANNER_HPP */

