#include <pthread.h>

typedef struct thread_struct{
    int pid;

} THREAD;

THREAD *currentThread(void);