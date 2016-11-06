#ifndef _INCLUDE_COMMON_H_
#define _INCLUDE_COMMON_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// from `man shm_open`
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <signal.h>
#include <semaphore.h>

#define MY_SHM "/JIT"

typedef struct {
    sem_t resource;
    sem_t binary;
    int data;
    int readcount;
} Shared;

#endif //_INCLUDE_COMMON_H_

