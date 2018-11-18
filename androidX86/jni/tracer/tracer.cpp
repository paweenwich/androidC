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
#include <../util/util.hpp>
#include <../util/PtraceUtil.hpp>
#include <../util/logger.h>
#include <../util/payload.hpp>

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

#define TRACE_BIN   "/data/local/tmp/tracer.bin"

PtraceUtil ptraceUtil;
Logger logger(NULL,0);

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

    printf("offset_dlopen=%08X\n",(unsigned int)offset_dlopen);
    printf("offset_dlsym=%08X\n",(unsigned int)offset_dlsym);
    printf("offset_dlerror=%08X\n",(unsigned int)offset_dlerror);
    printf("offset_dlclose=%08X\n",(unsigned int)offset_dlclose);
    printf("offset_calloc=%08X\n",(unsigned int)offset_calloc);
    printf("offset_free=%08X\n",(unsigned int)offset_free);

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
            if(strcmp(argv[i],"-t")==0){
                printf("test with pid %d\n",pid);
                PrintAllAddress();
                GetOffsets();
                GetRemoteAddress(pid);
                //dlopen("aaaa",0);
                //_dlopen("aaaa",0);
                //Attach(pid);
                //Detach(pid);
                return 0;
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

