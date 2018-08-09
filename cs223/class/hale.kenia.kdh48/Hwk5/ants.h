#ifndef _NUM_H
#define _NUM_H

#include <stdio.h>

/*
 * High-precision arithmetic on non-negative number in base 10.
 */

typedef struct position Position;

typedef struct hash Hash;

// create a hash table for storing up to n elts
Hash *hashCreate(size_t n);

void hashDestroy(Hash *h);

void hashSet(Hash *h, Position *p, int value);

// if key is in h, put value in *value, return 1,
// else return 0
char hashGet(Hash *h, Position *p);

// print contents of h
void hashPrint(Hash *h);

#endif /* _NUM_H */