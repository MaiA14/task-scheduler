/******************************************************************************
 * @Author Mai Aloni 
 * @Version 20-08-2019
 * Reviewer: Alex Burstein
 * Title: Doubly linked list	
 * Description: This file contains functions of linked list, such as: 
   create linked list, insert new node, remove node, etc.
 *
 * compile: gd -I include/  tests/test_doubly_linked_list.c doubly_linked_list.c
*******************************************************************************/

#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "doubly_linked_list.h" /*dlist_node_t*/

#define UNUSED(X) (void)X
#define DUMMY_ADDRESS (void *)0xDEADBEEF

/*static functions*/
static void InitDlist(dlist_node_t *dlist_node, void *data, 
					  dlist_node_t *prev_node, dlist_node_t *next_node);
static dlist_iter_t DlistCreateNode(void *data, dlist_iter_t next_node, 
									dlist_iter_t prev_node);
static void DlistFreeAllNodes(dlist_iter_t node);
static int DlistAddOneToCounter(void *data, void *param);					 


struct dlist_node
{
	void *data;
	dlist_node_t *next_node;
	dlist_node_t *prev_node;
};


struct dlist
{
	dlist_node_t *dummy_start;
	dlist_node_t *dummy_end;
};


static void InitDlist(dlist_node_t *dlist_node, void *data, 
					  dlist_node_t *prev_node, dlist_node_t *next_node)
{
	dlist_node->data = data;
	dlist_node->next_node = next_node;
	dlist_node->prev_node = prev_node;
}					  


static dlist_iter_t DlistCreateNode(void *data, dlist_iter_t next_node, 
							 dlist_iter_t prev_node)
{
	dlist_iter_t new_node = NULL;
	
	new_node = (dlist_node_t *)malloc(sizeof(dlist_node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	InitDlist(new_node, data, prev_node, next_node);
	
	return new_node;
}


dlist_t *DlistCreate(void)
{
	dlist_t *dlist = (dlist_t *)malloc(sizeof(dlist_t));
	if (NULL == dlist)
	{
		return NULL;
	}
	
	dlist->dummy_start = DlistCreateNode(DUMMY_ADDRESS,NULL,NULL);
	if (NULL == dlist->dummy_start)
	{
		free(dlist); 
		dlist = NULL;
		return NULL;
	}
	
	dlist->dummy_end = DlistCreateNode(DUMMY_ADDRESS, NULL,dlist->dummy_start);
	if (NULL == dlist->dummy_end)
	{
		free(dlist);
		dlist = NULL;
		free(dlist->dummy_start); 
		dlist->dummy_start = NULL;
		return NULL;
	}
	
	(dlist->dummy_start)->next_node = dlist->dummy_end;
	
	return dlist;
}


static void DlistFreeAllNodes(dlist_iter_t node)
{
	dlist_iter_t next_node = NULL;
	
	while (NULL != node)
	{
		next_node = DlistIterNext(node);
		free(node);
		node = next_node; next_node = NULL;	
	}
	
}


void DlistDestroy(dlist_t *dlist)
{
	assert (NULL != dlist);
	
	DlistFreeAllNodes(dlist->dummy_start); 
	dlist->dummy_start = NULL;
	dlist->dummy_end = NULL;
	free(dlist); dlist = NULL;
}


dlist_iter_t DlistIterNext(dlist_iter_t current)
{
	assert (NULL != current);	
	
	return (current->next_node);
}


dlist_iter_t DlistIterPrev(dlist_iter_t current)
{
	assert (NULL != current);
	
	return (current->prev_node);
}


dlist_iter_t DlistBegin(dlist_t *dlist)
{
	assert (NULL != dlist);

	return (dlist->dummy_start->next_node);
}


dlist_iter_t DlistEnd(dlist_t *dlist)
{
	assert (NULL != dlist);
	
	return (dlist->dummy_end);
}


void *DlistGetData(dlist_iter_t element)
{
	assert (NULL != element);
	
	return (element->data);
}


int DlistIsSameIter(dlist_iter_t iter1, dlist_iter_t iter2)
{
	return (iter1 == iter2);
}


dlist_iter_t DlistInsert(dlist_t *dlist, dlist_iter_t current, void *data)
{
	dlist_iter_t new_node = DlistCreateNode(data, current, 
											DlistIterPrev(current));
	if (NULL == new_node)
	{
		return DlistEnd(dlist);
	}
	
	(current->prev_node)->next_node = new_node;
	current->prev_node = new_node;
	
	return new_node;
}


dlist_iter_t DlistRemove(dlist_iter_t current)
{
	dlist_iter_t next = NULL;
	
	next = DlistIterNext(current);
	
	(current->prev_node)->next_node = DlistIterNext(current);
	next->prev_node = DlistIterPrev(current);

	current->next_node = NULL;
	current->prev_node = NULL;
	
	free(current); current = NULL;
	
	return next;
}


dlist_iter_t DlistPushFront(dlist_t *dlist, void *data)
{	
	assert(NULL != dlist);

	return DlistInsert(dlist, DlistBegin(dlist), data);
}


dlist_iter_t DlistPushBack(dlist_t *dlist, void *data)
{	
	assert(NULL != dlist);

	return DlistInsert(dlist, DlistEnd(dlist), data);
}


void* DlistPopFront(dlist_t *dlist)
{
	void *data = NULL;
	dlist_iter_t element = NULL;
	
	assert(NULL != dlist);
	
	element = DlistBegin(dlist);
	data = DlistGetData(element);
	DlistRemove(element); element = NULL;
	
	return data;
}


void* DlistPopBack(dlist_t *dlist)
{
	void *data = NULL;
	dlist_iter_t element = NULL;
	
	assert(NULL != dlist);
	
	element = DlistIterPrev(DlistEnd(dlist));
	data = DlistGetData(element);
		
	DlistRemove(element); element = NULL;
	
	return data;
}


static int DlistAddOneToCounter(void *data, void *param)
{
	size_t *ptr_to_count = (size_t*)param;
	UNUSED(data);
	
	++(*ptr_to_count);
	
	return 0;
}


int DlistForEach(dlist_iter_t from, dlist_iter_t to,
				 action_func_t action_func, void *param_for_action_func)
{
	int action_func_result = 0;
	
	while ((from != to) && (0 == action_func_result))
	{
		action_func_result = action_func(from->data,param_for_action_func);
		from = from->next_node;
	}
	
	return action_func_result;
}


size_t DlistSize(const dlist_t *dlist)
{
	size_t count_nodes_in_dlist = 0;
	
	DlistForEach(DlistBegin((dlist_t *)dlist),DlistEnd((dlist_t *)dlist),
	DlistAddOneToCounter,&count_nodes_in_dlist);
	
	return count_nodes_in_dlist;
}


int DlistIsEmpty(const dlist_t *dlist)
{
	return (dlist->dummy_start->next_node == dlist->dummy_end);
}


dlist_iter_t DlistFind(const dlist_t *dlist,
					   dlist_iter_t from, dlist_iter_t to, 
					   match_func_t match_func, const void *data)
{	
	dlist_iter_t current = NULL;

	assert (NULL != match_func);
	
	for (current = from; current != to; current = DlistIterNext(current))
	{
		if (0 == match_func(DlistGetData(current), data))
		{
			return current;
		}
	}
	
	return DlistEnd((dlist_t *)dlist);
}		


dlist_iter_t DlistSplice(dlist_iter_t dest, dlist_iter_t src_from, 
						 dlist_iter_t src_to)
{

	dlist_node_t *copy_of_src_to_prev = NULL;

	assert(NULL != dest);
	assert(NULL != src_from);
	assert(NULL != src_to);
	assert(NULL != dest->prev_node);
	assert(NULL != src_to->prev_node);
	assert(NULL != src_from->prev_node);

	copy_of_src_to_prev = src_to->prev_node;

	src_to->prev_node->next_node = dest;
	src_to->prev_node = src_from->prev_node;

	src_from->prev_node->next_node = src_to;
	src_from->prev_node = dest->prev_node;

	dest->prev_node->next_node = src_from;
	dest->prev_node = copy_of_src_to_prev;
	
	return (src_from);
}
