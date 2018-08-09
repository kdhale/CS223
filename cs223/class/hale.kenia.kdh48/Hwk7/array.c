#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include "array.h"


struct node {
    int key;
    int size;
    struct node *left;  /* left child */
    struct node *right; /* right child */
};

struct array
{
	int (*funct)(int, int);
	size_t size;
	struct node *arr;
};


struct node * arrRecurse(size_t count, Array *a)
{
	struct node *new = malloc(sizeof(struct node));
	new->size = count;
	if(count == 1)
	{
		new->key = 0; // value of each value & rank
		return new;
	}
	else
	{
		new->left = arrRecurse(count/2,a);
		new->right = arrRecurse(count - (count/2),a);
		new->key = a->funct(new->left->key, new->right->key);
		return new;
	}
}


// Create a new array holding n values, all initially 0.
// Behavior is undefined if n == 0.
// Cost: O(n).
Array *arrayCreate(int (*combine)(int, int), size_t n)
{
	Array *a = malloc(sizeof(Array));
	a->size = n;
	a->funct = combine;
	a->arr = arrRecurse(n,a);
	return a;
}


void destRecurse(size_t count, struct node *n)
{
	if(count == 1)
		free(n);
	else
	{
		destRecurse(count/2, n->left);
		destRecurse(count - (count/2), n->right);
		free(n);
	}
}

// Free all space used by an array.
// Cost: O(n).
void arrayDestroy(Array *a)
{
	destRecurse(a->arr->size, a->arr);
	free(a);
}


// Return the number of elements of an array.
// Cost: O(1).
size_t arraySize(const Array *a)
{
	return a->size;
}


int getRecc(struct node *n, size_t i)
{
	//printf("i = %d\n");
	if(n->size == 1)
		return n->key;
	else if(i < n->size/2)
		return getRecc(n->left, i);
	else
		return getRecc(n->right, i - n->size/2);
}


// Return the i-th element of an array
// or 0 if i is out of range.
// Cost: O(log n).
int arrayGet(const Array *a, size_t i)
{
	if(i >= a->size || i < 0)
		return 0;
	else 
		return getRecc(a->arr,i);
}


void setRecc(Array *a, struct node *n, size_t i, int v)
{
	if(n->size == 1)
	{
		n->key = v;
		return;
	}
	else if(i < n->size/2)
		setRecc(a, n->left, i, v);
	else
		setRecc(a, n->right, i - n->size/2, v);
	n->key = a->funct(n->left->key, n->right->key); // because everything will have already been updated, no need to recurse
}

// Set the i-th element of an array to v.
// No effect if i is out of range.
// Cost: O(log n).
void arraySet(Array *a, size_t i, int v)
{
	if(i >= a->size || i < 0)
		return;
	else
		setRecc(a, a->arr, i, v);
}

// Return the result of aggregating the first k elements
// of an array in order using the combine function.
// If k is zero or greater than size, returns combination of all elements.
// Cost: O(log n).
int combineRecc(const Array *a, struct node *n, size_t k)
{
	if(n->size == k)
		return n->key;
	else if(k <= n->size/2) // if k is less, go left
		return combineRecc(a, n->left, k);
	else
		return a->funct(n->left->key, combineRecc(a, n->right, k - (n->size/2))); 
}


int arrayCombine(const Array *a, size_t k)
{
	if(k == 0 || k > a->size)
		return a->arr->key;
	else
		return combineRecc(a, a->arr, k); // because we're not counting 0
}
