#ifndef __REENTRANTLOCK_H__
#define __REENTRANTLOCK_H__

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "Thread.h"

#define LOCK REENTRANT_LOCK *lock
#define NODE LOCK_NODE *node
#define ACQUIRES int acquires
#define IS_FAIR lock->is_fair

#define _predecessor() node->predecessor(node)
#define _tryAcquire() tryAcquire(lock,acquires)

enum node_status {
    CANCELLED = 1,
    SIGNAL = -1,
    CONDITION = -2,
    PROPAGATE = -3
};

/*
*      +------+  prev +-----+       +-----+
* head |      | <---- |     | <---- |     |  tail
*      +------+       +-----+       +-----+
*/
typedef struct lock_node_struct{
    struct lock_node_struct *prev;
    struct lock_node_struct *next;
    struct lock_node_struct *next_waiter;
    THREAD *thread;
    enum node_status wait_status;
    struct lock_node_struct *(* predecessor)(NODE);
} LOCK_NODE;

typedef struct reentrant_lock_struct{
    int cas;
    int is_fair;
    THREAD *exclusive_owner_thread;
    int state;
    LOCK_NODE *tail;
    LOCK_NODE *head;
} REENTRANT_LOCK;



void lock(LOCK);

void tryLock(LOCK);

void unlock(LOCK);


#endif