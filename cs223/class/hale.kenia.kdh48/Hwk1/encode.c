#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

int
peekchar(void)
{
    int c;

    c = getchar();
    if(c != EOF) ungetc(c, stdin);      /* puts it back */
    
    return c;
}

int main(int argc, char **argv)
{
    int c = 0;
    char first;
    while((c = getchar()) != EOF) {
        if(isalpha(c))
        {
            first = c;
            if(isalpha(peekchar())) // keep checking if the next character is alphabet, if so, store it
            {
                int second = getchar();
                if(isalpha(peekchar()))
                {
                    int third = getchar();
                    if(isalpha(peekchar())) // once you get here, know that there's more than three letters in a row
                    {
                        if(isupper(first)) // second must match case of first, output second
                            putchar(toupper(second));
                        else
                            putchar(tolower(second)); // if first isn't uppercase, must be lowercase
                        putchar(third);// output the third
                        while(isalpha(peekchar()))// output every other letter till reach the end of word
                            putchar(getchar());
                        putchar(tolower(first)); // then output the old first letter at the end
                        putchar('o');// put 0
                        continue;// check next word
                    }
                    else // else, theres only 3 characters in word
                    {
                        if(isupper(first)) // second must match case of first
                            putchar(toupper(second));
                        else
                            putchar(tolower(second));
                        putchar(third); // output third
                        putchar(tolower(first));
                        putchar('a'); // add these at end because <= 3
                        putchar('n');
                        continue;
                    }
                }
                else // word size 2
                {
                    if(isupper(first))
                        putchar(toupper(second));
                    else
                        putchar(tolower(second));
                    putchar(tolower(first));
                    putchar('a');
                    putchar('n');
                    continue;
                }
            }
            else // one letter word
            {
                putchar(first);
                putchar('a');
                putchar('n');
                continue;
            }
        }
        else // if not alphabet, just output character
        {
            putchar(c);
            continue;
        }
    }
    return 0;
}