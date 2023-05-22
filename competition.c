#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "competition.h"

competition *competition_create()
{
    competition *ans = calloc(1, sizeof(competition));
    if (!ans)
        return NULL;

    ans->n = 0;

    ans->first = NULL;

    return ans;
}

void competition_destroy(competition *comp)
{
    if (!comp)
        return;

    for (team *t = comp->first; t;) /// se itereaza prin lista de echipa
    {
        if (t->name)
            free(t->name); /// dezalocam memoria utilizata pentru a stoca numele echipei

        if (t->first) /// incepem sa parcurgem playerii din echipa asta
        {
            node *now = t->first; /// primul player din echipa

            while (now) /// cat timp mai avem playeri de distrus
            {
                node *_aux = now->next; /// aux pentru a retine care e urm. player in lista (in cadrul echipei)
                node_destroy(now);
                now = _aux;
            }
        }

        team *next = t->next; /// aux pentru a retine care e urm. echipa in lista (in cadrul competitiei)
        free(t);
        t = next;
    }

    free(comp);

    return;
}

void competition_remove_min(competition *comp) /// functie care sterge echipa cu average-ul minim dintr-o competitie
{
    --(comp->n); /// scadem [# de echipe] din competitia in cauza

    long double Min = (long double)(1LL * 1000000000000000000); /// se initializeaza Min cu o valoare foarte mare (10^18)

    for (team *i = comp->first; i; i = (i->next)) /// aici se avanseaza echipa cu echipa: se pleaca din stanga, se merge spre dreapta
        if ((i->avg) < Min)                       /// incercam sa update-am minimul
            Min = i->avg;                         /// retinem echipa asta, ptr ca are min average until now

    if (((comp->first)->avg) == Min) /// caz special: echipa de removat e chiar prima din lista, grija mare la pointeri
    {
        team *keep = ((comp->first)->next);
        team_destroy(comp->first);

        (comp->first) = keep;
    }
    else
    {
        team *last = NULL; /// se va itera (din nou) prin lista de echipe, ca sa gasesc echipa cu min avg

        for (team *i = (comp->first); i; i = (i->next)) /// parcurgere
        {
            if ((i->avg) == Min) /// s-a gasit echipa cu min avg
            {
                (last->next) = (i->next); /// team "i" este "ignorata"/stearsa

                team_destroy(i); /// distrug, folosind functia din "team.h", echipa "i" (i.e.: cea cu average-ul min)

                return;
            }

            last = i;
        }
    }

    return;
}
