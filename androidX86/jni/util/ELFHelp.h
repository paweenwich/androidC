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
    std::vector<Elf32_Shdr *> sectionHeader;
    ELFHelp();
    ELFHelp(const ELFHelp& orig);
    int Load(char *fileName);
    bool IsELF();
    void Show(Elf32_Ehdr *ehdr);
    void Show(Elf32_Shdr *shdr);
    void *At(int index);
    char *GetHeaderString(int index);
    virtual ~ELFHelp();
private:

};

#endif /* ELFHELP_H */

