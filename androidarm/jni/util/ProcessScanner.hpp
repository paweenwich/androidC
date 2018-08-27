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
#include "MonoMockUp.hpp"

#ifndef PROCESSSCANNER_HPP
#define PROCESSSCANNER_HPP

class ProcessScanner;

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

class ScanData {
public:
    unsigned char data[64];
    int size;
    ScanData(){
	size = 0;
	memset(&data,0,sizeof(data));
    }
};

class ScanResult {
public:
    ScanData scanData;
    unsigned int addr;
    void show(){
	printf("%08X\n",addr);
    }
    ScanResult(){
        addr = 0;
    }
};

class MonoClassScanResult {
public:
    unsigned int addr;
    char name[128];
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

class ScanDataCache {
public:
    int pid;
    std::vector<ScanResult> cache;
    void load(int pid);
    void save();
    ScanResult get(ScanData scandata);
    void put(ScanResult result);
};

class ClassDataCacheData {
public:
    char name[128];
    unsigned int classAddr;
    unsigned int vTableAddr;
    ClassDataCacheData();
};

class ClassDataCache {
public:
    int pid;
    std::vector<ClassDataCacheData> cache;
    void load(int pid);
    void save();
    ClassDataCacheData get(char *name);
    ClassDataCacheData get(unsigned int classAddr);
    void put(ClassDataCacheData classData);
    void update(unsigned int classAddr,unsigned int vTableAddr);
};

class MonoArrayData: public MonoArray {
public:
    std::vector<unsigned int> vAddr;
    unsigned int get(int index);
};

class MonoTypeData: public MonoType
{
public:
    unsigned int thisAddr;
    void show(ProcessScanner &pscan);
    static char *GetTypeName(int typeEnum);
};

class MonoClassFieldData: public MonoClassField {
public:    
    unsigned int thisAddr;
    MonoTypeData typeData;
    void init(ProcessScanner &pscan);
    void show(ProcessScanner &pscan);
    MonoClassFieldData(){
	thisAddr = 0;
    }
    bool isInit(){
	return thisAddr != 0;
    }    
};

class MonoClassData: public MonoClass {
public:
    unsigned int thisAddr;
    void show(ProcessScanner &pscan);
    bool isValid(ProcessScanner &pscan);
    MonoClassData(){
	thisAddr = 0;
    }
    bool isInit(){
	return thisAddr != 0;
    }
    MonoClassFieldData GetField(ProcessScanner& pscan,char *name);
    std::string ToCClass(ProcessScanner& pscan);
    std::vector<MonoClassFieldData> GetInstanceFields(ProcessScanner& pscan);
    std::vector<MonoClassFieldData> GetFields(ProcessScanner& pscan);
};





class MonoVTableData: public MonoVTable
{
public:
    unsigned int thisAddr;
    MonoClassData classData;
    void show(ProcessScanner &pscan);
    unsigned int GetStaticInt(ProcessScanner &pscan,char *varName);
    MonoVTableData(){
	thisAddr = 0;
    }    
    bool isInit(){
	return thisAddr != 0;
    }
};

class MonoMethodData: public MonoMethod
{
public:
    unsigned int thisAddr;
    void show(ProcessScanner &pscan);
};

class MonoObjectData: public MonoObject
{
public:
    unsigned int thisAddr;
    void show(ProcessScanner &pscan);
    char *GetName(ProcessScanner& pscan);
    MonoVTableData GetVTable(ProcessScanner& pscan);
};

class MonoList: public MonoObject
{
public:
    MonoArray* _items;
    unsigned int _size;
    unsigned int _version;  
    MonoArrayData readData(ProcessScanner& pscan);
};


#define MODE_HEX    0
#define MODE_INT    1

class ProcessScanner {
public:
    Logger *logger;
    //PtraceUtil ptraceUtil;
    int pid;
    FILE *f;
    std::vector<ProcMapData> vProcMap;
    std::vector<MonoClassScanResult> vMonoClasses;
    std::vector<unsigned int> vFindObjectResult;
    //std::set<unsigned int> sDomains;
    unsigned int System_MonoType_Addr;
    ScanDataCache cache;
    ClassDataCache classCache;
    ProcessScanner();
    virtual ~ProcessScanner();
    bool open(int _pid);
    void openFile();
    void Stop();
    void Continue();
    void close();
    void readMap();
    void scanAll(unsigned int dataAddr,int dataSize,std::vector<ScanResult> &result,bool writeAble);
    void scanRange(unsigned int startRange,unsigned int endRange,unsigned int dataAddr,int dataSize,std::vector<ScanResult> &result,bool writeAble);
    void scanRange(unsigned int startRange,unsigned int endRange,std::vector<ScanData> &vData,std::vector<ScanResult> &result,int step,bool writeAble);
    bool read(unsigned int targetAddr,int size,unsigned int bufferAddr);
    template<typename T>
    T read(unsigned int targetAddr){
	T cd;
	read(targetAddr,sizeof(cd),(unsigned int)&cd);
	return cd;
    }
    bool readInt(unsigned int targetAddr,unsigned int &data);
    
    bool readByPtrace(unsigned int targetAddr,int size,unsigned int bufferAddr);
    bool write(unsigned int targetAddr,int size,unsigned int bufferAddr);
    bool writeAll(std::vector<WriteData> &vData);
    void dump(unsigned int targetAddr,int size,int DumpMode=MODE_HEX);
    static void memScan(unsigned int dataAddr,int dataSize,unsigned int memAddr,int memSize,std::vector<ScanResult> &result,int step);
    char * readMonoString(unsigned int monoObjAddr);
    char * readMonoClassName(unsigned int monoClassAddr);
    char * readCString(unsigned int monoClassAddr);
    MonoClassData readMonoClass(unsigned int monoClassAddr);
    void MonoClassScan();
    unsigned int MonoFindClass(char *className);
    unsigned int MonoFindVtable(unsigned int classAddr);
    void MonoFindObject(unsigned int vTableAddr);
    unsigned int IntFromHex(char *hex);
    unsigned int ReadInt(unsigned int targetAddr);
    bool isDataAddress(unsigned int addr);
    MonoArrayData readMonoArray(unsigned int monoAddr);
    MonoClassFieldData readMonoClassField(unsigned int monoAddr);
    MonoTypeData readMonoType(unsigned int monoAddr);
    MonoVTableData readMonoVTable(unsigned int monoAddr);
    MonoMethodData readMonoMethod(unsigned int monoAddr);
    MonoObjectData readMonoObject(unsigned int monoAddr);
    template<typename T>
    T GetStaticClassField(MonoVTableData &monoVTable,char *fieldName){
	T ret;
	if(!monoVTable.classData.isInit()){
	    monoVTable.classData = readMonoClass((unsigned int)monoVTable.klass);
	}
	MonoClassFieldData fd = monoVTable.classData.GetField(*this,fieldName);
	if(fd.isInit()){
	    unsigned int dataAddr = (unsigned int) monoVTable.data + fd.offset;
	    read(dataAddr,sizeof(ret),(unsigned int)&ret);
	}else{
	    printf("GetStaticClassField: Not found %s\n",fieldName);
	}
	return ret;
    }
    
    unsigned int GetStaticClassFieldInt(char *className,char *fieldName);
    unsigned short GetStaticClassFieldShort(char *className,char *fieldName);
    unsigned char GetStaticClassFieldByte(char *className,char *fieldName);
    char *GetStaticClassFieldCString(char *className,char *fieldName);
    unsigned int GetInstanceClassFieldInt(unsigned int objAddr,char *className,char *fieldName);
    MonoVTableData GetClassVTable(char *className);
    MonoClassData GetClassData(char *className);
    char *GetInstanceClassName(unsigned int instanceAddr);
    char *GetVTableClassName(unsigned int vTableAddr);
    template<typename T>
    bool PutInstanceClassField(unsigned int objAddr,char *className,char *fieldName,T value)
    {
	unsigned int classAddr = MonoFindClass(className);
	if(classAddr!=0){
	    MonoClassData classData = this->readMonoClass(classAddr);
	    MonoClassFieldData fd = classData.GetField(*this,fieldName);
	    if(fd.isInit()){
		unsigned int dataAddr = objAddr + fd.offset;
		this->write(dataAddr,sizeof(value),(unsigned int)&value);
		return true;
	    }else{
		printf("PutInstanceClassField: Not found %s.%s\n",className,fieldName);
	    }
	}
	return false;
    };
    bool PutInstanceClassFieldInt(unsigned int objAddr,char *className,char *fieldName,unsigned int value);    
    bool PutInstanceClassFieldShort(unsigned int objAddr,char *className,char *fieldName,unsigned short value);    
    bool PutInstanceClassFieldByte(unsigned int objAddr,char *className,char *fieldName,unsigned char value);    

private:

};


#endif /* PROCESSSCANNER_HPP */

