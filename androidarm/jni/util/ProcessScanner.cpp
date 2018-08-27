
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
#include <signal.h>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
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
    cache.load(pid);
    classCache.load(pid);
    Stop();
    return(f!=NULL);
}

void ProcessScanner::close()
{
    if(f!=NULL){
	fclose(f);
	Continue();	
	f = NULL;
    }
}

void ProcessScanner::Stop()
{
    kill(pid,SIGSTOP);	
}
void ProcessScanner::Continue()
{
    kill(pid,SIGCONT);
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
    vData.push_back(sd);
    scanRange(startRange,endRange,vData,result,1,writeAble);
}



void ProcessScanner::scanRange(unsigned int startRange,unsigned int endRange,std::vector<ScanData> &_vData,std::vector<ScanResult> &result,int step, bool writeAble)
{
    // check if we found this on cache
    std::vector<ScanData> vData(_vData);
    std::vector<int> vFoundIndex;
    for(int i=_vData.size()-1;i>=0;i--){
	ScanResult res = cache.get(_vData[i]);
	if(res.addr!=0){
	    // found
	    vFoundIndex.push_back(i);
	    // add result
	    //printf("Found in cache %08X\n",res.addr);
	    result.push_back(res);
	    //remove from tmp
	    vData.erase(vData.begin() + i);
	}
    }
    printf("Found %d/%d in cache\n",result.size(),_vData.size());
    
    for(int i=0;(i<vProcMap.size()) && (vData.size() > 0);i++){
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
	    if(read(p->startAddr,memSize,(unsigned int)buffer)){
                for(int j=0;j<vData.size();j++){
                    ScanData sd = vData[j];
                    std::vector<ScanResult> sresult;		
                    memScan((unsigned int)sd.data,sd.size,(unsigned int)buffer,memSize,sresult,step);
                    for(int i=0;i<sresult.size();i++){
                        ScanResult res;
                        printf("%d Found at = %08X\n",i, p->startAddr + sresult[i].addr);
			res.scanData = sd;
                        res.addr = p->startAddr + sresult[i].addr;
                        //cache.put(sd,res);
                        result.push_back(res);
                    }
                }
            }
	    free(buffer);
	}else{
	    printf("scanAll: malloc can not alocate %d\n",memSize);
	}
    }    
    // 1:1 match
    if(vData.size() == result.size()){
	for(int j=0;j<result.size();j++){
	    cache.put(result[j]);
	}
	cache.save();
    }
    //ptraceUtil.Detach();
}

bool ProcessScanner::readInt(unsigned int targetAddr,unsigned int &data)
{
    return read(targetAddr,4,(unsigned int)&data);
}

unsigned int ProcessScanner::ReadInt(unsigned int targetAddr)
{
    unsigned int ret;
    readInt(targetAddr,ret);
    return ret;
}

bool ProcessScanner::read(unsigned int targetAddr,int size,unsigned int bufferAddr)
{
    if(fseek(f,targetAddr,SEEK_SET)!=0){
	printf("seek %08X fail: %s\n",targetAddr,strerror(errno));
	return false;
    }
    if(fread((void *)bufferAddr,size,1,f)!=1){
        if(!readByPtrace(targetAddr,size,(unsigned int)bufferAddr)){
            //printf("read %08X for %d fail: %s\n",targetAddr,size,strerror(errno));
        }
        return false;
    }
    return true;
}

bool ProcessScanner::readByPtrace(unsigned int targetAddr,int size,unsigned int bufferAddr)
{
    PtraceUtil ptraceUtil;
    ptraceUtil.Attach(pid);
    ptraceUtil.waitForStop();
    bool ret = ptraceUtil.ReadProcessMemory(targetAddr,(unsigned char *)bufferAddr,size);
    ptraceUtil.Detach();
    return ret;
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

void ProcessScanner::dump(unsigned int targetAddr,int size,int dumpMode)
{
    unsigned char *buffer = (unsigned char *)malloc(size);
    read(targetAddr,size,(unsigned int)buffer);
    if(dumpMode == MODE_HEX){
        logger->logHex(buffer,size);
    }else if(dumpMode == MODE_INT){
        unsigned int *p = (unsigned int*) buffer;
        char tmp[1024];
        for(int i=0;i< size/sizeof(int);i++){
            sprintf(tmp,"0x%08X 0x%08X\t%d",targetAddr + (i*sizeof(int)),p[i],p[i]);
            logger->logRaw(tmp);
        }
    }
    free(buffer);
}

char * ProcessScanner::readMonoString(unsigned int monoObjAddr)
{
    static char out[512];
    memset(out,0,sizeof(out));
    unsigned char buf[1024];
    read(monoObjAddr,sizeof(buf),(unsigned int)&buf[0]);
    MonoString *pMonoString = (MonoString *)&buf[0];
    //printf("readMonoString size=%ld\n",pMonoString->length);
    int maxChar = pMonoString->length;
    if(maxChar > 512){ 
	maxChar =511;
    }
    if(pMonoString->length > 0){
    
    for(int i=0;i<maxChar ;i++){
	out[i] = pMonoString->chars[i];
    }
    out[maxChar] = 0;
    //printf("readMonoString %s\n",out);
    //logger->logHex((unsigned char *)&out[0],64);
    }
    return &out[0];
}

MonoClassData ProcessScanner::readMonoClass(unsigned int monoClassAddr)
{
    MonoClassData ret;
    read(monoClassAddr,sizeof(MonoClass),(unsigned int)&ret);
    ret.thisAddr = monoClassAddr;
    return ret;
}

MonoArrayData ProcessScanner::readMonoArray(unsigned int monoArrayAddr)
{
    MonoArrayData ret;
    ret.max_length = 0;
    read(monoArrayAddr,16,(unsigned int)&ret);
    if(ret.max_length>0){
	printf("readMonoArray size=%ld\n",ret.max_length);
	//read all data
	unsigned int *vAddr = (unsigned int *)malloc(ret.max_length * sizeof(int));
	read(monoArrayAddr + 16,ret.max_length * sizeof(int),(unsigned int)vAddr);
	for(int i=0;i<ret.max_length;i++){
	    ret.vAddr.push_back(vAddr[i]);
	    //printf("%08X\n",vAddr[i]);
	}
	free(vAddr);
    }
    return ret;
}


MonoClassFieldData ProcessScanner::readMonoClassField(unsigned int monoAddr)
{
    MonoClassFieldData ret;
    read(monoAddr,sizeof(MonoClassField),(unsigned int)&ret);
    ret.thisAddr = monoAddr;
    ret.init(*this);
    return ret;
}

MonoTypeData ProcessScanner::readMonoType(unsigned int monoAddr)
{
    MonoTypeData ret;
    read(monoAddr,sizeof(MonoType),(unsigned int)&ret);
    ret.thisAddr = monoAddr;
    return ret;
}

MonoVTableData ProcessScanner::readMonoVTable(unsigned int monoAddr)
{
    MonoVTableData ret;
    if(read(monoAddr,sizeof(MonoVTable),(unsigned int)&ret)){
	ret.thisAddr = monoAddr;
    }
    return ret;    
}

MonoMethodData ProcessScanner::readMonoMethod(unsigned int monoAddr)
{
    MonoMethodData ret;
    read(monoAddr,sizeof(MonoMethodData),(unsigned int)&ret);
    ret.thisAddr = monoAddr;
    return ret;    
}

MonoObjectData ProcessScanner::readMonoObject(unsigned int monoAddr)
{
    MonoObjectData ret;
    read(monoAddr,sizeof(MonoObjectData),(unsigned int)&ret);
    ret.thisAddr = monoAddr;
    return ret; 
}

char * ProcessScanner::readCString(unsigned int addr)
{
    static char out[512];
    memset(out,0,sizeof(out));
    read(addr,sizeof(out)-1,(unsigned int)&out[0]);
    return &out[0];
}

char * ProcessScanner::readMonoClassName(unsigned int monoClassAddr)
{
    static char out[512];
    memset(out,0,sizeof(out));
    if(this->isDataAddress(monoClassAddr)){
	MonoClassData monoClass =  readMonoClass(monoClassAddr);
	if(monoClass.isValid(*this)){
	    char strName[128];
	    char strNameSpace[128];
	    strcpy(strName,readCString((unsigned int)monoClass.name));
	    strcpy(strNameSpace,readCString((unsigned int)monoClass.name_space));
	    if(strlen(strNameSpace)!=0){
		sprintf(out,"%s.%s",strNameSpace,strName);
	    }else{
		
		if((unsigned int)monoClass.nested_in!=0){
		    char strNestedClass[128];
		    strcpy(strNestedClass,readMonoClassName((unsigned int)monoClass.nested_in));
		    sprintf(out,"%s.%s",strNestedClass,strName);
		}else{
		    sprintf(out,"%s",strName);
		}
	    }
	    //printf("className=[%s]\n",out);
	}else{
	    //printf("SKIP: not valid class address\n");
	}
    }
    return &out[0];
}


unsigned int ProcessScanner::IntFromHex(char *hex)
{
    unsigned int h[4];
    unsigned char c[4];
    sscanf(hex,"%x %x %x %x",&h[0],&h[1],&h[2],&h[3]);
    for(int i=0;i<4;i++){
	c[i] = h[i];
    }
    unsigned int *p = (unsigned int *)&c[0];
    return *p;
}

bool ProcessScanner::isDataAddress(unsigned int addr)
{
    for(int i=0;i<vProcMap.size();i++){
	ProcMapData *p = &vProcMap[i];
	if(!p->isCanWrite()){
	    continue;
	}
	if((addr >= p->startAddr)&&(addr <= p->endAddr)){
	    return true;
	}
	
    }
    return false;
}

void ProcessScanner::MonoClassScan()
{
   std::set<unsigned int> sVTableAddr;
   vMonoClasses.clear();
   for(int i=0;i<vProcMap.size();i++){
	ProcMapData *p = &vProcMap[i];
	if(!p->isCanWrite()){
	    continue;
	}
	unsigned int memSize = p->size();
	unsigned char *buffer = (unsigned char*)malloc(memSize);
	if(buffer!=NULL){
	    if(read(p->startAddr,memSize,(unsigned int)buffer)){
		unsigned int *pInt = (unsigned int *)buffer;
                for(int j=0;j<memSize/sizeof(int);j++){
		    unsigned int currentAddr = p->startAddr + (j*sizeof(int));
		    if(pInt[j] == currentAddr){
			MonoClass *monoClass = (MonoClass *)&pInt[j];
			if((monoClass->instance_size >0) 
				&&(monoClass->instance_size < 512)
				&&(isDataAddress((unsigned int)monoClass->parent)) 
				&&(monoClass->idepth <10 ) 
			){
			    char *className = readMonoClassName(currentAddr);
			    if(strlen(className)==0) continue;
			    /*printf("MonoClass found at %08X %s %08X %d %d vtable=%08X %d\n",
				    currentAddr,className,
				    (unsigned int)monoClass->parent,
				    monoClass->idepth,
				    monoClass->rank,
				    (unsigned int)monoClass->vtable,
				    monoClass->vtable_size
			    );
			    logger->logHex((unsigned char*)&pInt[j],64);
			    */
			    MonoClassScanResult rs;
			    rs.addr = currentAddr;
			    strcpy(rs.name,className);
			    vMonoClasses.push_back(rs);
			    if(strcmp(className,"System.MonoType")==0){
				System_MonoType_Addr = currentAddr;
			    }
			    /*if(vClassAddr.size()>100){
				i=100000000;
				break;
			    }*/
			}
			//sVTableAddr.insert((unsigned int)monoObject->vtable);
		    }
                }
            }
	    free(buffer);
	}else{
	    printf("MonoClassScan: malloc can not alocate %d\n",memSize);
	}
    }        
   printf("Class scan found %d objects\n",vMonoClasses.size());
   printf("System.MonoType = 0x%08X\n",System_MonoType_Addr);
   for(std::set<unsigned int>::iterator i = sVTableAddr.begin(); i != sVTableAddr.end(); i++) {
	unsigned int vTableAddr = *i;
	//printf("vtable = %08X\n",vTableAddr);
   }
}

unsigned int ProcessScanner::MonoFindClass(char *className)
{
    ClassDataCacheData ret = classCache.get(className);
    if(ret.classAddr!=0){
        printf("MonoFindClass %s cahce found\n",className);
        return ret.classAddr;
    }
    if(vMonoClasses.size()==0){
	MonoClassScan();
    }
    for(int i=0;i<vMonoClasses.size();i++){
	if(strcmp(className,vMonoClasses[i].name)==0){
            ClassDataCacheData d;
            strcpy(d.name,className);
            d.classAddr = vMonoClasses[i].addr;
            d.vTableAddr = 0;
            classCache.put(d);
	    return vMonoClasses[i].addr;
	}
    }
    return 0;
}
unsigned int ProcessScanner::MonoFindVtable(unsigned int classAddr)
{
    ClassDataCacheData ret = classCache.get(classAddr);
    if(ret.vTableAddr!=0){
        printf("MonoFindVtable %08X cahce found\n",classAddr);
        return ret.vTableAddr;
    }    
    if(vMonoClasses.size()==0){
	MonoClassScan();
    }    
    for(int i=0;i<vProcMap.size();i++){
	ProcMapData *p = &vProcMap[i];
	if(!p->isCanWrite()){
	    continue;
	}
	unsigned int memSize = p->size();
	unsigned char *buffer = (unsigned char*)malloc(memSize);
	if(buffer!=NULL){
	    if(read(p->startAddr,memSize,(unsigned int)buffer)){
		unsigned int *pInt = (unsigned int *)buffer;
                for(int j=0;j<memSize/sizeof(int);j++){
		    unsigned int currentAddr = p->startAddr + (j*sizeof(int));
		    if(pInt[j] == classAddr){
			MonoVTable *monoVtable = (MonoVTable *)&pInt[j];
			//printf("Found possible vtable at 0x%08X %d %d %08X\n",currentAddr,
			//	monoVtable->max_interface_id,
			//	monoVtable->rank,
			//	(unsigned int)monoVtable->type
			//);
			//logger->logHex((unsigned char*)&pInt[j],sizeof(MonoVTable));
			//if((unsigned int)monoVtable->domain  == 0) continue;
			//if((unsigned int)monoVtable->interface_bitmap  == 0) continue;
			if((unsigned int) monoVtable->data!=0){
			    if(!isDataAddress((unsigned int)monoVtable->data)){
				continue;
			    }
			}
			if((unsigned int) monoVtable->domain!=0){
			    if(!isDataAddress((unsigned int)monoVtable->domain)){
				continue;
			    }
			}
			if(isDataAddress((unsigned int)monoVtable->type)){
			    unsigned int typeAddr  = ReadInt((unsigned int)monoVtable->type);
			    if(isDataAddress(typeAddr)){
				unsigned int typeAddr2  = ReadInt(typeAddr);
				if((typeAddr2==System_MonoType_Addr)/*||((unsigned int)monoVtable->type == (unsigned int)monoVtable->klass)*/ ){
				    printf("Found vtable at 0x%08X %d %d %08X\n",currentAddr,
					    monoVtable->max_interface_id,
					    monoVtable->rank,
					    typeAddr
				    );
				    logger->logHex((unsigned char*)&pInt[j],sizeof(MonoVTable));
				    free(buffer);
                                    classCache.update(classAddr,currentAddr);
				    return(currentAddr);
				    //continue;
				}else{
                                    /*
				     printf("Found Possible vtable at 0x%08X %d %d %08X\n",currentAddr,
					    monoVtable->max_interface_id,
					    monoVtable->rank,
					    typeAddr
				    );
				    logger->logHex((unsigned char*)&pInt[j],sizeof(MonoVTable));
                                    */
				}
			    }
			}
		    }
                }
            }
	    free(buffer);
	}else{
	    printf("MonoFindVtable: malloc can not alocate %d\n",memSize);
	}
    }     
    return 0;
}

void ProcessScanner::MonoFindObject(unsigned int vTableAddr)
{
    if(vMonoClasses.size()==0){
	MonoClassScan();
    }    
    vFindObjectResult.clear();
    for(int i=0;i<vProcMap.size();i++){
	ProcMapData *p = &vProcMap[i];
	if(!p->isCanWrite()){
	    continue;
	}
	unsigned int memSize = p->size();
	unsigned char *buffer = (unsigned char*)malloc(memSize);
	if(buffer!=NULL){
	    if(read(p->startAddr,memSize,(unsigned int)buffer)){
		unsigned int *pInt = (unsigned int *)buffer;
                for(int j=0;j<memSize/sizeof(int);j++){
		    unsigned int currentAddr = p->startAddr + (j*sizeof(int));
		    if(pInt[j] == vTableAddr){
			MonoObject *monoObject = (MonoObject *)&pInt[j];
			if(monoObject->synchronisation!=0) continue;
			    printf("Found object at 0x%08X\n",currentAddr
			);
			logger->logHex((unsigned char*)&pInt[j],32);
			vFindObjectResult.push_back(currentAddr);
		    }
                }
            }
	    free(buffer);
	}else{
	    printf("MonoObjectScan: malloc can not alocate %d\n",memSize);
	}
    }        
    printf("MonoObjectScan 0x%08X found %d\n",vTableAddr,vFindObjectResult.size());
}

unsigned int ProcessScanner::GetStaticClassFieldInt(char *className,char *fieldName)
{
    MonoVTableData mv = GetClassVTable(className);
    if(mv.isInit()){
        unsigned int ret = mv.GetStaticInt(*this,fieldName);
        printf("Found static %s.%s = 0x%08X\n",className,fieldName,ret);
        return ret;
    }else{
	printf("Not Found Vtable %s\n",className);
    }
    return 0;
}

unsigned short ProcessScanner::GetStaticClassFieldShort(char *className,char *fieldName)
{
    MonoVTableData mv = GetClassVTable(className);
    if(mv.isInit()){
        unsigned short ret = (unsigned short) mv.GetStaticInt(*this,fieldName);
        printf("Found static %s.%s = 0x%04X\n",className,fieldName,ret);
        return ret;
    }
    return 0;
}
unsigned char ProcessScanner::GetStaticClassFieldByte(char *className,char *fieldName)
{
    MonoVTableData mv = GetClassVTable(className);
    if(mv.isInit()){
        unsigned char ret = (unsigned char)mv.GetStaticInt(*this,fieldName);
        printf("Found static %s.%s = 0x%02X\n",className,fieldName,ret);
        return ret;
    }
    return 0;
}

char *ProcessScanner::GetStaticClassFieldCString(char *className,char *fieldName)
{
    MonoVTableData mv = GetClassVTable(className);
    if(mv.isInit()){
        unsigned int strObjAddr = mv.GetStaticInt(*this,fieldName);
        char *ret = readMonoString(strObjAddr);
        printf("Found static %s.%s = [%s]\n",className,fieldName,ret);
        return ret;
    }
    return NULL;
}

unsigned int ProcessScanner::GetInstanceClassFieldInt(unsigned int objAddr,char *className,char *fieldName)
{
    unsigned int classAddr = MonoFindClass(className);
    if(classAddr!=0){
        MonoClassData classData = this->readMonoClass(classAddr);
        MonoClassFieldData fd = classData.GetField(*this,fieldName);
        if(fd.isInit()){
            unsigned int dataAddr = objAddr + fd.offset;
            unsigned int ret = this->ReadInt(dataAddr);
            printf("Found %s.%s at offset=%d addr=0x%08X value=0x%08X\n",className,fieldName,fd.offset,dataAddr,ret);            
            return ret;            
        }else{
            printf("Notfound %s.%s\n",className,fieldName);
        }
    }
    return 0;
}


bool ProcessScanner::PutInstanceClassFieldInt(unsigned int objAddr,char *className,char *fieldName,unsigned int value)
{
    return PutInstanceClassField(objAddr,className,fieldName,value);
}

bool ProcessScanner::PutInstanceClassFieldShort(unsigned int objAddr,char *className,char *fieldName,unsigned short value)
{
    return PutInstanceClassField(objAddr,className,fieldName,value);    
}

bool ProcessScanner::PutInstanceClassFieldByte(unsigned int objAddr,char *className,char *fieldName,unsigned char value)
{
    return PutInstanceClassField(objAddr,className,fieldName,value);
}

char *ProcessScanner::GetVTableClassName(unsigned int vTableAddr)
{
    MonoVTableData vtableData = this->readMonoVTable(vTableAddr);
    return(this->readMonoClassName((unsigned int)vtableData.klass));
}

char *ProcessScanner::GetInstanceClassName(unsigned int instanceAddr)
{
    MonoObject mo = read<MonoObject>(instanceAddr);
    return GetVTableClassName((unsigned int)mo.vtable);
}


MonoVTableData ProcessScanner::GetClassVTable(char *className)
{
    unsigned int classAddr = MonoFindClass(className);
    printf("%s classAddr = 0x%08X\n",className,classAddr);
    if(classAddr!=0){
	unsigned int vTableAddr = MonoFindVtable(classAddr);
	printf("%s vTableAddr = 0x%08X\n",className,vTableAddr);
	if(vTableAddr!=0){
	    MonoVTableData mv = readMonoVTable(vTableAddr);
            return mv;
        }
    }
    return MonoVTableData();
}

MonoClassData ProcessScanner::GetClassData(char *className)
{
    MonoClassData ret;
    unsigned int classAddr = MonoFindClass(className);
    printf("%s classAddr = 0x%08X\n",className,classAddr);
    if(classAddr!=0){
        ret = this->readMonoClass(classAddr);
    }
    return ret;
}


MonoArrayData MonoList::readData(ProcessScanner& pscan)
{
    MonoArrayData ret = pscan.readMonoArray((unsigned int)this->_items);
    return ret;
}