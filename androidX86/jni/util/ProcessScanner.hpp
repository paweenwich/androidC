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
//#include <string>
#include "PtraceUtil.hpp"
#include "util.hpp"


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

class SnapShotResult{
public:
    unsigned int addr;
    unsigned char data[4];
};

bool ascendingAddr(const SnapShotResult& guy1, const SnapShotResult& guy2);

class ISnapShotData {
public:
    unsigned int startAddr;
    unsigned int size;
    virtual std::vector<SnapShotResult> findInt32(unsigned int) =0;
    virtual std::vector<SnapShotResult> findBinary(std::vector<unsigned char>)=0;
};

class SnapShotData: public ISnapShotData {
public:
    void *buf;
    void *GetVirtualAddress(unsigned int addr){
	unsigned char *ptr = (unsigned char *)buf;
	return &ptr[addr - startAddr];
    }
    std::vector<SnapShotResult> findInt32(unsigned int);
    std::vector<SnapShotResult> findBinary(std::vector<unsigned char>);
};

class SnapShotFileData: public SnapShotData {
public:
    FileMap fileMap;
    SnapShotFileData(std::string fileName){
	fileMap = FileMap();
	//printf("%d %d\n",size,fileMap.filesize);
	std::string sAddr = SplitByChar(SplitByChar(fileName,'/').back(),'-')[0];
	//std::string s = StringReplaceChar(onlyFileName,'-',' ');
	//std::string sAddr = SplitByChar(s,' ')[0];
	sscanf(sAddr.c_str(),"%X",&startAddr);
	buf = fileMap.map(fileName);
	size = fileMap.filesize;	
    }
};


class SnapShot {
public:
    std::vector<SnapShotData> vData;
    std::vector<SnapShotResult> findInt32(unsigned int);
    std::vector<SnapShotResult> findBinary(std::vector<unsigned char>);
    static std::vector<SnapShotResult> readFromFile(char *fileName);
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
    std::vector<ProcMapData> getHeap();
    std::vector<ProcMapData> getWriteable();
    std::vector<ProcMapData> getNotExecute();
    std::vector<ProcMapData> getAll();
    bool buffToFile(unsigned int bufferAddr,int size,char *fileName);
    static void memScan(unsigned int dataAddr,int dataSize,unsigned int memAddr,int memSize,std::vector<ScanResult> &result,int step);
private:

};

#endif /* PROCESSSCANNER_HPP */

