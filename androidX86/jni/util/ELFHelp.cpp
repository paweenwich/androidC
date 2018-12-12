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
*/ 
ELFHelp::ELFHelp() {
}

ELFHelp::ELFHelp(const ELFHelp& orig) {
}

int ELFHelp::Load(char *fileName)
{
    this->fileName = fileName;
    buffer =  ReadFile("libfp.so");
    if(buffer.size()>0){
        header = (Elf32_Ehdr *)At(0);
        shdrStringtable = (Elf32_Shdr *)At(header->e_shoff + (header->e_shstrndx*header->e_shentsize));
        //Show(shdrStringtable);
        sectionHeader.clear();
        for(int i=0;i<header->e_shnum;i++){
            Elf32_Shdr *shdr = (Elf32_Shdr *)At(header->e_shoff + (i*header->e_shentsize));
            sectionHeader.push_back(shdr);
            if(shdr->sh_type == SHT_DYNSYM){
                this->shdrDynsym = shdr;
            }
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

void ELFHelp::Show(Elf32_Ehdr *ehdr)
{
    printf("EI_CLASS %d\n",ehdr->e_ident[EI_CLASS]);
    printf("e_type %d\n",ehdr->e_type);
    printf("e_machine %d\n",ehdr->e_machine);
    printf("e_version %d\n",ehdr->e_version);
    printf("e_entry %08X\n",ehdr->e_entry);
    printf("e_phoff %08X\n",ehdr->e_phoff);
    printf("e_shoff %08X\n",ehdr->e_shoff);
    printf("e_flags %d\n",ehdr->e_flags);
    printf("e_ehsize %d\n",ehdr->e_ehsize);
    printf("e_phentsize %d\n",ehdr->e_phentsize);
    printf("e_phnum %d\n",ehdr->e_phnum);
    printf("e_shentsize %d\n",ehdr->e_shentsize);
    printf("e_shnum %d\n",ehdr->e_shnum);
    printf("e_shstrndx %d\n",ehdr->e_shstrndx);
}

void ELFHelp::Show(Elf32_Shdr *shdr)
{
    printf("sh_name %d [%s]\n",shdr->sh_name,GetHeaderString(shdr->sh_name));
    printf("sh_type %d\n",shdr->sh_type);
    printf("sh_flags %d\n",shdr->sh_flags);
    printf("sh_addr %08X\n",shdr->sh_addr); /* address */
    printf("sh_offset %08X\n",shdr->sh_offset); /* file offset */
    printf("sh_size %08X\n",shdr->sh_size);
    printf("sh_link %d\n",shdr->sh_link);
    printf("sh_info %d\n",shdr->sh_info);
    printf("sh_addralign %d\n",shdr->sh_addralign);
    printf("sh_entsize %d\n",shdr->sh_entsize);
}

void *ELFHelp::At(int index)
{
    return (void *)&buffer[index];
}

char *ELFHelp::GetHeaderString(int index)
{
    return (char *)At(shdrStringtable->sh_offset + index);
}


ELFHelp::~ELFHelp() {
}

