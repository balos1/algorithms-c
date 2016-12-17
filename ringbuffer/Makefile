CC=gcc
CFLAGS=-c -Wall -std=c99 -I/usr/local/include -DUNIT_TESTING
HEADERS=ringbuffer.h
OBJECTS=tests.o ringbuffer.o
LIBS=-lcmockery
LDFLAGS=-L/usr/local/lib
EXECUTABLE=tests

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(EXECUTABLE) 

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -rf *.o $(EXECUTABLE)
