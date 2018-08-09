#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "treeSort.h"


struct tree{

    Node *nodes;
    //char *kidstring;
};
struct node{
    int numkids;
    Node **kids; /* right child */
};

// generate a random binary search tree
// with keys in range [lo,hi)

int
peekchar(void)
{
    int c;
    c = getchar();
    if(c != EOF) ungetc(c, stdin);      /* puts it back */
    
    return c;
}

/*int
treeSize(Node *n)
{
    if(n == 0) {
        return 0;
    } else {
        return 1 + treeSize(n->left) + treeSize(n->right);
    }
}
*/
int
treeHeight(Node *n)
{
    int h = 1;
    if(n->numkids == 0) {
        return h;
    } else {
        for(int i = 0; i < n->numkids; i++)
        {
            h += treeHeight(n->kids[i]);
        }
        return h;
    }
}

void
deq(Node *q)
{
    //int ret;
    //Node *e;
    /* patch out first element */
    //printf("numkids = %d", q->numkids)
    for(int i = 0; i < q->numkids; i++)
    {
        deq(q->kids[i]);
    }
    free(q->kids);
    free(q);
    //free(e);
}

Node *buildbracketList(Tree *t, int arrsize, Node* root) 
{
  char c = 0;
  Node* n = malloc(sizeof(Node)); // new node being built
  n->numkids = 0;
  n->kids = NULL;
  while((c = getchar()) != EOF)
  {
    if(c == '[')
    {
        n->numkids +=1;
        n->kids = realloc(n->kids, (n->numkids) * sizeof(Node));
        n->kids[n->numkids - 1] = buildbracketList(t,arrsize,n);
    }
    else if(c == ']') // if see a right bracket, return self
    {
        return n;
    }
    else //if(numclosed > numopen || (c != ']' && c != '[' && c != '\n' )) // if mismatched brackets or char that shouldn't be there
    {
        deq(n);
        free(t);
        exit(1);
    }
  }
  deq(n);
  free(t);
  exit(1); // if numclosed never equals num open, exit

}


Node* buildTree(Tree *t)
{
    Node *root = NULL;
    char c = getchar();
    //char* arr = malloc(sizeof(char) * 10); 
    if(c == '[')
    {
        //arr[0] = c;
        root = buildbracketList(t,10,root);
    }
    else
        exit(1);
    return root;

}



int
intCompare(const void *a, const void *b)
{
    return (treeHeight((*((Node**) a))) - treeHeight((*((Node**) b)))) * -1;
}


Node* sort(Node* n)
{
    for(int i = 0; i < n->numkids; i++)
    {
        sort(n->kids[i]);
    }
    if(n->numkids > 0)
        qsort(n->kids, n->numkids,sizeof(Node *), intCompare);
    return n;
}
void recprint(Node* n)
{
    printf("[");
    for(int i = 0; i < n->numkids; i++)
        recprint(n->kids[i]);
    printf("]");
}


int
main(int argc, char **argv)
{
    Tree * t = malloc(sizeof(Tree));
    Node *root = buildTree(t);
    t->nodes = root;

    //printf("original: ");

    //recprint(root);

    //printf("\nsorted: ");

    /*for(int i = 0; i < root->numkids; i++)
    {
        printf("height = %d", treeHeight(root->kids[i]));
    }*/

    recprint(sort(root));

    /*for(int i = 0; i < t->numchars; i++)
    {
        printf("%c", t->kidstring[i]);
    }*/
    deq(t->nodes);
    free(t);

    //Node *n = treeMakeRandom(0, atoi(argv[1]));
/*    printf("size = %d\n", treeSize(t));
    printf("height = %d\n", treeHeight(t));
*/
    

    return 0;
}