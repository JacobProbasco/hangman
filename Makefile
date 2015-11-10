CFLAGS=-std=c11 -Wall -Wextra -pedantic -Werror

.PHONY: clean debug

hangman:hangman.c

debug: CFLAGS+=-g
debug: hangman


clean:
	-rm hangman *.o
