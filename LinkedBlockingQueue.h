#ifndef __LINKED_BLOCKING_QUEUE_H__
#define __LINKED_BLOCKING_QUEUE_H__

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define LINKED_BLOCKING_QUEUE_DEFAULT_INITIAL_CAPACITY 20
#define LINKED_BLOCKING_QUEUE_DEFAULT_LOAD_FACTOR 0.75

#define LBQ LINKED_BLOCKING_QUEUE *queue
#define QUEUE_SIZE(queue) queue->size(queue)
#define QUEUE_IS_EMPTY(queue) queue->isEmpty(queue)
#define QUEUE_ADD(queue,value) queue->add(queue,value)
#define QUEUE_TAKE(queue) queue->take(queue)

typedef struct queue_node_struct {
    void *value;
    struct queue_node_struct *next;
} QUEUE_NODE;

typedef struct linked_blocking_queue_struct{
    int size;
    QUEUE_NODE *node;
    pthread_mutex_t mutex;
    sem_t *slots;
    sem_t *tasks;

    int (* size)(LBQ);
    int (* isEmpty)(LBQ);
    int (* add)(LBQ,void *value);
    void *(* take)(LBQ);

} LINKED_BLOCKING_QUEUE;

LINKED_BLOCKING_QUEUE *initLinkedBlockingQueue(int size);


#endif