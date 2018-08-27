/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   shell.hpp
 * Author: Administrator
 *
 * Created on September 4, 2016, 3:43 PM
 */

#ifndef SHELL_HPP
#define SHELL_HPP

#define	    CMD_LUA	0
#define	    CMD_SEACH	1
#define	    CMD_DUMP	2
#define	    CMD_WRITE	3

class ShellCommand
{
public:
    int type;
    std::vector<std::string> params;
};

class LuaShell
{
public:
    std::string scriptFile;
    ProcessScanner pscan;
    LuaScript *script;
    Logger *logger;
    void Shell(int pid,Logger *logger,LuaScript *script);
    void GetInts(char *param,std::vector<unsigned int> &vints);
    void Dump(std::vector<std::string> &params);
    void Write(std::vector<std::string> &params);
    std::vector<std::string> ParseParam(char *line);
    unsigned int EvalInt(char *);
};


#endif /* SHELL_HPP */

