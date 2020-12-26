#include "atomic.h"

static void getAndIncrementInt(struct atomic_struct *atomic);
static void getAndDecrementInt(struct atomic_struct *atomic);

ATOMIC *atomicInt(int value){
    int *i = mallco(sizeof(int));
    *i = value;
    ATOMIC *ai = malloc(sizeof(ATOMIC));
    ai->value = i;
    ai->getAndIncrement = &getAndIncrementInt;
    return ai;
}

static void getAndIncrementInt(ATOMIC *a){
     __sync_fetch_and_add((int *)a->value,1);
}

static void getAndDecrementInt(struct atomic_struct *a){
    __sync_fetch_and_sub((int *)a->value,1);
}