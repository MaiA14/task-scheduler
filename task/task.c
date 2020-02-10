/******************************************************************************
 * @Author Mai Aloni 
 * @Version 26-08-2019
 * Title: Task	
 * Description: This file contains functions of task, 
   such as: create task, destroy prioirity queue, execute task, etc.
 *
 * compile:  gd -I task/include/ task/task.c task/tests/test_task.c -I ~/mai-aloni/ds/UID/include ~/mai-aloni/ds/UID/UID.c

*******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "task.h" /* functions declartions of task */
#include "UID.h" /* functions declartions of UID */


struct task
{
	ilrd_uid_t uid;
	action_func_t action_func;
	void *param;
	time_t exe_interval_in_seconds;
	time_t init_execution_time; 
};


task_t *TaskCreate(
				   action_func_t action_func, 
				   void *param,
				   time_t exe_interval_in_seconds, 
				   time_t init_execution_time
				  )
{
	
	task_t *task = NULL;
	
	assert(NULL != action_func);
	
	task = (task_t *)malloc(sizeof(task_t));
	if (NULL == task) 
	{	
		free(task);
		task = NULL;
		return NULL;
	}
	
	task->uid = UIDCreate();
	if (UIDIsSame(task->uid,BAD_UID))
	{
		return NULL;
	}
	
	task->param = param;
	task->exe_interval_in_seconds = exe_interval_in_seconds; 
	task->init_execution_time = init_execution_time;
	
	return task;	
}


void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	free(task); task = NULL;
}				  


time_t TaskGetTimeToExecution(const task_t *task)
{
	assert(NULL != task);
	
	return task->init_execution_time;
}


int TaskExecute(task_t *task)
{
	assert(NULL != task);
	if (0 == task->action_func)
	{
		return 0;
	}
	return 1;
}


ilrd_uid_t TaskGetUID(const task_t *task)
{
	assert(NULL != task);
	
	return task->uid;
}


void TaskUpdateTimeToExecute(task_t *task)
{	
	assert(NULL != task);
	
	task->exe_interval_in_seconds += time(NULL);	
}








