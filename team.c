#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "team.h"

team *team_create()
{
    team *ans = calloc(1, sizeof(team));
    if (!ans)
        return NULL;

    ans->n = ans->sum = 0;
    ans->avg = 0;

    ans->name = NULL;

    ans->first = NULL;

    ans->next = NULL;

    return ans;
}

void team_destroy(team *t)
{
    if (!t)
        return;

    if (t->name)
        free(t->name);

    if (t->first) /// daca am playeri in echipa "t"
    {
        node *now = t->first; /// primul player din echipa

        while (now) /// cat timp mai am de "distrus" playeri din echipa
        {
            node *_aux = now->next; /// avansez playerul (il tin intr-un aux)
            node_destroy(now);      /// distrug nodul (adica player-ul) curent
            now = _aux;
        }
    }

    free(t); /// nu uitam sa stergem si pointer-ul catre "t", echipa de distrus

    return;
}
