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


class ELFHelp {
public:
    std::string fileName;
    std::vector<unsigned char> buffer;
    Elf32_Ehdr *header;
    Elf32_Shdr *shdrStringtable;
    Elf32_Shdr *shdrDynsym;
//    Elf32_Shdr *shdrDynstr;
    Elf32_Shdr *shdrDynamic;
    Elf32_Dyn *dynStrTab;
    //unsigned int dynamic_strtab;
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
    void ShowDynamic(Elf32_Shdr *shdr);
    void *At(int index);
    char *GetHeaderString(int index);
    char *GetDynamicString(int index);
    char *GetString(int addr);
    void Save(char *fileName = NULL);
    std::string SectionFlagToString(int flag);
    
private:

};

#endif /* ELFHELP_H */

