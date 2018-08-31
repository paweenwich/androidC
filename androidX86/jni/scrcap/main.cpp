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
#include <sys/stat.h>
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

Logger logger;
using namespace std;

class SearchCommand {
public:
    char op;
    char type;
    int iValue;
    float fValue;
    //char sValue[1024];
    std::vector<unsigned char>hValue;
    string sValue;
    // {op}{type}{value}
    // op -> = > < x c :
    // type -> i f 
    static SearchCommand parse(char *data){
	//printf("SearchCommand:parse [%s]\n",data);
	SearchCommand ret;
	char buf[1024];
	strcpy(buf,data);
	ret.op = buf[0];
	ret.type = buf[1];
	if(ret.op == ':'){ //  :path
	    ret.sValue.append(&data[1]);
	}else{
	    if(ret.type == 'i'){
		sscanf(&data[2],"%d",&ret.iValue);
	    }
	    if(ret.type == 'f'){
		sscanf(&data[2],"%f",&ret.fValue);
	    }
	    if(ret.type == 's'){
		//sscanf(&data[2],"%s",ret.sValue);
		ret.hValue.insert(ret.hValue.end(), &data[2], &data[strlen(data)]);

	    }
	    if(ret.type == 'h'){
		printf("[%s]\n",data);
		ret.hValue = hex2bin(&data[2]);
		//logger.logHex(ret.hValue.begin(),ret.hValue.size());
	    }
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
	if(op == ':'){
	    printf("DUMP %c [%s]\n",op,sValue.c_str());
	}else{
	    if(type == 'i'){
		printf("%c %c %d\n",op,type,iValue);
	    }
	    if(type == 'f'){
		printf("%c %c %f\n",op,type,fValue);
	    }
	    if(type == 's'){
		printf("%c %c\n",op,type);
		logger.logHex(hValue.begin(),hValue.size());

	    }
	    if(type == 'h'){
		printf("%c %c\n",op,type);
		logger.logHex(hValue.begin(),hValue.size());
	    }
	}
	
    }
};

void dumpToDir(std::vector<ProcMapData>& vMaps, ProcessScanner& pscan, char *path)
{
    for(int i=0;i<vMaps.size();i++){
//if(vMaps[i].startAddr < 0x94455000){
//    printf("SKIP %08X\n",vMaps[i].startAddr);
//    continue;
//}
	    //heapMap[i].show();
	char *buf = (char *)malloc(vMaps[i].size());
	if(buf == NULL){
	    printf("malloc fail for %d",vMaps[i].size());
	    continue;
	}
	if(pscan.read(vMaps[i].startAddr,vMaps[i].size(),(unsigned int)&buf[0])){
	    SnapShotData sn;
	    sn.buf = (void *)&buf[0];
	    sn.size = vMaps[i].size();
	    sn.startAddr = vMaps[i].startAddr;
	    char dumpFileName[1024];
	    sprintf(dumpFileName,"%s/%08X-%08X.bin",path,vMaps[i].startAddr,vMaps[i].endAddr);
	    pscan.buffToFile((unsigned int)&buf[0],vMaps[i].size(),dumpFileName);
	    //printf("dump %s\n",dumpFileName);
	}else{
	    //printf("Read fail %08X\n",vMaps[i].startAddr);
	}
	free(buf);
    }
    printf("Done\n");
}

void searchDir(std::string dirName,SearchCommand &cmd)
{
    printf("%s\n",dirName.c_str());
    std::vector<std::string> vFiles = DirectoryListFile(dirName,".bin");    
    //std::vector<SnapShotResult> allAddrs;
    for(int i=0;i<vFiles.size();i++){
	std::string fileName = dirName + "/" + vFiles[i];
	if(cmd.hasCommand()){
	    SnapShotFileData snapShot(fileName);
	    std::vector<SnapShotResult> currentAddrs;
	    if(cmd.op == '='){
		if(cmd.type=='i'){
		    currentAddrs = snapShot.findInt32(cmd.iValue);
		}
		if((cmd.type=='s')||(cmd.type=='h')){
		    currentAddrs = snapShot.findBinary(cmd.hValue);
		}
	    }
	    //allAddrs.insert(allAddrs.end(),currentAddrs.begin(),currentAddrs.end());
	    if(currentAddrs.size()>0){
		printf("%s\n",fileName.c_str());
		for(int j=0;j<currentAddrs.size();j++){
		    unsigned int addr = (unsigned int)snapShot.GetVirtualAddress(currentAddrs[j].addr);
		    printf("%08X %08X\n",currentAddrs[j].addr,addr);
		    logger.logHex((unsigned char *)addr,64);
		}
	    }
	}else{
	    //printf("%s\n",fileName.c_str());
	}
    }
    if(cmd.hasCommand()){
	//printf("%d\n",allAddrs.size());
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    if(argc<=1){
        printf("Usage:\n");
        printf("%s pid|pname -c cmd [-o outfile] [-i infile]\n",argv[0]);
	printf("%s pid|pname -c :dir ;to dump\n",argv[0]);
	printf("%s pid|pname -c =ixxx ;to search int xxxx\n",argv[0]);
	printf("%s pid|pname -c =sxxx ;to search string xxxx\n",argv[0]);
	printf("%s pid|pname -c =hxxx ;to search hex xxxx\n",argv[0]);
	printf("%s pid|pname search dir -c cmd \n",argv[0]);
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
    std::string mainCommand;
    std::string argv1;
    outputFileName[0] = 0;
    inputFileName[0] = 0;
    bool flgDump = false;
    bool flgParseOnly = false;
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
	    if(strcmp(argv[i],"-p")==0){
		flgParseOnly = true;
	    }
	    if(strcmp(argv[i],"search")==0){
		mainCommand = std::string(argv[i]);
		i++;
		argv1 = std::string(argv[i]);
	    }
	    
	}
    }
    if(flgParseOnly){
	printf("Done (parse only)\n");
	return 0;
    }
    if(mainCommand!=""){
	if(mainCommand == "search"){
	    searchDir(argv1,cmd);
	}
	return 0;
    }
	
    if(!cmd.hasCommand()){
	printf("-c not found\n");
	return 0;
    }
//printf("DEBUG BREAK\n");    
//return 0;    
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
	//std::vector<ProcMapData> heapMap = pscan.getHeap();
	std::vector<ProcMapData> heapMap = pscan.getWriteable();
	
	if(cmd.op == ':'){
	    if(cmd.sValue.size()==0){
		printf("Directory [%s] not define\n",(char *)cmd.sValue.c_str());
	    }else{
		if(!isDirectoryExist(cmd.sValue.c_str())){
		    printf("Directory [%s] not found\n",(char *)cmd.sValue.c_str());
		    mkdir((char *)cmd.sValue.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		    printf("Create Directory [%s]\n",(char *)cmd.sValue.c_str());
		}
		dumpToDir(heapMap,pscan,(char *)cmd.sValue.c_str());
	    }
	    pscan.close();
	    return 0;
        }

	SnapShot snapShot;
	//printf("%d\n",heapMap.size());
	for(int i=0;i<heapMap.size();i++){
	    //heapMap[i].show();
	    char *buf = (char *)malloc(heapMap[i].size());
	    if(buf == NULL){
		printf("malloc fail for %d",heapMap[i].size());
		continue;
	    }
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
		printf("Read fail\n");
	    }
	}
	std::vector<SnapShotResult> currentAddrs;
	if(cmd.op == '='){
	    if(cmd.type=='i'){
		currentAddrs = snapShot.findInt32(cmd.iValue);
	    }
	    if((cmd.type=='s')||(cmd.type=='h')){
		currentAddrs = snapShot.findBinary(cmd.hValue);
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

