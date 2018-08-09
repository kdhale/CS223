
# Any line that starts with a sharp is a comment and is ignored
# by Make.

# These lines set variables that control make's default rules.
# We STRONGLY recommend putting "-Wall -pedantic -g3" in your CFLAGS.
CC=gcc

CFLAGS=-std=c99 -Wall -pedantic -g3

shrink: shrink.o hash.o stack.o
		${CC} ${CFLAGS} -o $@ $^