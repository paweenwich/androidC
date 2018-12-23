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
#include "../util/luascript.h"
#include "../luaserver/lua_server.hpp"
#include "../util/elf_hook.h"


#define  LOG_TAG    "elf"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define	 CMD_DUMP   "DUMP"
#define	 CMD_REPLACE   "REPLACE"
#define	 CMD_STRIP   "STRIP"
#define	 CMD_ADDSO   "ADDSO"
#define	 CMD_ADDSO1   "ADDSO1"
#define	 CMD_ADDSO2   "ADDSO2"
#define	 CMD_TEST   "TEST"
Logger logger(NULL,0);
char **_argv;

void elf_dump(char *fileName)
{
    if(fileName == NULL){
	printf("Usage: %s %s filename\n",_argv[0],CMD_DUMP);
	return;
    }
    printf("dump %s\n",fileName);
    ELFHelp elfHelp;
    if(elfHelp.Load((char *)fileName)<0){
        printf("Fail: Load File\n");
	exit(0);
    }
    elfHelp.Show(elfHelp.header);
    //elfHelp.Show(elfHelp.shdrStringtable);
    //logger.logHex((unsigned char *)elfHelp.At(elfHelp.shdrStringtable->sh_offset),64);
    printf("Section Headers\n");
    for(int i=0;i<elfHelp.sectionHeader.size();i++){
	Elf32_Shdr *shdr = elfHelp.sectionHeader[i];
        printf("%d %08X %08X %08X %d [%s] %s\n",i,shdr->sh_addr,shdr->sh_offset,shdr->sh_size,shdr->sh_type,
		elfHelp.GetHeaderString(shdr->sh_name),
		elfHelp.SectionFlagToString(shdr->sh_flags).c_str()
		
	);
    }
    //printf("%08X\n",elfHelp.shdrDynsym->sh_offset);
    //printf("%08X\n",elfHelp.dynStrTab->d_un.d_val);
    printf("FileSize = %08X\n",elfHelp.buffer.size());
    printf("End = %08X\n",elfHelp.header->e_shoff + (elfHelp.header->e_shentsize * elfHelp.header->e_shnum));
    printf("Memsize = %08X\n",elfHelp.GetMemorySize());
    //elfHelp.Show(elfHelp.GetProgramHeaderData());
    //elfHelp.Show(elfHelp.GetProgramHeaderCode());
    //elfHelp.Show(elfHelp.shdrDynsym);
    //elfHelp.Show(elfHelp.shdrDynamic);
    //logger.logHex((unsigned char *)elfHelp.At(elfHelp.shdrDynamic->sh_offset),320);
    elfHelp.ShowDynamic(elfHelp.shdrDynamic);

    printf("Program Headers\n");
    for(int i=0;i<elfHelp.programHeader.size();i++){
	Elf32_Phdr *phdr = elfHelp.programHeader[i];
	//elfHelp.Show(phdr);
        printf("%02d o:%08X v:%08X p:%08X fz:%08X mz:%08X e:%08X %s a:%d [%s]\n",i,
                phdr->p_offset,phdr->p_vaddr,phdr->p_paddr,
                phdr->p_filesz,phdr->p_memsz,
                phdr->p_offset + phdr->p_filesz,
                elfHelp.ProgramFlagToString(phdr->p_flags).c_str(),
                phdr->p_align,
                elfHelp.GetProgramHeaderType(phdr->p_type).c_str()
	);

    }
    Elf32_Shdr * rel_dyn =  elfHelp.GetSectionHeaderByName(".rel.dyn");
    Elf32_Shdr * rel_plt =  elfHelp.GetSectionHeaderByName(".rel.plt");
    {
        DumpHex(stdout,elfHelp.At(rel_dyn->sh_offset),rel_dyn->sh_size);
        int num = rel_dyn->sh_size/sizeof(Elf32_Rel);
        for(int i=0;i<num;i++){
            Elf32_Rel *rel = (Elf32_Rel *)elfHelp.At(rel_dyn->sh_offset + (i*sizeof(Elf32_Rel)));
            printf("%08X %08X %s\n",rel->r_offset,rel->r_info,elfHelp.GetDynamicString(ELF32_R_SYM(rel->r_info)));
        }
    }
    
    {
        DumpHex(stdout,elfHelp.At(rel_plt->sh_offset),rel_plt->sh_size);
        int num = rel_plt->sh_size/sizeof(Elf32_Rel);
        for(int i=0;i<num;i++){
            Elf32_Rel *rel = (Elf32_Rel *)elfHelp.At(rel_plt->sh_offset + (i*sizeof(Elf32_Rel)));
            printf("%08X %08X %s\n",rel->r_offset,rel->r_info,elfHelp.GetDynamicString(ELF32_R_SYM(rel->r_info)));
        }
    }
    {
        DumpHex(stdout,elfHelp.At(elfHelp.shdrDynsym->sh_offset),elfHelp.shdrDynsym->sh_size);
        int num = elfHelp.shdrDynsym->sh_size/sizeof(Elf32_Sym);
        for(int i=0;i<num;i++){
            Elf32_Sym *sym = (Elf32_Sym *)elfHelp.At(elfHelp.shdrDynsym->sh_offset + (i*sizeof(Elf32_Sym)));
            printf("name=%08X value=%08X %s\n",sym->st_name,sym->st_value,elfHelp.GetDynamicString(sym->st_name));
        }
        
    }
    //elfHelp.ShowDependency(elfHelp.shdrDynamic);
    //elfHelp.ReplaceDependency(elfHelp.shdrDynamic,"liblog.so","libmog.so");
    //elfHelp.Save();
}

void elf_replace(char *fileName,char *from,char *to)
{
    if((fileName == NULL)||(from == NULL)||(to == NULL)){
	printf("Usage: %s %s filename from to\n",_argv[0],CMD_REPLACE);
	return;
    }
    printf("%s %s %s %s\n",CMD_REPLACE,fileName,from,to);
    ELFHelp elfHelp;
    if(elfHelp.Load((char *)fileName)<0){
        printf("Fail: Load File\n");
	return;
    }
    //elfHelp.Show(elfHelp.header);
    elfHelp.ShowDependency(elfHelp.shdrDynamic);
    elfHelp.ReplaceDependency(elfHelp.shdrDynamic,from,to);
    elfHelp.Save();
}

void elf_strip(char *fileIn,char *fileOut)
{
    if((fileIn == NULL)||(fileOut == NULL)){
	printf("Usage: %s %s fileIn fileOut\n",_argv[0],CMD_STRIP);
	return;
    }
    printf("%s %s %s\n",CMD_STRIP,fileIn,fileOut);
    ELFHelp elfHelp;
    if(elfHelp.Load((char *)fileIn)<0){
        printf("Fail: Load File\n");
	return;
    }
    elfHelp.Strip();
    elfHelp.Save(fileOut);
    printf("%s done\n",fileOut);
}

void elf_addDependencyByGNU(char *fileIn,char *fileOut,char *dependencyName)
{
    if((fileIn == NULL)||(fileOut == NULL)||(dependencyName == NULL)){
	printf("Usage: %s %s fileIn fileOut soName\n",_argv[0],CMD_ADDSO);
	return;
    }
    printf("%s %s %s %s\n",CMD_ADDSO,fileIn,fileOut,dependencyName);
    ELFHelp elfHelp;
    if(elfHelp.Load((char *)fileIn)<0){
        printf("Fail: Load File\n");
	return;
    }
    
    printf("Using AddDependencyByGNU\n");
    if(!elfHelp.AddDependencyByGNU(dependencyName)){
        printf("Fail: AddDependencyByGNU()\n");
	return;
    }
    
    // Save to output file
    elfHelp.Save(fileOut);
    printf("%s done\n",fileOut);

}

void elf_addDependency(char *fileIn,char *fileOut,char *dependencyName)
{
    if((fileIn == NULL)||(fileOut == NULL)||(dependencyName == NULL)){
	printf("Usage: %s %s fileIn fileOut soName\n",_argv[0],CMD_ADDSO1);
	return;
    }
    printf("%s %s %s %s\n",CMD_ADDSO1,fileIn,fileOut,dependencyName);
    ELFHelp elfHelp;
    if(elfHelp.Load((char *)fileIn)<0){
        printf("Fail: Load File\n");
	return;
    }
    
    printf("Using AddDependency\n");
    if(!elfHelp.AddDependency(dependencyName)){
        printf("Fail: AddDependency()\n");
	return;
    }
    
    // Save to output file
    elfHelp.Save(fileOut);
    printf("%s done\n",fileOut);

}

void (*org_puts)(char *str);
void hooked_puts(char *str)
{
    printf("puts(%s)\n",str);
    org_puts(str);
}

void elf_test(char *fileIn,char *fileOut)
{
    printf("TEST\n");
    void *handle = dlopen("/data/local/tmp/libtestso.so", RTLD_LAZY);
    DLSYM_ENSURE_API(handle,void *,Test1,(void));
    Test1();
    //void * base1 = LIBRARY_ADDRESS_BY_HANDLE(handle1);
    void *base1 = (void *)FindBaseLibrary("/data/local/tmp/libtestso.so",getpid());    
    printf("base1=%08X\n",UINT(base1));
    //printf("base2=%08X handle1=%08X\n",UINT(base2),UINT(handle1));    
    printf("puts=%08X\n",UINT(puts));    
    org_puts = (void (*)(char*))elf_hook("/data/local/tmp/libtestso.so", base1, "puts", (void const *)hooked_puts);
    printf("original1=%08X\n",UINT(org_puts));    

    Test1();
    //void *elf_hook("libtestso.so", void const *library_address, char const *function_name, void const *substitution_address);
}

void elf(char *cmd,char *param1,char *param2,char *param3)
{
    if(strcmp(cmd,CMD_DUMP)==0){
	elf_dump(param1);return;
    }
    if(strcmp(cmd,CMD_REPLACE)==0){
	elf_replace(param1,param2,param3);return;
    }
    if(strcmp(cmd,CMD_STRIP)==0){
	elf_strip(param1,param2);return;
    }
    if(strcmp(cmd,CMD_ADDSO)==0){
	elf_addDependencyByGNU(param1,param2,param3);return;
    }
    if(strcmp(cmd,CMD_ADDSO1)==0){
	elf_addDependency(param1,param2,param3);return;
    }
    
    if(strcmp(cmd,CMD_TEST)==0){
	elf_test(param1,param2);return;
    }

}


int main(int argc, char** argv) {
    _argv = argv;
    //printf("%d\n",argc);
    if(argc==2){
	elf(argv[1],NULL,NULL,NULL);return 0;
    }
    if(argc==3){
	elf(argv[1],argv[2],NULL,NULL);return 0;
    }
    if(argc==4){
	elf(argv[1],argv[2],argv[3],NULL);return 0;
    }
    if(argc==5){
	elf(argv[1],argv[2],argv[3],argv[4]);return 0;
    }
    printf("Usage: %s command [param...]\n",argv[0]);
    printf("\tcommand as\n");
    printf("\t%s filename\t;just dump so\n",CMD_DUMP);
    printf("\t%s filename from to\t;replace dll dependency\n",CMD_REPLACE);
    printf("\t%s filename fileout\t;strip unused info\n",CMD_STRIP);
    printf("\t%s filein fileout soName\t;add soName in dependency list by GNU\n",CMD_ADDSO);    
    printf("\t%s filein fileout soName\t;add soName in dependency list\n",CMD_ADDSO1);    
//    printf("\t%s filein fileout soName\t;add soName in dependency list by append file\n",CMD_ADDSO2);        
    
    
}


