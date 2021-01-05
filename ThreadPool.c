#include "ThreadPool.h"

static void excute(POOL,void *task);
static int addWorker(POOL,void *task,int isCore);
static WORKER *newWorder(POOL,void *firstTask);
static void runWorker(void *argp);
static void addWorkerFailed(POOL,WORKER *w);
static int isRunning(POOL);
static void reject(void *task);
static int remove(void *task);


THREAD_POOL *newFixedThreadPool(int nThreads, int tasks){
    THREAD_POOL *pool = malloc(sizeof(THREAD_POOL));
    pool->corePoolSize = nThreads;
    pool->maximumPoolSize = nThreads;
    pool->workerCount = atomicInt(0);
    pool->runState = atomicInt(0);
    pool->queue = initLinkedBlockingQueue(tasks);
    pool->workers = ARRAYLIST_INIT;
    pool->mainLoc = createReentrantLock();
    return pool;
}

static WORKER *newWorder(POOL,void *firstTask){
    WORKER *w = malloc(sizeof(WORKER));
    w->state = -1;
    w->firstTask = firstTask;
    w->lock = createReentrantLock();
    w->pool = pool;
    w->thread = createThread(&runWorker,(void *)w); //WORKER中的线程成员可以引用自己
    return w;
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
        if(addWorker(pool,task,1)){
            return;
        }
    }
    if(isRunning(pool) && QUEUE_ADD(pool->queue,task)){
        workerCount = *(int *)(pool->workerCount->value);
        if(!isRunning(pool) && remove(task)){
            reject(task);
        }else if(workerCount == 0){
            addWorker(pool,NULL,0);
        }
    }else if(!addWorker(pool,task,0)){
        reject(task);
    }
}

static int addWorker(POOL,void *task,int isCore){
    retry:
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
            if(workerCount >= CAPACITY || 
                workerCount >= (isCore ? pool->corePoolSize : pool->maximumPoolSize)){
                return 0;
            }
            if(compareAndSet(pool->workerCount->value,workerCount,workerCount+1)){
                break;
            }
            int reRs = *(int *)(pool->runState->value);
            if(rs != reRs){
                goto retry;
            }
        }
    }
    int workerStarted = 0;
    int workerAdded = 0;

    WORKER *w = newWorder(pool,task);
    THREAD *t = w->thread;
    if(t != NULL){
        lock(pool->mainLoc);
        int rs = *(int *)(pool->runState->value);
        if(rs < SHUTDOWN || (rs == NULL && task == NULL) ){
            ARRAYLIST_ADD(pool->workers,w);
            int workerSize = ARRAYLIST_LENGTH(pool->workers);
            if(workerSize > pool->largestPoolSize){
                pool->largestPoolSize = workerSize;
            }
            workerAdded = 1;
        }
    }
    if(workerAdded){
        runThread(t);
        workerStarted = 1;
    }
    if(!workerStarted){
        addWorkerFailed(pool,w);
    }
    unlock(pool->mainLoc);
    return workerStarted;
}

static void addWorkerFailed(POOL,WORKER *w){

}

/**
 * @brief 
 * 
 * @param argp 
 */
static void runWorker(void *argp){
    WORKER *w = (WORKER *)argp;
    THREAD *wt = currentThread();
    void *task = w->firstTask;
    unlock(w->lock);
    int completedAbruptly = 1;
    while( task != NULL || (task = QUEUE_TAKE(w->pool->queue))){




    }

}