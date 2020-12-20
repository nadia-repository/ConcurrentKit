#include <pthread.h>

typedef struct thread_struct{
    int pid;
    char *name;
    int priority;
    int is_self;
    void (* target)(void *arg);

    struct thread_struct *next;
} THREAD;

THREAD *currentThread(void);

void *runThread(THREAD *thread);