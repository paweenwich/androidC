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


void ScanDataCache::load(int _pid)
{
    pid = _pid;
    char fileName[64];
    sprintf(fileName,"%d.cache",pid);
    
    FILE *f = fopen(fileName,"rb");
    if(f!=NULL){
        int num;
        fread(&num,sizeof(num),1,f);
        for(int i=0;i<num;i++){
            ScanResult data;
            if(fread(&data,sizeof(data),1,f)==1){
                cache.push_back(data);
            }
        }
	printf("ScanDataCache Cache size = %d\n",cache.size());
        fclose(f);
    }
}
void ScanDataCache::save()
{
    char fileName[64];
    sprintf(fileName,"%d.cache",pid);
    
    FILE *f = fopen(fileName,"wb");
    if(f!=NULL){
        int num = cache.size();
        fwrite(&num,sizeof(num),1,f);
        for(int i=0;i<num;i++){
            ScanResult data = cache[i];
            if(fwrite(&data,sizeof(data),1,f)==1){

            }
        }
        fclose(f);
    }    
}

ScanResult ScanDataCache::get(ScanData scandata)
{
    ScanResult ret;
    for(int i=0;i<cache.size();i++){
        if(memcmp(&scandata,&(cache[i].scanData),sizeof(ScanData))==0){
            return cache[i];
        }
    }
    return ret;
}

void ScanDataCache::put(ScanResult scanResult)
{
    ScanResult ret = get(scanResult.scanData);
    if(ret.addr == 0){
        cache.push_back(scanResult);
        //save();
    }
}


//----------------------------------------------------------------

ClassDataCacheData::ClassDataCacheData()
{
    classAddr = 0;
    vTableAddr = 0;
    name[0] = 0;
}

void ClassDataCache::load(int _pid)
{
    pid = _pid;
    char fileName[64];
    sprintf(fileName,"%d.classcache",pid);
    FILE *f = fopen(fileName,"rb");
    if(f!=NULL){
        int num;
        fread(&num,sizeof(num),1,f);
        for(int i=0;i<num;i++){
            ClassDataCacheData data;
            if(fread(&data,sizeof(data),1,f)==1){
                cache.push_back(data);
            }
        }
	printf("ClassDataCache Cache size = %d\n",cache.size());
        fclose(f);
    }
}
void ClassDataCache::save()
{
    char fileName[64];
    sprintf(fileName,"%d.classcache",pid);
    
    FILE *f = fopen(fileName,"wb");
    if(f!=NULL){
        int num = cache.size();
        fwrite(&num,sizeof(num),1,f);
        for(int i=0;i<num;i++){
            ClassDataCacheData data = cache[i];
            if(fwrite(&data,sizeof(data),1,f)==1){

            }
        }
        fclose(f);
    }    
}

ClassDataCacheData ClassDataCache::get(char *name)
{
    ClassDataCacheData ret;
    for(int i=0;i<cache.size();i++){
        //printf("ClassDataCache [%s] [%s]\n",name,cache[i].name);
        if(strcmp(cache[i].name,name)==0){
            return cache[i];
        }
    }
    return ret;
}

ClassDataCacheData ClassDataCache::get(unsigned int classAddr)
{
    ClassDataCacheData ret;
    for(int i=0;i<cache.size();i++){
        if(classAddr ==cache[i].classAddr){
            return cache[i];
        }
    }
    return ret;    
}

void ClassDataCache::put(ClassDataCacheData data)
{
    ClassDataCacheData ret = get(data.name);
    if(ret.classAddr == 0){
        cache.push_back(data);
        save();
    }
}

void ClassDataCache::update(unsigned int classAddr,unsigned int vTableAddr)
{
    for(int i=0;i<cache.size();i++){
        if(classAddr ==cache[i].classAddr){
            cache[i].vTableAddr = vTableAddr;
            save();
            break;
        }
    }
}
