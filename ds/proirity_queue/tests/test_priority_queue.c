
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#include "priority_queue.h" /*pq_t*/

#define UNUSED(x) ((void)x)


static int IntCmp(void *first_num, void *second_num, void *param);
static int IsMatch(const void *queue_element_data, const void* user_data_to_erase);

void CheckFunctionalityOfPriorityQueue();

int main()
{
	CheckFunctionalityOfPriorityQueue();
	
	return 0;
}


void CheckFunctionalityOfPriorityQueue()
{
	int num1 = 2;
	int num2 = 4;
	int num3 = 6;
	
	/*check create*/
	pq_t *pq = PriorityQCreate(IntCmp, NULL);
	
	printf("\nCheck functionality of priority queue:\n");
	/*check IsEmpty*/
	if (PriorityQIsEmpty(pq))
	{
		printf("\033[1;32m- IsEmpty works as expected\033[0m\n");
	}
	else
	{
		printf("\033[1;31m- Problem in IsEmpty functionality\033[0m\n");
	}
	/*check size*/
	if (0 == PriorityQSize(pq))
	{
		printf("\033[1;32m- Size works as expected\033[0m\n");
	}
	else
	{
		printf("\033[1;31m- Problem in functionality of size\033[0m\n");
	}
	/*check PriorityQEnqueue*/
	PriorityQEnqueue(pq,&num3);
	PriorityQEnqueue(pq,&num1);
	PriorityQEnqueue(pq,&num2);
	/*check size*/
	if (3 == PriorityQSize(pq))
	{
		printf("\033[1;32m- Size works as expected\033[0m\n");
	}
	else
	{
		printf("\033[1;31m- Problem in functionality of size\033[0m\n");
	}
	/*check PriorityQDequeue*/ 
	PriorityQDequeue(pq);
	/*check PriorityQPeek*/
	if (&num2 == PriorityQPeek(pq))
	{
		printf("\033[1;32m- PriorityQPeek works as expected\033[0m\n");
	}
	else
	{
		printf("\033[1;31m- Problem in functionality of PriorityQPeek\033[0m\n");
	}
	/*check PriorityQErase*/
	PriorityQErase(pq, &num2, IsMatch);
	if (1 == PriorityQSize(pq))
	{
		printf("\033[1;32m- PriorityQErase works as expected\033[0m\n");
	}
	else
	{
		printf("\033[1;31m- Problem in functionality of PriorityQErase\033[0m\n");
	}

	/*check PriorityQClear*/ 	
	PriorityQClear(pq);
	if (0 == PriorityQSize(pq))
	{
		printf("\033[1;32m- PriorityQClear works as expected\033[0m\n");
	}
	else
	{
		printf("\033[1;31m- Problem in PriorityQClear of size\033[0m\n");
	}

	/*check destory*/
	PriorityQDestroy(pq);
}

static int IntCmp(void *first_num, void *second_num, void *param)
{
	UNUSED(param);
	
	if (*(int*)first_num == *(int*)second_num)
	{
		return 0;
	}
	
	return (*(int*)first_num - *(int*)second_num);
}


static int IsMatch(const void *queue_element_data, const void* user_data_to_erase)
{
	if (*(int*)queue_element_data == *(int*)user_data_to_erase)
	{
		return 1;
	}
	
	return 0;
}










