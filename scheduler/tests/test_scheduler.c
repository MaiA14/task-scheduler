#include <stdio.h>
#include "scheduler.h"
#include "task.h"

#define SUCCESS(str) (printf("\033[1;32m- %s\033[0m\n", str))
#define FAILURE(str) (printf("\033[1;31m- %sin\033[0m in line %d\n", str, __LINE__))

void CheckFunctionalityOfSched();
static int AddInt(void *data);
 
int main()
{
	void CheckFunctionalityOfSched();
	
	return 0;
}


void CheckFunctionalityOfSched()
{
	ilrd_uid_t task_to_be_removed; 
	/*check create*/
	scheduler_t *sched = SchedCreate();
	printf("\nCreate scheduler, check if its empty, check size, add tasks, remove task, check size, destroy scheduler:\n");
	/*check IsEmpty*/ 
	if (SchedIsEmpty(sched))
	{
		SUCCESS("IsEmpty works");
	}
	else
	{
		FAILURE("Problem in IsEmpty - there should be 0 tasks ");
	}
	/*check size*/
	if (0 == SchedSize(sched))
	{
		SUCCESS("Size works");
	}
	else
	{
		FAILURE("Problem in size - there should be 0 tasks ");
	}
	/*check add task*/
	SchedAddTask(sched, AddInt, NULL, 2, time(NULL) + 3);
	SchedAddTask(sched, AddInt, NULL, 3, time(NULL) + 7);
	SchedAddTask(sched, AddInt, NULL, 3, time(NULL) + 3);
	SchedRun(sched);
	if (3 == SchedSize(sched))
	{
		SUCCESS("SchedAddTask works");
	}
	else
	{
		FAILURE("Problem in SchedAddTask - there should be 3 tasks ");
	}
	task_to_be_removed = SchedAddTask(sched, AddInt, NULL, 7, time(NULL) + 3);
	if (4 == SchedSize(sched))
	{
		SUCCESS("Size works");
	}
	else
	{
		FAILURE("Problem in size - there should be 4 tasks ");
	}
	SchedRemoveTask(sched, task_to_be_removed);
	if (3 == SchedSize(sched))
	{
		SUCCESS("SchedRemoveTask works");
	}
	else
	{
		FAILURE("Problem in SchedRemoveTask - 1 task should be removed ");
	}
	SchedRun(sched);
	/*check destroy*/
	SchedDestroy(sched); sched = NULL;
}


static int AddInt(void *data)
{
	if (NULL == data) 
	{
		printf("0");
		return STOP;
	}
	printf("num + 1");
	*(int *)data = *(int *)data  + 1;
	
	return REPEAT;
}



