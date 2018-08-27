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
#include <dirent.h>
#include "../util/logger.h"
#include "../util/util.hpp"
#include "../util/payload.hpp"
#include "../luac/luascript.h"
#include "../util/ProcessScanner.hpp"
#include "hello.h"
#include "lua_hello.hpp"

#define lua_open()  luaL_newstate()

#define  LOGD(...)  printf(__VA_ARGS__)
#define  LOGE(...)  printf(__VA_ARGS__)
//#define	 LOGHEX(x,y)	logger->logHex((x),(y));

typedef unsigned int (*GetFuncAddress_t)(const char* libname, const char* funcName);
typedef unsigned int (*GetFuncOffset_t)(const char* libname, const char* funcName);
typedef unsigned int (*FindBaseLibrary_t)( const char *library, int pid);
typedef unsigned int (*FindBaseLibraryFromAddress_t)(unsigned int address, int pid);
typedef void (*FindLibraryPath_t)(const char* libname,char *path,int len);
typedef void (*Test_t)();
typedef char* (*GetBaseLibraryNameFromAddress_t)(unsigned int address, int pid);

Logger logger(NULL,0);


void hello()
{
    printf("Hello World X86 %08X\n",getpid());    
}

void traceme()
{
    char data[1024];
    strcpy(data,"Hello World");
    unsigned int addr = (unsigned int)::getpid;
    printf("%08X %s %d\n",(unsigned int)data,data,getpid());
    printf("addr=%08X\n",addr);
    printf("dlopen addr=%08X\n",(unsigned int)::dlopen);
    logger.logHex((unsigned char*)addr,32);
    printf("^Crtl C to endprogram\n");
    
    while(1){
        getchar();
        logger.logHex((unsigned char*)addr,32);        
        printf("%d\n",getpid());
    }
    return;    
}

void tracemeLoad()
{
    char data[1024];
    strcpy(data,"Hello World");
    unsigned int addr = (unsigned int)::getpid;
    printf("%08X %s %d\n",(unsigned int)data,data,getpid());
    printf("addr=%08X\n",addr);
    printf("dlopen addr=%08X\n",(unsigned int)::dlopen);
    logger.logHex((unsigned char*)addr,32);
    printf("^Crtl C to endprogram\n");
    
    while(1){
        getchar();
        dlopen("/data/local/tmp/libloader.so",0);
        logger.logHex((unsigned char*)addr,32);        
        printf("%d\n",getpid());
    }
    return;    
}

void armhlpx86(bool flgArm)
{
    GetFuncAddress_t GetFuncAddress;
    FindBaseLibrary_t FindBaseLibrary;
    FindBaseLibraryFromAddress_t FindBaseLibraryFromAddress;
    GetFuncOffset_t GetFuncOffset;
    FindLibraryPath_t FindLibraryPath;
    Test_t Test;
    GetBaseLibraryNameFromAddress_t GetBaseLibraryNameFromAddress;
    
    char libName[1024];
    if(!flgArm){
        strcpy(libName,"./libarmhlpx86.so");
    }else{
        strcpy(libName,"./libarmhlparm.so");        
    }
    printf("Test loading %s\n",libName);
    void* handle = dlopen(libName,0);
    if(handle == 0){
        perror("dlopen:");
        printf("error no %d\n",errno);
        printf("can not load %s\n",libName);
        return;
    }
    GetFuncAddress = (GetFuncAddress_t)dlsym(handle,"GetFuncAddress");
    if(GetFuncAddress == 0){
        perror("dlsym: GetFuncAddress");
        return;
    }
    printf("GetFuncAddress=%08X\n",(unsigned int)GetFuncAddress);
    GetFuncOffset = (GetFuncOffset_t)dlsym(handle,"GetFuncOffset");
    printf("GetFuncOffset=%08X\n",(unsigned int)GetFuncOffset);
    
    FindBaseLibrary = (FindBaseLibrary_t)dlsym(handle,"FindBaseLibrary");
    printf("FindBaseLibrary=%08X\n",(unsigned int)FindBaseLibrary);
    FindBaseLibraryFromAddress = (FindBaseLibraryFromAddress_t)dlsym(handle,"FindBaseLibraryFromAddress");
    printf("FindBaseLibraryFromAddress=%08X\n",(unsigned int)FindBaseLibraryFromAddress);
    
    FindLibraryPath = (FindLibraryPath_t)dlsym(handle,"FindLibraryPath");
    printf("FindLibraryPath=%08X\n",(unsigned int)FindLibraryPath);
    
    Test = (Test_t)dlsym(handle,"Test");
    printf("Test=%08X\n",(unsigned int)Test);

    GetBaseLibraryNameFromAddress = (GetBaseLibraryNameFromAddress_t)dlsym(handle,"GetBaseLibraryNameFromAddress");
    printf("GetBaseLibraryNameFromAddress=%08X\n",(unsigned int)GetBaseLibraryNameFromAddress);
    
    unsigned int linkerBase = FindBaseLibraryFromAddress((unsigned int)dlopen,0);
    printf("linkerBase = %08X\n",linkerBase);
    printf("offset dlopen = %08X\n",(unsigned int)dlopen - linkerBase);
    printf("linkername %s\n",GetBaseLibraryNameFromAddress((unsigned int)dlopen,0));
    
    unsigned int dlHandle = (unsigned int)dlopen("libdl.so",0);
    printf("dlHandle = %08X\n",dlHandle);
    unsigned int dlopen_libdl = (unsigned int)dlsym((void *)dlHandle,"dlopen");
    printf("dlopen_libdl = %08X\n",dlopen_libdl);
    unsigned int dlopen_libdlBase = FindBaseLibraryFromAddress((unsigned int)dlopen_libdl,0);
    printf("dlopen_libdlBase = %08X\n",dlopen_libdlBase);
    printf("dlopen_libdlBase offset dlopen = %08X\n",(unsigned int)dlopen_libdl - dlopen_libdlBase);
    printf("dlopen_libdlBase linkername %s\n",GetBaseLibraryNameFromAddress((unsigned int)dlopen_libdl,0));
    
    printf("read addr = %08X\n",(unsigned int)read);
    logger.logHex((unsigned char *)read,32);    
    printf("write addr = %08X\n",(unsigned int)write);
    logger.logHex((unsigned char *)write,32);
    printf("lib %s\n",GetBaseLibraryNameFromAddress((unsigned int)read,0));

    getchar();
}

typedef unsigned (*asmFunc)(void);

void Detour()
{
   printf("Detour\n");    
   
   unsigned int dlopenAddr = FinddlopenAddress(getpid());
   printf("dlopen Addr = %08X %08X\n",dlopenAddr,(unsigned int)dlopen);
   
   
    // write some code in
   unsigned char * tempCode = (unsigned char *) AllocateExecutableMemory(4096);
   printf("virtualCodeAddress = %08X\n", (unsigned int)tempCode);
#ifdef __arm__
   unsigned char branchToAddressCmd[] = {
        0x00,0xC0,0x9F,0xE5,    //LDR r12,[pc,0]
        0x1C,0xFF,0x2F,0xE1,    //BX	r12
        0x11,0x22,0x33,0x44,    //jump addr
   };
   printf("arm\n");
   //ARM HEX  http://armconverter.com/   
   unsigned char cmd[] = {
        //0x08,0x00,0x1F,0xE5,  //LDR   r0,[pc, #-8]   this will point to current instruction due to prefect again
        //0x10,0x00,0x1F,0xE5,  //LDR   r0,[pc, #-16]   this will point to nop1
        
        0x01,0x00,0x00,0xEA,    //B 4  (prefetch 1 word (4), So equal 4 + 4 = 8 byte)
        0xAA,0xBB,0xCC,0xDD,    // data[0]        -- string addr
        0x01,0x01,0xA0,0xE1,    // data[1]        -- dlopen addr
        0x0F,0x70,0xA0,0xE1,    //mov r7,pc
        0x10,0x70,0x47,0xE2,    //sub r7,16     -- set r7 to addr of data[0]]

        0xFF,0x00,0x2D,0xE9,    //push {r0-r7}
        0x04,0xE0,0x2D,0xE5,    //push {lr}
        
        0x00,0x10,0xA0,0xE3,    //mov  r1, #0       -- load now
        0x00,0x00,0x97,0xE5,    //LDR r0, [r7]      -- addr of library name
        0x04,0x80,0x97,0xE5,    //ldr r8,[r7,4]     -- addr of function
        0x38,0xFF,0x2F,0xE1,    //blx r8            -- call dlopen
        
        0x04,0x30,0x9D,0xE4,    //pop  {r3}
        0x03,0xE0,0xA0,0xE1,    //mov  lr, r3
        0xFF,0x00,0xBD,0xE8,    //pop  {r0-r7}
        
        0x04,0x00,0x97,0xE5,    //LDR r0, [r7,4]
        0x1E,0xFF,0x2F,0xE1,    //BL  lr      
        0x00,0x00,0x00,0x00,    //backup instruction
        0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,
        
   };
   memcpy(tempCode,branchToAddressCmd,sizeof(branchToAddressCmd));  
   int dataOffset = sizeof(branchToAddressCmd) + 4;
   memcpy(tempCode+sizeof(branchToAddressCmd),cmd,sizeof(cmd));  
   // set jump addr
   *(unsigned int *)((unsigned char*)tempCode + 8) = (unsigned int)tempCode + sizeof(branchToAddressCmd);
   // set library name addr
   char *libname = "./libarmhlparm.so";
   *(unsigned int *)((unsigned char*)tempCode + dataOffset) = (unsigned int)libname;
   
   //set dlopen addr
   *(unsigned int *)((unsigned char*)tempCode + dataOffset + 4) = (unsigned int)dlopenAddr;
#else   
   // MOV EAX 0xEEDD1100
   tempCode[0] = 0xb8;
   tempCode[1] = 0x00;
   tempCode[2] = 0x11;
   tempCode[3] = 0xdd;
   tempCode[4] = 0xee;
   // ret code! Very important!
   tempCode[5] = 0xc3;
#endif
   asmFunc myFunc = (asmFunc) (tempCode);
   getchar();
   unsigned out = myFunc();

   printf("out is %08X\n", out);

}

void hooklibc()
{
   unsigned int tempCode = AllocateExecutableMemory(4096);
   printf("tempCode Addr %08X\n",tempCode);
   
   unsigned int dlopenAddr = FinddlopenAddress(getpid());
   printf("dlopen Addr = %08X %08X\n",dlopenAddr,(unsigned int)dlopen);
   
   unsigned int writeAddr = FindwriteAddress(getpid());
   
   printf("writeAddr Addr = %08X %08X\n",writeAddr,(unsigned int)write);
   logger.logHex((unsigned char *)writeAddr,32);   
   
   unsigned int libcBase = FindBaseLibrary("libc_orig.so",0);
   printf("libcBase Addr = %08X\n",libcBase);
   //writeAddr = (unsigned int)getpid;
   
   unsigned int libcSize = GetBaseLibraryTextSize("libc_orig.so",0);
   printf("libcSize = %08X\n",libcSize);
   
   if(mprotect((void *)libcBase, libcSize, PROT_READ | PROT_WRITE | PROT_EXEC)){
       printf("mprotect error %s\n",strerror(errno));
       return;
   }
   printf("mprotect +w done\n");
   unsigned char backupTargetCode[3*4];
   memcpy((void *)backupTargetCode,(void *)writeAddr,sizeof(backupTargetCode));
   printf("Backup done\n");
   
#ifdef __arm__
   unsigned char branchToAddressCmd[] = {
        0x00,0xC0,0x9F,0xE5,    //LDR r12,[pc,0]
        0x1C,0xFF,0x2F,0xE1,    //BX	r12
        0x11,0x22,0x33,0x44,    //jump addr
   };  
   // set jump addr
   *(unsigned int *)((unsigned char*)branchToAddressCmd + 8) = tempCode;
   //memcpy((void *)writeAddr,(void *)branchToAddressCmd,sizeof(branchToAddressCmd));   
   
   //memset((void *)writeAddr,0,sizeof(backupTargetCode));
   //ARM HEX  http://armconverter.com/   
   unsigned char cmd[] = {
        //0x08,0x00,0x1F,0xE5,  //LDR   r0,[pc, #-8]   this will point to current instruction due to prefect again
        //0x10,0x00,0x1F,0xE5,  //LDR   r0,[pc, #-16]   this will point to nop1
        0x0F,0x30,0xA0,0xE1,    //mov r3,pc
        0x04,0x30,0x83,0xE2,    //add r3,#4      -- set r3 to addr of data[0]]  
     
        0x05,0x00,0x00,0xEA,    //B 20  (prefetch 1 word (4), So equal 4 + 4 = 8 byte)
        0xAA,0xBB,0xCC,0xDD,    // data[0]        -- string addr
        0x01,0x01,0xA0,0xE1,    // data[1]        -- dlopen addr
        0x00,0x00,0x00,0x00,    //backup instruction
        0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,    //back up address
        
        0xFF,0x01,0x2D,0xE9,    //push {r0-r8}
        0x04,0xE0,0x2D,0xE5,    //push {lr}
        // copy original code back
        //move backup back to original
        0x14,0x00,0x93,0xE5,    //LDR r0, [r3,20]   -- load backup addr to r0
        0x08,0x80,0x93,0xE5,    //LDR r8, [r3,8]]   -- load first instruction
        0x00,0x80,0x80,0xE5,    //STR r8, [r0]      -- copy first instruction]
        0x04,0x00,0x80,0xE2,    //ADD r0, 4         -- add index
        0x0C,0x80,0x93,0xE5,    //LDR r8, [r3,12]]   -- load 2nd instruction
        0x00,0x80,0x80,0xE5,    //STR r8, [r0]      -- copy 2nd instruction]
        0x04,0x00,0x80,0xE2,    //ADD r0, 4         -- add index
        0x10,0x80,0x93,0xE5,    //LDR r8, [r3,16]]   -- load 3rd instruction
        0x00,0x80,0x80,0xE5,    //STR r8, [r0]      -- copy 3rd instruction]
        
        
        0x00,0x10,0xA0,0xE3,    //mov r1, #0       -- load now
        0x00,0x00,0x93,0xE5,    //LDR r0,[r3]      -- addr of library name
        0x04,0x80,0x93,0xE5,    //ldr r8,[r3,4]     -- addr of function
        0x38,0xFF,0x2F,0xE1,    //blx r8            -- call dlopen
        
        //0x04,0x30,0x9D,0xE4,    //pop  {r3}
        //0x03,0xE0,0xA0,0xE1,    //mov  lr, r3
        0x04,0xE0,0x9D,0xE4,    //pop  {lr}
        0xFF,0x01,0xBD,0xE8,    //pop  {r0-r8}
        
        //jump back
        0x14,0x30,0x93,0xE5,    //LDR r3, [r3,20]
        0x13,0xFF,0x2F,0xE1,    //bx r3
   };
   memcpy((void *)(cmd+20),(void *)backupTargetCode,sizeof(backupTargetCode));
    
   //memcpy(tempCode,branchToAddressCmd,sizeof(branchToAddressCmd));  
   int dataOffset = 12;
   memcpy((void *)tempCode,(void *)cmd,sizeof(cmd));  
   // set library name addr
   char *libname = "./libarmhlparm.so";
   *(unsigned int *)((unsigned char*)tempCode + dataOffset) = (unsigned int)libname;
   //set dlopen addr
   *(unsigned int *)((unsigned char*)tempCode + dataOffset + 4) = (unsigned int)dlopenAddr;
   //set return address
   *(unsigned int *)((unsigned char*)tempCode + dataOffset + 20) = (unsigned int)writeAddr;
   
   memcpy((void *)writeAddr,(void *)branchToAddressCmd,sizeof(branchToAddressCmd));   
   getchar();
   printf("Test1 %d\n",getpid());   
   //printf("Test2\n");  
#endif   
   //shell code should restore it
   //memcpy((void *)writeAddr,(void *)backupTargetCode,sizeof(backupTargetCode));   
   //printf("Restore done\n");  
   
   if(mprotect((void *)libcBase, libcSize, PROT_READ | PROT_EXEC)){
       printf("mprotect error %s\n",strerror(errno));
       return;
   }
   printf("mprotect -w done\n");
   
    
}

void dumpoffset()
{
   unsigned int libcBase = FindBaseLibrary("libc_orig.so",0);
   unsigned int libcSize = GetBaseLibraryTextSize("libc_orig.so",0);
   printf("libcBase Addr = %08X-%08X\n",libcBase,libcBase + libcSize);
   printf("libcSize = %08X\n",libcSize);
   printf("getpid() %08X %08X\n",(unsigned int)::getpid,(unsigned int)::getpid-libcBase);
   printf("gettid() %08X %08X\n",(unsigned int)::gettid,(unsigned int)::gettid-libcBase);
   printf("mmap() %08X %08X\n",(unsigned int)::mmap,(unsigned int)::mmap-libcBase);
   printf("dlsym() %08X %08X\n",(unsigned int)::dlsym,(unsigned int)::dlsym-libcBase);
}
/*
dlopenAddr=B6EF4378 B6EF4378
38 40 2D E9 00 40 A0 E1 48 00 9F E5 01 50 A0 E1 8.......H....P..
00 00 8F E0 C6 31 00 EB 04 00 A0 E1 05 10 A0 E1 .....1..........
DD 0A 00 EB 00 40 50 E2 04 00 00 0A 28 10 9F E5 ......P.........
01 00 8F E0 F6 31 00 EB 04 00 A0 E1 38 80 BD E8 .....1......8...
PUSH	{R3, R4, R5, LR}
MOV	R4, R0
LDR	R0, [PC, #0x48]
MOV	R5, R1
ADD	R0, PC, R0
BL	#0xC734
MOV	R0, R4
MOV	R1, R5
BL	#0x2B9C
SUBS	R4, R0, #0
BEQ	#0x40
LDR	R1, [PC, #0x28]
ADD	R0, PC, R1
BL	#0xC814
MOV	R0, R4
POP	{R3, R4, R5, PC}
 */
void libdl()
{
    unsigned int handle = (unsigned int)dlopen("/system/lib/arm/libdl.so",0);
    printf("handle=%08X\n",handle);
    unsigned int dlopenAddr = (unsigned int)dlsym((void *)handle,"dlopen");
    printf("dlopenAddr=%08X %08X\n",dlopenAddr,(unsigned int)::dlopen);
    logger.logHex((unsigned char*)dlopenAddr,64);
}

void testlua()
{
    printf("Test lua\n");
    LuaScript *script = new LuaScript(tolua_lua_hello_open);
    //lua_State *luaState = lua_open();  /* create state */    
    //printf("Create lua state %08X\n",(unsigned int )luaState);
    script->execString("alert('1213')");

}


struct CharacterData {
    unsigned int creatureId;
    unsigned int combatType;
    unsigned int baseHp;
    unsigned int hpf;
    unsigned int baseMp;
    float mpf;
    float baseMpRegen;
    float mprf;
    unsigned int baseAttackPoint;
    float apf;
    unsigned int movePoint;
    float baseDr;
    float drf;
    float baseCr;
    float crf;
    float baseDgr;
    float dgrf;
    float baseHr;
    float hrf;
    float baseCar;
    float carf;
    float baseCadr;
    float cadrf;
    float mastery;
};
void readprocess(int pid)
{
    ProcessScanner pscan;
    if(pscan.open(pid)){
	printf("Open success\n");
	struct CharacterData kai;
	kai.creatureId = 1114114;
	kai.combatType = 3;
	std::vector<ScanResult> result;
	//;0x872CED64
	pscan.dump(0x872CED64,64);
	pscan.scanRange(0x80000000,0x90000000,(unsigned int)&kai,8,result,true);
	for(int i=0;i<result.size();i++){
	    result[i].show();
	    pscan.dump(result[i].addr,64);
	    pscan.read(result[i].addr,sizeof(kai),(unsigned int)&kai);
	    //kai.baseHp += 1000;
	    kai.baseAttackPoint = 10000;
	    kai.baseDr = 0.8;
	    kai.baseDgr = 0.5;
	    
	    pscan.write(result[i].addr,sizeof(kai),(unsigned int)&kai);
	    pscan.dump(result[i].addr,64);
	}
	pscan.close();
	
    }
}

int main(int argc,char *argv[])
{
    logger.logStr("Hello");
    if(argc==1){
        printf("Usage:\n");
        printf("%s traceme|tracemeLoad\n",argv[0]);
        printf("%s hello\n",argv[0]);
        printf("%s armhlpx86\n",argv[0]);
        printf("%s armhlparm\n",argv[0]);        
        printf("%s detour\n",argv[0]); 
        printf("%s hooklibc\n",argv[0]);
        printf("%s dumpoffset\n",argv[0]);
        printf("%s libdl\n",argv[0]);  
	printf("%s testlua\n",argv[0]);  
	printf("%s readprocess pid addr\n",argv[0]);  
        return 0;
    }
    
    if(argc>1){
        if(strcmp(argv[1],"hello")==0){
            hello();
            getchar();
            return 1;
        }
        if(strcmp(argv[1],"libdl")==0){
            libdl();
            getchar();
            return 1;
        }        
        if(strcmp(argv[1],"traceme")==0){
            traceme();
            return 1;
        }
        if(strcmp(argv[1],"tracemeLoad")==0){
            tracemeLoad();
            return 1;
        }
        if(strcmp(argv[1],"armhlpx86")==0){
            armhlpx86(false);
            return 1;
        }
        if(strcmp(argv[1],"armhlparm")==0){
            armhlpx86(true);
            return 1;
        }
        if(strcmp(argv[1],"detour")==0){
            Detour();
            return 1;
        }
        if(strcmp(argv[1],"hooklibc")==0){
            hooklibc();
            return 1;
        }
        if(strcmp(argv[1],"dumpoffset")==0){
            dumpoffset();
            return 1;
        }
        if(strcmp(argv[1],"testlua")==0){
            testlua();
            return 1;
        }
	if(strcmp(argv[1],"readprocess")==0){
	    int pid = atoi(argv[2]);
            readprocess(pid);
            return 1;
	    
	}
        
    }
    
}