#include "thread.h"

THREAD *all_threads = NULL;

static int getNextTid();

THREAD *createThread(void *target){


}

THREAD *currentThread(void){
    THREAD *t = all_threads;
    while(t != NULL){
        if(gettid() == all_threads->tid){
            return t;
        }else{
            t = t->next;
        }
    }
}

void *runThread(THREAD *thread){
    if(currentThread()->tid == gettid()){
        //执行run方法时不为当前线程本身，则执行
        
    }
}

void parkThread(THREAD *thread){

}

int isInterrupted(THREAD *thread, enum clear_interrupted flag){

    return 0;
}

void interruptThread(THREAD *thread){
    
}