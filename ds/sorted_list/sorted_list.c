/******************************************************************************
 * @Author Mai Aloni 
 * @Version 21-08-2019
 * Reviewer: Daniel Soifer
 * Title: Sorted list	
 * Description: This file contains functions of sorted doubly linked list, 
   such as: create linked list, insert new node, remove node, etc.
 *
 * compile: gd -I include/ -I ../sorted_list/include/ tests/test_sorted_list.c sorted_list.c ../doubly_linked_list/doubly_linked_list.c
*******************************************************************************/

#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "sorted_list.h" /*sorted_list_iter_t sorted_list_t*/


struct sorted_list
{
	dlist_t *dlist;
	is_before_t is_before;
	void *param;
};


sorted_list_t *SortedListCreate(is_before_t is_before, void *param)
{
	sorted_list_t *sorted_list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	if (NULL == sorted_list)
	{
		return NULL;
	}
	
	sorted_list->dlist = DlistCreate();
	if ( NULL == sorted_list->dlist)
	{
		free(sorted_list); sorted_list->dlist = NULL;
		
		return NULL;
	}
	
	sorted_list->is_before = is_before;
	sorted_list->param = param;
	
	return sorted_list;
}


void SortedListDestroy(sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	
	DlistDestroy(sorted_list->dlist);
	sorted_list->dlist = NULL;
	sorted_list->is_before = NULL;
	sorted_list->param = NULL;
	
	free(sorted_list); sorted_list = NULL;
}


sorted_list_iter_t SortedListBegin(sorted_list_t *sorted_list)
{
	sorted_list_iter_t begin_iter = {NULL};
	
	assert(NULL != sorted_list);
	
	begin_iter.dlist_iter = DlistBegin(sorted_list->dlist);
	
	return begin_iter;
}


sorted_list_iter_t SortedListEnd(sorted_list_t *sorted_list)
{
	sorted_list_iter_t end_iter = {NULL};
	
	assert(NULL != sorted_list);	
	
	end_iter.dlist_iter = DlistEnd(sorted_list->dlist);
	
	return end_iter;
}


sorted_list_iter_t SortedListIterNext(sorted_list_iter_t current)
{
	sorted_list_iter_t current_next =  {NULL};
	current_next.dlist_iter = DlistIterNext(current.dlist_iter);
	
	return current_next;
}


sorted_list_iter_t SortedListIterPrev(sorted_list_iter_t current)
{
	sorted_list_iter_t current_prev =  {NULL};
	current_prev.dlist_iter = DlistIterPrev(current.dlist_iter);
	
	return current_prev;
}


void *SortedListGetData(sorted_list_iter_t element)
{
	return DlistGetData(element.dlist_iter);
}


int SortedListIsSameIter(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{		
	return DlistIsSameIter(iter1.dlist_iter,iter2.dlist_iter);
}


sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
	sorted_list_iter_t inserted_element = {NULL};
	sorted_list_iter_t current = {NULL};

	assert(NULL != sorted_list);

	for (current = SortedListBegin(sorted_list);
		  !SortedListIsSameIter(current, SortedListEnd(sorted_list)) &&
		 !sorted_list->is_before(SortedListGetData(current), 
								 data, sorted_list->param);
		 current = SortedListIterNext(current))
	{}	 
	
	inserted_element.dlist_iter = DlistInsert(sorted_list->dlist, 
										   	  current.dlist_iter, data);

	return inserted_element;
} 


sorted_list_iter_t SortedListRemove(sorted_list_iter_t current)
{
	sorted_list_iter_t next_element_to_remove = {NULL};
	next_element_to_remove.dlist_iter = DlistRemove(current.dlist_iter);
	
	return  next_element_to_remove;
}


void* SortedListPopFront(sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	
	return DlistPopFront(sorted_list->dlist);
}


void* SortedListPopBack(sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	
	return DlistPopBack(sorted_list->dlist);
}


size_t SortedListSize(const sorted_list_t *sorted_list)
{	
	assert(NULL != sorted_list);
		
	return DlistSize(sorted_list->dlist);	
}


int SortedListIsEmpty(const sorted_list_t *sorted_list)
{	
	assert(NULL != sorted_list);
	
	return DlistIsEmpty(sorted_list->dlist);
}



sorted_list_iter_t SortedListFind(const sorted_list_t *sorted_list,
								  sorted_list_iter_t from,
								  sorted_list_iter_t to,
								  const void *data)								  
{
	sorted_list_iter_t current_element = {NULL};
	
	assert(NULL != sorted_list);
	
	/*the are two cases where the element can be find before*/
	for (current_element = from;
		 ((!SortedListIsSameIter(current_element, to))); 
		 current_element = SortedListIterNext(current_element))
	{	
	
		if (sorted_list->is_before(SortedListGetData(current_element),
			data,sorted_list->param) 
									  == 
			((sorted_list->is_before(data,
			SortedListGetData(current_element),sorted_list->param))))
		{
			return current_element;
		}	
	}
	
	return SortedListEnd((sorted_list_t*)sorted_list);	 
}


sorted_list_iter_t SortedListFindIf(const sorted_list_t *list,
									sorted_list_iter_t from,
					   				sorted_list_iter_t to,
									match_func_t match_func,
									const void *data)
{
	sorted_list_iter_t element_to_find = {NULL};
	
	assert(NULL != list);
	assert(NULL != match_func);

	element_to_find.dlist_iter = DlistFind(list->dlist, from.dlist_iter,
										   to.dlist_iter, match_func ,data);
	
	return element_to_find;
}


int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to,
					  action_func_t action_func,void *param_for_action_func)
{
	assert(NULL != action_func);

	return DlistForEach(from.dlist_iter, to.dlist_iter, 
						action_func, param_for_action_func);
}


void SortedListMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
	sorted_list_iter_t dest_iter = {NULL};
	sorted_list_iter_t src_iter = {NULL};
	sorted_list_iter_t dest_list_end =  SortedListEnd(dest_list);
	dest_iter = SortedListBegin(dest_list);
	
	 while ((NULL != src_list) &&
	        (NULL != dest_list) &&
	 	    (!SortedListIsSameIter(dest_iter,dest_list_end)) &&
	 	   	(!SortedListIsEmpty(src_list)))
	 {
	 	src_iter = SortedListBegin(src_list);
	 
	 	if (dest_list->is_before(SortedListGetData(dest_iter),
								 SortedListGetData(src_iter), NULL))
		{
			DlistSplice(dest_iter.dlist_iter, src_iter.dlist_iter,
						DlistIterNext(src_iter.dlist_iter));
		}
		
		else
		{
			dest_iter = SortedListIterNext(dest_iter);
		}							 
	 }
	 
	if (!SortedListIsEmpty(src_list))
	{
		DlistSplice(SortedListEnd(dest_list).dlist_iter,
					src_iter.dlist_iter,
					SortedListEnd(src_list).dlist_iter);
	}
}

