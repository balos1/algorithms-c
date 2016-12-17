#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <google/cmockery.h>
#include "ringbuffer.h"

static ringbuffer *rbuffer;

// Creates a new ringbuffer and sets the state 
// properly before running a unit test on 
// the ringbuffer instance.
void setup_rbuffer(void **state)
{
	rbuffer = new_ringbuffer(4);
	*state = (void*)rbuffer;
}

// Deletes a ringbuffer after running
// unit tests on the ringbuffer instance.
void teardown_rbuffer(void **state)
{
	delete_ringbuffer((ringbuffer*)*state);
}

void test_new_ringbuffer(void **state) 
{	
	// testing powers of two up to 16
	for (int i = 0; i < 16; ++i) {
		rbuffer = new_ringbuffer(1 << i);
		assert_true(rbuffer);
		assert_true(rbuffer->max == (1 << i));
		assert_true(rbuffer->tail == 0);
		assert_true(rbuffer->head == 0);
		assert_true(rbuffer->buffer);	
		delete_ringbuffer(rbuffer);
	}

	// testing non powers of two
	for (int i = 0; i < 8; ++i) {
		rbuffer = new_ringbuffer(11 << i);
		assert_false(rbuffer);
	}
}

void test_rbuffer_insert(void **state)
{
	ringbuffer_insert(rbuffer, 'C');
	assert_true(rbuffer->buffer[0] == 'C');

	ringbuffer_insert(rbuffer, 'o');
	ringbuffer_insert(rbuffer, 'd');
	ringbuffer_insert(rbuffer, 'y');
	assert_true(rbuffer->buffer[1] == 'o');
	assert_true(rbuffer->buffer[2] == 'd');
	assert_true(rbuffer->buffer[3] == 'y');
	
	ringbuffer_insert(rbuffer, 'B');
	assert_true(rbuffer->buffer[0] == 'B');
	assert_int_equal(rbuffer->head, 1);
	assert_int_equal(rbuffer->tail, 0);
}

void test_rbuffer_sfinsert(void **state)
{
	bool success = ringbuffer_sfinsert(rbuffer, 'C');
	assert_true(success);
	assert_true(rbuffer->buffer[0] == 'C');
	
	ringbuffer_sfinsert(rbuffer, 'o');
	ringbuffer_sfinsert(rbuffer, 'd');
	assert_true(rbuffer->buffer[1] == 'o');
	assert_true(rbuffer->buffer[2] == 'd');
	
	assert_false(ringbuffer_sfinsert(rbuffer, 'y'));
}

void test_rbuffer_remove(void **state)
{
	ringbuffer_sfinsert(rbuffer, 'C');
	ringbuffer_sfinsert(rbuffer, 'o');
	ringbuffer_sfinsert(rbuffer, 'd');
	assert_true(ringbuffer_remove(rbuffer) == 'C');
	assert_true(rbuffer->tail == 1);
	assert_true(ringbuffer_remove(rbuffer) == 'o');	
	assert_true(rbuffer->tail == 2);
	assert_true(ringbuffer_remove(rbuffer) == 'd');	
	assert_true(rbuffer->tail == 3);
	assert_false(ringbuffer_remove(rbuffer));	
	assert_true(rbuffer->tail == 3);
}

void test_rbuffer_peek(void **state)
{
	ringbuffer_sfinsert(rbuffer, 'C');
	ringbuffer_sfinsert(rbuffer, 'o');
	ringbuffer_sfinsert(rbuffer, 'd');

	assert_true(ringbuffer_peek(rbuffer) == 'C');
	assert_true(rbuffer->tail == 0);
	assert_true(ringbuffer_peek(rbuffer) == 'C');	
	assert_true(rbuffer->tail == 0);
	
	ringbuffer_remove(rbuffer);
	assert_true(ringbuffer_peek(rbuffer) == 'o');
	assert_true(rbuffer->tail == 1);
}

void test_rbuffer_isfull(void **state)
{
	assert_false(ringbuffer_isfull(rbuffer));
	ringbuffer_sfinsert(rbuffer, 'C');
	ringbuffer_sfinsert(rbuffer, 'o');
	ringbuffer_sfinsert(rbuffer, 'd');
	assert_true(ringbuffer_isfull(rbuffer));
}

void test_rbuffer_isempty(void **state)
{
	assert_true(ringbuffer_isempty(rbuffer));
	ringbuffer_sfinsert(rbuffer, 'C');
	assert_false(ringbuffer_isempty(rbuffer));
}

int main(void)
{
	const UnitTest tests[] = {
		unit_test(test_new_ringbuffer),
		unit_test_setup_teardown(test_rbuffer_insert, setup_rbuffer, teardown_rbuffer),
		unit_test_setup_teardown(test_rbuffer_sfinsert, setup_rbuffer, teardown_rbuffer),
		unit_test_setup_teardown(test_rbuffer_remove, setup_rbuffer, teardown_rbuffer),
		unit_test_setup_teardown(test_rbuffer_peek, setup_rbuffer, teardown_rbuffer),
		unit_test_setup_teardown(test_rbuffer_isfull, setup_rbuffer, teardown_rbuffer),
		unit_test_setup_teardown(test_rbuffer_isempty, setup_rbuffer, teardown_rbuffer)
	};

	return run_tests(tests);
}