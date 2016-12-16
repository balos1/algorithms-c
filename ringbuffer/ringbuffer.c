#include "ringbuffer.h"

#define MOD2(a,b)  ((a) & (b-1))

// Allocates a new ringbuffer with space for n elements of size sz.
// n must be a power of 2.
// Returns a pointer to the newly allocated ringbuffer.
ringbuffer* new_ringbuffer(uint32_t n)
{
	// First check to make sure n is a power of two.
	// This works because any power of 2, N, will only have
	// a single 1 in its binary representation. This single 1 
	// will be the most signficant bit ignoring leading zeroes. 
	// N - 1 will be the one's complement. So essentially we 
	// have N & ~N which is 0. 
	// 
	// To prove to yourself that a power of 2 ANDed with 
	// that power of 2 - 1 is always 0 observe this pattern: 
	// (2:1, 10:1) (4:3, 100:11) (8:7, 1000:111) (16:15, 10000:1111).
	if ((n & (n-1)) != 0)
		return NULL;

	ringbuffer* rbuf = malloc(sizeof(ringbuffer));

	if (rbuf != NULL) {
		rbuf->max    = n;
		rbuf->tail   = 0;
		rbuf->head   = 0;
		rbuf->buffer = malloc(sizeof(char) * n);
	}
	
	return rbuf;
}

void delete_ringbuffer(ringbuffer* rbuf)
{
	free(rbuf->buffer);
	free(rbuf);
}

// Inserts the value at the tail of the ringbuffer.
// Does not check if the buffer is full, and will 
// overwrite any existing values. For a safe insert
// use ringbuffer_sfinsert(ringbuffer* rbuf, char value).
void ringbuffer_insert(ringbuffer* rbuf, char value)
{
	uint32_t nextTail = MOD2(rbuf->head+1, rbuf->max);
	rbuf->buffer[rbuf->head] = value;
	rbuf->head = nextTail;
}

// Inserts the value at the tail of the ringbuffer.
// If the buffer is full, insertion will fail,
// and the function returns false.
bool ringbuffer_sfinsert(ringbuffer* rbuf, char value)
{
	if (!ringbuffer_isfull(rbuf)) {
		rbuf->buffer[rbuf->head] = value;
		rbuf->head = MOD2(rbuf->head+1, rbuf->max);;
		return true;
	} else {
		return false;
	}
}

// Removes the value at the tail of the ringbuffer.
// Returns the value removed.
char ringbuffer_remove(ringbuffer* rbuf)
{
	char item;
	if (!ringbuffer_isempty(rbuf)) {
		item = rbuf->buffer[rbuf->tail];
		rbuf->tail = MOD2(rbuf->tail+1, rbuf->max);;
	}
	return item;
}

// Returns the value at the tail of the ringbuffer.
char ringbuffer_peek(ringbuffer* rbuf)
{
	char item = NULL;
	if (!ringbuffer_isempty(rbuf)) 
		item = rbuf->buffer[rbuf->tail];
	return item;
}

// Checks if the ringbuffer instance is empty.
bool ringbuffer_isempty(ringbuffer* rbuf) 
{
	return rbuf->head == rbuf->tail;
}

// Checks if the ringbuffer instance is full.
bool ringbuffer_isfull(ringbuffer* rbuf) 
{
	return MOD2(rbuf->head+1, rbuf->max) == rbuf->tail;
}