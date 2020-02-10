#include <stdio.h> /*printf*/

#include "task.h" /* functions declartions of task */
#include "UID.h" /* functions declartions of UID */

#define UNUSED(x) ((void)x)

void CheckFunctionalityOfTask();
static int AddInt(void *data);

int main()
{
	
	CheckFunctionalityOfTask();
	
	return 0;
}




void CheckFunctionalityOfTask()
{
	time_t exe_interval_sec = 120;
	time_t start_from = time(NULL) + 60;
	
	/*check create*/
	task_t *task = TaskCreate(AddInt,NULL,exe_interval_sec,start_from);
	/*check TaskGetUID*/
	if (!UIDIsSame(BAD_UID, TaskGetUID(task)))
	{
		printf("\033[1;32m- TaskGetUID works\033[0m\n");
	}
	
	else
	{
		printf("\033[1;31m- Problem in TaskGetUID\033[0m\n");
	}
	
	/*check TaskGetTimeToExecution*/
	if (start_from == TaskGetTimeToExecution(task))
	{
		printf("\033[1;32m- TaskGetTimeToExecution works\033[0m\n");
	}
	else
	{
		printf("\033[1;31m- Problem in TaskGetTimeToExecution\033[0m\n");
	}
	
	/*check TaskExecute*/
	if (0 == TaskExecute(task))
	{
		printf("\033[1;32m- TaskExecute works\033[0m\n");
	}
	else
	{
		printf("\033[1;31m- Problem in TaskExecute\033[0m\n");
	}
	
	/*check destroy*/	
	TaskDestroy(task);
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

