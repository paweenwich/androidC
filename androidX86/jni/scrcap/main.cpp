/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kwang
 *
 * Created on August 22, 2018, 4:42 PM
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
#include <algorithm>
#include <dirent.h>
#include "../util/logger.h"
#include "../util/util.hpp"
#include "../util/payload.hpp"
#include "../util/ProcessScanner.hpp"

#define stricmp strcasecmp


using namespace std;

class SearchCommand {
public:
    char op;
    char type;
    int iValue;
    float fValue;
    // {op}{type}{value}
    // op -> = > < x c
    // type -> i f 
    static SearchCommand parse(char *data){
	//printf("SearchCommand:parse [%s]\n",data);
	SearchCommand ret;
	char buf[1024];
	strcpy(buf,data);
	ret.op = buf[0];
	ret.type = buf[1];
	if(ret.type == 'i'){
	    sscanf(&data[2],"%d",&ret.iValue);
	}
	if(ret.type == 'f'){
	    sscanf(&data[2],"%f",&ret.fValue);
	}
	return ret;
    }
    SearchCommand(){
	op = ' ';
    }
    bool hasCommand(){
	return op != ' ';
    }
    void show(){
	if(type == 'i'){
	    printf("%c %c %d\n",op,type,iValue);
	}else{
	    printf("%c %c %f\n",op,type,fValue);
	}
    }
};

/*
 * 
 */
int main(int argc, char** argv) {
    if(argc<=1){
        printf("Usage:\n");
        printf("%s pid|pname -c cmd [-o outfile] [-i infile]\n",argv[0]);
        return 0;
    }
    int pid;
    if(isdigit(argv[1][0])){
	pid = atoi(argv[1]);
    }else{
	printf("Find by name [%s]\n",argv[1]);
	pid = FindProcessByName(argv[1],NULL);
	printf("pid=%d\n",pid);
	if(pid==getpid()){
	    printf("Error: process (%d) not found\n",pid);
	    return 0;
	}
    }
    char outputFileName[128];
    char inputFileName[128];
    SearchCommand cmd;
    outputFileName[0] = 0;
    inputFileName[0] = 0;
    bool flgDump = false;
    //printf("%d\n",argc);
    if(argc>1){
	for(int i=2;i<argc;i++){
	    if(strcmp(argv[i],"-o")==0){
		i++;
		strcpy(outputFileName,argv[i]);
	    }
	    if(strcmp(argv[i],"-i")==0){
		i++;
		strcpy(inputFileName,argv[i]);
	    }
	    if(strcmp(argv[i],"-c")==0){
		i++;
		cmd = SearchCommand::parse(argv[i]);
		cmd.show();
	    }
	    if(strcmp(argv[i],"-d")==0){
		flgDump = true;
	    }
	}
    }
    if(!cmd.hasCommand()){
	printf("-c not found\n");
	return 0;
    }
    printf("i=%s o=%s\n",inputFileName,outputFileName);
    std::vector<SnapShotResult> prevAddrs;
    if(inputFileName[0]!=0){
	prevAddrs = SnapShot::readFromFile(inputFileName);
	printf("prevAddrs=%d\n",prevAddrs.size());
    }
    ProcessScanner pscan;
    if(pscan.open(pid)){
	//printf("Open success %d\n",pid);
	pscan.readMap();
	std::vector<ProcMapData> heapMap = pscan.getHeap();
	SnapShot snapShot;
	//printf("%d\n",heapMap.size());
	for(int i=0;i<heapMap.size();i++){
	    //heapMap[i].show();
	    char *buf = (char *)malloc(heapMap[i].size());
	    if(pscan.read(heapMap[i].startAddr,heapMap[i].size(),(unsigned int)&buf[0])){
		SnapShotData sn;
		sn.buf = (void *)&buf[0];
		sn.size = heapMap[i].size();
		sn.startAddr = heapMap[i].startAddr;
		snapShot.vData.push_back(sn);
		if(flgDump){
		    char dumpFileName[1024];
		    sprintf(dumpFileName,"/data/local/tmp/%08X-%08X.bin",heapMap[i].startAddr,heapMap[i].endAddr);
		    pscan.buffToFile((unsigned int)&buf[0],heapMap[i].size(),dumpFileName);
		    printf("dump %s\n",dumpFileName);
		}
	    }else{
		printf("Read fail \n");
	    }
	}
	std::vector<SnapShotResult> currentAddrs;
	if(cmd.op == '='){
	    if(cmd.type=='i'){
		currentAddrs = snapShot.findInt32(cmd.iValue);
	    }
	}
	printf("currentAddrs=%d\n",currentAddrs.size());
	std::vector<SnapShotResult> newAddress;
	if(inputFileName[0]!=0){
	    std::set_intersection(currentAddrs.begin(),currentAddrs.end(),prevAddrs.begin(),prevAddrs.end(),back_inserter(newAddress),ascendingAddr);
	    printf("newAddress=%d\n",newAddress.size());
	}else{
	    newAddress = currentAddrs;
	}
	if(outputFileName[0]!=0){
	    if(pscan.buffToFile((unsigned int)newAddress.begin(),newAddress.size()*sizeof(SnapShotResult),outputFileName)){
		printf("write success\n");
	    }
	}
	pscan.close();
    }else{
	printf("can not open %d\n",pid);
    }
    //upgrade(pid,argv[2]);
    //printf("PID=%d\n",pid);
    return 0;
}

