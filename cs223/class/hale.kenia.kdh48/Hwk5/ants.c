#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "ants.h"

struct position{
    int x;
    int y;
    int z;
};

struct elt {
    struct elt *next;
    char value;
    Position *p;
};

struct hash {
    size_t size;   // size of array
    size_t elts;   // how many elements
    struct elt *a; // actual table of elements
};

#define MULTIPLIER (2) // extra space to keep load factor down, see hashCreate
#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)

int
peekchar(void)
{
    int c;

    c = getchar();
    if(c != EOF) ungetc(c, stdin);      /* puts it back */
    
    return c;
}

static void
grow(Hash *h)
{
    Hash *h2;// = malloc(sizeof(Hash));            /* new dictionary we'll create */
    struct hash swap;   /* temporary structure for brain transplant */
    int i;
    //struct elt *e;

    h2 = hashCreate(h->size * GROWTH_FACTOR);

    for(i = 0; i < h->size; i++) {
            Position* start = malloc(sizeof(Position));
            start->x = h->a[i].p->x; // we already know the position, so just set it here
            start->y = h->a[i].p->y;
            start->z = h->a[i].p->z;
            hashSet(h2, start, h->a[i].value);
        }

    /* the hideous part */
    /* We'll swap the guts of d and d2 */
    /* then call DictDestroy on d2 */
    swap = *h;
    *h = *h2;
    *h2 = swap;

    hashDestroy(h2);
}

// create a hash table for storing up to n elts
Hash *
hashCreate(size_t n) {
    Hash *h = malloc(sizeof(Hash));
    
    h->size = MULTIPLIER * n;  // start extra big because we don't reallocate
    h->elts = 0;

    h->a = calloc(h->size, sizeof(struct elt));

    return h;
}

void
hashDestroy(Hash *h)
{
    // need to free ps
    //for(size_t i = 0; i < h->size; i++) {
        //if(h->a[i].p != 0) {
          //  free(h->a[i].p);
        //}
   // }

    free(h->a);
    free(h);
}

#define MULTIPLIERx (97)
#define MULTIPLIERy (61)
#define MULTIPLIERz (57)

size_t
hashFunction(Position *p)
{
    unsigned long h;

    h = 0;
    h = h * MULTIPLIERx + p->x;
    h = h * MULTIPLIERy + p->y;
    h = h * MULTIPLIERz + p->z;

    return h;
}

// find position of p in h
// or first empty position if not in h
static size_t
hashFind(Hash *h, Position *p)
{
    size_t hashed = hashFunction(p) % h->size;

    while(h->a[hashed].p != 0 && !(h->a[hashed].p->x == p->x && h->a[hashed].p->y == p->y && h->a[hashed].p->z == p->z)){
        hashed = (hashed + 1) % h->size;
    }

    return hashed;
}

void
hashSet(Hash *h, Position *p, int value)
{
    // where should p go?
    size_t pos = hashFind(h, p); // will find the index of wherever the matching positions are

    if(h->a[pos].p == 0) {
        // put in p
        h->a[pos].p = p;
        h->elts++;

        if(h->elts >= h->size * MAX_LOAD_FACTOR) {
            grow(h);
        }
        h->a[pos].value = value; // set the value at that point to value
    }
    else if (h->a[pos].p->x != p->x || h->a[pos].p->y != p->y || h->a[pos].p->z != p->z)
    {
        int i = pos;
        while(h->a[i].p->x != p->x || h->a[i].p->y != p->y || h->a[i].p->z != p->z)
        {
            i++;
        }
        h->a[i].value = value; // set the value at that point to value
    }
    else
        h->a[pos].value = value; // set the value at that point to value

}

// if p is in h, put value in *value, return 1,
// else return 0
char
hashGet(Hash *h, Position *p)
{
    size_t pos = hashFind(h, p);

    if(h->a[pos].p == 0) {
        return ' ';
    }
    else if (h->a[pos].p->x != p->x || h->a[pos].p->y != p->y || h->a[pos].p->z != p->z)
    { 
        int i = pos;
        while(h->a[i].p->x != p->x || h->a[i].p->y != p->y || h->a[i].p->z != p->z)
        {
            i++;
        }
        return h->a[i].value;
    } 
    else {
        //*value = h->a[pos].value;

        return h->a[pos].value;
    }


}


int main(int argc, char **argv)
{
    int c = 0; // needs to be int or will turn negative, was the reason that allAnts was saying invalid read of 4

    Position *posarr = calloc(256, sizeof(Position)); // array full of Positions of each character
    Hash *h = hashCreate(10000000); // start initial size
    for(int i = 0; i < 256; i++)
    {
        posarr[i].x = 0;
        posarr[i].y = 0;
        posarr[i].z = 0;
    }

    while((c = getchar()) != EOF) {
        int current = c;
        int ascii = (int) current; // keep track of ascii value of current symbol 
        struct elt curr_ant; // declare it as a new element
        
        curr_ant.value = current;
        Position start;
        start.x = posarr[ascii].x; // we already know the position, so just set it here
        start.y = posarr[ascii].y;
        start.z = posarr[ascii].z;
        curr_ant.p = &start;
        

       /* curr_ant.p->x = posarr[ascii].x;
        curr_ant.p->y = posarr[ascii].y;
        curr_ant.p->z = posarr[ascii].z;*/


        while(peekchar() != '\n' && peekchar() != EOF) // until you run into a new line or end of file
        {
            c = getchar(); // get the newest char in the line
            switch(c) {
                case 'h':
                    curr_ant.p->x -= 1;
                    break;
                case 'j':
                    curr_ant.p->y -= 1; 
                    break;
                case 'k':
                    curr_ant.p->y += 1;
                    break;
                case 'l':
                    curr_ant.p->x += 1;
                    break;
                case '<':
                    curr_ant.p->z += 1;
                    break;
                case '>':
                    curr_ant.p->z -= 1;
                    break;
                case '*':
                    curr_ant.p->z *= 2;
                    curr_ant.p->x *= 2;
                    curr_ant.p->y *= 2;
                    break;
                case '.':
                    hashSet(h,curr_ant.p,curr_ant.value);
                    break;
                case '?':
                    printf("%c", hashGet(h,curr_ant.p)); // %d %d %d",h->a[(hashFunction(curr_ant.p))].value, h->a[(hashFunction(curr_ant.p))].p->x, h->a[(hashFunction(curr_ant.p))].p->y, h->a[(hashFunction(curr_ant.p))].p->z);
/*                    printf("\t(%d,", curr_ant.p->x); 
                    printf("%d,", curr_ant.p->y); 
                    printf("%d)\n", curr_ant.p->z); */
                    break;
                default:
                    break;
                }
                posarr[ascii].x = curr_ant.p->x;
                posarr[ascii].y = curr_ant.p->y;
                posarr[ascii].z = curr_ant.p->z;
            }
            if(peekchar() == '\n')
                c = getchar();
        }
        free(posarr);
        hashDestroy(h);
    }

/*h Move the current ant one Position west. (-1, #, #)
j Move the current ant one Position south. (#, -1, #)
k Move the current ant one Position north.
l Move the current ant one Position east.
'<' Move the current ant one Position up.
'>' Move the current ant one Position down.
* Jump the current ant from its current Position (x, y, z) to Position (2x, 2y, 2z).
. Write the current ant's character to its current Position.
? Read the character at the current ant's current Position and print it to stdout.
\n character
Set the current ant to character. If \n is immediately followed by end-of-file, ignore it and exit.
EOF Exit.1*/