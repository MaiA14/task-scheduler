/**
 * @author Mai Aloni 
 * @version 18-08-2019
 * 
 * This file includes function of queue, such as creare queue, destory queue,
 * enqueue, dequeue, etc.
 *
 * compile: gd -I include/ -I ../linked_list/include/ tests/test_queue.c queue.c ../linked_list/linked_list.c
../linked_list/linked_list.c
 */

#include <stdio.h> /*size_t*/
#include <assert.h> /*assert*/

#include "queue.h" /*queue_t*/
#include "linked_list.h" /*slist_node_t*/


enum code_status_e
{
	SUCCESSES,
	FAILURE
};


struct queue
{
	slist_node_t *head_dummy;
	slist_node_t *tail;
};


queue_t *QueueCreate()
{
	queue_t *queue = NULL;
	slist_node_t *dummy = NULL;	

	queue = malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return NULL;
	}
	
	dummy = SlistCreateNode(NULL, NULL);
	if (NULL == dummy)
	{
		free(queue);
		return NULL;
	}

	queue->head_dummy  = dummy;
	queue->tail = dummy;
		  
	return queue;
}


void QueueDestroy(queue_t *queue)
{
	SlistFreeAll(queue->head_dummy); 
	queue->head_dummy = NULL;
 	queue->tail = NULL;

	free(queue);
	queue = NULL;
}


size_t QueueSize(const queue_t *queue)
{
	assert (NULL != queue);

	/*start from next_node because there is extra node to mark the end of
	the queue*/
	return 	SlistCount((queue->head_dummy)->next_node); 
}


int QueueIsEmpty(const queue_t *queue)
{
	assert (NULL != queue);
	
	return (queue->head_dummy == queue->tail);
}


int QueueEnqueue(queue_t *queue, void *data)
{

	slist_node_t *new_node_queue = SlistCreateNode(data,NULL);
	
	if (NULL == new_node_queue)
	{
		return FAILURE;
	}
	
	assert(NULL != queue);

	new_node_queue = SlistInsertAfterNode(queue->tail,new_node_queue);
	queue->tail = new_node_queue;

	return SUCCESSES;
}


void QueueDequeue(queue_t *queue)
{
	slist_node_t *node_to_be_removed = NULL;

	assert (NULL != queue);
	
	if (queue->head_dummy->next_node == queue->tail)
	{
		queue->tail = queue->head_dummy;
	}

	node_to_be_removed = SlistRemoveAfter(queue->head_dummy);
	free(node_to_be_removed);
	node_to_be_removed = NULL;
}


void* QueuePeek(const queue_t *queue)
{
	assert (NULL != queue);
	
	return (queue->head_dummy)->next_node->data;
}


queue_t *QueueAppend(queue_t *dest_queue, queue_t *src_queue)
{
	(dest_queue->tail)->next_node = (src_queue->head_dummy)->next_node;
	dest_queue->tail  = src_queue->tail;
	src_queue->tail = src_queue->head_dummy;
	(src_queue->head_dummy)->next_node = NULL;

	return dest_queue;
}


