#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>
#include <stdbool.h>

#include "team.h"

typedef struct nodeq
{
    team *X;

    struct nodeq *prev, *next;
} nodeq;

typedef struct queue
{
    int elems;

    nodeq *first, *last;
} queue;

nodeq *nodeq_create();
void nodeq_destroy(nodeq *n);

queue *queue_create();
void queue_enque(queue *q, nodeq *X);
nodeq *queue_deque(queue *q);
nodeq *queue_pop(queue *q);
void queue_destroy(queue *q);

#endif
