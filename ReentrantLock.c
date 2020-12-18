#include "reentrantLock.h"

static int compareAndSetState(int *this,int expect,int update);
static void fairLock(LOCK);
static void nonfairLock(LOCK);
static void acquire(LOCK,ACQUIRES);
static int tryAcquire(LOCK,ACQUIRES);
static int fairTryAcquire(LOCK,ACQUIRES);
static int nonfairTryAcquire(LOCK,ACQUIRES);
static int hasQueuedPredecessors(LOCK);
static int acquireQueued(LOCK,NODE,ACQUIRES);
static int shouldParkAfterFailedAcquire(LOCK_NODE *pred, LOCK_NODE *node);
static int parkAndCheckInterrupt();
static LOCK_NODE *addWaiter(LOCK_NODE *mode);
static void selfInterrupt(void);


void lock(LOCK){
    if(IS_FAIR){
        fairLock(lock);
    }else {
        nonfairLock(lock);
    }
}

void tryLock(LOCK){

}

void unlock(LOCK){

}

static int compareAndSetState(int *this,int expect,int update){
    return __sync_val_compare_and_swap(this,expect,update);
}

static void fairLock(LOCK){
    acquire(lock,1);
}

static void nonfairLock(LOCK){
    if(compareAndSetState(&lock->cas,0,1)){
        lock->exclusive_owner_thread = currentThread();
    }else{
        acquire(lock,1);
    }
}

static void acquire(LOCK,ACQUIRES){
    if( tryAcquire(lock,acquires) == 0 &&
        acquireQueued(lock,addWaiter(NULL),acquires)){
            selfInterrupt();
    }
}

static int tryAcquire(LOCK,ACQUIRES){
    if(IS_FAIR){
        fairTryAcquire(lock,acquires);
    }else{
        nonfairTryAcquire(lock,acquires);
    }
}

static int fairTryAcquire(LOCK,ACQUIRES){
    pid_t current_thread =currentThread();
    if(lock->state == 0){ //当前锁没有枷锁
        //再次检查是否有其他线程抢占锁
        if(hasQueuedPredecessors(lock) == 0 && //公平锁需要考虑等待队列中是否有其他等待的node
            compareAndSetState(&lock->cas,0,acquires)){
                lock->exclusive_owner_thread = currentThread();
                return 1;
        }
    }else if (current_thread == lock->exclusive_owner_thread){ //检查锁是否为当前线程持有
        lock->state += acquires; //锁重入
        return 1;
    }
    return 0;
}

static int nonfairTryAcquire(LOCK,ACQUIRES){
    pid_t current_thread = currentThread();
    if(lock->state == 0){ //当前锁没有枷锁
        //再次检查是否有其他线程抢占锁
        if(compareAndSetState(&lock->cas,0,acquires)){
            lock->exclusive_owner_thread = currentThread();
            return 1;
        }
    }else if (current_thread == lock->exclusive_owner_thread){ //检查锁是否为当前线程持有
        lock->state += acquires; //锁重入
        return 1;
    }
    return 0;
}

static int hasQueuedPredecessors(LOCK){
    LOCK_NODE *t = lock->tail;
    LOCK_NODE *h = lock->head;
    LOCK_NODE *s;
    //等待队列不为空，并且等待队列只有一个node，或者第一个等待node不是当前线程时
    return h != t && 
        ((s = h->next) == NULL || *(h->thread) != currentThread(););
}

static int acquireQueued(LOCK,NODE,ACQUIRES){
    int interrupted = 0;
    while (1){
        LOCK_NODE *p = _predecessor();
        if(p == lock->head && _tryAcquire()){ //如果第一个等待的节点是头节点，则重新尝试获取锁
            //当前节点获取到锁
            //当前节点晋升为head节点（空节点）
            lock->head = node;
            node->thread = NULL;
            node->prev = NULL;
            free(node->next);//释放老的prev节点空间
            return interrupted;
        }  
        if(shouldParkAfterFailedAcquire(p,node) && 
            parkAndCheckInterrupt()){
            interrupted = 1;
        }
    }
    if(1){
        
    }
    
}

LOCK_NODE *initNode(){
    LOCK_NODE *node = malloc(sizeof(LOCK_NODE));

    node->predecessor = &predecessor;
}

LOCK_NODE *predecessor(NODE){
    return node->prev;
}

static int shouldParkAfterFailedAcquire(LOCK_NODE *pred, LOCK_NODE *node){
    int ws = pred->wait_status;
    if(ws == SIGNAL){
        //SIGNAL状态的的node正在等待被唤醒，可以安全挂起
        return 1;
    }else if(ws > 0){
        //CANCELLED
        //当前节点状态为取消，查找之前不是CANCELLED的节点，并淘汰CANCELLED的节点
        do {
            node->prev = pred = pred->prev;
        }while (pred->wait_status > 0);
        pred->next = node;
    }else {
        compareAndSetState(&pred->wait_status,ws,SIGNAL);
    }
    return 0;
}

static int parkAndCheckInterrupt(){

    return 0;
}

static LOCK_NODE *addWaiter(LOCK_NODE *mode){

}

static void selfInterrupt(void){

}