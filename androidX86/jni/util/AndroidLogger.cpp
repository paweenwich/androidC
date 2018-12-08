/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AndroidLogger.cpp
 * Author: Administrator
 * 
 * Created on December 8, 2018, 3:02 PM
 */
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../util/util.hpp"
#include "AndroidLogger.h"

//#define  LOG_TAG    "loader"
//#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
//#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


AndroidLogger::AndroidLogger(char *name,bool flg) {
    strcpy(this->name,name);
    flgStdout = flg;
}


void AndroidLogger::_logStr(char *p){
    __android_log_print(ANDROID_LOG_DEBUG, name ,"%s",p);
    if(flgStdout){
        std::printf("%s: %s",name,p);
        fflush(stdout);
    }
}
AndroidLogger::~AndroidLogger() {
}

