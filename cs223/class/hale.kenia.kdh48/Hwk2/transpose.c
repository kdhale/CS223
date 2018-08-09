#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

int main(int argc, char **argv){

	int c;
	char *ptr;
	long long n = strtol(argv[1], &ptr,10);
	long long a = strtol(argv[2], &ptr,10);
	long long b = strtol(argv[3], &ptr,10);
	long long i;


	if(argc != 4 || n < 1) // if n < 1 or there aren't 3 arguments j and i should be long long, i and modulo to long long
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		printf("num args: %d\n", argc);
		printf("n: %lld\n", n);
		return 1;
	}
	else{
		while((c = getchar()) != EOF) // while not at end of file
		{
			char letters[n];// create array the size of n
			letters[0] = c; // place c at beginning of list since already extracted

			for(i = 1; i < n; i++) // populate list of n length full of characters
			{
				c = getchar();
				if(c == EOF) // if reaches end of file, start adding \0's
					letters[i] = '\0';
				else
					letters[i] = c;// else, just put it in the list
			}
			long long jcode[n]; // j code = list of numbers in new order (not entirely needed, but helps seperate ideas)

			for(i = 0; i < n; i++)
			{
				jcode[i] = (n + ((a * i) + b)%n)%n; // populating the list of the new number order
				printf("%c",letters[jcode[i]]); // printing chars out in that order
			}
			continue;

		}
		return 0;
	}

}