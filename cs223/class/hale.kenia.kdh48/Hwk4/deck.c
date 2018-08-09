// Abstract data type for a deck of playing cards
#include <stdio.h>
#include "deck.h"
#include <stdlib.h>
#include <string.h>
// Standard suits and ranks
#define SUITS "CDHS"
#define RANKS "A23456789TJQK"

// A single card
// This is small enough that we usually pass it 
// around by copying instead of using pointers.
// typedef struct card {
//     char rank;    from RANKS 
//     char suit;   /* from SUITS */
// } Card;

// A deck of cards
//typedef struct deck Deck;
struct cardList {
    struct cardList *next;  /* pointer to next element in the list */
    Card contents;      /* contents of this element */
};

struct deck {

    struct cardList *head;  /* dequeue this next */
    struct cardList *tail; 
};


// Create a new unshuffled deck of 52 cards,
// ordered by suit then rank:
//
// AC 2C 3C ... KC AD 2D 3D ... KD AH 2H 3H ... KS
Deck *deckCreate(void)
{
	Deck *d = malloc(sizeof(Deck));
	//char * suits = {'C', 'D', 'H', 'S'};
	//char * ranks = {'A', '2', '3', '4','5','6','7','8','9','10','J','Q','K'};
	d->head = NULL;
	d->tail = NULL;
	for(int i = 0; i < strlen(SUITS); i++)
	{
		for(int j = 0; j < strlen(RANKS); j++)
		{
			Card c;
			c.suit = SUITS[i]; // have to do "." instead of "->" because c is just a card, it doesn't have a pointer
			c.rank = RANKS[j];
			deckPutCard(d,c);
		}
	}
	return d;
}

// Free all space used by d.
// Running time should be O(length of deck)
void deckDestroy(Deck *d)
{
	while(deckNotEmpty(d)) {
        deckGetCard(d);
    }
    free(d);
}

// Return true if deck is not empty.
// Running time should be O(1).
int deckNotEmpty(const Deck *d)
{
	return d->head != NULL;
}

// Remove and return the top card of a deck.
// If deck is empty, behavior is undefined.
// Running time should be O(1).
Card deckGetCard(Deck *d)
{
	Card old;
	struct cardList *c; // don't need to malloc because it's a pointer

	old = d->head->contents; // the old head 
	c = d->head; // the head pointer
	d->head = c->next; // the head pointer now point where next was pointing
	free(c);
	return old;
}

// Add a card to the bottom of a deck.
// This is not required to do anything special if the card is bogus
//   (e.g. "1C", "?X", "A-").
// Running time should be O(1).
void deckPutCard(Deck *d, Card c)
{
	struct cardList *k;
	k = malloc(sizeof(struct cardList));
	k->contents = c;
	k->next = NULL;

	if(d->head == NULL)
		d->head = k;
	else
		d->tail->next = k;
	d->tail = k;
	//free(k);
}

// Split a deck into two piles:
//    *d1 is new deck with first n cards in d.
//    *d2 is new deck with remaining cards in d.
// Order of cards is preserved.
// If d contains fewer than n cards, put them all in d1.
// Destroys d.//
// Running time should be O(n).
void deckSplit(Deck *d, int n, Deck **d1, Deck **d2)
{
	*d1 = malloc(sizeof(Deck));
	*d2 = malloc(sizeof(Deck));
	int i = 0;
	(*d1)->head = NULL;
	(*d1)->tail = NULL;
	(*d2)->head = NULL;
	(*d2)->tail = NULL;

	while(deckNotEmpty(d) && i < n)
	{
		deckPutCard(*d1,deckGetCard(d));
		i++;
	}
	(*d2)->head = d->head;
	(*d2)->tail = d->tail;
	free(d);
}

// Shuffle two decks together by alternating cards from
// d1 and d2 to obtain new deck.
//
// If d1 is X X X X 
// and d2 is Y Y Y Y Y Y Y,
// return value is X Y X Y X Y X Y Y Y Y.
//
// If d1 is X X X X
// and d2 is Y Y,
// return value is X Y X Y X X.
//
// Running time should be O(length of shorter deck).
// Destroys d1 and d2.
Deck *deckShuffle(Deck *d1, Deck *d2)
{
	Deck *d;
	d = malloc(sizeof(Deck));
	struct cardList *c = malloc(sizeof(struct cardList));
	d->head = NULL;//
	d->tail = c;//malloc(sizeof(struct cardList));
	d->tail->next = c;
	if(!deckNotEmpty(d1))
	{
		free(d1);
		return d2;
	}
	else if(!deckNotEmpty(d2))
	{
		free(d2);
		return d1;
	}
	while(deckNotEmpty(d1) && deckNotEmpty(d2))
	{
		deckPutCard(d,deckGetCard(d1));
		deckPutCard(d,deckGetCard(d2));
	}
	if(deckNotEmpty(d1))
	{
		d->tail->next = d1->head;
		d->tail = d1->tail;
	}
	else
	{
		d->tail->next = d2->head;
		d->tail = d2->tail;
	}
	free(d1);
	free(d2);
	free(c);
	return d;

}

// Print the contents of deck to f as sequence of ranks/suits
// separated by spaces.
// Example output: "AS TC 9D 3H 5S" (without quotes)
// Running time should be O(length of deck).
void deckPrint(const Deck *d, FILE *f)
{
	struct cardList *c;// = malloc(sizeof(struct cardList));
	//fprintf(f, "%c%c", d->head->contents.rank, d->head->contents.suit);
	for(c = d->head; c != NULL; c = c->next) {
        if(c->next == NULL)
        	fprintf(f, "%c%c", c->contents.rank, c->contents.suit);
        else
        	fprintf(f, "%c%c ", c->contents.rank, c->contents.suit);
    }
    free(c);
}
