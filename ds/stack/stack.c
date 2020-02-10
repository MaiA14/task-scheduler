/**
 * @author Mai Aloni 
 * @version 07-08-2019
 * The file contains functions of stack, such as create stack, push, pop, etc
 *
 * compile: gd -I include/  tests/test_stack.c stack.c
 */

#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include <assert.h>/*assert*/

#include "stack.h" 

enum {SUCCESS ,FAILURE};


struct stack
{
	void *base;
	void *current;
	void *end;
	size_t size_of_element;
};


stack_t *StackCreate(size_t max_capacity, size_t size_of_element)
{
	size_t stack_length_bytes = max_capacity * size_of_element;

	stack_t *stack = malloc(sizeof(stack_t));
	if (NULL == stack)
	{
		return NULL;
	}
	
	stack->base = malloc(stack_length_bytes);
	if (NULL == stack->base)
	{
		free(stack);
		return NULL;	
	}

	stack->current = stack->base;
	stack->end = (char*)stack + stack_length_bytes;
	stack->size_of_element = size_of_element;

	return stack;
}


void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);

	free(stack->base);
	free(stack); 	
}



int StackPush(stack_t *stack, void *data)
{
	assert(NULL != data);

	if (stack->current == stack->end)
	{
		return FAILURE;
	}

	memcpy(stack->current, data, stack->size_of_element);
	stack->current = (char*)stack->current + stack->size_of_element; 
 
	return SUCCESS;	
}


int StackPop(stack_t *stack)
{
	assert(NULL != stack);
	
	if (StackIsEmpty(stack))
	{
		return FAILURE;
	}

	stack->current =(char*)stack-> current - stack->size_of_element;
	
	return SUCCESS;	 	
}


void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);

	if (!StackIsEmpty(stack))
	{
		return ((char*)stack->current - stack->size_of_element);	 
	}
	
	return NULL;	
}


size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);

	return (((((size_t)(stack->current) - (size_t)stack->base)))
			/stack->size_of_element);
}


int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);

	if (stack->current == stack->base)
	{
		 return  FAILURE;
	}
  
	return SUCCESS;
}

