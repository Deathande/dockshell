CC=gcc
CFLAGS=-g -Wall
LFLAGS=

all: docksh

docksh: main.o mycommands.o
	$(CC) $(LFLAGS) $+ -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) $<

mycommands.o: mycommands.c mycommands.h
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f *.o docksh
