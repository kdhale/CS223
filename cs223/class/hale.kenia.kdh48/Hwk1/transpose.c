#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

int main(int argc, char **argv){

	int c;
	int n = argc[1];
	int a = argv[2];
	int b = argv[3];
	int i;

	if(argc != 3 || n < 1) // if n < 1 or there aren't 3 arguments
	{
		fprintf(stderr, "Usage: %s", argv[0]);
		return 1;
	}
	else{
		while((c = getchar()) != EOF)
		{
			char *letters[n];// create array the size of n
			for(i = 0; i < n; i++)
				letters[i] = getchar(); // put letters in array
			int *jcode[n];
			for(i = 0; i < n; i++)
			{
				jcode[i] = abs(((a * i) + b)%n);
			}
			for(i = 0; i < n; i++)
			{
				putchar(letters[jcode[i]]);
			}
			continue;

		}
		return 0;
	}

}

// should return non-zero exit code if n < 1 or not 3 variables
// to access arguments, argc = number of args, argv[0] = ./transpose
//argv[1] = n, argv[2] = a, argv[3] = b
// a and b can be negative, but should return the same as positive, use abs