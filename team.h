#ifndef __TEAM_H__
#define __TEAM_H__

#include <stdlib.h>
#include <stdbool.h>

#include "node.h"
#include "team.h"

typedef struct team
{
    int n, sum;
    long double avg;

    char *name;

    node *first;

    struct team *next;
} team;

team *team_create();
void team_destroy(team *t);

#endif
