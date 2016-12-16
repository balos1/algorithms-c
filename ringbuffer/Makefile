CC=gcc
CFLAGS=-c -Wall -std=c99
HEADERS=ringbuffer.h
OBJECTS=tests.o ringbuffer.o
EXECUTABLE=tests

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o $(EXECUTABLE)
