/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ELFHelp.cpp
 * Author: Administrator
 * 
 * Created on December 12, 2018, 8:09 PM
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
#include <../util/AndroidLogger.h>
#include <../util/elf_help.h>


#include "ELFHelp.h"
/*
https://blogs.oracle.com/solaris/inside-elf-symbol-tables-v2
https://grugq.github.io/docs/subversiveld.pdf
http://sco.com/developers/gabi/latest/ch4.symtab.html
*/ 

ELFHelp::ELFHelp() {
}

ELFHelp::ELFHelp(const ELFHelp& orig) {
}

int ELFHelp::Load(char *fileName)
{
    this->fileName = fileName;
    buffer =  ReadFile(fileName);
    if(buffer.size()>0){
        header = (Elf32_Ehdr *)At(0);
	if(!IsELF()){
	    printf("Fail: Only elf file supported\n");
	    return -1;
	}
	if(header->e_entry !=0){
	    printf("Fail: e_entry !=0 possible executable file, only so supported\n");
	    return -1;
	}
	if(header->e_ident[EI_CLASS]!=1){
	    printf("Fail: Not a 32bit elf file\n");
	    return -1;
	}	
	
        shdrStringtable = (Elf32_Shdr *)At(header->e_shoff + (header->e_shstrndx*header->e_shentsize));
        
	//load section header
        sectionHeader.clear();
        for(int i=0;i<header->e_shnum;i++){
            Elf32_Shdr *shdr = (Elf32_Shdr *)At(header->e_shoff + (i*header->e_shentsize));
            sectionHeader.push_back(shdr);
            if(shdr->sh_type == SHT_DYNSYM){
                this->shdrDynsym = shdr;
            }
	    if(shdr->sh_type == SHT_DYNAMIC){
		this->shdrDynamic = shdr;
	    }
        }
	if(this->shdrDynsym == NULL){
	    printf("SHT_DYNSYM not found\n");return -1;
	}
	if(this->shdrDynamic == NULL){
	    printf("SHT_DYNAMIC not found\n");return -1;
	}
	
	//find star tab of dynamic seciont
	std::vector<Elf32_Dyn *> dyns = GetDynamics(shdrDynamic);
	for(int i=0;i<dyns.size();i++){
	    Elf32_Dyn *dyn = dyns[i];
	    if(dyn->d_tag == DT_STRTAB){
		dynStrTab = dyn;
	    }
	    if(dyn->d_tag == DT_NULL){
		break;
	    }
	}
	
	/*int num = shdrDynamic->sh_size/shdrDynamic->sh_entsize;
	for(int i=0;i<num;i++){
	    Elf32_Dyn *dyn = (Elf32_Dyn *)At(shdrDynamic->sh_offset + (i*shdrDynamic->sh_entsize));
	    if(dyn->d_tag == DT_STRTAB){
		dynStrTab = dyn;
	    }
	    if(dyn->d_tag == DT_NULL){
		break;
	    }
	}*/
	if(this->dynStrTab == NULL){
	    printf("DT_STRTAB not found\n");return -1;
	}
	
	// load program header 
	programHeader.clear();
	for(int i=0;i<header->e_phnum;i++){
            Elf32_Phdr *phdr = (Elf32_Phdr *)At(header->e_phoff + (i*header->e_phentsize));
            programHeader.push_back(phdr);
        }
	
        return buffer.size();
    }else{
        return -1;
    }
}

bool ELFHelp::IsELF()
{
    if(buffer.size()>0){
         if(IS_ELF((*header))){
            return true; 
         }
    }
    return false;
}

std::string ELFHelp::SectionFlagToString(int flg)
{
    std::string ret;
    if(flg & SHF_WRITE) ret+="W";
    if(flg & SHF_ALLOC) ret+="A";
    if(flg & SHF_EXECINSTR) ret+="E";
    if(flg & SHF_MASKPROC) ret+="M";
    return ret;
}

std::string ELFHelp::ProgramFlagToString(int flg)
{
    std::string ret;
    if(flg & PF_X) ret+="X";
    if(flg & PF_W) ret+="W";
    if(flg & PF_R) ret+="R";
    return ret;
}

std::string ELFHelp::GetProgramHeaderType(int type)
{
    switch(type){
        case PT_NULL: return STRINGIFY(PT_NULL);
        case PT_LOAD: return STRINGIFY(PT_LOAD);
        case PT_DYNAMIC: return STRINGIFY(PT_DYNAMIC);
        case PT_INTERP: return STRINGIFY(PT_INTERP);
        case PT_NOTE: return STRINGIFY(PT_NOTE);
        case PT_SHLIB: return STRINGIFY(PT_SHLIB);
        case PT_PHDR: return STRINGIFY(PT_PHDR);
        case PT_NUM: return STRINGIFY(PT_NUM);
//        case PT_TLS: return STRINGIFY(PT_TLS);        
        case PT_GNU_EH_FRAME: return STRINGIFY(PT_GNU_EH_FRAME);
        case PT_GNU_STACK: return STRINGIFY(PT_GNU_STACK);
        case PT_GNU_RELRO: return STRINGIFY(PT_GNU_RELRO);
//        case PT_HIOS: return STRINGIFY(PT_HIOS);        
        default:
            if(type && PT_LOOS){
                return StringPrintf("%08X (os)",type);
            }
            if(type && PT_LOPROC){
                return StringPrintf("%08X (proc)",type);
            }
            return StringPrintf("%d",type);
    }
}

#define PRINTF(f,n) printf(#n " " f "\n",hdr->n)
void ELFHelp::Show(Elf32_Ehdr *hdr)
{
    printf("EI_CLASS %d\n",hdr->e_ident[EI_CLASS]);
    PRINTF("%d",e_type);
    PRINTF("%d",e_machine);
    PRINTF("%d",e_version);
    PRINTF("%08X",e_entry);
    PRINTF("%08X",e_phoff);
    PRINTF("%08X",e_shoff);
    PRINTF("%d",e_flags);
    PRINTF("%d",e_ehsize);
    PRINTF("%d",e_phentsize);
    PRINTF("%d",e_phnum);
    PRINTF("%d",e_shentsize);
    PRINTF("%d",e_shnum);
    PRINTF("%d",e_shstrndx);
}

void ELFHelp::Show(Elf32_Shdr *hdr)
{
    printf("sh_name %d [%s]\n",hdr->sh_name,GetHeaderString(hdr->sh_name));
    PRINTF("%d",sh_type);
    PRINTF("%d",sh_flags);
    PRINTF("%d",sh_flags);
    PRINTF("%08X",sh_addr);
    PRINTF("%08X",sh_offset);
    PRINTF("%d",sh_size);
    PRINTF("%d",sh_link);
    PRINTF("%d",sh_info);
    PRINTF("%d",sh_addralign);
    PRINTF("%d",sh_entsize);
}

void ELFHelp::Show(Elf32_Phdr *hdr)
{
    PRINTF("%d",p_type);
    PRINTF("%08X",p_offset);
    PRINTF("%08X",p_vaddr);
    PRINTF("%08X",p_paddr);
    PRINTF("%08X",p_filesz);
    PRINTF("%08X",p_memsz);
    PRINTF("%08X",p_flags);
    PRINTF("%d",p_align);
}

void ELFHelp::Show(Elf32_Dyn *dyn)
{
    //printf("%d %d\n",dyn->d_tag,dyn->d_un.d_val);
    //return;

    switch(dyn->d_tag){
	case DT_NEEDED:
	    printf("%d %d DT_NEEDED [%s]\n",dyn->d_tag,dyn->d_un.d_val,GetDynamicString(dyn->d_un.d_val));
	    break;
	case DT_STRTAB:	    
	    printf("%d %d DT_STRTAB\n",dyn->d_tag,dyn->d_un.d_val);
	    //DumpHex(stdout,At(dyn->d_un.d_val),64);
	    break;
	case DT_SYMTAB:	    
	    printf("%d %d DT_SYMTAB\n",dyn->d_tag,dyn->d_un.d_val);
	    //DumpHex(stdout,At(dyn->d_un.d_val),64);
	    break;
	case DT_HASH:	    
	    printf("%d %d DT_HASH\n",dyn->d_tag,dyn->d_un.d_val);
	    break;
	case DT_PLTGOT:
	    printf("%d %d DT_PLTGOT\n",dyn->d_tag,dyn->d_un.d_val);
	    break;
	case DT_NULL:	    
	    printf("%d %d DT_NULL\n",dyn->d_tag,dyn->d_un.d_val);
	    break;
	default:
	    printf("%d %d\n",dyn->d_tag,dyn->d_un.d_val);
	    break;
    }
}

void ELFHelp::ShowDynamic(Elf32_Shdr *hdr,int filter)
{
    std::vector<Elf32_Dyn *> dyns = GetDynamics(hdr);
    for(int i=0;i<dyns.size();i++){
	Elf32_Dyn *dyn = dyns[i];
	if((filter==0)||(filter == dyn->d_tag)){
	    Show(dyn);
	}
	if(dyn->d_tag == DT_NULL){
	    break;
	}
    }
}

std::vector<Elf32_Dyn *> ELFHelp::GetDynamics(Elf32_Shdr *hdr)
{
    std::vector<Elf32_Dyn *> ret;
    int num = hdr->sh_size/hdr->sh_entsize;
    for(int i=0;i<num;i++){
	Elf32_Dyn *dyn = (Elf32_Dyn *)At(hdr->sh_offset + (i*hdr->sh_entsize));
	ret.push_back(dyn);
    }
    return ret;
}

void *ELFHelp::At(int index)
{
    return (void *)&buffer[index];
}

char *ELFHelp::GetHeaderString(int index)
{
    //return (char *)At(shdrStringtable->sh_offset + index);
    return GetString(shdrStringtable->sh_offset + index);
}

char *ELFHelp::GetDynamicString(int index)
{
    return GetString(dynStrTab->d_un.d_val + index);
}

char *ELFHelp::GetString(int addr)
{
    return (char *)At(addr);
}

void ELFHelp::Save(char *fileName)
{
    std::string outFileName;
    if(fileName == NULL){
	outFileName = this->fileName + ".out";
    }else{
	outFileName = fileName;
    }
    DumpMemory((unsigned int)&buffer[0],buffer.size(),(char *)outFileName.c_str());
    //DumpHex(stdout,At(0),64);
}

void ELFHelp::ShowDependency(Elf32_Shdr *hdr)
{
    ShowDynamic(hdr,DT_NEEDED);
}

bool ELFHelp::ReplaceDependency(Elf32_Shdr *hdr,char *from,char *to)
{
    std::vector<Elf32_Dyn *> dyns = GetDynamics(hdr);
    if(strlen(from)!=strlen(to)){
	printf("only libname with the same size support [%s] [%s]",from,to);
	return false;
    }
    printf("scaning DT_NEEDED\n");
    for(int i=0;i<dyns.size();i++){
	Elf32_Dyn *dyn = dyns[i];
	if(dyn->d_tag == DT_NEEDED){
	    char *soName = GetDynamicString(dyn->d_un.d_val);
	    printf("found %s\n",soName);
	    if(strcmp(soName,from)==0){
		printf("Change %s -> %s\n",from,to);
		strcpy(soName,to);
		if(strcmp(GetDynamicString(dyn->d_un.d_val),to)==0){
		    printf("Done\n");
		    return true;
		}else{
		    printf("Verify fail\n");
		    return false;
		}
		
	    }
	}

    }
    printf("scaning done %s not found\n",from);
    return false;
}



ELFHelp::~ELFHelp() {
}

