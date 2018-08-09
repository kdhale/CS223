#ifndef _STACK_H
#define _STACK_H


// basic stack implementation
// stack is a pointer to its first element
// caller will keep a pointer to this
typedef struct elt *Stack;

// create and destroy stacks
void stackDestroy(Stack *);

// usual functions
void stackPush(Stack *s, char* value);

// don't call this on an empty stack
char *stackPop(Stack *s);

// returns true if not empty
int stackEmpty(const Stack *s);

// print the elements of a stack to stdout
// using function print
void stackPrint(const Stack *s);

#endif