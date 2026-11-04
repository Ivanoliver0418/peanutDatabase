CC = gcc
CFLAGS = -g -O
CPPFLAGS = -Wall -Wextra -pedantic -I.

.PHONY: all clean

all: main

main: main.o pager.o
	$(CC) $(CFLAGS) $(CPPFLAGS) main.o pager.o -o main

main.o: main.c main.h pager.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c main.c -o main.o

pager.o: pager.c pager.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c pager.c -o pager.o

clean:
	rm -f main main.o
	@echo "all cleaned up!"
