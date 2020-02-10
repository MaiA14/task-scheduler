#include <stdio.h>
#include "queue.h"


void TestCreateQueueCheckSizeEnqueuePeekDestory();
void TestCreateQueueAppend();
 
int main()
{
	
	TestCreateQueueCheckSizeEnqueuePeekDestory();
	TestCreateQueueAppend();
	
	return 0;
}

void TestCreateQueueCheckSizeEnqueuePeekDestory()
{
	
	size_t i = 0;	
	size_t enqueue_tests[] = {2,4,6,8,10};
	size_t num_of_enqueue_tests = sizeof(enqueue_tests)/enqueue_tests[0];
	
	queue_t *queue_test = QueueCreate();
	
	printf("\nCreate a queue, check if it empty, check size, enqueue, dequeue, peek and destory queue: \n");
	
	if (1 != QueueIsEmpty(queue_test))
	{
		printf("\033[1;32m- Problem in IsEmpty functionality\033[0m\n");
	}
	else
	{
		printf("\033[1;32m- IsEmpty works as expected\033[0m\n");
	}
	
	for (i = 0; i < num_of_enqueue_tests; i++)
	{
		QueueEnqueue(queue_test,&enqueue_tests[i]);
	} 
	
	if (num_of_enqueue_tests != QueueSize(queue_test))
	{
		printf("\033[1;32m- Problem in functionality of size\n");
	}
	
	else
	{
		printf("\033[1;32m- Size function works\033[0m\n");
	}
	
	if (2 != (*(size_t*)QueuePeek(queue_test)))
	{
		printf("\033[1;32m- Problem in peek functionality\n");
	}
	
	else
	{
		printf("\033[1;32m- Peek works\033[0m\n");
	}
	
	QueueDequeue(queue_test);
	
	if (4 != (*(size_t*)QueuePeek(queue_test)))
	{
		printf("\033[1;32m- Problem in peek functionality\n");
	}
	
	else
	{
		printf("\033[1;32m- Peek works\033[0m\n\n");
	}
	
	QueueDestroy(queue_test);
	
}


void TestCreateQueueAppend()
{
	size_t i = 0; 
	size_t src_tests[] = {2,4,6,8};
	size_t dest_tests[] = {10,12,14,16};
	size_t num_of_tests = sizeof(src_tests)/sizeof(src_tests[0]);
	
	queue_t *dest_queue = QueueCreate();
	queue_t *src_queue = QueueCreate();
	
	printf("Create a queue, check enqueue, append and peek: \n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if (0 != QueueEnqueue(src_queue, &src_tests[i]))
		{
			printf("\033[1;32m- Problem in enqueue\n");
		}	
		
		else
		{
			printf("\033[1;32m- equeue works\033[0m\n");
		}
	}
	
	for (i = 0; i < num_of_tests; i++)
	{
		if (0 != QueueEnqueue(dest_queue, &dest_tests[i]))
		{
			printf("\033[1;32m- Problem in enqueue\n");
		}	
		
		else
		{
			printf("\033[1;32m- equeue works\033[0m\n");
		}
	}
	
	QueueAppend(dest_queue, src_queue);
	
	if (8 != (QueueSize(dest_queue)))
	{
		printf("\033[1;32m- Problem in size functionality\n");
	}
	
	else
	{
		printf("\033[1;32m- Size function works\033[0m\n");
	}
	
	if (10 != (*(size_t*)QueuePeek(dest_queue)))
	{
		printf("\033[1;32m- Problem in peek functionality\n");
	}
	
	else
	{
		printf("\033[1;32m- Peek works\033[0m\n");
	}
	
	QueueDestroy(dest_queue);
	QueueDestroy(src_queue);	
}



