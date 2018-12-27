/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   elf_hook.h
 * Author: kwang
 *
 * Created on December 19, 2018, 9:22 AM
 */
#include <string>
#include <vector>
#include <cctype>


#include "ELFHelp.h"

#ifndef ELF_HOOK_H
#define ELF_HOOK_H

#ifdef __cplusplus
extern "C" {
#endif

//Not work
//#define LIBRARY_ADDRESS_BY_HANDLE(x) ((NULL == x) ? NULL : (void *)*(size_t const *)(x))  //undocumented hack to get shared library's address in memory by its handle
void *elf_hook(char const *library_filename, void const *library_address, char const *function_name, void const *substitution_address);

#ifdef __cplusplus
}
#endif


class ELFHook {
public:
    ELFHelp elfHelp;
    std::string libName;
    unsigned int baseAddress;
    bool Open(char *library_filename);
    bool Hook(char *function_name, void *substitution_address, unsigned int *originalAddr);
    static void ShowMap();
    ~ELFHook();
};



#endif /* ELF_HOOK_H */

