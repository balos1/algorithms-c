// A simple, generic, ring buffer implementation.
// 
// The MIT License
//
// Copyright (c) 2016-2017 Cody Balos. http://github.com/cojomojo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "ringbuffer.h"

#if UNIT_TESTING
	extern void* _test_malloc(const size_t size, const char *file, const int line);
	extern void _test_free(void* const ptr, const char* file, const int line);

	#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
	#define free(ptr) _test_free(ptr, __FILE__, __LINE__)
#endif 

#define MOD2(a,b)  ((a) & (b-1))

// Allocates a new ringbuffer with space for n/n-1 elements
// where n must be a power of 2. If utilizing ringbuffer_sfinsert,
// then the max usable space is n-1 because of the definitions of 
// the "full" state and "empty" states.
// 
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

// Frees memory used by ringbuffer.
void delete_ringbuffer(ringbuffer* rbuf)
{
	free(rbuf->buffer);
	free(rbuf);
}

// Inserts the value at the head of the ringbuffer.
// Does not check if the buffer is full, and will 
// overwrite any existing values. For a safe insert
// use ringbuffer_sfinsert(ringbuffer* rbuf, char value).
void ringbuffer_insert(ringbuffer* rbuf, char value)
{
	uint32_t nextHead = MOD2(rbuf->head+1, rbuf->max);
	rbuf->buffer[rbuf->head] = value;
	rbuf->head = nextHead;
}

// Inserts the value at the head of the ringbuffer.
// If the buffer is full, insertion will fail,
// and the function returns false. Utlizing sfinsert
// limits the usable space of the ringbuffer to n-1.
// 
// Returns true if insertion was successful. 
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

// Removes the value at the head of the ringbuffer.
// 
// Returns the value removed, or 0 if it failed.
char ringbuffer_remove(ringbuffer* rbuf)
{
	char item = 0;
	if (!ringbuffer_isempty(rbuf)) {
		item = rbuf->buffer[rbuf->tail];
		rbuf->tail = MOD2(rbuf->tail+1, rbuf->max);;
	}
	return item;
}

// Returns the value at the head of the ringbuffer,
// or 0 when the buffer is empty.
char ringbuffer_peek(ringbuffer* rbuf)
{
	char item = 0;
	if (!ringbuffer_isempty(rbuf)) 
		item = rbuf->buffer[rbuf->tail];
	return item;
}

// Checks if the ringbuffer instance is empty.
// The buffer is defined as empty if the head is
// equal to the tail.
// 
// Returns true if it is empty, else it returns false.
bool ringbuffer_isempty(ringbuffer* rbuf) 
{
	return rbuf->head == rbuf->tail;
}

// Checks if the ringbuffer instance is full.
// The buffer is defined as full if the head + 1
// element is equal to the tail. 
// 
// Returns true if it is full, else it returns false.
bool ringbuffer_isfull(ringbuffer* rbuf) 
{
	return MOD2(rbuf->head+1, rbuf->max) == rbuf->tail;
}