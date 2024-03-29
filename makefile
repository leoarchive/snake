TARGET=snake
LIBS=
CC=gcc
CFLAGS= -pedantic -Wall

.PHONY: default all

default: $(TARGET)
all: default

OBJECTS = $(patsubst  , , $(wildcard *.c))
HEADERS = $(wildcard *.h)

:   $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

clean: 
	-rm -f *.o
	-rm -f *.tmp
	-rm -f $(TARGET)
