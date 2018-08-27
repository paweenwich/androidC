#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <dlfcn.h>
#include <android/log.h>
#include <pthread.h>
#include "Mutex.hpp"



void MutexCreate( Mutex* m )
{
#ifdef WINDOWS
    InitializeCriticalSection( m );
#else
    pthread_mutex_init( m, NULL );
#endif
}


void MutexDestroy( Mutex* m )
{
#ifdef WINDOWS
    DeleteCriticalSection( m );
#else
    pthread_mutex_destroy( m);
#endif
}

void MutexLock( Mutex* m )
{
#ifdef WINDOWS
    EnterCriticalSection( m );
#else
    pthread_mutex_lock( m );
#endif
}

void MutexUnlock( Mutex* m )
{
#ifdef WINDOWS
    LeaveCriticalSection( m );
#else
    pthread_mutex_unlock( m );
#endif
}