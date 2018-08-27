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
#include <algorithm>
#include <dirent.h>
#include "../util/logger.h"
#include "../util/util.hpp"
#include "../util/payload.hpp"
#include "../util/ProcessScanner.hpp"
#include "../luac/luascript.h"
#include "MonoObjectIndex.hpp"
#include "lua_upgrade.hpp"
#include "shell.hpp"
#include "upgrade.hpp"
extern unsigned int luaResultInt;

std::vector<std::string> LuaShell::ParseParam(char *line)
{
    std::vector<std::string> ret;
    
    char *ptr = line;
    std::string currentTok;
    bool flgOnBracket = false;
    while(*ptr){
	if((*ptr == ' ')&&(flgOnBracket == false)){
	    if(currentTok.size()>0){
		ret.push_back(currentTok);
		currentTok.clear();
	    }
	    ptr++;
	    continue;
	}else{
	    if(*ptr == '['){
		flgOnBracket = true;
		ptr++;
		continue;
	    }
	    if(*ptr == ']'){
		flgOnBracket = false;
		if(currentTok.size()>0){
		    ret.push_back(currentTok);
		    currentTok.clear();
		}
		ptr++;
		continue;
	    }
	    currentTok += *ptr;
	}
	ptr++;
    }
    if(currentTok.size()>0){
	ret.push_back(currentTok);
	currentTok.clear();
    }
    for(int i=0;i<ret.size();i++){
	//printf("[%s]\n",ret[i].c_str());
    }
    return ret;
}

unsigned int LuaShell::EvalInt(char *line)
{
    luaResultInt = 0;
    char cmd[1024];
    sprintf(cmd,"luaResultInt = %s",line);
    //printf("Eval [%s]\n",cmd);
    script->execString(cmd);
    return luaResultInt;
}

void LuaShell::GetInts(char *param,std::vector<unsigned int> &vints)
{
    char *pch = strtok (param,"-._:,/");
    while (pch != NULL)
    {
        unsigned int data = EvalInt(pch);
        /*if(strncmp(pch,"0x",2)==0){
            sscanf(pch+2,"%x",&data);
        }else{
            data = atoi(pch);
        }
        //printf("%08X\n",data);*/
        vints.push_back(data);
	pch = strtok (NULL,"-._:,/");
    }
}

void LuaShell::Dump(std::vector<std::string> &params)
{
    char cmd[64];
    strcpy(cmd,(char *)params[0].c_str());
    int dumpMode = MODE_HEX;
    if((strcmp(cmd,"d")==0)||(strcmp(cmd,"dx")==0)){
        dumpMode = MODE_HEX;
    }
    if((strcmp(cmd,"di")==0)){
        dumpMode = MODE_INT;
    }
    int dumpSize = 64;
    if(params.size() >=3){
        dumpSize = atoi(params[2].c_str());
    }
    
    unsigned int addr = EvalInt((char *)params[1].c_str());
    logger->printf("Dump 0x%08X\n",addr);
    pscan.dump(addr,dumpSize,dumpMode);
}

void LuaShell::Write(std::vector<std::string> &params)
{
    char cmd[64];
    strcpy(cmd,(char *)params[0].c_str());
    if(params.size() >=3){
        unsigned int addr = EvalInt((char *)params[1].c_str());
        std::vector<unsigned int> vInts;
        GetInts((char *)params[2].c_str(),vInts);
        int size = vInts.size()*sizeof(int);
        pscan.write(addr,size,(unsigned int)&vInts[0]);
        logger->printf("write %08X for %d done\n",addr,size);
	
	pscan.dump(addr,size,MODE_HEX);
        //char cmd[1024];
        //sprintf(cmd,"d %08X %d",addr,size);
        //Dump(cmd);
    }
}    


void LuaShell::Shell(int pid,Logger *_logger,LuaScript *_script)
{
    logger = _logger;
    script = _script;
    std::vector<std::string> history;
    if(pscan.open(pid)){
        pscan.Continue();
        char line[1024];
        printf(">");fflush(stdout);
        std::vector<ScanResult> result;                    
        while(gets(line)!=NULL){
	    if(strlen(line) >0){
		std::vector<std::string> params = ParseParam(line);
		pscan.Stop();
		std::vector<unsigned int> vInts;
		if(params[0] == "s"){
		    /*
		     * s value
		     * s value dumpsize
		     * - value = 121213 or 0xAADDDDD
		     */
		    result.clear();
		    int dumpSize = 64;
		    GetInts((char *)params[1].c_str(),vInts);		
		    if(params.size()==3){
		       dumpSize = atoi(params[2].c_str());
		    }
		    ScanData sd;
		    unsigned int *p = (unsigned int *)&sd.data;
		    sd.size = vInts.size() * sizeof(int);
		    for(int i=0;i<vInts.size();i++){
			p[i] = vInts[i];
		    }
		    pscan.scanAll((unsigned int)&sd.data,sd.size,result,true);
		    printf("Found %d\n",result.size());
		    for(int i=0;i<result.size();i++){
			printf("%08X\n",result[i].addr);
			pscan.dump(result[i].addr,dumpSize);
		    }
		}else if(params[0].c_str()[0] == 'd'){
		    Dump(params);
		}else if(params[0].c_str()[0] == 'w'){
		    Write(params);
		}else if(params[0].c_str()[0] == 'l'){
		    script->execFile((char *)scriptFile.c_str());
		}else if(params[0].c_str()[0] == 't'){

		    if(params.size() == 3){
			unsigned int d1 = EvalInt((char *)params[1].c_str());
			unsigned int d2 = EvalInt((char *)params[2].c_str());
			printf("%d %d\n",d1,d2);
			//pscan.readMonoString(d1);
			pscan.MonoClassScan();
		    }

		}else{
		    script->execString(line);
		}
		pscan.Continue();
	    }
	    printf(">");fflush(stdout);	    
        }
        pscan.close();
    }
}
