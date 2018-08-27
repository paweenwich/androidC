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

void Logger::printf(char *format, ...)
{
    char buff[2048];
    va_list args;
    va_start(args, format);
    vsprintf(buff,format, args);
    va_end(args);
    logStr(buff);
}

void Logger::logStr(FILE *file, char *p,bool flgRaw)
{
    //printf("logStr\n");
    if(file!=NULL){
	MutexLock(&mutex);
	time_t t;
	time(&t);
	char *stime = ctime(&t);
	stime[strlen(stime)-1]=0;
	if(flgRaw){
	    fprintf(file,"%s\n",p);
	}else{
	    if(flgNoTime){
		fprintf(file,"[%5d] %s\n",gettid(),p);
	    }else{
		fprintf(file,"%s [%5d] %s\n",stime,gettid(),p);
	    }
	}
	fflush(file);
	MutexUnlock(&mutex);
    }
}

void Logger::logStr(char *p){
    logStr(fp,p);
}

void Logger::logRaw(char *p)
{
    logStr(fp,p,true);
}

//
//  Dump HEX in ultraedit like format into log file
//
void Logger::logHex(unsigned char *p,int len)
{
    int i,j;
    if(fp!=NULL){
	MutexLock(&mutex);
	for(i=0;i<len;i++){
	    fprintf(fp,"%02X ",p[i]);
	    if(((i+1)%16)==0){
		for(j=16;j>0;j--){
		    unsigned char ch = p[i+1-j];
		    if(isalnum(ch)){
			    fprintf(fp,"%c",ch);
		    }else{
			    fprintf(fp,".");
		    }
		}
		fprintf(fp,"\n");
	    }
	}
	int index = i%16;
	// pad space 
	for(j=0;j<(16-index);j++){
	    fprintf(fp,"   ");
	}
	// add the resh if have
	for(j=index;j>0;j--){
	    unsigned char ch = p[i-j];
	    if(isalnum(ch)){
		    fprintf(fp,"%c",ch);
	    }else{
		    fprintf(fp,".");
	    }
	}
	fprintf(fp,"\n");
	fflush(fp);
	MutexUnlock(&mutex);
    }
}

