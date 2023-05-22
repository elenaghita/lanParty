#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>

#include "player.h"

struct _list
{
    Player X;

    struct _list *next;
};
typedef struct _list list;

list *list_create();
void list_add(list *l, Player X);
void list_destroy(list *l);

#endif
