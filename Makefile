CC=g++
CFLAGS= -Wall -Werror

all: game_of_life

game_of_life: main.cpp
	$(CC) $(CFLAGS) $(CLIBS) -o $@ main.cpp

clean:
	-rm *~ *.o game_of_life

.PHONY: tags

tags:
	ctags *.[ch]