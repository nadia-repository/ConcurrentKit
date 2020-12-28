#ifndef __LINKED_BLOCKING_QUEUE_H__
#define __LINKED_BLOCKING_QUEUE_H__

#define LBQ LINKED_BLOCKING_QUEUE *queue
#define QUEUE_SIZE(queue) queue->size(queue)
#define QUEUE_IS_EMPTY(queue) queue->isEmpty(queue)

typedef struct linked_blocking_queue_struct{
    
    int (* size)(LBQ);
    int (* isEmpty)(LBQ);

    int (* add)(LBQ,void *value);
    void *(* take)(LBQ);

} LINKED_BLOCKING_QUEUE;

LINKED_BLOCKING_QUEUE *initLinkedBlockingQueue(int size);

int addBlockQueue(LBQ,void *value);

void *takeBlockQueue(LBQ);



#endif