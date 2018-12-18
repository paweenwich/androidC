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
http://michalmalik.github.io/elf-dynamic-segment-struggles
https://en.wikipedia.org/wiki/Executable_and_Linkable_Format

The linux kernel does not really care about the dynamic segment, but looking for PT_DYNAMIC 
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
	if(header->e_type != ET_DYN ){
	    printf("Fail: e_type != ET_DYN possible executable file, only so supported\n");
	    return -1;
	}
/*	if(header->e_entry !=0){
	    printf("Fail: e_entry !=0 possible executable file, only so supported\n");
	    return -1;
	}*/
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
	    printf("%d %08X DT_NEEDED [%s]\n",dyn->d_tag,dyn->d_un.d_val,GetDynamicString(dyn->d_un.d_val));
	    break;
	case DT_STRTAB:	    
	    printf("%d %08X DT_STRTAB\n",dyn->d_tag,dyn->d_un.d_val);
	    //DumpHex(stdout,At(dyn->d_un.d_val),64);
	    break;
	case DT_SYMTAB:	    
	    printf("%d %08X DT_SYMTAB\n",dyn->d_tag,dyn->d_un.d_val);
	    //DumpHex(stdout,At(dyn->d_un.d_val),64);
	    break;
	case DT_HASH:	    
	    printf("%d %08X DT_HASH\n",dyn->d_tag,dyn->d_un.d_val);
	    break;
	case DT_PLTGOT:
	    printf("%d %08X DT_PLTGOT\n",dyn->d_tag,dyn->d_un.d_val);
	    break;
	case DT_NULL:	    
	    printf("%d %08X DT_NULL\n",dyn->d_tag,dyn->d_un.d_val);
	    break;
	default:
	    printf("%d %08X\n",dyn->d_tag,dyn->d_un.d_val);
	    break;
    }
}

int ELFHelp::GetDynamicIndex(int type)
{
    std::vector<Elf32_Dyn *> dyns = GetDynamics(shdrDynamic);
    for(int i=0;i<dyns.size();i++){
	Elf32_Dyn *dyn = dyns[i];
	if(dyn->d_tag == type){
	    return i;
	}
    }
    return -1;
}

int ELFHelp::CountDynamicEmptyEntries()
{
    int index = GetDynamicIndex(DT_NULL);
    if(index >=0){
	return GetDynamics(shdrDynamic).size() - index;
    }else{
	return 0;
    }
    /*int ret = 0;
    std::vector<Elf32_Dyn *> dyns = GetDynamics(shdrDynamic);
    for(int i=0;i<dyns.size();i++){
	Elf32_Dyn *dyn = dyns[i];
	if(dyn->d_tag == DT_NULL){
	    ret++;
	}
	if(ret>0){
	    Show(dyn);
	}
    }
    return ret;*/
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

std::vector<Elf32_Shdr *> ELFHelp::GetStripableSection()
{
    std::vector<Elf32_Shdr *> ret;
    for(int i=0;i<sectionHeader.size();i++){
	Elf32_Shdr *shdr = sectionHeader[i];
	if((shdr->sh_addr == 0) && (shdr->sh_size > 0)){
	    ret.push_back(shdr);
	}
    }
    return ret;
}

Elf32_Shdr * ELFHelp::FindBestStripableSection(int size)
{
    std::vector<Elf32_Shdr *> lst = GetStripableSection();
    for(int i=0;i<lst.size();i++){
	Elf32_Shdr *shdr = lst[i];
	if(shdr->sh_size < size) continue;
	// ignore shstrtab symtab strtab because we might need this info
	// even kernel does not need it
	char *name = GetHeaderString(shdr->sh_name);
	if(strstr(name,"tab")==NULL){
	    //simply return first on found
	    return shdr;
	}
    }
    return NULL;
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
    unlink((char *)outFileName.c_str());
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

/* getmemorysize() determines the offset of the last byte of the file
 * that is referenced by an entry in the program segment header table.
 * (Anything in the file after that point is not used when the program
 * is executing, and thus can be safely discarded.)
 */
int ELFHelp::GetMemorySize()
{
    unsigned long size, n;
    int i;

    /* Start by setting the size to include the ELF header and the
     * complete program segment header table.
     */
    size = header->e_phoff + header->e_phnum * header->e_phentsize;
    if (size < header->e_ehsize)
	size = header->e_ehsize;

    /* Then keep extending the size to include whatever data the
     * program segment header table references.
     */
    for (i = 0 ; i < programHeader.size() ; ++i) {
	if (programHeader[i]->p_type != PT_NULL) {
	    n = programHeader[i]->p_offset + programHeader[i]->p_filesz;
	    if (n > size)
		size = n;
	}
    }
    return size;

}

bool ELFHelp::Strip()
{
    int lastOffset = GetMemorySize();
    // remove buffer 
    buffer.erase(buffer.begin() + lastOffset,buffer.end());
    return true;
}

Elf32_Phdr * ELFHelp::GetProgramHeaderData()
{
    for (int i = 0 ; i < programHeader.size() ; ++i) {
	if (programHeader[i]->p_type == PT_LOAD) {
	    if (ProgramFlagToString(programHeader[i]->p_flags) == "WR") {
		return programHeader[i];
	    }
	}
    }
    return NULL;
}

Elf32_Phdr * ELFHelp::GetProgramHeaderCode()
{
    for (int i = 0 ; i < programHeader.size() ; ++i) {
	if (programHeader[i]->p_type == PT_LOAD) {
	    if (ProgramFlagToString(programHeader[i]->p_flags) == "XR") {
		return programHeader[i];
	    }
	}
    }
    return NULL;    
}

Elf32_Dyn * ELFHelp::GetDynamic(int type)
{
    std::vector<Elf32_Dyn *> dyns = GetDynamics(shdrDynamic);
    for(int i=0;i<dyns.size();i++){
	Elf32_Dyn *dyn = dyns[i];
	//Show(dyn);
	if(dyn->d_tag == type){
	    return dyn;
	}
    }
    return NULL;
}

Elf32_Shdr * ELFHelp::GetSectionHeaderByName(char *name)
{
    for(int i=0;i<sectionHeader.size();i++){
	if(strcmp(GetHeaderString(sectionHeader[i]->sh_name),name)==0){
	    return sectionHeader[i];
	}
    }
    return NULL;
}

/* 
 *  using gnu.version section as space to put our string
 */
bool ELFHelp::AddDependencyByGNU(char *dependencyName)
{
    int dataSize = strlen(dependencyName) + 1;
    //Elf32_Phdr *data = GetProgramHeaderData();

    // dyn does not has size info need to get size fomr ".dynstr" section
    Elf32_Shdr *shdrDynStr = GetSectionHeaderByName(".dynstr");
    //Elf32_Shdr *shdrData = GetSectionHeaderByName(".data");
    
    Elf32_Shdr *shdrGnu = GetSectionHeaderByName(".gnu.version");
    if(shdrGnu == NULL){
	printf("Fail: .gnu.version section not found\n");
	return false;
    }
    if(shdrGnu->sh_size < dataSize){
	printf("Fail: .gnu.version section size < needed size\n");
	return false;
    }
    Elf32_Dyn *dynNull = GetDynamic(DT_NULL);    
    
    DumpHex(stdout,At(shdrGnu->sh_offset),shdrGnu->sh_size);
    //memset(At(shdrGnu->sh_offset),0x65,shdrGnu->sh_size);
    memcpy(At(shdrGnu->sh_offset),dependencyName,dataSize);
    DumpHex(stdout,At(shdrGnu->sh_offset),shdrGnu->sh_size);
    dynNull->d_tag = DT_NEEDED;
    dynNull->d_un.d_val = shdrGnu->sh_offset - shdrDynStr->sh_offset;
    printf("offset from string table %08X\n",dynNull->d_un.d_val);
    return true;
}

/*
 * Find empty section (stripable)
 * write our string to it
 * adjust data section to cover whole file
 * add DT_NEEDED point to our string by relative strtab
 * 
*/
bool ELFHelp::AddDependency(char *dependencyName)
{
    Elf32_Phdr *data = GetProgramHeaderData();
    Elf32_Phdr *code = GetProgramHeaderCode();

    // dyn does not has size info need to get size fomr ".dynstr" section
    Elf32_Shdr *shdrDynStr = GetSectionHeaderByName(".dynstr");
    Elf32_Shdr *shdrData = GetSectionHeaderByName(".data");
    
    Elf32_Shdr *shdrGnu = GetSectionHeaderByName(".gnu.version");
    
    
    if(CountDynamicEmptyEntries()==0){
	printf("Fail: no empty dyn entry found\n");
	return false;
    }
    Elf32_Dyn *dynNull = GetDynamic(DT_NULL);    
    
    // check empty section
    int dataSize = strlen(dependencyName) + 1;
    Elf32_Shdr *emptySection = FindBestStripableSection(dataSize);
    if(emptySection == NULL){
	printf("Fail: empty section not found\n");
	return false;
    }
    
    //int delta = 0;
    int delta = data->p_memsz - data->p_filesz;    
    if(delta > 0){
	printf("Warning!data section memsz != filesz mz=%08X fz=%08X\n",data->p_memsz,data->p_filesz);
    }
    DumpHex(stdout,At(shdrDynStr->sh_offset),shdrDynStr->sh_size);

    int endData = data->p_offset + data->p_filesz;
    DumpHex(stdout,At(endData),delta);
    memset(At(endData),0,delta);
    DumpHex(stdout,At(endData),delta);
    
    
    //elfHelp.Show(emptySection);
    //DumpHex(stdout,At(shdrDynStr->sh_offset),shdrDynStr->sh_size);
    
    //printf("Found target section %s\n",GetString(emptySection->sh_name));
    DumpHex(stdout,At(emptySection->sh_offset + delta),32);
    memcpy(At(emptySection->sh_offset + delta),dependencyName,dataSize);
    DumpHex(stdout,At(emptySection->sh_offset + delta),32);
    //adjust data section to cover whole file
    data->p_memsz = buffer.size() - data->p_offset;
    data->p_filesz = buffer.size() - data->p_offset;

    // use retive distance between va(shrtab - data)  + fileoffset(emptysection - data)
    dynNull->d_tag = DT_NEEDED;
    dynNull->d_un.d_val = shdrData->sh_addr - shdrDynStr->sh_addr + emptySection->sh_offset - shdrData->sh_offset + delta; // + offset ;
    printf("%08X %08X %08X\n",shdrDynStr->sh_addr,shdrData->sh_addr,emptySection->sh_offset - shdrData->sh_offset);
    printf("%08X\n",dynNull->d_un.d_val);
    return true;
}

/*
 * Append Strtab + out data at the end of file
 * adjust size of data section to cover all of it
 * chnage strtab to new location 
 * add DT_NEEDED point to our string
*/
bool ELFHelp::AddDependencyByAppend(char *dependencyName)
{
    Elf32_Dyn *dynNull = GetDynamic(DT_NULL);    
    if(dynNull == NULL){
	printf("Fail: no empty dynamic entry found\n");
	return false;
    }
    Elf32_Phdr *data = GetProgramHeaderData();
    Elf32_Phdr *code = GetProgramHeaderCode();

    unsigned int oldEndFileOffset = buffer.size();
    Elf32_Dyn *dynStrTab = GetDynamic(DT_STRTAB);
    
    // dyn does not has size info need to get size fomr ".dynstr" section
    Elf32_Shdr *shdrDynStr = GetSectionHeaderByName(".dynstr");
    int dynStrOffset = shdrDynStr->sh_offset;
    int dynStrSize = shdrDynStr->sh_size;
    
    Elf32_Shdr *shdrData = GetSectionHeaderByName(".data");
    int offset = shdrData->sh_addr - shdrData->sh_offset;
    printf("offset=%08X\n",offset);
    
    //copy oldstrtable to appendBuffer first, then remember relative offset that we append 
    // out string, then add our string to appendBuffer
    std::vector<unsigned char> appendBuffer;
    std::copy(buffer.begin() + dynStrOffset,buffer.begin() + dynStrOffset + dynStrSize,
	    std::back_inserter(appendBuffer));
    //logger.logHex((unsigned char *)appendBuffer.begin(),appendBuffer.size());
    int myStringOffset = appendBuffer.size();
    char *myString = dependencyName; //"libmog.so";
    std::copy(&myString[0],&myString[strlen(myString) + 1],std::back_inserter(appendBuffer));
    //logger.logHex((unsigned char *)appendBuffer.begin(),appendBuffer.size());

    
    // point dynStrTab to new location 
    // need to add offset because we add to .data which load to different offset then 
    // old str table (text)
    dynStrTab->d_un.d_val = oldEndFileOffset + offset;

    // fix data section program header size to have more appendBuffer data
    data->p_memsz = buffer.size() - data->p_offset + appendBuffer.size();
    data->p_filesz = buffer.size() - data->p_offset + appendBuffer.size();
    
    //add DT needed at lastest DT_NULL
    //this might has a bug if no DT_NULL in so
    dynNull->d_tag = DT_NEEDED;
    dynNull->d_un.d_val = myStringOffset;
    
    // append to buffer
    //!IMPORTANT need to do this after modify all data
    //because vector might allocate new buffer when append and all pointers that we have 
    //before will mot make sense
    std::copy(appendBuffer.begin(),appendBuffer.end(),std::back_inserter(buffer));
    return true;
}

ELFHelp::~ELFHelp() {
}

