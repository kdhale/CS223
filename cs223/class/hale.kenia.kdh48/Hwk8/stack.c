#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"


struct elt {
    struct elt *next;
    char* value;
};



struct stack {
    struct elt *head;
};

/* 
 * We could make a struct for this,
 * but it would have only one component,
 * so this is quicker.
 */

#define STACK_EMPTY (0)

/* push a new value onto top of stack */
void
stackPush(Stack *s, char* value)
{
    struct elt *e;

    e = malloc(sizeof(struct elt));
    assert(e);

    e->value = value;
    e->next = *s;
    *s = e;
}

int
stackEmpty(const Stack *s)
{
    return (*s == 0);
}

char *
stackPop(Stack *s)
{
    char* ret;
    struct elt *e;

    ret = (*s)->value;

    /* patch out first element */
    e = *s;
    *s = e->next;

    free(e);

    return ret;
}

/* print contents of stack on a single line */
void
stackPrint(const Stack *s)
{
    struct elt *e;

    for(e = *s; e != 0; e = e->next) {
        printf("%s\n", e->value);
    }
}
