#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "logger.h"
//
// Log message 
//
Logger::Logger(char *logfile,bool FLGNOTIME)
{
    MutexCreate(&mutex);
    if(logfile == NULL){
        fp = stdout;
    }else{
        flgNoTime = FLGNOTIME;
        if((fp=fopen(logfile,"a+"))!=NULL){
	    chmod(logfile, 0777);
        }
    }
}

Logger::Logger()
{
    MutexCreate(&mutex);
    fp = stdout;
    flgNoTime = true;
    
}

Logger::~Logger()
{
    if(fp!=NULL){
        if(fp!=stdout){
            fclose(fp);
        }
    }
}

char *Logger::toHex(unsigned char *p,int len)
{
    static char tmp[1024*1000];
    char t[32];
    tmp[0]=0;
    MutexLock(&mutex);
    for(int i=0;(i<len)&&(i<16);i++){
            sprintf(t,"%02X ",p[i]);
            strcat(tmp,t);
    }
    if(len > 16){
            strcat(tmp,"...");
    }
    MutexUnlock(&mutex);
    return(tmp);
}

void Logger::_logStr(char *buff)
{
    if(fp!=NULL){
        fprintf(fp,"%s",buff);
        fflush(fp);
    }
}

void Logger::printf(char *format, ...)
{
    char buff[2048];
    va_list args;
    va_start(args, format);
    vsprintf(buff,format, args);
    va_end(args);
    MutexLock(&mutex);
    _logStr(buff);
    MutexUnlock(&mutex);    
}

void Logger::logStr(char *p){
    time_t t;
    time(&t);
    char *stime = ctime(&t);
    stime[strlen(stime)-1]=0;
    if(flgNoTime){
        printf("[%5d] %s\n",gettid(),p);
    }else{
        printf("%s [%5d] %s\n",stime,gettid(),p);
    }
}

//
//  Dump HEX in ultraedit like format into log file
//
void Logger::logHex(unsigned char *p,int len)
{
    char tmp[128];
    char line[128];
    int i,j;
    line[0] = 0;
    for(i=0;i<len;i++){
        //printf("%02X ",p[i]);
        sprintf(tmp,"%02X ",p[i]);strcat(line,tmp);
        if(((i+1)%16)==0){
            for(j=16;j>0;j--){
                unsigned char ch = p[i+1-j];
                if(isalnum(ch)){
                    sprintf(tmp,"%c",ch);strcat(line,tmp);
                }else{
                    strcat(line,".");
                }
            }
            strcat(line,"\n");
            _logStr(line);
            line[0]=0;
        }
    }
    int index = i%16;
    // pad space 
    for(j=0;j<(16-index);j++){
        //printf("   ");
        strcat(line,"   ");
    }
    // add the rest if have
    for(j=index;j>0;j--){
        unsigned char ch = p[i-j];
        if(isalnum(ch)){
            sprintf(tmp,"%c",ch);strcat(line,tmp);
        }else{
            strcat(line,".");
        }
    }
    strcat(line,"\n");
    _logStr(line);
}


