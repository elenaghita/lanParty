#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

nodeq *nodeq_create()
{
    nodeq *ans = calloc(1, sizeof(nodeq));
    if (ans)
        ans->X = NULL, ans->prev = ans->next = NULL;
    return ans;
}

void nodeq_destroy(nodeq *n)
{
    if (!n)
        return;

    free(n);

    return;
}

queue *queue_create()
{
    queue *ans = calloc(1, sizeof(queue));
    if (ans)
        ans->elems = 0, ans->first = ans->last = NULL;
    return ans;
}

void queue_enque(queue *q, nodeq *X) /// se adauga (la final; in dreapta) un nou element (PUSH_BACK)
{
    if (!q || !X)
        return;

    X->prev = X->next = NULL;

    ++(q->elems); /// se incrementeaza [# de elemente] din coada

    if ((q->elems) == 1)        /// primul element din coada
        q->first = q->last = X; /// primul si ultimul element din coada reprezinta acelasi nod, acest "X" din parametru
    else
        X->prev = q->last, q->last->next = X, q->last = X; /// mai avem si alte elemente, deci ultimul element adaugat este "X"

    return;
}

nodeq *queue_deque(queue *q) /// se scoate (la inceput; in stanga) element (POP_FRONT)
{
    if (!q)
        return NULL;

    if ((q->elems) == 0) /// NU e nimic de scos, 0 echipe in coada
        return NULL;

    --(q->elems); /// se decrementeaza [# de elemente] din coada

    nodeq *ans = q->first;

    if ((q->elems) == 0)
    {
        q->first = q->last = NULL;

        return ans;
    }

    q->first = q->first->next;

    if (q->first)
        q->first->prev = NULL;

    return ans;
}

nodeq *queue_pop(queue *q)
{
    if (!q)
        return NULL;

    if ((q->elems) == 0)
        return NULL;

    --(q->elems);

    nodeq *ans = q->last;

    q->last = q->last->prev;

    if (q->last)
        q->last->next = NULL;

    return ans;
}

void queue_destroy(queue *q)
{
    if (!q)
        return;

    if ((q->elems) > 0)
        for (nodeq *i = q->first; i;)
        {
            nodeq *next = i->next;

            nodeq_destroy(i);

            i = next;
        }

    free(q);

    return;
}
