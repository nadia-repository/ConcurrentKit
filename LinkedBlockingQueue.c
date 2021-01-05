#include "LinkedBlockingQueue.h"

static int addBlockQueue(LBQ,void *value);
static void *takeBlockQueue(LBQ);
static int isLinkedBlockingQueueEmpty(LBQ);
static int sizeOfLinkedBlockingQueue(LBQ);

LINKED_BLOCKING_QUEUE *initLinkedBlockingQueue(int size){
    if(size <=0 ){
        size = LINKED_BLOCKING_QUEUE_DEFAULT_INITIAL_CAPACITY;
    }
    LINKED_BLOCKING_QUEUE *queue = malloc(sizeof(LINKED_BLOCKING_QUEUE));
    queue->size = size;
    queue->node = NULL;
    queue->add = &addBlockQueue;
    queue->take = &takeBlockQueue;
    queue->isEmpty = &isLinkedBlockingQueueEmpty;
    queue->size = &sizeOfLinkedBlockingQueue;

    pthread_mutex_init(&queue->mutex, NULL);
    queue->slots = sem_open("slots",O_CREAT, S_IRUSR | S_IWUSR, queue->size);
    queue->tasks = sem_open("items",O_CREAT, S_IRUSR | S_IWUSR, 0);
    return queue;
}

static int addBlockQueue(LBQ,void *value){
    sem_waite(queue->slots);
    pthread_mutex_lock(&queue->mutex);
    QUEUE_NODE *currentNode = malloc(sizeof(QUEUE_NODE));
    currentNode->value = value;
    currentNode->next = NULL;
    if(queue->node == NULL){
        queue->node = currentNode;
    }else {
        currentNode->next = queue->node;
        queue->node = currentNode;
    }
    pthread_mutex_unlock(&queue->mutex);
    sem_post(queue->tasks);
}

static void *takeBlockQueue(LBQ){
    void *value;
    sem_waite(queue->tasks);
    pthread_mutex_lock(&queue->mutex);
    value = queue->node->value;
    queue->node = queue->node->next;
    pthread_mutex_unlock(&queue->mutex);
    sem_post(queue->slots);
    return value;
}

static int isLinkedBlockingQueueEmpty(LBQ){
    if(queue->node == NULL){
        return 1;
    }
    return 0;
}

static int sizeOfLinkedBlockingQueue(LBQ){
    return queue->size;
}