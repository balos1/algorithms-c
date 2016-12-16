#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct _ringbuffer {
	uint32_t max;     // max number of elements in the buffer
	uint32_t head;    // input
	uint32_t tail;    // output
	char* buffer;     // underlying buffer
} ringbuffer;

// Allocates a new ringbuffer with space for n elements of size sz.
// Returns a pointer to the newly allocated ringbuffer.
ringbuffer* new_ringbuffer(uint32_t n);

void delete_ringbuffer(ringbuffer* rbuf);

// Inserts the value at the tail of the ringbuffer.
// Does not check if the buffer is full, and will 
// overwrite any existing values. For a safe insert
// use ringbuffer_sfinsert(ringbuffer* rbuf, char value).
void ringbuffer_insert(ringbuffer* rbuf, char value);

// Inserts the value at the tail of the ringbuffer.
// If the buffer is full, insertion will fail,
// and the function returns false.
bool ringbuffer_sfinsert(ringbuffer* rbuf, char value);

// Removes the value at the head of the ringbuffer.
// Returns the value removed.
char ringbuffer_remove(ringbuffer* rbuf);

// Returns the value at the head of the ringbuffer.
char ringbuffer_peek(ringbuffer* rbuf);

// Checks if the ringbuffer instance is empty.
bool ringbuffer_isempty(ringbuffer* rbuf);

// Checks if the ringbuffer instance is full.
bool ringbuffer_isfull(ringbuffer* rbuf);

#endif


