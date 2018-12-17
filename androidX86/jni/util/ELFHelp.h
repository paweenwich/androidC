/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ELFHelp.h
 * Author: Administrator
 *
 * Created on December 12, 2018, 8:09 PM
 */

#ifndef ELFHELP_H
#define ELFHELP_H

#define PT_GNU_EH_FRAME 0x6474e550      /* GCC .eh_frame_hdr segment */  
#define PT_GNU_STACK    0x6474e551      /* Indicates stack executability */  
#define PT_GNU_RELRO    0x6474e552      /* Read-only after relocation */

class ELFHelp {
public:
    std::string fileName;
    std::vector<unsigned char> buffer;
    Elf32_Ehdr *header;
    Elf32_Shdr *shdrStringtable;
    Elf32_Shdr *shdrDynsym;
    Elf32_Shdr *shdrDynamic;
    Elf32_Dyn *dynStrTab;
    std::vector<Elf32_Shdr *> sectionHeader;
    std::vector<Elf32_Phdr *> programHeader;
    ELFHelp();
    ELFHelp(const ELFHelp& orig);
    virtual ~ELFHelp();
    int Load(char *fileName);
    bool IsELF();
    void Show(Elf32_Phdr *ehdr);
    void Show(Elf32_Ehdr *ehdr);
    void Show(Elf32_Shdr *shdr);
    void Show(Elf32_Dyn *dyn);
    void ShowDynamic(Elf32_Shdr *shdr,int filter=0);
    void *At(int index);
    char *GetHeaderString(int index);
    char *GetDynamicString(int index);
    char *GetString(int addr);
    std::string GetProgramHeaderType(int type);
    void Save(char *fileName = NULL);
    std::string SectionFlagToString(int flag);
    std::string ProgramFlagToString(int flg);
    std::vector<Elf32_Dyn *> GetDynamics(Elf32_Shdr *shdr);
    void ShowDependency(Elf32_Shdr *shdr);
    bool ReplaceDependency(Elf32_Shdr *shdr,char *from,char *to);
    int GetMemorySize();
    bool Strip();
    Elf32_Phdr * GetProgramHeaderData();
    Elf32_Phdr * GetProgramHeaderCode();
    Elf32_Dyn * GetDynamic(int type);
    Elf32_Shdr * GetSectionHeaderByName(char *name);
    int CountDynamicEmptyEntries();
    int GetDynamicIndex(int type);    
private:

};

#endif /* ELFHELP_H */

