#ifndef __CONCURRENT_TOOLS_H__
#define __CONCURRENT_TOOLS_H__

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int compareAndSet(int *this,int expect,int update);


#endif