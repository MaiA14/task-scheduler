#include <stdio.h>
#include "stack.h"

enum {SUCCESS ,FAILURE};


void FlowCreateStackIsEmptyDestroy();
void FlowCreateStackPopPeek();
void FlowCreatePushCalcStackSize();

int main()
{
	FlowCreateStackIsEmptyDestroy();
	FlowCreateStackPopPeek();
	FlowCreatePushCalcStackSize();
	
	return 0;
}

void FlowCreateStackIsEmptyDestroy()
{
	stack_t *returned_stack;
	size_t max_capacity[] = {0,10,5000};
	size_t size_of_element[]= {sizeof(size_t),sizeof(char),sizeof(double)};
	size_t num_of_tests = sizeof(max_capacity)/sizeof(max_capacity[0]);
	size_t i = 0;
	
	printf("\nCreate stack, then check if it is empty and free the memory:\n");

	for (i = 0; i < num_of_tests; ++i)
	{
		returned_stack = StackCreate(max_capacity[i],size_of_element[i]);
		if(returned_stack != NULL)
		{
			printf("\033[1;32mTest is Succeded\033[0m\n");
		}

		else
		{
			printf("\033[1;32mUnable to allocate memory\033[0m\n");
		}
		StackDestroy(returned_stack);
	}
	
}

void FlowCreateStackPopPeek()
{
	stack_t *returned_stack;
	size_t max_capacity[] = {0,10,5000};
	size_t size_of_element[]= {sizeof(size_t),sizeof(char),sizeof(double)};
	size_t num_of_tests = sizeof(max_capacity)/sizeof(max_capacity[0]);
	size_t i = 0;
	char string[] = "mai";
	
	printf("\nCreate stack, then push element, peek and free the memory:\n");

	for (i = 0; i < num_of_tests; ++i)
	{
		returned_stack = StackCreate(max_capacity[i],size_of_element[i]);
		if (StackPush(returned_stack, string))
		{
			printf("\033[1;32mTest is Succeded\033[0m\n");
		}

		else
		{
			printf("\033[1;32mStack is empty\033[0m\n");
		}

		StackPeek(returned_stack);
		StackDestroy(returned_stack);		
	}
	

}


void FlowCreatePushCalcStackSize()
{
	stack_t *returned_stack;
	size_t max_capacity = 10;
	size_t size_of_element= sizeof(size_t);
	int a = 3;
	
	printf("\nCreate stack, then push 1 element, calculate stack size and free the memory:\n");

	returned_stack = StackCreate(max_capacity,size_of_element);
	StackIsEmpty(returned_stack);
	StackPush(returned_stack,&a);
	if (StackIsEmpty(returned_stack))
	{
		printf("\033[1;32mTest is Succeded\033[0m\n");
	}
	else
	{
		printf("\033[1;32mStack is empty\033[0m\n");
	}

	StackDestroy(returned_stack);

}
	




