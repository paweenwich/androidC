/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tracer.c
 * Author: kwang
 *
 * Created on July 13, 2016, 4:23 PM
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
#include <cctype>
#include <dirent.h>
#include <pthread.h>
#include <stdint.h>
#include <elf.h>

#include <../util/util.hpp>
#include <../util/PtraceUtil.hpp>
#include <../util/AndroidLogger.h>
#include <../util/payload.hpp>
#include "../util/ELFHelp.h"

#include "../util/SimpleTCPServer.hpp"
#include "../libloader/BaseCommandService.h"
#include "../util/ProcessScanner.hpp"
//#include "../util/luascript.h"
//#include "../luaserver/lua_server.hpp"
#include "../util/Slua.h"
#define stricmp strcasecmp

void *_dlopen;
void *_dlsym;
void *_dlerror;
void *_dlclose;
void *_calloc;
void *_free;

std::string lib;

/*#define offset_dlopen 0x00001300
#define offset_dlsym 0x00001130
#define offset_dlerror 0x00000F90
#define offset_dlclose 0x00001000

#define offset_calloc 0x0000D290
#define offset_free 0x0000D260*/

unsigned int offset_dlopen=0;
unsigned int offset_dlsym=0;
unsigned int offset_dlerror=0;
unsigned int offset_dlclose=0;

unsigned int offset_calloc=0;
unsigned int offset_free=0;
unsigned int offset_getpid=0;

#define TRACE_BIN   "/data/local/tmp/tracer.bin"

#define  LOG_TAG    "loader"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


PtraceUtil ptraceUtil;
Logger logger(NULL,0);
Logger *serverLogger = new AndroidLogger("tracer",true);

unsigned long call(int pid,void *function, int nargs, ...);
int wordAlignSize(int size);
void PrintAllAddress();

void GetOffsets()
{
    int pid = getpid();
    unsigned int linkerBase = FindBaseLibrary("/system/bin/linker",pid);
    printf("[%d] linkerBase=%08X\n",pid,linkerBase);
    offset_dlopen = (unsigned int)dlopen - linkerBase;
    offset_dlsym = (unsigned int)dlsym - linkerBase;
    offset_dlerror = (unsigned int)dlerror - linkerBase;
    offset_dlclose = (unsigned int)dlclose - linkerBase;
    
    unsigned int libCBase = FindBaseLibrary("/system/lib/libc.so",pid);
    printf("[%d] libCBase=%08X\n",pid, libCBase);
    offset_calloc = (unsigned int)calloc - libCBase;
    offset_free = (unsigned int)free - libCBase;
    offset_getpid = (unsigned int)getpid - libCBase;

    printf("offset_dlopen=%08X\n",(unsigned int)offset_dlopen);
    printf("offset_dlsym=%08X\n",(unsigned int)offset_dlsym);
    printf("offset_dlerror=%08X\n",(unsigned int)offset_dlerror);
    printf("offset_dlclose=%08X\n",(unsigned int)offset_dlclose);
    printf("offset_calloc=%08X\n",(unsigned int)offset_calloc);
    printf("offset_free=%08X\n",(unsigned int)offset_free);
    printf("offset_getpid=%08X %08X\n",(unsigned int)offset_getpid,(unsigned int)getpid);

}

long Attach(int pid)
{
    long ret = ptrace( PTRACE_ATTACH, pid, 0,0 );
    if( ret == -1){
        perror("ptrace ATTACH");
        printf("Errorno = %d\n",errno);
        return -1;
    }
    printf("ATTACH Success\n");
    return 0;
}

long Detach(int pid)
{
    long ret = ptrace(PTRACE_DETACH, pid, 0,0 );
    if( ret == -1){
        perror("ptrace PTRACE_DETACH");
        printf("Errorno = %d\n",errno);
        return -1;
    }
    return 0;
}

long TraceContinue(int pid)
{
    long ret = ptrace( PTRACE_CONT, pid, 0,0 );
    if( ret == -1){
        perror("ptrace PTRACE_CONT");
        printf("Errorno = %d\n",errno);
        return -1;
    }
    return ret;
}

int GetRegs(int pid,pt_regs *reg)
{
    long ret = ptrace(PTRACE_GETREGS, pid, 0,reg );
    if( ret == -1){
        perror("ptrace PTRACE_GETREGS");
        printf("Errorno = %d\n",errno);
        return -1;
    }
    return ret;
}

int SetRegs(int pid,pt_regs *reg)
{
    long ret = ptrace( PTRACE_SETREGS, pid, 0,reg );
    if( ret == -1){
        perror("ptrace PTRACE_SETREGS");
        printf("Errorno = %d\n",errno);
        return -1;
    }
    return ret;
}

int PeekText(int pid,size_t addr)
{
    errno = 0;
    long ret = ptrace( PTRACE_PEEKTEXT, pid,addr,0);
    if( ret == -1){
        if(errno){
            perror("ptrace PTRACE_PEEKTEXT");
            printf("Errorno = %d\n",errno);
            return -1;
        }
    }
    return ret;
}

long PokeText(int pid,size_t addr,size_t value)
{
    long ret = ptrace( PTRACE_POKETEXT, pid,addr,value);
    if( ret == -1){
        perror("ptrace PTRACE_POKETEXT");
        printf("Errorno = %d\n",errno);
        return -1;
    }
    return ret;
}

void ShowRegs(pt_regs *reg)
{
#ifdef __arm__ 
#else    
    printf("ebx\t%08lX\n",reg->ebx);
    printf("ecx\t%08lX\n",reg->ecx);
    printf("edx\t%08lX\n",reg->edx);
    printf("esi\t%08lX\n",reg->esi);
    printf("ebp\t%08lX\n",reg->ebp);
    printf("eax\t%08lX\n",reg->eax);
    printf("xds\t%08X\n",reg->xds);
    
    printf("xes\t%08X\n",reg->xes);
    printf("xfs\t%08X\n",reg->xfs);
    printf("xgs\t%08X\n",reg->xgs);
    printf("orig_eax\t%08lX\n",reg->orig_eax);
    printf("eip\t%08lX\n",reg->eip);
    printf("xcs\t%08X\n",reg->xcs);
    printf("eflags\t%08lX\n",reg->eflags);
    printf("esp\t%08lX\n",reg->esp);
    printf("xss\t%08X\n",reg->xss);
#endif    
}

bool ReadProcessMemory(int pid, size_t addr, unsigned char *buf, size_t blen) {
    size_t i = 0;
    long ret = 0;

    for (i = 0; i < blen; i += sizeof (size_t)) {
        ret = PeekText(pid, addr + i);
        if (ret == -1) {
            printf("ReadProcessMemory %d %08X fail\n",pid,addr);
            return false;
        }
        memcpy(&buf[i], &ret, sizeof (ret));
    }
    return true;
}

int wordAlignSize(int size)
{
    return (size + size % sizeof (size_t));
}

bool WriteProcessMemory(int pid, size_t addr, unsigned char *buf, size_t blen) {
    size_t i = 0;
    long ret;
    unsigned long size = wordAlignSize(blen);
    // make sure the buffer is word aligned
    char *ptr = (char *) calloc(size, 1);
    memcpy(ptr, buf, blen);

    for (i = 0; i < size; i += sizeof (size_t)) {
        ret = PokeText(pid,addr + i,*(size_t *) & ptr[i]);
        if (ret == -1) {
            ::free(ptr);
            return false;
        }
    }
    ::free(ptr);
    return true;
}

unsigned long AllocProcessMemoryString(int pid,const char *s) 
{
    printf("AllocProcessMemoryString %d %s\n",pid,s);
    int size = wordAlignSize(strlen(s) + 1);
    unsigned long mem = call(pid, _calloc, 2, size, 1 );
    printf("AllocProcessMemoryString mem=%08X\n",(unsigned int)mem);
    WriteProcessMemory(pid, mem, (unsigned char *)s, size);
    return mem;
}
int GetRemoteAddress(int pid)
{
    unsigned int linkerBase = FindBaseLibrary("/system/bin/linker",pid);
    if(linkerBase==0){
        printf("/system/bin/linker of pid=%d not found\n",pid);
        return -1;
    }
    printf("[%d] linkerBase=%08X\n",pid,linkerBase);
    _dlopen = (void *)(linkerBase +  offset_dlopen);
    _dlsym = (void *)(linkerBase +  offset_dlsym);
    _dlerror = (void *)(linkerBase +  offset_dlerror);
    _dlclose = (void *)(linkerBase +  offset_dlclose);

    unsigned int libCBase = FindBaseLibrary("/system/lib/libc.so",pid);
    printf("[%d] libCBase=%08X\n",pid,libCBase);
    _calloc = (void *)(libCBase +  offset_calloc);    
    _free = (void *)(libCBase +  offset_free);    
    if((linkerBase == 0)||(libCBase == 0)){
        printf("GetRemoteAddress: FAIL %08X %08X\n",linkerBase,libCBase);
        return -1;
    }
    
    PrintAllAddress();
    return 0;
}

void PrintAllAddress()
{
    printf("_dlopen=%08X\n",(unsigned int)_dlopen);
    printf("_dlsym=%08X\n",(unsigned int)_dlsym);
    printf("_dlerror=%08X\n",(unsigned int)_dlerror);
    printf("_dlclose=%08X\n",(unsigned int)_dlclose);
    printf("_calloc=%08X\n",(unsigned int)_calloc);
    printf("_free=%08X\n",(unsigned int)_free);
}


void test(int i1,int i2,int i3,int i4)
{
#ifdef __arm__ 
#else     
    printf("Test asm %d %d %d %d\n",i1,i2,i3,i4);

    //int src = 1;
    //int dst;
     
    asm ("mov %1, %0\n\t"
         "add $1, %0"
         : "=r" (i1)
         : "r" (i2));
     
   printf("Test asm %d %d %d %d\n",i1,i2,i3,i4);
#endif

/*        
        __asm__("movl	$1,%eax\n

        xor	%ebx,%ebx\n
        int	$0x80\n
	");
*/


    //injectSharedLibrary(0,0,0);
    //GetRemoteAddress(pid);
}

int waitForStop(int pid)
{
    printf("waitForStop %d\n",pid);
    while(true){
        int wstatus = 0;
        int ret = waitpid( pid, &wstatus, __WALL );
        printf("waitForStop pid=%d ret=%d status=%08X\n",pid, ret,wstatus);
        if(WIFSTOPPED(wstatus)){
            printf("WIFSTOPPED\n");
            break;
        }
        //if(WIFCONTINUED(wstatus)){
        //    printf("WIFCONTINUED\n");
        //    continue;
        //}
        if(WSTOPSIG(wstatus)){
            printf("WSTOPSIG\n");
            continue;
        }
        if(WTERMSIG(wstatus)){
            printf("WTERMSIG\n");
            continue;
        }
        if(WIFSIGNALED(wstatus)){
            printf("WIFSIGNALED\n");
            continue;
        }
        if(WEXITSTATUS(wstatus)){
            printf("WEXITSTATUS\n");
            continue;
        }
        if(WIFEXITED(wstatus)){
            printf("WIFEXITED\n");
            return -1;
        }
        
    }
    return 0;
}

void Shell_dlopen()
{
#ifdef __arm__ 
#else     
    // ebx = dlopen address
    // ecx = library name addr
    asm(
        "push $1        \n"
        "push %ecx      \n"
        "call *%ebx     \n"
        "int $3"
    );
#endif    
}



int inject(int pid,char *lib)
{
    printf("inject pid=%d lib=[%s]\n",pid,lib);
    printf("MyFunction dlopen %08X\n",(unsigned int)::dlopen);
    printf("MyFunction dlsym %08X\n",(unsigned int)::dlsym);    
    printf("MyFunction dlerror %08X\n",(unsigned int)::dlerror);
    printf("MyFunction dlclose %08X\n",(unsigned int)::dlclose);
    
    printf("MyFunction calloc %08X\n",(unsigned int)::calloc);
    printf("MyFunction free %08X\n",(unsigned int)::free);
    
    unsigned int cBase = FindBaseLibrary("/system/lib/libc.so",0);
    unsigned int linkerBase = FindBaseLibrary("/system/bin/linker",0);
    printf("/system/lib/libc.so base %08X\n",cBase);
    printf("/system/bin/linker base %08X\n",linkerBase);
    
    //check if diffferent is correct 
    if(((unsigned int)::dlopen - linkerBase) != offset_dlopen){
        printf("Linker offset incorrect\n");
        return -1;
    }
    if(((unsigned int)::calloc - cBase) != offset_calloc){
        printf("libc offset incorrect\n");
        return -1;
    }
    if(GetRemoteAddress(pid)<0){
        return -1;
    }
    printf("Trying to ATTACH\n");
    if(Attach(pid)!=0){
        return -1;
    }
    printf("ATTACH Success\n");
    if(waitForStop(pid)==0){
        struct pt_regs oldReg,regs;
        GetRegs(pid,&regs);
        memcpy(&oldReg,&regs,sizeof(struct pt_regs));
        ShowRegs(&oldReg);
        //currentRegs.eip+=2;
        // test Set reg
        if(SetRegs(pid,&regs)==0){
            long freeAddr = (long)FindFreeSpace(pid,NULL) + sizeof(long);
            printf("freespaceaddr=%08lX\n",freeAddr);
           
            //SetRegs(pid, &regs);
            //size_t injectSharedLibrary_size = (intptr_t)injectSharedLibrary_end - (intptr_t)injectSharedLibrary;
            //intptr_t injectSharedLibrary_ret = (intptr_t)findRet(injectSharedLibrary_end) - (intptr_t)injectSharedLibrary;
            //printf("injectSharedLibrary_size=%d\n",injectSharedLibrary_size);
            //printf("injectSharedLibrary_ret=%d\n",injectSharedLibrary_ret);
            //bool ReadProcessMemory(int pid, size_t addr, unsigned char *buf, size_t blen) {
            unsigned char backupCode[1024] = {0};
            ReadProcessMemory(pid,freeAddr,&backupCode[0],256);
            WriteProcessMemory(pid,freeAddr,(unsigned char *)Shell_dlopen,32);
            WriteProcessMemory(pid,freeAddr+128,(unsigned char *)lib,strlen(lib)+1);
            
             unsigned int linkerBase = FindBaseLibrary("/system/lib/arm/linker",pid);
             printf("ARM linkerBase = %08X\n",linkerBase);
             _dlopen = (void *)(linkerBase + 0x00001378);
             printf("ARM _dlopen = %08X\n",(unsigned int)_dlopen);
#ifdef __arm__ 
#else             
            regs.eip = freeAddr;
            regs.ebx = (unsigned int)_dlopen;
            regs.ecx = freeAddr+128;
#endif            
            SetRegs(pid, &regs);
            TraceContinue(pid);
            if(waitForStop(pid)==0){
                //copy coed back
                WriteProcessMemory(pid,freeAddr,&backupCode[0],256);
                SetRegs(pid,&oldReg);
                
                //TraceContinue(pid);
            }
        }else{
            printf("SetRegs Fail\n");
        }
        
        
    }
    if(Detach(pid)==0){
        printf("DETACH Success\n");
    }
    return (0);    
}


_PayloadData payLoadData;
//
// Assume already attach and stop process
//
#define MAX_FREESPACE_SIZE  512
#define LIBC_SIZE       0x68000
#define LIBLOG_SIZE     0x04000
void PtraceLoadLibrary(bool flgDump,int pid,char *libName,unsigned int funcAddr,unsigned int dlopenAddr,unsigned int libcAddr,unsigned int dlsymAddr)
{
    if(flgDump){
	printf("Dump Mode\n");
    }
    printf("PtraceLoadLibrary(%d,%s,%08X,%08X)\n",pid,libName,funcAddr,dlopenAddr);
    // Find free space from liblog.so
    // because we use free space from this dll, loader program MUST NOT use anyfunction from liblog

    unsigned int freeSpaceAddr = FindFreeSpace(pid,NULL);
    printf("freeSpaceAddr=%08X\n",freeSpaceAddr);
    // Backup freeSpace
    ptraceUtil.BackupMemory(freeSpaceAddr,MAX_FREESPACE_SIZE);
    // Backup targetFunc
    ptraceUtil.BackupMemory(funcAddr,32);
    // 
    ptraceUtil.BackupMemory(dlopenAddr,32);
    MemoryBackup *backupdlopenAddr = ptraceUtil.FindBackupMemory(dlopenAddr);
    printf("backupdlopenAddr found %d\n",backupdlopenAddr->size);
    logger.logHex((unsigned char *)(backupdlopenAddr->data),backupdlopenAddr->size);
    printf("\n");    
    /*
     * FreeSpace
     * [ CODE_OFFSET payLoadData]
     * [ MAX_FREESPACE_SIZE-CODE_OFFSET asmCode] 
     */
    //int codeOffset = CODE_OFFSET;
    unsigned int freeSpaceDataAddr = freeSpaceAddr;
    unsigned int freeSpaceCodeAddr = freeSpaceAddr+CODE_OFFSET;
    printf("freeSpaceCodeAddr=%08X\n",freeSpaceCodeAddr);
    
    // code to write to targetFunction to jump to our code in freespaceAddr
    unsigned char branchToAddressCmd[] = {
        0x00,0x30,0x9F,0xE5,    //LDR r3,[pc,0]    ;load 12 from jump addr
        0x13,0xFF,0x2F,0xE1,    //BX	r3
        0x11,0x22,0x33,0x44,    //jump_addr
    };  
    // set jump_addr to freeSpaceAddr
    *(unsigned int *)((unsigned char*)branchToAddressCmd + 8) = freeSpaceCodeAddr;
    printf("branchToAddressCmd code\n");
    logger.logHex((unsigned char *)(branchToAddressCmd),sizeof(branchToAddressCmd));
    printf("\n");
    //ARM HEX  http://armconverter.com/   
    unsigned char asmCode[] = {
        0x0F,0x30,0xA0,0xE1,    //mov r3,pc         -- copy pc to r3 (r3 => B20 due to prefetch)
        0x88,0x30,0x43,0xE2,    //sub r3,128 + 8    -- point r3 to payload
        // DEBUG simply return
        //0x00,0x00,0xA0,0xE3,    //mov	r0, #0
        //0x1E,0xFF,0x2F,0xE1,    //bx lr
        
        //0x04,0x30,0x83,0xE2,    //add r3,#4      -- set r3 to addr of data[0]]  
        0xFF,0x01,0x2D,0xE9,    //push {r0-r8}      -- save r0-r8
        0x04,0xE0,0x2D,0xE5,    //push {lr}         -- save lr   

        //mprotect(freeSpaceAddr,liblogsize,PROT_READ | PROT_WRITE | PROT_EXEC)
        0xFF,0x01,0x2D,0xE9,    //push {r0-r8}      -- save r0-r8
        0x48,0x00,0x93,0xE5,    //ldr     r0, [r3, 64+8] -- point to freeSpaceAddr
        0x01,0x19,0xA0,0xE3,    //mov     r1, 0x4000    -- liblog size 0x4000
        0x07,0x20,0xA0,0xE3,    //mov     r2, #7
        0x07,0xC0,0xA0,0xE1,    //mov     r12, r7
        0x7D,0x70,0xA0,0xE3,    //mov     r7, 125
        0x00,0x00,0x00,0xEF,    //svc     0x00000000
        0x0C,0x70,0xA0,0xE1,    //mov     r7, r12
        0xFF,0x01,0xBD,0xE8,    //pop  {r0-r8}      -- pop r0-r8
        
        //mprotect(libcAddr,libcsize,PROT_READ | PROT_WRITE | PROT_EXEC)
        0xFF,0x01,0x2D,0xE9,    //push {r0-r8}      -- save r0-r8
        0x4C,0x00,0x93,0xE5,    //ldr     r0, [r3, 64+12] -- point to libcAddr
        0x1A,0x19,0xA0,0xE3,    //mov     r1, 0x68000    -- libc size 
        0x07,0x20,0xA0,0xE3,    //mov     r2, #7
        0x07,0xC0,0xA0,0xE1,    //mov     r12, r7
        0x7D,0x70,0xA0,0xE3,    //mov     r7, 125
        0x00,0x00,0x00,0xEF,    //svc     0x00000000
        0x0C,0x70,0xA0,0xE1,    //mov     r7, r12    
        0xFF,0x01,0xBD,0xE8,    //pop  {r0-r8}      -- pop r0-r8
        
        //alocate exe space mmap(0,size,PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE,0,0);
        //0x5C,0x80,0x93,0xE5,    //ldr r8,[r3,64 + (7*4)]    -- addr of function (mmap) 
        //0x04,0x30,0x2D,0xE5,               //push {r3}

        //0x01,0x19,0xA0,0xE3,    //mov   r1, 0x4000    -- size
	//0x00,0x00,0xA0,0xE3,    //mov	r0, #0
	//0x07,0x20,0xA0,0xE3,    //mov	r2, #7          -- PROT
	//0x00,0x00,0x8D,0xE5,    //str	r0, [sp]        -- 0
	//0x04,0x00,0x8D,0xE5,    //str	r0, [sp, #4]    -- 0
	//0x22,0x30,0xA0,0xE3,    //mov	r3, #34         -- MAP
	//0x38,0xFF,0x2F,0xE1,    //blx   r8                -- mmap
        
        
        
        //move backup back to original
        0x44,0x00,0x93,0xE5,    //LDR r0, [r3,64 + 4]   -- load backup addr to r0
        0x50,0x80,0x93,0xE5,    //LDR r8, [r3,64 + 16]   -- load first instruction
        0x00,0x80,0x80,0xE5,    //STR r8, [r0]      -- copy first instruction]
        0x04,0x00,0x80,0xE2,    //ADD r0, 4         -- add index
        0x54,0x80,0x93,0xE5,    //LDR r8, [r3,64 + 16 + 4]]  -- load 2nd instruction
        0x00,0x80,0x80,0xE5,    //STR r8, [r0]      -- copy 2nd instruction]
        0x04,0x00,0x80,0xE2,    //ADD r0, 4         -- add index
        0x58,0x80,0x93,0xE5,    //LDR r8, [r3,64 + 16 + 8]]  -- load 3rd instruction
        0x00,0x80,0x80,0xE5,    //STR r8, [r0]      -- copy 3rd instruction
        
        //dlopen
        0x04,0x30,0x2D,0xE5,    //push {r3}         -- dlopen migh destroy r0-r4
        0x00,0x10,0xA0,0xE3,    //mov r1, #0        -- LOADNOW 
        0x03,0x00,0xA0,0xE1,    //mov r0,r3         -- r3 already point to libname
        0x40,0x80,0x93,0xE5,    //ldr r8,[r3,64]    -- addr of function (dlopen) 408093E5
        0x38,0xFF,0x2F,0xE1,    //blx r8            -- call dlopen
        0x04,0x30,0x9D,0xE4,    //pop   {r3}
        
        //dlsym use result in r0 and param to dlsym
        //0x04,0x30,0x2D,0xE5,    //push {r3}         -- dlopen migh destroy r0-r4
        //0x5C,0x80,0x93,0xE5,    //ldr r8,[r3,64 + (7*4)]    -- addr of function (dlsym)
        //0x03,0x10,0xA0,0xE1,    //mov r1,r3
        //0x60,0x10,0x81,0xE2,    //add r1,64 + (8*4)     -- r1 point to addr of funcName
        //0x38,0xFF,0x2F,0xE1,    //blx r8            -- call dlsym
        //0x04,0x30,0x9D,0xE4,    //pop   {r3}
        //0x5C,0x80,0x93,0xE5,    //ldr r8,[r3,64 + (7*4)]    -- addr of function (dlsym)
        
        
        
        //FAKE CALL TO MPROTECT TO CHECK ADDR
        //0xFF,0x01,0x2D,0xE9,    //push {r0-r8}      -- save r0-r8
        //0x01,0x19,0xA0,0xE3,    //mov     r1, 0x4000    -- liblog size 0x4000
        //0x07,0x20,0xA0,0xE3,    //mov     r2, #7
        //0x07,0xC0,0xA0,0xE1,    //mov     r12, r7
        //0x7D,0x70,0xA0,0xE3,    //mov     r7, 125
        //0x00,0x00,0x00,0xEF,    //svc     0x00000000
        //0x0C,0x70,0xA0,0xE1,    //mov     r7, r12
        //0xFF,0x01,0xBD,0xE8,    //pop  {r0-r8}      -- pop r0-r8        
        
        
        // call kkk by using address writtern by loader that we just loaded)
        //0x60,0x80,0x93,0xE5,    //ldr r8,[r3,64 + (8*4)]    -- addr of function (kkkAddr)
        //0x04,0x30,0x2D,0xE5,    //push {r3}         -- dlopen migh destroy r0-r4
        //0x38,0xFF,0x2F,0xE1,    //blx r8            -- call kkk
        //0x04,0x30,0x9D,0xE4,    //pop   {r3}

        // restore all register
        0x04,0xE0,0x9D,0xE4,    //pop  {lr}         -- pop lr
        0xFF,0x01,0xBD,0xE8,    //pop  {r0-r8}      -- pop r0-r8
        
        //jump to newFreeSpaceCodeAddr which loader create for us
        0x68,0x20,0x93,0xE5,    //ldr r2,[r3,64 + (10*4)]    -- addr of newFreeSpaceCodeAddr
        0x12,0xFF,0x2F,0xE1,    //bx r2             -- jump to newFreeSpaceCodeAddr
        
        //0x1E,0xFF,0x2F,0xE1,    //bx lr
        
        0x14,0x14,0x14,0x14,    //backup instruction[3]
        0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,    
        0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,
        
        0x00,0x30,0x9F,0xE5,    //LDR r3,[pc,0]    ;load 12 from jump addr
        0x13,0xFF,0x2F,0xE1,    //BX	r3
        0x11,0x22,0x33,0x44,    //jump_addr2        
    };
    unsigned char backup_pattern[] = {0x14,0x14,0x14,0x14};
    int backupOffset = MemoryFind(asmCode,sizeof(asmCode),backup_pattern,sizeof(backup_pattern));
    printf("backupOffset=%d\n",backupOffset);
    if(backupOffset <0){
        printf("backupOffset not found\n");
        return;
    }
    *(unsigned int *)((unsigned char*)asmCode + sizeof(asmCode) - 4) = funcAddr+32;
    
    // copy backup write code to backup in asmCode
    MemoryBackup *backupFunc = ptraceUtil.FindBackupMemory(funcAddr);
    printf("backupFunc found %d\n",backupFunc->size);
    memcpy((void *)(asmCode + backupOffset),(void *)backupFunc->data,backupFunc->size);
    logger.logHex((unsigned char *)(backupFunc->data),backupFunc->size);
    printf("\n");
    
    if(memcmp((unsigned char *)(backupFunc->data),branchToAddressCmd,8)==0){
	printf("WANRING: already patch funcAddr\n");
    }
    
   // make sure payLoadData < CODE_OFFSET
    if(sizeof(payLoadData)>CODE_OFFSET){
        printf("ERROR: payLoadData (%d) > CODE_OFFSET (%d)\n",sizeof(payLoadData),CODE_OFFSET);
        return;
    }
    
    // make sure asmCode < MAX_FREESPACE_SIZE - CODE_OFFSET
    if(sizeof(asmCode)>(MAX_FREESPACE_SIZE - CODE_OFFSET)){
        printf("ERROR: asmCode (%d) > (MAX_FREESPACE_SIZE - CODE_OFFSET) (%d)\n",sizeof(asmCode),(MAX_FREESPACE_SIZE - CODE_OFFSET));
        return;
    }    
    
    printf("asmCode size=%d\n",sizeof(asmCode));
    ptraceUtil.WriteProcessMemory(freeSpaceCodeAddr,asmCode, sizeof(asmCode));
    printf("Dump freeSpaceCodeAddr\n");
    ptraceUtil.DumpHex(freeSpaceCodeAddr,sizeof(asmCode));
    printf("\n");
    
    memset(&payLoadData,0,sizeof(payLoadData));
    // copy libName to payloadData
    strcpy(payLoadData.libName,libName);
    // copy dlopen addr to payload
    payLoadData.dlopenAddr = dlopenAddr;
    payLoadData.funcAddr = funcAddr;
    payLoadData.freeSpaceAddr = freeSpaceAddr;
    payLoadData.libcAddr = libcAddr;
    memcpy((void *)(payLoadData.backupInstruction),(void *)backupFunc->data,12);
    payLoadData.dlsymAddr = dlsymAddr;
    // hard code call back function kkk();)
    //strcpy(payLoadData.funcName,"kkk");
    
    // copy payload to freeSpaceDataAddr;
    if(!flgDump){
	if(ptraceUtil.WriteProcessMemory(freeSpaceDataAddr,(unsigned char *)&payLoadData, sizeof(payLoadData))){
	    printf("Patch payload success\n");
	}
    }
    printf("Dump freeSpaceDataAddr\n");
    ptraceUtil.DumpHex(freeSpaceDataAddr,sizeof(payLoadData));
    printf("\n");

    // Create tracer.bin contain original data of freeAddress
    
    if(!flgDump){
	MemoryBackup *backupFreeSpace = ptraceUtil.FindBackupMemory(freeSpaceAddr);
	if(backupFreeSpace!=NULL){
	    WriteAllBytes(TRACE_BIN,backupFreeSpace->data,backupFreeSpace->size);
	}
    }

    //unsigned int libcSize = GetBaseLibraryTextSize("/system/lib/arm/libc.so",pid);    
    // patch WriteAddr
    //for(int i=0;i<libcSize - sizeof(branchToAddressCmd);i+= sizeof(branchToAddressCmd)){
    //    if(ptraceUtil.WriteProcessMemory(writeAddr+i,branchToAddressCmd,sizeof(branchToAddressCmd))==false){
    //        printf("Write Fail at %08X\n",writeAddr+i);
    //        break;
    //    }
    //}
    if(!flgDump){
	if(ptraceUtil.WriteProcessMemory(funcAddr,branchToAddressCmd,sizeof(branchToAddressCmd))){
	   printf("Patch target function success\n");
	}
    }
    
    //getchar();
    //ptraceUtil.Continue();
    //if(waitForStop(-1)==0){
    //    getchar();
    //}
        // Restore targetFunc
        //ptraceUtil.RestoreMemory(writeAddr);
        // Restore freeSpace
    //ptraceUtil.RestoreMemory(freeSpaceAddr);
    //}
    //ptraceUtil.Continue();
}


int inject_arm(bool flgDump,int pid,char *lib,unsigned int funcOffset)
{
    unsigned int offset_arm_dlopen   = 0x00000390;  //ref with /system/lib/arm/libdl.so find from armhlp
    
    printf("inject_arm pid=%d lib=[%s] funcOffset=%08X\n",pid,lib,funcOffset);
    unsigned int libdl_base = FindBaseLibrary("/system/lib/arm/libdl.so",pid);
    if(libdl_base == 0){
        printf("libdl.so not found Try linker\n");
        libdl_base = FindBaseLibrary("/system/lib/arm/linker",pid);
        offset_arm_dlopen = 0x00001378; ///system/lib/arm/linker
    }
    printf("Target libdl_base = %08X\n",libdl_base);    
    unsigned int libc_base = FindBaseLibrary("/system/lib/arm/libc_orig.so",pid);
    if(libc_base == 0){
        printf("libc_orig.so not found: try libc.so\n");            
        libc_base = FindBaseLibrary("/system/lib/arm/libc.so",pid);
    }
    printf("Target libc_base = %08X\n",libc_base);
    unsigned int funcAddr = libc_base + funcOffset;
    unsigned int dlopenAddr = libdl_base + offset_arm_dlopen;
    //unsigned int mmapAddr = libc_base + 0x000182F4;     //mmap();
    unsigned int dlsymAddr = libc_base + 0x0008A234;    // dlsym()
    printf("funcAddr=%8X dlopen=%08X libc_base=%08x dlsym=%08X\n",funcAddr,dlopenAddr,libc_base,dlsymAddr);
    printf("Trying to ATTACH\n");
    
    if(ptraceUtil.Attach(pid)!=0){
        printf("Attach fail\n");
        return -1;
    }
    printf("ATTACH Success\n");
    if(waitForStop(pid)==0){
        //struct pt_regs oldReg,regs;
        //GetRegs(pid,&regs);
        //memcpy(&oldReg,&regs,sizeof(struct pt_regs));
        //ShowRegs(&oldReg);
        PtraceLoadLibrary(flgDump,pid,lib,funcAddr,dlopenAddr,libc_base,dlsymAddr);
    }
    if(ptraceUtil.Detach()==0){
        printf("DETACH Success\n");
    }
    return 0;
}

void ReadAllLines(char *filename,std::vector<std::string> &out)
{
    char buffer[2048];
    FILE *fp = NULL;
    fp = fopen(filename, "rt");
    if (fp == NULL) {
        goto done;
    }
    out.clear();
    while (fgets(buffer, sizeof (buffer), fp)) {
        buffer[strlen(buffer)-1] = 0;
        std::string line = buffer;
        out.push_back(line);
    }
done:
    if (fp) {
        fclose(fp);
    }
}


unsigned int GetFunctionOffset(char *fileName,char *funcName)
{
    printf("GetFunctionOffset(%s,%s)\n",fileName,funcName);
    std::vector<std::string> lines;
    ReadAllLines(fileName,lines);
    for(int i=0;i<lines.size();i++){
	char filler[128];
	char stroffset[128];
	char fName[128];
	if(sscanf(lines[i].c_str(),"%s%s%s%s%s",filler,filler,filler,stroffset,fName)==5){
	    //printf("%s %s\n",fName,stroffset);
	    if(strcmp(fName,funcName)==0){
		unsigned int offset=0;
		printf("%s\n",lines[i].c_str());
		if(sscanf(stroffset,"%x",&offset)==1){
		    printf("offset found %08X\n",offset);
		    return offset;
		}
		break;
	    }
	}
    }
    printf("ERROR: GetFunctionOffset not found\n");
    return 0;
}

int counter = 0;

int test1()
{
    counter++;
    printf("test1 %d\n",counter);
    __asm__(
	"movl $0x1414,%eax \n"
	"int $0x3\n"
    );
}

int test2()
{
    counter++;    
    printf("test2 %d\n",counter);
    LOGD("test2\n");

}

void *AntiStopThreadFunc(void *mesg)
{
    printf("AntiStopThreadFunc start with param [%s]\n",(char *)mesg);
    while(true){
	double start = GetTickCount();
	sleep(5);
	double end = GetTickCount();
	double diff = end - start;
	LOGD("%f\n",diff);
	if(diff > 6000){
	    printf("Someone stop me %f\n",diff);
	    exit(0);
	}
    }
}

void *AntiDebugThreadFunc(void *mesg)
{
    
    printf("AntiDebugThreadFunc with param [%s]\n",(char *)mesg);
    while(true){
	int tracerID = GetMyTracerPID();
	if(tracerID!=0){
	    printf("Someone debug me %d\n",tracerID);
	    exit(0);
	}
    }
    
}

void *mono_search_hook (char *aname, void *user_data)
{
        /*GList *tmp;
       for (tmp = loaded_assemblies; tmp; tmp = tmp->next) {
               MonoAssembly *ass = tmp->data;
               if (mono_assembly_names_equal (aname, &ass->aname))
		       return ass;
       }
       return NULL;*/
    printf("mono_search_hook\n");
    return NULL;
}

void loadMono()
{
    void *handle = dlopen("/data/app-lib/com.gravity.romg-2/libmono.so",RTLD_NOW);

#define MONO_API(h, r, n, p) \
    r (* n) p;\
    n = ( r (*) p )dlsym(h, #n);\
    if(n==NULL){ printf("ERROR %s not found\n",#n); exit(-1); }

#define MONO_LOAD(n) \
    {\
    void *assembly = mono_domain_assembly_open(domain,"/data/local/tmp/Managed/mono/1.0/" n);\
    void *image = mono_assembly_get_image(assembly);\
    printf("%s assembly=%08X image=%08X\n",n,(unsigned int)assembly,(unsigned int)image);\
    }

    printf("%08X\n",(unsigned int)handle);
    MONO_API(handle,void *,mono_get_root_domain,(void));
    MONO_API(handle,void  ,mono_set_dirs,(const char *,const char *));
    MONO_API(handle,void *,mono_jit_init,(const char *));
    MONO_API(handle,void *,mono_jit_init_version,(const char *,const char *));
    MONO_API(handle,void *,mono_jit_exec,(void *,void *,int,void *));		
    MONO_API(handle,void *,mono_domain_assembly_open,(void *,const char *));
    MONO_API(handle,void *,mono_config_parse,(void *));
    MONO_API(handle,void *,mono_assembly_load,(char *,char *,MonoImageOpenStatus *));
    MONO_API(handle,void *,mono_assembly_loaded,(char *));
    MONO_API(handle,void *,mono_assembly_get_image,(void *));
    MONO_API(handle,char *,mono_assembly_getrootdir,(void));
    MONO_API(handle,char *,mono_unity_get_data_dir,(void));
    MONO_API(handle,void  ,mono_unity_set_data_dir,(char *));
    MONO_API(handle,void *,mono_unity_set_vprintf_func,(void *));
    MONO_API(handle,void *,mono_trace_set_level_string,(char *));
    MONO_API(handle,void *,mono_trace_set_mask_string,(char *));
    MONO_API(handle,void  ,mono_install_assembly_search_hook,(void *,void *));

   // mono_get_runtime_build_info = (char *(*)(void))dlsym(handle, "mono_get_runtime_build_info");
    printf("addr %08X\n",(unsigned int)mono_trace_set_level_string);

    mono_config_parse(NULL);
    mono_set_dirs("/data/local/tmp/Managed","/data/local/tmp/Managed");
    mono_unity_set_data_dir("/data/local/tmp/Managed/mono/1.0");
    void *domain = mono_jit_init("kwang");
    void *rootDomain = mono_get_root_domain();                
    printf("%s\n",mono_unity_get_data_dir());                
    printf("mono_assembly_getrootdir = %s\n",mono_assembly_getrootdir());                
    printf("domain %08X rootDomain %08X\n",(unsigned int)domain,(unsigned int)rootDomain);

    mono_unity_set_vprintf_func((void *)vprintf);                
    mono_trace_set_level_string("debug");
    mono_trace_set_mask_string("all");


    //void *domain = mono_jit_init_version("kwang","v1.1.4322");

    MONO_LOAD("System.dll");
    MONO_LOAD("System.Core.dll");
    MONO_LOAD("System.Xml.dll");
    MONO_LOAD("Mono.Security.dll");

    printf("begin install search hook\n");
    mono_install_assembly_search_hook ((void *)mono_search_hook, NULL);
    printf("end install search hook\n");

    //MonoImageOpenStatus openStatus;
    //void *loadassembly = mono_assembly_load("System.dll","/data/local/tmp/Managed",&openStatus);
    //printf("loadassembly %08X %d\n",(unsigned int)loadassembly,(int)openStatus);

    //void *assembly = mono_domain_assembly_open(domain,"/data/local/tmp/Managed/mono/1.0/mscorlib.dll");
    void *assembly = mono_domain_assembly_open(domain,"/data/local/tmp/hello.exe");
    if(assembly==NULL){
	printf("hello.exe not found\n");
	exit(0);
    }
    void *image = mono_assembly_get_image(assembly);
    printf("assembly %08X image %08X\n",(unsigned int)assembly,(unsigned int)image);

    /*if(assembly != NULL){
	try{
	    mono_jit_exec(domain,assembly,0,NULL);
	}catch(...){
	    printf("Exception \n");
	}
    }*/
    //printf("info %s\n",mono_get_runtime_build_info());

}

void testLoader()
{
    void *handle = dlopen("/data/local/tmp/libloader.so",RTLD_NOW);
    printf("load success\n");
    /*FileMap m;
    void *mapAddr = m.map("/data/local/tmp/hello.exe");
    printf("mapAddr=%08X\n",(unsigned int)mapAddr);*/
    while(1){
        sleep(1);
    }
    //m.unMap();
}

void decryptDes()
{
    void *handle = dlopen("/data/local/tmp/libslua.so",RTLD_NOW);
    if(handle!=NULL) printf("load success\n");
    MONO_API(handle,void,InitDes,(void));
    MONO_API(handle,unsigned int,GetDesCodeLenth,(void *));
    MONO_API(handle,void,desDKey,(void *,int,void *));
    MONO_API(handle,int,IsDesCode,(void *,int));
    
    //loadbufferx/AScript.org.puremvc.lua.multicore.patterns.facade.Facade
    std::vector<unsigned char> buffer = ReadFile("/data/local/tmp/loadbufferx/AScript.org.puremvc.lua.multicore.patterns.facade.Facade");
    printf("%d\n",buffer.size());
    int isDesCode = IsDesCode(&buffer[0],buffer.size());
    printf("%d\n",isDesCode);
    int outSize = GetDesCodeLenth(&buffer[0]);
    printf("%08X %08X\n",outSize,buffer.size());   
    if(outSize > 0){
	char decryptBuffer[outSize];
	std::string outFileName = "/data/local/tmp/loadbufferx/AScript.org.puremvc.lua.multicore.patterns.facade.Facade.lua";
	desDKey(&buffer[0],buffer.size(),&decryptBuffer[0]);
	//printf("%08X\n",ret);
	if(DumpMemory(UINT(&decryptBuffer[0]),outSize,(char *)outFileName.c_str())){
	    printf("save %s success\n",(char *)outFileName.c_str());
	}else{
	    printf("save %s fail\n",(char *)outFileName.c_str());
	}
                //DumpHex(stdout,&decryptBuffer[0],outSize);
                //break;
    }    
    return;
    
    std::string path = "/data/local/tmp/loadbufferx";
    std::vector<std::string> files = DirectoryListFile(path);
    for(int i=0;i<files.size();i++){
        char fileName[512];
        strcpy(fileName,files[i].c_str());
        if(strcmp(fileName,".")==0) continue;
        if(strcmp(fileName,"..")==0) continue;
        if(strstr(fileName,".lua")!=NULL) continue;
        std::string inFileName = path + "/" + files[i];
        std::vector<unsigned char> buffer = ReadFile(inFileName.c_str());
        int isDesCode = IsDesCode(&buffer[0],buffer.size());
        printf("%d %s\n",isDesCode,fileName);
        if(isDesCode == 0){
            int outSize = GetDesCodeLenth(&buffer[0]);
            printf("%08X %08X\n",outSize,buffer.size());
            if(outSize > 0){
                char decryptBuffer[outSize];
                std::string outFileName = path + "/" + files[i] + std::string(".lua");
                desDKey(&buffer[0],buffer.size(),&decryptBuffer[0]);
                //printf("%08X\n",ret);
                if(DumpMemory(UINT(&decryptBuffer[0]),outSize,(char *)outFileName.c_str())){
                    printf("save %s success\n",(char *)outFileName.c_str());
                }
                //DumpHex(stdout,&decryptBuffer[0],outSize);
                //break;
            }else{
                break;
            }
        }
    }
    //DumpHex(stdout,&buffer[0],outSize);
    //printf("\n");
    //DumpHex(stdout,&decryptBuffer[0],outSize);
    
}

int main(int argc, char** argv) {
    bool flgDump = false;
    char funcName[128] = {0};
    char libraryName[128] = {0};
    int pid = 0;
    int funcOffset = 0;
    for(int i=1;i<argc;i++){
	if(argv[i][0] == '-'){
	    if(strcmp(argv[i],"-d")==0){
		printf("DumpMode\n");
		flgDump = true;
	    }
	    if(strcmp(argv[i],"-f")==0){
		i++;
		strcpy(funcName,argv[i]);
		if(strlen(funcName)==0){
		    strcpy(funcName,"getpid");
		}
		if(strncmp(funcName,"0x",2)==0){
		    sscanf(&funcName[2],"%x",&funcOffset);
		}else{
		    printf("Funcion Name=%s\n",funcName);
		    funcOffset = GetFunctionOffset("./libc_orig.offset",funcName);
		}
		printf("funcOffset=%08X\n",funcOffset);
	    }
	    if(strcmp(argv[i],"-p")==0){
		i++;
		if(isdigit(argv[i][0])){
		    pid = atoi(argv[i]);
		}else{
		    printf("Find by name [%s]\n",argv[i]);
		    pid = FindProcessByName(argv[i],NULL);
		    printf("pid=%d\n",pid);
		    if(pid==getpid()){
			printf("Error: process (%d) not found\n",pid);
			return 0;
		    }
		}
	    }
	    if(strcmp(argv[i],"-l")==0){
		i++;
		strcpy(libraryName,argv[i]);
	    }
	    if(strcmp(argv[i],"-tdecrypt")==0){
                decryptDes();
		exit(0);
	    }
            if(strcmp(argv[i],"-tslua")==0){
                Slua slua;
                if(!slua.Init()){
                    printf("slua Init Fail %s\n",dlerror());
                    exit(0);
                }
		char *fileName = "/data/local/tmp/script/rom.lua";
		if(argv[i+1]!=NULL){
		    fileName = argv[i+1];
		}
		printf("Run File [%s]\n",fileName);
                lua_State *L = slua.luaL_newstate();
                slua.luaL_openlibs(L);
                //printf("%d\n",slua.lua_gettop(L));
                //for(int i=0;i<20;i++){
                    if(!slua.DoFile(L,fileName)){
                        printf("Fail %s\n",slua.lastError.c_str());                
                    }
                //}
                //printf("%d\n",slua.lua_gettop(L));
/*                std::vector<unsigned char> buffer = ReadFile("/data/local/tmp/script/rom.lua");
                printf("size=%d\n",buffer.size());
                int ret = slua.luaL_loadbufferx(L,(char *)&buffer[0],buffer.size(),"/data/local/tmp/script/rom.lua",NULL);
                printf("ret=%d\n",ret);
                if(ret !=0){
                    std::string lastError = std::string(slua.luaL_tolstring(L, -1,NULL));
                    LOGE("Slua::DoFile Fail load %s",lastError.c_str());
                    slua.lua_gettop(L);      // get message from stack
                    return false;
                }else{
                    ret = slua.lua_pcallk(L,0,-1,0,NULL,NULL);
                    std::string lastError = std::string(slua.luaL_tolstring(L, -1,NULL));
                    if(ret !=0){
                        LOGE("Slua::DoFile exec Fail %s",lastError.c_str());
                        return false;
                    }else{
                        lastError = "";
                        return true;
                    }
                }*/
                exit(0);
            }

	    if(strcmp(argv[i],"-tloadso")==0){
		if(argv[i+1]==NULL){
		    printf("USAGE: %s -tloadso fileName\n",argv[0]);
		    exit(0);
		}
		bool flgDump = false;
		if(argv[i+2]!=NULL){
		    flgDump = true;
		}
		std::string filename = std::string("/data/local/tmp/") + ((char *)argv[i+1]);
		if(argv[i+1][0]=='/'){
		    filename = std::string("") + ((char *)argv[i+1]);
		}
		void *handle = dlopen(filename.c_str(),RTLD_NOW);
		if(handle!=NULL){
		    printf("load success\n");
                    std::vector<std::string> out;
                    ReadMaps(getpid(),out);
                    for(int j=0;j<out.size();j++){
			printf("%s\n",out[j].c_str());
			if(flgDump){
			    if(strstr(out[j].c_str(),(char *)argv[i+1])!=NULL){
				char addr[64];
				char perms[64];
				char unk[64];
				char unk2[64] = {0};
				char unk3[64] = {0};
				char unk4[512] = {0};
				sscanf(out[j].c_str(),"%s %s %s %s %s %s",addr, perms, unk,unk2,unk3,unk4);
				std::string strAddr = addr;
				std::replace( strAddr.begin(), strAddr.end(), '-', ' ');
				unsigned int from;
				unsigned int to;
				sscanf(strAddr.c_str(),"%x %x",&from,&to);

				DumpHex(stdout,(unsigned char *)from,to - from);
			    }
			}
                    }
		    MONO_API(handle,void *,Test1,(void));
		    Test1();
		}else{
		    printf("load fail %s\n",dlerror());
		}
		exit(0);
	    }
	    if(strcmp(argv[i],"-tclient")==0){
		int port = 1414;
		if(argv[i+1]!=NULL){
		    sscanf(argv[i+1],"%d",&port);
		}
		printf("port=%d\n",port);
		SimpleTCPClient client(port);
		if(client.ConnectLocal()){
		    printf("Connect success %d\n",port);
		    client.sock.SendLine("! dofile('/data/local/tmp/ragnarok.lua')");
		    std::vector<std::string> lines = client.sock.ReadUntil(BSC_OK);
		    for(int j=0;j<lines.size();j++){
			printf("%s\n",lines[j].c_str());fflush(stdout);
		    }
                    while(!client.sock.IsClosed()){
                        printf(">");fflush(stdout);
                        char line[1024];
                        gets(line);
                        client.sock.SendLine(line);
                        //std::string ret;
			std::vector<std::string> lines = client.sock.ReadUntil(BSC_OK);
                        /*while(ret!=BSC_OK){
                            ret = client.sock.ReadLine();
                            //if(ret==""){
                            //    break;
                            //}
                            if(ret!=""){
                                printf("%s\n",ret.c_str());fflush(stdout);
                            }
                        }*/
			for(int j=0;j<lines.size();j++){
			    printf("%s\n",lines[j].c_str());fflush(stdout);
			}
			usleep(500);
                    }
		    //client.sock.Close();
		}
		exit(0);
	    }
	    if(strcmp(argv[i],"-tloader")==0){
		//loadMono();
		testLoader();
		exit(0);
	    }
/*	    if(strcmp(argv[i],"-tlua")==0){
		//Logger *luaLogger = new AndroidLogger("testlua",true);
		LuaScript *lua = new LuaScript(tolua_lua_server_open);
                lua->luaLogger->logStr("Hello");
                lua->luaLogger->logHex((unsigned char *)strcmp,35);
                lua->luaLogger->logStr("Hello");
                lua->execFile("ragnarok.lua");
		
		std::vector<std::string> cmds = GetCurrentCommandLine();
		for(int i=0;i<cmds.size();i++){
		    printf("%s\n",cmds[i].c_str());
		}
		exit(0);
	    }*/
	    
	    if(strcmp(argv[i],"-t2")==0){
		loadMono();
		exit(0);
	    }
            if(strcmp(argv[i],"-t")==0){
		unsigned int targetIP = 0;
		i++;
		sscanf(argv[i],"%X",&targetIP);
                printf("test with pid %d %08X\n",pid,targetIP);
                GetOffsets();
                GetRemoteAddress(pid);
		//void* handle = dlopen("/data/local/tmp/libloader.so",RTLD_LAZY);
		//printf("test with pid %08X\n",(unsigned int)handle);
		//dlclose(handle);
                //dlopen("aaaa",0);
                //_dlopen("aaaa",0);
		printf("Trying to STOP\n");
		kill(pid, SIGSTOP);
		if(waitForStop(pid)==0){
		    printf("stop by signal\n");
		}
		printf("Trying to ATTACH\n");
		if(ptraceUtil.Attach(pid)!=0){
		    //sleep(100);		    
		    return -1;
		}
		printf("ATTACH Success\n");
		//ptraceUtil.Detach();
		//return 0;
		if(waitForStop(pid)==0){
		    
		    long parameters[10];    

		    struct pt_regs oldReg,regs;
		    ptraceUtil.GetRegs(&regs);
		    memcpy(&oldReg,&regs,sizeof(struct pt_regs));
		    ShowRegs(&oldReg);
		    if(ptraceUtil.SetRegs(&regs)==0){
			unsigned int freeAddr = (unsigned int)FindFreeSpace(pid,NULL) + sizeof(long);
			printf("freespaceaddr=%08X\n",freeAddr);
			unsigned char backupCode[256] = {0};
			unsigned char currentCode[256] = {0};
			/*ptraceUtil.ReadProcessMemory(freeAddr,&backupCode[0],256);
			logger.logHex(&backupCode[0],256);
			char *dllFile = "/data/local/tmp/libloader.so";
			if(!ptraceUtil.WriteProcessMemory(freeAddr,(unsigned char *)dllFile,32)){
			    printf("WriteProcessMemory fail\n");
			}
			ptraceUtil.ReadProcessMemory(freeAddr,&currentCode[0],256);
			logger.logHex(&currentCode[0],256);

			//parameters[0] = freeAddr;       
			parameters[0] = 0x08049E60;
			parameters[1] = RTLD_NOW| RTLD_GLOBAL;
			if (ptraceUtil.Call((uint32_t)_dlopen, parameters, 2, &regs) == -1){    
			    printf("Call  fail\n");
			}else{
			    printf("Call  Success %08X\n",(uint32_t) _dlopen);
			    ptraceUtil.GetRegs(&regs);
			    int returnValue  = (int)ptraceUtil.GetReturnValue(&regs);
			    printf("Return %d %s\n",returnValue,strerror(returnValue));
			    ShowRegs(&regs);
			}
			
			ptraceUtil.WriteProcessMemory(freeAddr,&backupCode[0],256);
			//ptraceUtil.ReadProcessMemory(freeAddr,&currentCode[0],256);
			//logger.logHex(&currentCode[0],256);
			
			SetRegs(pid,&oldReg);
			*/
			
			//ptraceUtil.Continue();			
			//ptraceUtil.Push(0,&regs);
			unsigned char codetmp[256];
			ptraceUtil.ReadProcessMemory(regs.eip,&codetmp[0],256);
			logger.logHex(&codetmp[0],256);
			
			if(targetIP!=0){
			    regs.eip = targetIP; 

			    ptraceUtil.SetRegs(&regs);
			    //ptraceUtil.ShowRegs();

			    //ptraceUtil.Continue();
			    int stat = 0;
			    //waitpid(pid, &stat, WUNTRACED);  
			    //waitpid(pid, &stat, 0);  
			    while(stat != 0xb7f){
				if(ptraceUtil.Continue()==-1){
				    printf("error");
				}
				waitpid(pid, &stat, 0);  
				if (WIFSTOPPED(stat)){
				    printf("WIFSTOPPED [%d]",WSTOPSIG(stat));
				}
				//if(WSTOPSIG(stat)){
				    //printf("WSTOPSIG ");
				//}
				//if(WTERMSIG(stat)){
				    //printf("WTERMSIG ");
				//}
				if(WIFSIGNALED(stat)){
				    printf("WIFSIGNALED [%d]",WTERMSIG(stat));
				}
				//if(WEXITSTATUS(stat)){
				    //printf("WEXITSTATUS ");
				    //break;
				//}
				if(WIFEXITED(stat)){
				    printf("WIFEXITED [%d]",WEXITSTATUS(stat));
				    break;
				}
				printf(" %08X\n",stat);			    
			    }
			    printf("Here\n");
			    ptraceUtil.GetRegs(&regs);
			    int returnValue  = (int)ptraceUtil.GetReturnValue(&regs);
			    printf("Return %d %s\n",returnValue,strerror(returnValue));
			    ShowRegs(&regs);			
			}
			SetRegs(pid,&oldReg);
		    }else{
			printf("SetRegs Fail\n");
		    }
		    /*unsigned int addr = 0x08052F51;
		    printf("Stop 1\n");
		    unsigned char buf[32];
		    memset(&buf[0],0,sizeof(buf));
		    ptraceUtil.ReadProcessMemory(addr,&buf[0],32);
		    logger.logHex(&buf[0],sizeof(buf));
		    buf[0] = 'P';
		    ptraceUtil.WriteProcessMemory(addr,&buf[0],32);
		    ptraceUtil.ReadProcessMemory(addr,&buf[0],32);
		    logger.logHex(&buf[0],sizeof(buf));
		    */
		    
		    //TraceContinue(pid);
		    //if(waitForStop(pid)==0){
		    //sleep(1);
		    //}
		    //printf("Enter to continue\n");
		    //getchar();
		    ptraceUtil.Detach();
		    kill(pid, SIGCONT);
		}
                return 0;
            }
	    if(strcmp(argv[i],"-dummy")==0){
		std::string exeName = GetCurrentExecutable();
		std::string exePath = GetCurrentExecutableDirectory();
		printf("%s %s\n",exeName.c_str(),exePath.c_str());
		
		if(IsSelinuxEnabled()){
		    printf("SelinuxEnabled\n");
		}
		//TempDirectory tmpDir;
		//printf("tempdir = %\n",tmpDir.path());
		
		pthread_t thread1;
		int iret1 = pthread_create( &thread1, NULL, AntiDebugThreadFunc, (void*) "1234");
		int iret2 = pthread_create( &thread1, NULL, AntiStopThreadFunc, (void*) "1234");
		printf("%d %d\n",iret1,iret2);

		printf("Dummy Mode\n");
		printf("kwangpid=%d %08X %08X %d\n",getpid(),(unsigned int)test1,(unsigned int)test2,counter);
		//IsDebugDetect();
		while(true){
		    sleep(2);
		    LOGD("kwangpid=%d %08X %08X %d\n",getpid(),(unsigned int)test1,(unsigned int)test2,counter);
		    //printf("kwangpid=%d\n",getpid());
		    //fflush(stdout);
		}
	    }
	    if(strcmp(argv[i],"-sleep")==0){
		printf("Sleep Mode\n");
		printf("kwangpid=%d %08X %08X %d\n",getpid(),(unsigned int)test1,(unsigned int)test2,counter);
		while(true){
		    sleep(3);
		    LOGD("kwangpid=%d %08X %08X %d\n",getpid(),(unsigned int)test1,(unsigned int)test2,counter);
		    fflush(stdout);
		}
	    }
	    if(strcmp(argv[i],"-getchar")==0){
		printf("getchar Mode\n");
		printf("kwangpid=%d %08X %08X %d\n",getpid(),(unsigned int)test1,(unsigned int)test2,counter);
		while(true){
		    getchar();
		}
	    }	    
	    
	}
    }
    if((pid!=0)&&(strlen(libraryName)!=0)){
	if(funcOffset==0){
	    return 0;
	}
	inject_arm(flgDump,pid,libraryName,funcOffset);
    }else{
	printf("Usage:%s [option]\n",argv[0]);
	printf("option:\n");
	printf("-d				    ;dump mode\n");
	printf("-p processID|processName	    \n");
	printf("-f functName			    \n");
	printf("-l libraryName			    \n");
    }
    /*
    if(argc!=4){
        printf("Usage %s test\n",argv[0]);
        printf("Usage %s inject [pid|pname] file\n",argv[0]);
        printf("Usage %s [injectarm|dumparm] [pid|pname] file\n",argv[0]);
        printf("Usage %s injectapp [pid|pname] file\n",argv[0]);        
        printf("Usage %s [injectfunc] [pid|pname] file\n",argv[0]);
        return(-1);
    }
    //LoadSharedLibrary();
    // always remove trace bin
    remove(TRACE_BIN);
    lib = argv[3];

    if(stricmp(argv[1],"test")==0){
        test(1,2,3,4);
        return(0);
    }else if(stricmp(argv[1],"inject")==0){
        int pid;
        if(isdigit(argv[2][0])){
            pid = atoi(argv[2]);
        }else{
            printf("Find by name [%s]\n",argv[2]);
            pid = FindProcessByName(argv[2],NULL);
            printf("pid=%d\n",pid);
            if(pid==getpid()){
                printf("process not found\n");
                return 0;
            }
        }
        if(pid>0){
            inject(pid,argv[3]);
        }
        return(0);
    }else if(stricmp(argv[1],"injectarm")==0){
        int pid;
        if(isdigit(argv[2][0])){
            pid = atoi(argv[2]);
        }else{
            printf("Find by name [%s]\n",argv[2]);
            pid = FindProcessByName(argv[2],NULL);
            printf("pid=%d\n",pid);
            if(pid==getpid()){
                printf("process not found\n");
                return 0;
            }            
        }
        if(pid>0){
            inject_arm(false,pid,argv[3]);
            printf("injectarm done\n");
        }
        return(0);  
    }else if(stricmp(argv[1],"dumparm")==0){
        int pid;
        if(isdigit(argv[2][0])){
            pid = atoi(argv[2]);
        }else{
            printf("Find by name [%s]\n",argv[2]);
            pid = FindProcessByName(argv[2],NULL);
            printf("pid=%d\n",pid);
            if(pid==getpid()){
                printf("process not found\n");
                return 0;
            }            
        }
        if(pid>0){
            inject_arm(true,pid,argv[3]);
            printf("dumparm done\n");
        }
        return(0);  	
    }else if(stricmp(argv[1],"injectapp")==0){
        int pid;
        if(isdigit(argv[2][0])){
            pid = atoi(argv[2]);
        }else{
            printf("Find by name [%s]\n",argv[2]);
            pid = FindProcessByName(argv[2],"app_");
            printf("pid=%d\n",pid);
            if(pid==getpid()){
                printf("process not found\n");
                return 0;
            }            
        }
        if(pid>0){
            inject_arm(false,pid,argv[3]);
        }
        return(0);        
    }else{        
        printf("Unknown command [%s]\n",argv[1]);
        return(-1);
    }
    */
}


