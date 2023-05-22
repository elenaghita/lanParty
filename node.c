#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "node.h"

void *node_create()
{
    node *ans = calloc(1, sizeof(node));
    if (!ans)
        return NULL;

    ans->X.firstName = ans->X.secondName = NULL;
    ans->next = NULL;

    return ans;
}

void node_destroy(node *n)
{
    if (!n)
        return;

    if (n->X.firstName)
        free(n->X.firstName);
    if (n->X.secondName)
        free(n->X.secondName);

    free(n);

    return;
}
