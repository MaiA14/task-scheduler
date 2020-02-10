/******************************************************************************
 * @Author Mai Aloni 
 * @Version 23-08-2019
 * Reviewer: Hay Hoffman
 * Title: Priority queue	
 * Description: This file contains functions of prioirity queue, 
   such as: create priority queue, destroy prioirity queue, peek, etc.
 *
 * compile: gd -I include/ -I ../priority_queue/include/ tests/test_priority_queue.c priority_queue.c -I include/ -I ../sorted_list/include/ ../sorted_list/sorted_list.c ../doubly_linked_list/doubly_linked_list.c 
 ******************************************************************************/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc,free*/

#include "sorted_list.h" /*declartions of sorted list functions*/
#include "priority_queue.h"/*declartions of sorted  priority queue functions*/


typedef struct params_for_pq
{
	cmp_func_t cmp_func;
	void *param_for_cmp;
} params_for_pq_t;

struct pq
{
	sorted_list_t *sorted_list;
	params_for_pq_t *params_for_pq;
};


/*static functions declartions*/
static int IsBefore(const void *queue_element_data, const void *user_data,
					void *param);


pq_t *PriorityQCreate(cmp_func_t cmp_func, void *param_for_cmp)
{
	pq_t *pq = NULL;
	
	assert(NULL != cmp_func);
	
	pq = (pq_t *)malloc(sizeof(pq_t));
	if (NULL == pq) 
	{	
		return NULL;
	}
	
	pq->params_for_pq = (params_for_pq_t*)malloc(sizeof(params_for_pq_t));
	if (NULL == pq->params_for_pq)
	{
		free(pq); 
		pq = NULL;
		return NULL;
	}
	
	pq->params_for_pq->cmp_func = cmp_func;
	pq->params_for_pq->param_for_cmp = param_for_cmp;
	
	pq->sorted_list = SortedListCreate(IsBefore, pq->params_for_pq);
	if (NULL == pq->sorted_list)
	{
		free(pq); 
		pq = NULL;
		free(pq->params_for_pq);
		pq->params_for_pq = NULL;
		return NULL;
	}

	return pq;
}


static int IsBefore(const void *pq_element_data, const void *user_data,
					void *param)
{
	cmp_func_t cmp_func = NULL;
	void *param_for_cmp = NULL;

	assert(NULL != param);
	cmp_func = ((params_for_pq_t*)param)->cmp_func;
	param_for_cmp = ((params_for_pq_t*)param)->param_for_cmp;

	assert(NULL != cmp_func);
	/*in case the result of cmp is smaller or equal to zero, 
	total result is before*/
	if(0 <= cmp_func ((void*)pq_element_data, (void*)user_data, param_for_cmp))
	{
		return 1;
	}
	/*data is bigger than previous data*/
	return 0;
}					


void PriorityQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	assert(NULL != pq->sorted_list);
	assert(pq->params_for_pq);
	

	SortedListDestroy(pq->sorted_list);
	pq->sorted_list = NULL;

	pq->params_for_pq->cmp_func = NULL;
	pq->params_for_pq->param_for_cmp = NULL;
	free(pq->params_for_pq);
	free(pq); pq = NULL;
}


size_t PriorityQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SortedListSize(pq->sorted_list);
}


int PriorityQIsEmpty(const pq_t *pq)
{
	assert(NULL !=pq);
	
	return SortedListIsEmpty(pq->sorted_list);
}


int PriorityQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);
	
	if (SortedListIsSameIter(SortedListInsert(pq->sorted_list,data),
							 SortedListEnd(pq->sorted_list)))
	{
		return 0;
	}
	
	return 1;
}


void PriorityQDequeue(pq_t *pq)
{
	assert(PriorityQIsEmpty);
	assert(NULL != pq);
	
	SortedListPopFront(pq->sorted_list);
}


void* PriorityQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SortedListGetData(SortedListBegin(pq->sorted_list));
}


void PriorityQClear(pq_t *pq)
{
	sorted_list_iter_t element_to_remove = {NULL};
	sorted_list_iter_t list_end = {NULL};
	
	assert (NULL != pq);

	element_to_remove = SortedListBegin(pq->sorted_list);
	list_end = SortedListEnd(pq->sorted_list);

	while (!SortedListIsSameIter(element_to_remove,list_end))
	{
		element_to_remove = SortedListRemove(element_to_remove);
	}
}


void* PriorityQErase(pq_t *pq, 
					void *data_to_erase,
					is_match_t is_match)
{	
	sorted_list_iter_t current = {NULL};
	sorted_list_iter_t list_end = {NULL};
	void *returned_data = NULL;
	
	assert(NULL != pq);
	assert(NULL != is_match);	
		
	current = SortedListBegin(pq->sorted_list);	
	list_end = SortedListEnd(pq->sorted_list);

	while(!SortedListIsSameIter(current, list_end))
	{
		returned_data = SortedListGetData(current);
		if (0 == is_match(returned_data, 
			data_to_erase)) 
		{
			SortedListRemove(current);
			return returned_data;
		}
		
		current = SortedListIterNext(current);	
	}
	
	return NULL;
}
			  

