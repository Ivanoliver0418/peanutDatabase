CC = gcc
CFLAGS = -g -O
CPPFLAGS = -Wall -Wextra -pedantic -I.

.PHONY: all clean

all: main

main: main.o main.h
	$(CC) $(CFLAGS) $(CPPFLAGS) main.o -o main

main.o: main.c main.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c main.c -o main.o

clean:
	rm -f main main.o
	@echo "all cleaned up!"
