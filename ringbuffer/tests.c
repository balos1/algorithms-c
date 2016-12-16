#include <stdio.h>
#include <stdlib.h>
#include "ringbuffer.h"

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
	ringbuffer* rbuffer = new_ringbuffer(8);

	if (rbuffer == NULL)
	{
		printf("Could not allocate buffer.\n");
		return -1;
	}	

	ringbuffer_insert(rbuffer, 'C');
	printf("\ninserted %c\n", 'C');
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);
	

	ringbuffer_insert(rbuffer, 'o');
	printf("\ninserted %c\n", 'o');
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);

	ringbuffer_insert(rbuffer, 'd');
	printf("\ninserted %c\n", 'd');
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);

	ringbuffer_insert(rbuffer, 'y');
	printf("\ninserted %c\n", 'y');
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);

	ringbuffer_insert(rbuffer, '_');
	printf("\ninserted %c\n", '_');
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);
	
	ringbuffer_insert(rbuffer, 'B');
	printf("\ninserted %c\n", 'B');
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);

	printf("\nremoved %c\n", ringbuffer_remove(rbuffer));
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);

	printf("\nremoved %c\n", ringbuffer_remove(rbuffer));
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);

	ringbuffer_insert(rbuffer, 'a');
	printf("\ninserted %c\n", 'a');
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);
	
	ringbuffer_insert(rbuffer, 'l');
	printf("\ninserted %c\n", 'l');
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);
	
	printf("\nelement at tail is %c\n", ringbuffer_peek(rbuffer));
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);

	if (ringbuffer_sfinsert(rbuffer, 'o'))
		printf("\ninserted %c\n", 'o');
	else 
		printf("\ndid not insert... buffer is full\n");
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);

	printf("\nelement at tail is %c\n", ringbuffer_peek(rbuffer));
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);

	if (ringbuffer_sfinsert(rbuffer, 's'))
		printf("\ninserted %c\n", 's');
	else 
		printf("\ndid not insert... buffer is full\n");
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);

	printf("\nremoved %c\n", ringbuffer_remove(rbuffer));
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);

	if (ringbuffer_sfinsert(rbuffer, 's'))
		printf("\ninserted %c\n", 's');
	else 
		printf("\ndid not insert... buffer is full\n");
	ringbuffer_print(rbuffer);
	printf("tail=%d\n", rbuffer->tail);
	printf("head=%d\n", rbuffer->head);

	delete_ringbuffer(rbuffer);

	return 0;
}