#include <stdio.h>
#include "num.h"
#include <stdlib.h>
#include <string.h>

/*
 * High-precision arithmetic on non-negative number in base 10.
 */
//typedef struct num Num; // define type of struct num --> Num

struct num {

    int *value; // array with least significant number in 0th place
    int length;
};

int myisDigit(const char *s) // will check if each number within is an actual number
{
	int len = strlen(s);
	for(int i = 0; i < len; i++)
	{
		if(s[i] < '0' || s[i] > '9')
			return -1;
		else
			continue;
	}
	return 0;
}

unsigned long long removeleadingZeros(const char *s) // will return index of first non-zero character
{
	unsigned long long i = 0;
	while(s[i] == '0')
		i++;
	if(s[i] == '\0') // means there are only zeros, return 0
		return -1;
	return i;
}

char * reverseNum(char * forward, int len) // will put array so least significant is in 0th place;
{
	char* reverse = malloc(sizeof(char) * len);
	for(int i = 0; i < len; i++)
	{
		reverse[len - 1 -i] = forward[i];
	}
	return reverse;
}
int chartoInt(char c)
{
	return c - '0';
}
/* constructs a Num from a string */
/* string contains representation of the number
 * in base 10, e.g. numCreate("314159");
 * Returns a null pointer (0) if the string contains any non-digits.
 * Leading zeros are OK: numCreate("012") parses as 12.
 * Empty string parses as 0 */
Num * numCreate(const char *s)
{
	Num *c;
	int len = strlen(s);
	c = malloc(sizeof(Num));
	if(s[0] == '\0')// Empty string parses as 0 */
	{
		c->length = 1;
		c->value = malloc(sizeof(int) * c->length);
		c->value[0] = 0;
	}
	else if(myisDigit(s) == -1) // Returns a null pointer (0) if the string contains any non-digits.
		return 0;
	else 
	{	
		if(s[0] == '0')
		{
			int nonzero = removeleadingZeros(s);
			if(nonzero == -1)
			{
				c->length = 1;
				c->value = malloc(sizeof(int) * c->length);
				c->value[0] = 0;
			}
			else
			{
				c->length = len - nonzero;
				c->value = malloc(sizeof(int) * c->length);
				for(int i = 0; i < c->length; i++)
					c->value[i] = chartoInt(s[i + nonzero]); // setting every value in the array	
			}
		}
		else
		{
			c->length = len;
			c->value = malloc(sizeof(int) * c->length);
			for(int i = 0; i < c->length; i++)
				c->value[i] = chartoInt(s[i]); // setting every value in the array
		}
	}
    return c;
}

/* Free all resources used by a Num */
void numDestroy(Num *n)
{
	free(n->value);
	free(n);
}

/* Get the value of the i-th least significant digit of a Num.
 * Returns 0 if i is out of range.
 * Example:
 *   n = numCreate("12345");
 *   numGetDigit(n, 0) == 5
 *   numGetDigit(n, 3) == 2
 *   numGetDigit(n, 17) == 0
 *   numGetDigit(n, -12) == 0
 */
int numGetDigit(const Num *n, int i)
{
	if(i < 0 || i > (n->length -1))
		return 0;
	else
		return n->value[n->length - i - 1];
}

/* add two Nums, returning a new Num */
/* does not destroy its inputs, caller must destroy output */

Num * numAdd(const Num *x, const Num *y)
{
	int * arr;
	int num; // keeps track of the number being kept
	int remainder = 0; // keep track of number being carried 
	int i = 0; // index 
	if(x->length >= y->length) // will be in reversed order
	{
		arr = malloc(sizeof(int) * (x->length + 1)); // allocating space for numbers
		for(int k = 0; k < x->length + 1; k++)
			arr[k] = 0;
		for(i = y->length -1; i >= 0; i--)
		{
			num = y->value[i] + x->value[i  +(x->length - y->length)] + remainder;
			remainder = 0;
			if(num > 9)
			{
				remainder = 1;
				num = num%10;
			}
			arr[i + (x->length - y->length) + 1] = num;
		}
		for(i = x->length - y->length -1; i >= 0; i--)
		{
			arr[i + 1] = x->value[i] + remainder;
			remainder = 0;
		}
		char * string = malloc(sizeof(char) * (x->length + 1));
		for(i = 0; i < x->length + 1; i++)
		{
			string[i] = arr[i] + '0';
		}
		free(arr);
		return numCreate(string);
	}
	else // needs to be at least length of y + 1
	{
		arr = malloc(sizeof(int) * (y->length + 1)); // allocating space for numbers
		for(i = x->length -1; i >= 0; i--)
		{
			num = x->value[i] + y->value[i  +(y->length - x->length)] + remainder;
			remainder = 0;
			if(num > 9)
			{
				remainder = 1;
				num = num%10;
			}
			arr[i + (y->length - x->length) + 1] = num;
		}
		for(i = y->length - x->length -1; i >= 0; i--)
		{
			arr[i + 1] = y->value[i] + remainder;
			remainder = 0;
		}
		char * string = malloc(sizeof(char) * (y->length + 1));
		for(i = 0; i < y->length + 1; i++)
		{
			string[i] = arr[i] + '0';
		}
		free(arr);
		return numCreate(string);
	}
	
}
/* multiply two Nums, returning a new Num */
/* does not destroy its inputs, caller must destroy output */
Num * numMultiply(const Num *x, const Num *y)
{
	int * arr;
	int num; // keeps track of the number being kept
	int carry = 0; // keep track of number being carried 
	int BASE = 10;
	int i = 0;
	int j = 0;
	arr = calloc((x->length) + (y->length), sizeof(int));
	for(i = 0; i < x->length; i++)
	{
		for(j = 0; j < y->length; j++)
		{
			num = y->value[j] * x->value[i];
			arr[i + j + 1] += num; // (x->length) * (y->length) - 
		}
	}
	for(i = (x->length + y->length) -1; i >= 0; i--)
	{
		int temp = arr[i] + carry;
		arr[i] = temp%BASE;
		carry = temp/10;
	}
	char * string = malloc(sizeof(char) * (y->length + x->length + 1));
	for(i = 0; i < y->length + x->length; i++)
	{
		string[i] = arr[i] + '0';
	}
	string[y->length + x->length] = '\0';
	Num *c;
	c = malloc(sizeof(Num));
	free(arr);
	if(string[0] == '0')
	{
		int nonzero = removeleadingZeros(string);
		if(nonzero == -1)
		{
			c->length = 1;
			c->value = malloc(sizeof(int) * c->length);
			c->value[0] = 0;
		}
		else
		{
			c->length = y->length + x->length - nonzero;
			c->value = malloc(sizeof(int) * c->length);
			for(i = 0; i < c->length; i++)
				c->value[i] = chartoInt(string[i + nonzero]); // setting every value in the array	
		}
	}
	else
	{
		c->length = y->length + x->length;
		c->value = malloc(sizeof(int) * c->length);
		for(int i = 0; i < c->length; i++)
			c->value[i] = chartoInt(string[i]); // setting every value in the array
	}
	free(string);
	return c;//numCreate(string);
}



/* Print the digits of a number to file.
 * Do not print any leading zeros unless n is zero. */
void numPrint(const Num *n, FILE *f)
{
	for(int i = 0; i < n->length; i++)
		fprintf(f, "%c", n->value[i] + '0');
    
}