#include <stdio.h>
#include "UID.h"
 
void TestUID(); 

int main()
{
	TestUID();	
	
	return 0;
}


void TestUID()
{	
	ilrd_uid_t uid_arr[3];
	
	uid_arr[0] = UIDCreate();
	uid_arr[1] = UIDCreate();
	uid_arr[2] = UIDCreate();
	
	printf("Check UID:\n");
	
	if (0 == (uid_arr[0].counter))
	{
		printf("\033[1;32mGenrating new UID succeded\033[0m\n");
	}
	else
	{
		printf("\033[1;31mProblem in genrating new UID\033[0m\n");
	}
	if (1 == (uid_arr[1].counter))
	{
			printf("\033[1;32mGenrating new UID succeded\033[0m\n");
	}
	else
	{
		printf("\033[1;31mProblem in genrating new UID\033[0m\n");
	}
	
	if (2 == (uid_arr[2].counter))
	{
			printf("\033[1;32mGenrating new UID succeded\033[0m\n");
	}
	else
	{
		printf("\033[1;31mProblem in genrating new UID\033[0m\n");
	}
	
	if (UIDIsSame(uid_arr[0],uid_arr[0]))
	{
		printf("\033[1;32mUIDIsSame works\033[0m\n");
	}
	
	else
	{
		printf("\033[1;31mProblem in UIDIsSame\033[0m\n");
	}
	
	if (!UIDIsSame(uid_arr[0],uid_arr[1]))
	{
		printf("\033[1;32mUIDIsSame works\033[0m\n");
	}
	
	else
	{
		printf("\033[1;31mProblem in UIDIsSame\033[0m\n");
	}
	
	if (!UIDIsSame(uid_arr[2],uid_arr[1]))
	{
		printf("\033[1;32mUIDIsSame works\033[0m\n");
	}
	
	else
	{
		printf("\033[1;31mProblem in UIDIsSame\033[0m\n");
	}
}	







