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

// Allocates a new ringbuffer with space for n/n-1 elements
// where n must be a power of 2. If utilizing ringbuffer_sfinsert,
// then the max usable space is n-1 because of the definitions of 
// the "full" state and "empty" states.
// 
// Returns a pointer to the newly allocated ringbuffer.
ringbuffer* new_ringbuffer(uint32_t n);

// Frees memory used by ringbuffer.
void delete_ringbuffer(ringbuffer* rbuf);

// Inserts the value at the head of the ringbuffer.
// Does not check if the buffer is full, and will 
// overwrite any existing values. For a safe insert
// use ringbuffer_sfinsert(ringbuffer* rbuf, char value).
void ringbuffer_insert(ringbuffer* rbuf, char value);

// Inserts the value at the head of the ringbuffer.
// If the buffer is full, insertion will fail,
// and the function returns false. Utlizing sfinsert
// limits the usable space of the ringbuffer to n-1.
// 
// Returns true if insertion was successful. 
bool ringbuffer_sfinsert(ringbuffer* rbuf, char value);

// Removes the value at the head of the ringbuffer.
// 
// Returns the value removed, or 0 if it failed.
char ringbuffer_remove(ringbuffer* rbuf);

// Returns the value at the head of the ringbuffer,
// or 0 when the buffer is empty.
char ringbuffer_peek(ringbuffer* rbuf);

// Checks if the ringbuffer instance is empty.
// The buffer is defined as empty if the head is
// equal to the tail.
// 
// Returns true if it is empty, else it returns false.
bool ringbuffer_isempty(ringbuffer* rbuf);

// Checks if the ringbuffer instance is full.
// The buffer is defined as full if the head + 1
// element is equal to the tail. 
// 
// Returns true if it is full, else it returns false.
bool ringbuffer_isfull(ringbuffer* rbuf);

#endif


