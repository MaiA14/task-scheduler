#include <stdio.h>
#include <doubly_linked_list.h>

void CreateDlistInsertGetDataDestroy();
void CreateDlistCheckSize();
void CreateDlistPushFrontPushBack();

int main()
{
	CreateDlistInsertGetDataDestroy();	
	CreateDlistCheckSize();
	CreateDlistPushFrontPushBack();
	return 0;
}

void CreateDlistInsertGetDataDestroy()
{
	dlist_t *dlist_test = DlistCreate();
	size_t num_to_be_inseretd[] = {2};
	size_t find_num = 2;
	
	dlist_iter_t begin_iter = NULL;
	dlist_iter_t inserted = NULL;
	size_t i = 0;
	
	printf("Create doubly linked list, check if it is empty, insert and get data:\n");
	if (1 != DlistIsEmpty(dlist_test))
	{
		printf("\033[1;31m- Problem in functionality of IsEmpty\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32m- IsEmpty works as expected\033[0m\n");
	}
	
	begin_iter = DlistBegin(dlist_test);
	
	inserted = DlistInsert(dlist_test,begin_iter,&num_to_be_inseretd);
	if(2 != (*(size_t*)DlistGetData(inserted)))
	{
		printf("\033[1;31m- Problem in GetData\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32m- GetData works\033[0m\n");
	}
	
	DlistDestroy(dlist_test);
}


void CreateDlistCheckSize()
{
	size_t nums_to_be_inserted[] = {2,4,6,8};
	size_t i = 0;

	dlist_t *dlist_test = DlistCreate();
	dlist_iter_t node_holder = NULL;

	printf("\nCreate doubly linked list, insert and check size:\n");
	for (i = 0; i < 4; i++)
	{
		DlistInsert(dlist_test ,DlistBegin(dlist_test), &nums_to_be_inserted[i]);
	}

	if(DlistSize(dlist_test) != 4)
	{
			printf("\033[1;31m- Problem in functionality of size\033[0m\n");
	}
	else
	{
		printf("\033[1;32m- Size works\033[0m\n");
	}
	
	node_holder = DlistIterNext(DlistIterNext(DlistBegin(dlist_test)));
	
	if(*(size_t*)DlistGetData(node_holder) != 4)
	{
		printf("\033[1;31m- Problem in iterNext\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32m- iterNext works\033[0m\n");
	}
	
	node_holder = DlistIterPrev(DlistIterPrev(DlistEnd(dlist_test)));
	if(*(size_t*)DlistGetData(node_holder) != 4)
	{
		printf("\033[1;31m- Problem in iterPrev\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32m- iterPrev works\033[0m\n");
	}
	
	if (DlistIsSameIter(DlistIterNext(DlistIterNext(DlistBegin(dlist_test))),
		(DlistIterPrev(DlistIterPrev(DlistEnd(dlist_test))))) != 1)
	{
		printf("\033[1;31m- Problem in SameIter\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32m- SameIter works\033[0m\n");
	}	
	
	DlistDestroy(dlist_test);				
}

void CreateDlistPushFrontPushBack()
{
	size_t nums_to_be_inserted[] = {2,4,6,8};
	size_t i = 0;
	

	dlist_t *dlist_test = DlistCreate();
	dlist_iter_t node_holder = NULL;

	printf("\nCreate doubly linked list, insert, push back & push front:\n");
	for (i = 0; i < 4; i++)
	{
		DlistInsert(dlist_test ,DlistBegin(dlist_test), &nums_to_be_inserted[i]);
	}
	
	node_holder = DlistPushFront(dlist_test,&nums_to_be_inserted[2]);
	
	if(*(size_t*)DlistGetData(node_holder) != 6)
	{
		printf("\033[1;31m- Problem in PushFront\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32m- PushFront works\033[0m\n");
	}
	
	node_holder = DlistPushBack(dlist_test,&nums_to_be_inserted[1]);
	
	if(*(size_t*)DlistGetData(node_holder) != 4)
	{
		printf("\033[1;31m- Problem in PushBack\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32m- PushBack works\033[0m\n");
	}
	
	
	DlistDestroy(dlist_test);	
}










