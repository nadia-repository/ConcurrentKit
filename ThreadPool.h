#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <stdio.h>
#include <stdlib.h>
#include "Thread.h"
#include "Atomic.h"
#include "LinkedBlockingQueue.h"
#include "ConcurrentTools.h"
#include "arraylist.h"
#include "ReentrantLock.h"

#define POOL THREAD_POOL *pool 

enum pool_state {
    RUNNING = -1,
    SHUTDOWN = 0,
    STOP = 1,
    TIDYING = 2,
    TERMINATED = 3
};

static const int CAPACITY = (1 < (sizeof(int)-3)) -1;

typedef struct threadpool_struct{
    volatile int corePoolSize;
    volatile int maximumPoolSize;
    int largestPoolSize;
    LINKED_BLOCKING_QUEUE *queue;

    ARRAYLIST *workers;
    ATOMIC *workerCount;
    ATOMIC *runState;

    REENTRANT_LOCK *mainLoc;
} THREAD_POOL;

typedef struct worker_struct{
    volatile int state;
    void (*firstTask)();
    THREAD *thread;
    REENTRANT_LOCK *lock;
} WORKER;

THREAD_POOL *newFixedThreadPool(int nThreads, int tasks);

void *submit(POOL,void *task);

void shutdown(POOL);

#endif