#include "ThreadPool.h"

static void excute(POOL,void *task);
static int addWorker(POOL,void *task,int isCore);

THREAD_POOL *newFixedThreadPool(int nThreads, int tasks){
    THREAD_POOL *pool = malloc(sizeof(THREAD_POOL));
    pool->corePoolSize = nThreads;
    pool->maximumPoolSize = nThreads;
    pool->workerCount = atomicInt(0);
    pool->runState = atomicInt(0);
    pool->queue = initLinkedBlockingQueue(tasks);
    return pool;
}

void *submit(POOL,void *task){
    if(task == NULL){
        printf(stderr,"task can't NULL \n");
    }
    excute(pool,task);
}

void shutdown(POOL){

}

void excute(POOL,void *task){
    int workerCount = *(int *)(pool->workerCount->value);
    if(workerCount < pool->corePoolSize){

    }

}

static int addWorker(POOL,void *task,int isCore){
    while(1){
        int rs = *(int *)(pool->runState->value);
        //线程池状态不为RUNNING，不能添加任务
        if(rs >= SHUTDOWN &&
            !(rs == SHUTDOWN &&
                task == NULL &&
                 QUEUE_IS_EMPTY(pool->queue) > 0)){
            return 0;
        }

        while (1){
            int workerCount = *(int *)(pool->workerCount->value);
            


        }
        



    }
}