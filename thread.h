#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

enum clear_interrupted {NOT_RESET = 0,RESET = 1};

typedef struct thread_struct{
    pthread_t *tid;
    char *name;
    int priority;
    void (* target)(void *arg);
    void *argp;
    int is_interrupted;
    struct thread_struct *next;
} THREAD;

THREAD *createThread(void *target, void *argp);

THREAD *currentThread(void);

void *runThread(THREAD *thread);

void parkThread(THREAD *thread);

int isInterrupted(THREAD *thread, enum clear_interrupted flag);

void interruptThread(THREAD *thread);

int isAlive();

#endif