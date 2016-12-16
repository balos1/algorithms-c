#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <google/cmockery.h>
#include <stdio.h>
#include <stdlib.h>
#include "ringbuffer.h"

static ringbuffer *rbuffer;

void setup_rbuffer(void **state)
{
	rbuffer = new_ringbuffer(4);
	*state = (void*)rbuffer;
}

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
	ringbuffer_insert(rbuffer, 'C');
	assert_true(rbuffer->buffer[0] == 'C');

	ringbuffer_insert(rbuffer, 'o');
	ringbuffer_insert(rbuffer, 'd');
	ringbuffer_insert(rbuffer, 'y');
	assert_true(rbuffer->buffer[1] == 'o');
	assert_true(rbuffer->buffer[2] == 'd');
	// assert_true(rbuffer->buffer[3] == 'y');
	
	// ringbuffer_insert(rbuffer, 'B');
	// assert_true(rbuffer->buffer[0] == 'C');
	assert_int_equal(rbuffer->head, 0);
	assert_int_equal(rbuffer->tail, 0);
}

void ringbuffer_print(ringbuffer* rbuf) 
{	
	uint32_t i;
	printf("\n{");
	for (i = 0; i < rbuf->max; ++i)
		printf(" %c", rbuf->buffer[i]);
	printf(" }\n");
}

int main(void)
{
	const UnitTest tests[] = {
		unit_test(test_new_ringbuffer),
		unit_test_setup_teardown(test_rbuffer_insert, setup_rbuffer, teardown_rbuffer),
		unit_test_setup_teardown(test_rbuffer_sfinsert, setup_rbuffer, teardown_rbuffer)
	};

	return run_tests(tests);
	// ringbuffer* rbuffer = new_ringbuffer(8);

	// if (rbuffer == NULL)
	// {
	// 	printf("Could not allocate buffer.\n");
	// 	return -1;
	// }	

	// ringbuffer_insert(rbuffer, 'C');
	// printf("\ninserted %c\n", 'C');
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);
	

	// ringbuffer_insert(rbuffer, 'o');
	// printf("\ninserted %c\n", 'o');
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);

	// ringbuffer_insert(rbuffer, 'd');
	// printf("\ninserted %c\n", 'd');
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);

	// ringbuffer_insert(rbuffer, 'y');
	// printf("\ninserted %c\n", 'y');
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);

	// ringbuffer_insert(rbuffer, '_');
	// printf("\ninserted %c\n", '_');
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);
	
	// ringbuffer_insert(rbuffer, 'B');
	// printf("\ninserted %c\n", 'B');
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);

	// printf("\nremoved %c\n", ringbuffer_remove(rbuffer));
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);

	// printf("\nremoved %c\n", ringbuffer_remove(rbuffer));
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);

	// ringbuffer_insert(rbuffer, 'a');
	// printf("\ninserted %c\n", 'a');
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);
	
	// ringbuffer_insert(rbuffer, 'l');
	// printf("\ninserted %c\n", 'l');
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);
	
	// printf("\nelement at tail is %c\n", ringbuffer_peek(rbuffer));
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);

	// if (ringbuffer_sfinsert(rbuffer, 'o'))
	// 	printf("\ninserted %c\n", 'o');
	// else 
	// 	printf("\ndid not insert... buffer is full\n");
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);

	// printf("\nelement at tail is %c\n", ringbuffer_peek(rbuffer));
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);

	// if (ringbuffer_sfinsert(rbuffer, 's'))
	// 	printf("\ninserted %c\n", 's');
	// else 
	// 	printf("\ndid not insert... buffer is full\n");
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);

	// printf("\nremoved %c\n", ringbuffer_remove(rbuffer));
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);

	// if (ringbuffer_sfinsert(rbuffer, 's'))
	// 	printf("\ninserted %c\n", 's');
	// else 
	// 	printf("\ndid not insert... buffer is full\n");
	// ringbuffer_print(rbuffer);
	// printf("tail=%d\n", rbuffer->tail);
	// printf("head=%d\n", rbuffer->head);

	// delete_ringbuffer(rbuffer);

	return 0;
}