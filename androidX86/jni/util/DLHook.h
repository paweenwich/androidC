/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLHook.h
 * Author: Administrator
 *
 * Created on December 23, 2018, 12:55 PM
 */

#include <string>
#include <vector>

#ifndef DLHOOK_H
#define DLHOOK_H

typedef struct _HookData {
    char *name;
    void *hookAddr;
    unsigned int *originalAddr;
} HookData;

class DLHook {
public:
    //static std::vector<HookData> vHookData;
    //static std::vector<std::string> vWatchlibrary;
    static std::vector<HookData> GetDLHookData();
    static std::vector<std::string> GetWatchlibrary();
    static bool IsWatched(char *name);
    //static void AddWatch(char *name);
    static void ReHook(char *libname);
};


#endif /* DLHOOK_H */

