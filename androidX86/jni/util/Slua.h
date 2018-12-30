/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Slua.h
 * Author: Administrator
 *
 * Created on December 30, 2018, 4:01 PM
 */
#include <string>
#include <vector>

#ifndef SLUA_H
#define SLUA_H

#define lua_State void    
#define SLUAFUCP(r,n,p)  r (* n) p
class Slua {
public:
    SLUAFUCP(lua_State *,luaL_newstate,(void));
    SLUAFUCP(int,luaL_loadfilex,(lua_State *, char *, char *));
    SLUAFUCP(void,luaL_openlibs,(lua_State *));
    SLUAFUCP(char *,luaL_tolstring,(lua_State *, int ,int *));
    SLUAFUCP(void,lua_gettop,(lua_State *));
    SLUAFUCP(int, lua_pcallk,(lua_State *L,int nargs,int nresults,int msgh,void* ctx,void* k));
    std::string lastError;
    Slua();
    virtual ~Slua();
    bool Init(char *libname = NULL);   //libslua.so
    bool DoFile(lua_State *L,char *fileName);
    
private:

};

#endif /* SLUA_H */

