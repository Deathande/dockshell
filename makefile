CC=gcc
CFLAGS=-g -Wall
LFLAGS=

all: docksh

docksh: main.o
	$(CC) $(LFLAGS) $+ -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f *.o docksh
