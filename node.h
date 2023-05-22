#ifndef __NODE_H__
#define __NODE_H__

#include <stdlib.h>
#include <stdbool.h>

#include "player.h"

typedef struct node
{
    Player X;

    struct node *next;
} node;

void *node_create();
void node_destroy(node *n);

#endif
