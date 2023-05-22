#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

list *list_create()
{
    list *ans = calloc(1, sizeof(list));
    if (!ans)
        return NULL;

    ans->X.firstName = ans->X.secondName = NULL;
    ans->X.points = 0;

    ans->next = NULL;

    return ans;
}

void list_add(list *l, Player X) /// se adauga un nou jucator in echipa l
{
    if (l->X.firstName == NULL && l->X.secondName == NULL) /// jucatorul curent (adica X) este primul jucator in lista asta
    {
        l->X = X;
        return;
    }

    list *new_node = calloc(1, sizeof(list)); /// create new node, pentru a assigna X-ul primit ca parametru
    if (!new_node)
        return;

    new_node->X = X;
    new_node->next = l; /// noul nod se adauga la inceputul listei, in stanga, asa cum este indicat in spec

    l = new_node; /// deci, primul nod din lista, acum, este chiar new_node (cel creat acum)

    return;
}

void list_destroy(list *l) /// distrugere lista
{
    if (!l)
        return;

    while (l)
    {
        list *next = l->next;
        free(l);
        l = next;
    }

    return;
}
