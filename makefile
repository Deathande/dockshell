CC=gcc
CFLAGS=-g -Wall -std=c99
LFLAGS=

all: docksh

docksh: main.o mycommands.o parsing.o
	$(CC) $(LFLAGS) $+ -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) $<

mycommands.o: mycommands.c mycommands.h
	$(CC) -c $(CFLAGS) $<

parsing.o: parsing.c parsing.h
	$(CC) -c $(CFLAGS) $<


clean:
	rm -f *.o docksh
