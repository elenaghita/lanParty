#ifndef __COMPETITION_H__
#define __COMPETITION_H__

#include <stdlib.h>
#include <stdbool.h>

#include "team.h"

typedef struct competition
{
    int n; /// [# de echipe din competitia curenta]

    struct team *first; /// pointer catre prima echipa (din lista, tot este implementat ca o lista simplu linkata)
} competition;

competition *competition_create();
void competition_destroy(competition *comp);
void competition_remove_min(competition *comp);

#endif
