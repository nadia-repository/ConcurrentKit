#ifndef __ATOMIC_H__
#define __ATOMIC_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct atomic_struct{
    volatile void *value;
    void  (* getAndIncrement)(struct atomic_struct *atomic);
    void  (* getAndDecrement)(struct atomic_struct *atomic);
}ATOMIC;

ATOMIC *atomicInt(int value);


#endif
