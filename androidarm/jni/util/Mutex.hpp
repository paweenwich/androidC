/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mutex.hpp
 * Author: kwang
 *
 * Created on August 9, 2016, 8:17 AM
 */

#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef pthread_mutex_t Mutex;
void MutexCreate( Mutex* m );
void MutexDestroy( Mutex* m );
void MutexLock( Mutex* m );
void MutexUnlock( Mutex* m );


#ifdef __cplusplus
}
#endif

#endif /* MUTEX_HPP */

