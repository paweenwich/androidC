/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AndroidLogger.h
 * Author: Administrator
 *
 * Created on December 8, 2018, 3:02 PM
 */
#include "logger.h"

#ifndef ANDROIDLOGGER_H
#define ANDROIDLOGGER_H

class AndroidLogger: public Logger {
public:
    bool flgStdout;
    char name[64];
    AndroidLogger(char *name,bool flgStdout = false);
    //AndroidLogger(const AndroidLogger& orig);
    virtual ~AndroidLogger();
    virtual void _logStr(char *p);
private:

};

#endif /* ANDROIDLOGGER_H */

