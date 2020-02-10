/******************************************************************************
 * @Author Mai Aloni 
 * @Version 26-08-2019
 * Title: Scheduler	
 * Description: This file contains functions of scheduler, 
   such as: create scheduler, destroy scheduler, etc.
 *
 * compile: gd -I ./include/ scheduler.c ./tests/test_scheduler.c  -I ~/mai-aloni/ds/proirity_queue/include/ ~/mai-aloni/ds/proirity_queue/priority_queue.c -I ~/mai-aloni/projects/task/include/ ~/mai-aloni/projects/task/task.c -I ~/mai-aloni/ds/UID/include/ ~/mai-aloni/ds/UID/UID.c  -I ~/mai-aloni/ds/sorted_list/include/ ~/mai-aloni/ds/sorted_list/sorted_list.c -I ~/mai-aloni/ds/doubly_linked_list/include/ ~/mai-aloni/ds/doubly_linked_list/doubly_linked_list.c

 ******************************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#ifdef _WIN32
#include <Windows.h> /* sleep*/
#else
#include <unistd.h> /*sleep*/
#endif

#include "priority_queue.h" /* functions declartions of priority queue */
#include "task.h" /* functions declartions of task */
#include "scheduler.h" 
 
 
#define UNUSED(x) ((void)x)

enum run_sched_status {RUN_STOPPED_BECAUSE_FAILURE = -1 , RUN_STOPPED_NORMALLY};
 
struct scheduler
{
	pq_t *pq;
 	task_t *current_task;
 	int is_sched_stop;
};
 

/*static functions*/
static int CmpTime(void* task_time1, void* task_time2, void* param); 
static int TaskUidCmp(const void *data1, const void *data2);   

static int CmpTime(void* task_time1, void* task_time2, void* param)
{
	UNUSED(param);
	
	task_time1 = (task_t*)task_time1;
	task_time2 = (task_t*)task_time2;
	
	return (TaskGetTimeToExecution(task_time1) - 
			TaskGetTimeToExecution(task_time2));
}

  
scheduler_t *SchedCreate(void)
{
	scheduler_t *sched = NULL;
	
	sched = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == sched) 
	{	
		free(sched);
		sched = NULL;
		return NULL;
	}
	
	sched->pq = PriorityQCreate(CmpTime,NULL); 
	if (NULL == sched->pq)
	{
		free(sched->pq);
		sched->pq = NULL;
		return NULL;
	}
	
	sched->current_task = NULL;
	sched->is_sched_stop = 0;
	
	return sched;
} 


void SchedDestroy(scheduler_t *sched)
{
	assert(NULL != sched);
	
	sched->current_task = NULL;
	
	PriorityQDestroy(sched->pq);
	sched->pq = NULL;
	
	free(sched); sched = NULL;
}


ilrd_uid_t SchedAddTask(scheduler_t *sched, action_func_t task_action_func,
						void *params, time_t exe_interval_in_seconds,
						time_t execution_start_time)
{
	task_t *new_task = NULL;
	
	assert(NULL != task_action_func);
	
	new_task = TaskCreate(task_action_func,
			   			  params,
			   			  exe_interval_in_seconds,
			   			  execution_start_time);
	if (NULL == new_task)
	{
		return BAD_UID;
	}
	
	assert(NULL != sched);
	if (0 !=  PriorityQEnqueue(sched->pq,new_task))
	{
		return BAD_UID;
	}
	
	return TaskGetUID(new_task);  						
}


static int TaskUidCmp(const void *data1, const void *data2)
{
	task_t *task1 = (task_t*)data1;
	ilrd_uid_t *uid2 = (ilrd_uid_t*)data2;

	return (UIDIsSame(TaskGetUID(task1), *uid2));
}


void SchedRemoveTask(scheduler_t *sched, ilrd_uid_t task_uid)
{
	task_t *task_to_be_free = NULL;
	
	assert(NULL != sched);
	
	task_to_be_free = PriorityQErase(sched->pq, &task_uid, TaskUidCmp);
	TaskDestroy(task_to_be_free);
}


int SchedIsEmpty(const scheduler_t *sched)
{
	assert(NULL != sched);
	
	return PriorityQIsEmpty(sched->pq);
}				   


size_t SchedSize(const scheduler_t *sched)
{	
	assert(NULL != sched);
	
	return PriorityQSize(sched->pq);	
}


void SchedClear(scheduler_t *sched)
{
	assert(NULL != sched);

	while (!SchedIsEmpty(sched))
	{
		TaskDestroy((task_t*)PriorityQPeek(sched->pq));
		PriorityQDequeue(sched->pq);
	}
}
		

void SchedStop(scheduler_t *sched)
{
	sched->is_sched_stop = 1;
}
