#ifndef LOGGER_H
#define LOGGER_H
#include <stdarg.h>
#include "Mutex.hpp"
class Logger  {
public:
    Mutex mutex;
    FILE *fp;
    bool flgNoTime;
    Logger(char *logfile,bool FLGNOTIME=false);
    Logger();
    ~Logger();
    void logStr(FILE *file, char *p,bool flgRaw = false);
    virtual void logStr(char *p);
    virtual void logRaw(char *p);
    void logHex(unsigned char *p,int len);
    char *toHex(unsigned char *p,int len);
    void printf(char *format, ...);
};


#endif
