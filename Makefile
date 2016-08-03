IDIR=.
CC=gcc
CFLAGS=-Wall -std=c99 -g -DdbgPrint -I$(IDIR)
SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
EXECUTABLE=AVLTest

all: $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS)

clean:
	rm -f *.o $(EXECUTABLE)