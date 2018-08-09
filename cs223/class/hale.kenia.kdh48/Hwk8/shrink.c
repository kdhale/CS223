#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "stack.h"
#include "hash.h"




int vowel(char c)
{
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int match(char a, char b)
{
    if(abs((int)a - (int)b) <= 5)
    {
        //printf("match: %c %c \n", a , b);
        return 1;
    }
    else if(vowel(a) && vowel(b))
    {
        //printf("match: %c %c \n", a , b);
        return 1;
    }
    else
        return 0;

}

char* rotate(char* str, int strlen, int ileft, int iright)
{
    char* new = malloc(sizeof(char) * strlen + 1);
    int i = 0;
    for(i = 0; i < iright; i++)
        new[i] = str[i];
    new[ileft] = str[iright];
    for(i = iright; i<strlen; i++)
        new[i] = str[i+1];
    new[strlen] = '\0';
    return new; 

}

int findMatch(Dict d, Stack* s, char* str, int len)
{
    int val = 3;
    int newlen = 0;
    if(len == 1)
    {
        //printf("pushing %s onto the stack \n", str);
        stackPush(s, str);
        //free(str);
        return 1; // finished!!!!!
    }
    else if(len == 2 && !(match(str[0], str[1])))
        return 0;
    for(int i = 0; i < len; i++)
    {
        if(len >= (i + 1) && match(str[i], str[i+1])) // 
        {
            newlen = len-1;
            char * newstr = rotate(str, newlen, i, i+1); // so now right is on left
            //printf("%s \n", newstr);
            //printf("\n");
            if(DictSearch(d, newstr)) // if this new string is in the dictionary, free and return 0;
            {
                free(newstr);
                return 0;
            }
            else
            {
                val = findMatch(d, s, newstr, newlen);
                if(val == 1)
                {
                    //printf("pushing %s onto the stack \n", str);
                    stackPush(s, str);
                    return 1;
                }
                else
                {
                    DictInsert(d, newstr, newstr);
                    free(newstr);
                }
            }
        }
        if(len >= (i + 3) && match(str[i], str[i+3]))
        {
            newlen = len-1;
            char * newstr = rotate(str, newlen, i, i+3); // so now right is on left
            //printf("%s \n", newstr);
            //printf("\n");
            if(DictSearch(d, newstr)) // if this new string is in the dictionary, free and return 0;
            {
                free(newstr);
                return 0;
            }
            else
            {
                val = findMatch(d, s, newstr, newlen);
                if(val == 1)
                {
                    //printf("pushing %s onto the stack \n", str);
                    stackPush(s, str);
                    return 1;
                }
                else
                {
                    DictInsert(d, newstr, newstr);
                    free(newstr);
                }
            }
        }
    }
    return 0;
}


int
main(int argc, char **argv)
{
    int i;

    Dict d = DictCreate();

    int len = strlen(argv[1]);
    char *str = malloc(sizeof(char) * len + 1);
    strcpy(str, argv[1]);
    str[len] = '\0';
    Stack *s = calloc(1,sizeof(Stack));

    i = findMatch(d,s,str,len);
    if(i == 1)
        stackPrint(s);

    DictDestroy(d);
    while(!(stackEmpty(s)))
    {
       free(stackPop(s)); 
    }
    free(s);
    free(str);

    
    return 0;
}