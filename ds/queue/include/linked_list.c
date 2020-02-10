/**
 * @Author Mai Aloni 
 * @Version 16-08-2019
 * Reviewer: Dor Tambour
 *	
 * This file contains functions of linked list, such as: create linked list,
 * insert new node, remove node, etc.
 *
 * compile: gd -I include/  tests/test_linked_list.c linked_list.c
 */

#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "linked_list.h" /*declarations of linked list functions*/

enum code_status
{
	SUCCSSES,
	FAILURE
};

static void SwapNodesData(void **ptr1, void **ptr2);
static void InitSlistNode(slist_node_t *slist_node, void *data, 
		       			  slist_node_t *next_node);

slist_node_t *SlistCreateNode(void *data, slist_node_t *next_node)
{
	slist_node_t *new_node = NULL;
	
	new_node = (slist_node_t*)malloc(sizeof(slist_node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
		
	InitSlistNode(new_node, data, next_node);
		  
	return new_node;
}

static void InitSlistNode(slist_node_t *slist_node, void *data, 
		       			  slist_node_t *next_node)
{
	slist_node->data = data;
	slist_node->next_node = next_node;
}


static void SwapNodesData(void **first_node_data, void **second_node_data)
{
	void *old_data = *first_node_data;
	*first_node_data = *second_node_data;
	*second_node_data = old_data;
}

slist_node_t *SlistInsertNode(slist_node_t *current_node,
							  slist_node_t *new_node)
{
	assert (NULL != current_node);
	assert (NULL != new_node);

	SwapNodesData(&current_node->data,&new_node->data);

	new_node->next_node = current_node->next_node; 
	current_node->next_node = new_node;
	
	return current_node;
}

slist_node_t *SlistInsertAfterNode(slist_node_t *current_node,
								   slist_node_t *new_node)
{
	assert (NULL != current_node);
	assert (NULL != new_node);
	
	new_node->next_node = current_node->next_node;
	current_node->next_node = new_node;
	
	return new_node;
}

void SlistFreeAll(slist_node_t *head)
{
	slist_node_t *current_ptr = head;
	slist_node_t *next_ptr = NULL;
	
	while (NULL != current_ptr) 
	{
		next_ptr = current_ptr->next_node;
		free(current_ptr);
		current_ptr = next_ptr;
	}
}

slist_node_t *SlistRemove(slist_node_t *current_node)
{
	slist_node_t *node_to_be_removed = current_node->next_node;
		
	assert (NULL !=current_node);
	
	SwapNodesData((&node_to_be_removed->data),(&current_node->data));
	current_node->next_node = node_to_be_removed->next_node;
	node_to_be_removed->next_node = NULL;
	
	return node_to_be_removed;
}

slist_node_t *SlistRemoveAfter(slist_node_t *current_node)
{
	slist_node_t *node_to_be_removed = NULL;
	
	assert (NULL != current_node->next_node);

	node_to_be_removed = current_node->next_node;
	current_node->next_node = node_to_be_removed->next_node;
	node_to_be_removed->next_node = NULL;
	
	return node_to_be_removed;
}

size_t SlistCount(const slist_node_t *head)
{
	size_t count_nodes_in_list = 0;

	while (NULL != head)
	{
		count_nodes_in_list++; 
		head = head->next_node;
	}
	
	return count_nodes_in_list;
}

slist_node_t *SlistFind(const slist_node_t *head, const void *data, 
						match_func_t match_func)
{
	slist_node_t *head_next_ptr = NULL;
	
	assert (NULL != match_func);
	
	head_next_ptr = (slist_node_t*)head;
	
	while ((head_next_ptr != NULL) &&
			 (0 != (match_func(head_next_ptr->data, data))))
	{
		head_next_ptr = head_next_ptr->next_node;
	}

	return head_next_ptr;
}

int SlistForEach(slist_node_t *head, action_func_t action_func, 
				 void *param_for_action_func)
{
	int action_func_result = 0;
	
	assert (NULL != action_func);
	
	while (NULL != head)
	{
		action_func_result = action_func(head->data, param_for_action_func);
		
		if (0 != action_func_result)
		{
			break;
		}
		
		head = head->next_node;
	}

	return action_func_result;
}

slist_node_t *SlistFlip(slist_node_t *head)
{
	slist_node_t *previous = NULL;
	slist_node_t *next = NULL;

	while (NULL != head)
	{
		next = head->next_node;
		head->next_node = previous; 
		previous = head;
		head = next; 
	}
	
	return previous;
}

int SlistHasLoops(const slist_node_t *head)
{
	slist_node_t *move_one_node_after = NULL;
	slist_node_t *moves_two_node_after = NULL;

	assert (NULL != head);

	move_one_node_after = (slist_node_t*)head;
	moves_two_node_after = head->next_node;

	while ((moves_two_node_after != move_one_node_after) && 
			(NULL != moves_two_node_after->next_node) &&
			 (NULL != move_one_node_after))
	{
		move_one_node_after = move_one_node_after->next_node; 
		moves_two_node_after = moves_two_node_after->next_node->next_node; 
	}	
			
	return (move_one_node_after == moves_two_node_after);
}

slist_node_t *SlistFindIntersection(const slist_node_t *head1,
									const slist_node_t *head2)
{
	size_t list1_length = 0;
	size_t list2_length = 0;
	size_t diff_between_lists_lengths = 0;
	size_t i = 0;
	const slist_node_t *head1_ptr_next = head1;
	const slist_node_t *head2_ptr_next = head2;

	assert (NULL != head1);
	assert (NULL != head2);

	list1_length = SlistCount(head1);
	list2_length = SlistCount(head2);

	if (list1_length > list2_length)
	{
		 diff_between_lists_lengths = list1_length - list2_length;
		
		while (i <  diff_between_lists_lengths)
		{
			head1_ptr_next = head1_ptr_next->next_node;
			i++;
		}
	}

	else
	{
		 diff_between_lists_lengths = list2_length - list1_length;
		
		while (i <  diff_between_lists_lengths)
		{
			head2_ptr_next = head2_ptr_next->next_node;
			i++;
		}
	}

	while ((head1_ptr_next != head2_ptr_next) && (NULL != head1) && 
			(NULL != head2))
	{
		head1_ptr_next = head1_ptr_next->next_node;
		head2_ptr_next = head2_ptr_next->next_node;
	}
	
	if ((NULL == head1) || (NULL == head2))
	{
		return NULL;
	}
	
	return (slist_node_t*)head1_ptr_next;
}
