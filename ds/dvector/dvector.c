/**
 * @author Mai Aloni 
 * @version 08-08-2019
 *	The file contains functions of dynamic vector, such as create a dynamic vector push back, pop back, etc.
 * compile: gd -I include/  tests/test_d_vector.c dvector.c
 */

#include <stdlib.h> /*malloc, realloc, free*/
#include <string.h> /*memcpy*/
#include <assert.h>/*assert*/

#include "d_vector.h" /*declarations of vector functions*/

#define DECREASE_FACTOR (4)
#define INCREASE_FACTOR (2)


enum code_statuses 
{
	CANT_POP_EMPTY_VECTOR = -3,
	UNABLE_ALLOCATE_MEMORY = -1,
	SUCCESS = 0,
	VECTOR_IS_EMPTY = 1,
	CAPACITY_SMALLER_THAN_USED_SIZE = 2
}; 


struct d_vector
{
	void *start;
	void *end;
	void *current;
	size_t size_of_element;
};


d_vector_t *DVectorCreate(const size_t size_of_element, const size_t capacity)
{	
	d_vector_t *vector = malloc(sizeof(struct d_vector));

	if (NULL != vector)
	{
		vector->start = malloc (capacity * size_of_element); 

		if (NULL != vector-> start)
		{
			vector->current = vector->start; 
			vector->end = (char*)(vector->start) + 
				(capacity * size_of_element);
	 		vector->size_of_element = size_of_element;
		}
	
		else
		{
			free(vector);
			vector = NULL;			
		}
	}

 	return vector;
}


void DVectorDestroy(d_vector_t *d_vector)
{
	assert (NULL != d_vector);

	free(d_vector->start);
	free(d_vector); 	
}


int DVectorPushBack(d_vector_t *d_vector, const void *data)
{
	void* start_ptr = NULL;
	size_t capacity = DVectorCapacity(d_vector);
	
	assert (NULL != d_vector);
	assert (NULL != data);
	
	if (DVectorSize(d_vector) == capacity)
	{
		start_ptr = realloc (d_vector->start, (capacity * 
			INCREASE_FACTOR *  d_vector->size_of_element));
	
		if (NULL == start_ptr)
		{
			return UNABLE_ALLOCATE_MEMORY;
		}
		
		d_vector->start = start_ptr;
		d_vector->current = (char*)d_vector->start + 
			capacity * (d_vector->size_of_element);

		start_ptr = NULL;
		d_vector->end = (char*)(d_vector->start) + (capacity * 
			INCREASE_FACTOR * d_vector->size_of_element);
	}

	memcpy(d_vector->current, data, d_vector->size_of_element);
	d_vector->current = (char*)(d_vector->current)
								 + d_vector->size_of_element;
	
	return SUCCESS;	
}


int DVectorPopBack(d_vector_t *d_vector)
{
	void *start_ptr = NULL;
	size_t capacity = 0;	
	size_t curr_size = 0;

	assert (NULL != d_vector);

	if (VECTOR_IS_EMPTY == (DVectorIsEmpty(d_vector)))
	{
		return CANT_POP_EMPTY_VECTOR;
	}

	d_vector->current = (char*)d_vector->current - d_vector->size_of_element;	
	
	capacity = DVectorCapacity(d_vector);
	curr_size = (DVectorSize(d_vector));

	if (capacity >= (DVectorSize(d_vector) *  DECREASE_FACTOR))
	{

		start_ptr = realloc (d_vector->start, (d_vector->size_of_element) *
						 capacity / DECREASE_FACTOR);
		d_vector->current = (char*)d_vector->start + 
			capacity * (d_vector->size_of_element);

		if (NULL == start_ptr) /*in case realloc failed*/
		{
			return UNABLE_ALLOCATE_MEMORY;
		}

		d_vector->start = start_ptr; /*realloc succeded. point to the current start of the vector*/
		start_ptr = NULL; 
		d_vector->end = (char*)(d_vector->start) + 
				((d_vector->size_of_element * capacity) / DECREASE_FACTOR);
		d_vector->current = (char*)d_vector->start +
			 					(curr_size * d_vector->size_of_element);
	}

	return SUCCESS;		 	
}


size_t DVectorSize(const d_vector_t *d_vector)
{
	assert (NULL != d_vector);

	return (((char*)(d_vector->current) - 
			(char*)d_vector->start)/d_vector->size_of_element);
}


int DVectorIsEmpty(const d_vector_t *d_vector)
{
	assert (NULL != d_vector);

	return (d_vector->current == d_vector->start);
}	


void *DVectorGetItemAddress(const d_vector_t *d_vector, size_t index)
{	
	assert (NULL != d_vector);
	
	if (DVectorSize(d_vector) <= index)
	{
		return NULL;
	}
	
	return ((char*)(d_vector->start) + 
			(index * (d_vector->size_of_element)));	
}


size_t DVectorCapacity(const d_vector_t *d_vector)
{
	assert (NULL != d_vector);

	return (size_t)(((char *)d_vector->end - 
		(char *)d_vector->start)/ d_vector->size_of_element);
}


int DVectorReserve(d_vector_t *d_vector, size_t number_of_elements)
{
	void *start_ptr = NULL;
	size_t new_capacity = (number_of_elements * d_vector->size_of_element);
	
	if ((DVectorSize(d_vector)) > number_of_elements)
	{
		return CAPACITY_SMALLER_THAN_USED_SIZE;
	}	

	start_ptr = realloc (d_vector->start, new_capacity);
	d_vector->current = (char*)d_vector->start + 
				new_capacity * (d_vector->size_of_element);

	if (NULL == start_ptr)
	{
		return UNABLE_ALLOCATE_MEMORY;
	}
	
	d_vector->start = start_ptr;
	start_ptr = NULL;
	d_vector->end = (char*)(d_vector->start) + new_capacity;

	return SUCCESS;
}	








