#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <stdio.h>
#include <stdlib.h>
#include "thread.h"
#include "atomic.h"
#include "linked_blocking_queue.h"

#define POOL THREAD_POOL *pool 

enum pool_state {
    RUNNING = -1,
    SHUTDOWN = 0,
    STOP = 1,
    TIDYING = 2,
    TERMINATED = 3
};

typedef struct threadpool_struct{
    volatile int corePoolSize;
    volatile int maximumPoolSize;
    LINKED_BLOCKING_QUEUE *queue;

    ATOMIC *workerCount;
    ATOMIC *runState;
} THREAD_POOL;

THREAD_POOL *newFixedThreadPool(int nThreads, int tasks);

void *submit(POOL,void *task);

void shutdown(POOL);

#endif