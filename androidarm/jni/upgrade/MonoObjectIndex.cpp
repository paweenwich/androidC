/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MonoObjectIndex.cpp
 * Author: kwang
 * 
 * Created on September 2, 2016, 8:37 AM
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

#include <string>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include "../util/logger.h"
#include "../util/util.hpp"
#include "MonoObjectIndex.hpp"

void CharacterDataIndexManager::load(int _pid)
{
    pid = _pid;
    char fileName[64];
    sprintf(fileName,"%d.index",pid);
    
    FILE *f = fopen(fileName,"rb");
    if(f!=NULL){
        int num;
        fread(&num,sizeof(num),1,f);
        for(int i=0;i<num;i++){
            CharacterDataIndex data;
            if(fread(&data,sizeof(data),1,f)==1){
                index.push_back(data);
            }
        }
	printf("Index size = %d\n",index.size());
        fclose(f);
    }    
}

void CharacterDataIndexManager::save()
{
    char fileName[64];
    sprintf(fileName,"%d.index",pid);
    
    FILE *f = fopen(fileName,"wb");
    if(f!=NULL){
        int num = index.size();
        fwrite(&num,sizeof(num),1,f);
        for(int i=0;i<num;i++){
            CharacterDataIndex data = index[i];
            if(fwrite(&data,sizeof(data),1,f)==1){

            }
        }
        fclose(f);
    }    
}

unsigned int CharacterDataIndexManager::get(int creatureID)
{
    for(int i=0;i<index.size();i++){
        if(index[i].creatureId == creatureID){
            return index[i].addr;
        }
    }
    return 0;    
}

void CharacterDataIndexManager::put(int creatureID,unsigned int addr)
{
    if(get(creatureID)==0){
	CharacterDataIndex data;
	data.addr = addr;
	data.creatureId = creatureID;
	index.push_back(data);
    }
}
