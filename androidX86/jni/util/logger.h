#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include <stdarg.h>
#include "Mutex.hpp"
class Logger  {
public:
	Mutex mutex;
	FILE *fp;
	bool flgNoTime;
	Logger(char *logfile,bool FLGNOTIME=false);
        Logger();
        virtual ~Logger();
	void logStr(char *p);
	void logHex(unsigned char *p,int len);
	char *toHex(unsigned char *p,int len);
        void printf(char *format, ...);
        virtual void _logStr(char *);
};

class StdOutLogger: public Logger {
public:
    char name[64];
    StdOutLogger(char *name);
    virtual ~StdOutLogger();
    virtual void _logStr(char *p);
private:
};
#endif
