#include <stdio.h>
#include <sorted_list.h>

/*private functions*/
static int IsIntBefore(const void *element_data,
					   const void *user_data,
					   void *param);
static int CompareInt(const void *list_data, const void *user_data);					   

void TestFlow1();
void TestFlow2();
void TestFlow3();
void TestFlow4();

int main()
{
	TestFlow1();	
	TestFlow2();
	TestFlow3();
	TestFlow4();
	
	return 0;
}


static int IsIntBefore(const void *list_data,
					   const void *user_data,
					   void *param)
{
	(void)param;
	
	return (*(int *)list_data < *(int *)user_data);
}


static int CompareInt(const void *list_data, const void *user_data)
{
	return (!(*(int *)list_data == *(int *)user_data));
}


void TestFlow1()
{
	sorted_list_t *sorted_test = NULL;
	sorted_list_iter_t iter;
	int num;
	sorted_test = SortedListCreate(IsIntBefore, NULL);
	iter = SortedListBegin(sorted_test);
	num = 33;
	
	printf("\nCreate sorted linked list, insert, check if is empty, get data, size, remove, find if and destroy:\n");
	
	if (!SortedListIsEmpty(sorted_test))
	{
		printf("\033[1;31m- Problem in functionality of IsEmpty\033[0m\n");
	}
	else
	{
		printf("\033[1;32m- IsEmpty works as expected\033[0m\n");
	}
	
	iter = SortedListInsert(sorted_test, &num);
	
	if (*(int *)(SortedListGetData(iter)) != num)
	{
		printf("\033[1;31m- Problem in functionality of GetData\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32m- GetData works\033[0m\n");
	}
	
	if (SortedListIsEmpty(sorted_test))
	{
		printf("\033[1;31m- Problem in functionality of Insert - list already contains one element\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32m- Insert works\033[0m\n");
	}
	
	if (1 != SortedListSize(sorted_test))
	{
		printf("\033[1;31m- Problem in functionality of size - list already contains one element\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32m- Size works\033[0m\n");
	}
	
	if (*(int*)SortedListGetData(SortedListFindIf(sorted_test, SortedListBegin(sorted_test), SortedListEnd(sorted_test), CompareInt, &num)) !=  num)
	{
		printf("\033[1;31m- Problem in functionality of sizeFindIf\033[0m\n");
	}

	SortedListRemove(iter);
	
	if (0 != SortedListSize(sorted_test))
	{
		printf("\033[1;31m- Problem in functionality of size - list already contains one element\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32m- Size works\033[0m\n");
	}

	SortedListDestroy(sorted_test); sorted_test  = NULL;
}


void TestFlow2()
{
	sorted_list_t *sorted_test2 = SortedListCreate(IsIntBefore, NULL);
	
	int num1 = 100;
	int num2 = 20;
	int num3 = 30;
	int num4 = 20;
	int num5 = 30;

	SortedListInsert(sorted_test2 ,&num1);
	SortedListInsert(sorted_test2 ,&num2);
	SortedListInsert(sorted_test2 ,&num3);
	SortedListInsert(sorted_test2 ,&num4);
	SortedListInsert(sorted_test2 ,&num5);

	printf("\nCreate sorted linked list, check begin, pop back, pop front and destroy:\n");
	SortedListPopBack(sorted_test2 );
	if (SortedListGetData(SortedListBegin(sorted_test2 )) != &num1)
	{
		printf("\033[1;31m- Problem in functionality of pop back\033[0m\n");
	}
	
	else
	{
			printf("\033[1;32m- Pop back works\033[0m\n");
	}
	
	SortedListPopFront(sorted_test2);
	if (SortedListGetData(SortedListBegin(sorted_test2 )) != &num3)
	{
		printf("\033[1;31m- Problem in functionality of Pop front\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32m- Pop front works\033[0m\n");
	}
	
	SortedListDestroy(sorted_test2); sorted_test2  = NULL;
	
}


void TestFlow3()
{
	size_t dest_tests[] = {1, 10, 11, 12, 13};
	size_t src_tests[] = {2, 3, 4, 5, 19};
	size_t num_of_tests = sizeof(dest_tests)/sizeof(dest_tests[0]);

	size_t i = 0;

	sorted_list_t *dest = NULL;
	sorted_list_t *src = NULL;

	dest = SortedListCreate(IsIntBefore, NULL);
	src = SortedListCreate(IsIntBefore, NULL);
	printf("\nCreate two lists and check merge:\n");
	for (i = 0; i < num_of_tests; ++i)
	{
		SortedListInsert(src, &src_tests[i]);
	}

	for (i = 0; i < num_of_tests; ++i)
	{
		SortedListInsert(dest, &dest_tests[i]);
	}

	SortedListMerge(dest, src);

	if (10 != SortedListSize(dest))
	{
		printf("\033[1;31m- Problem in functionality of merge\033[0m\n");	
	}
	else
	{
		printf("\033[1;32m- Merge works\033[0m\n");
	} 
	
	SortedListDestroy(dest); dest = NULL;
	SortedListDestroy(src); src = NULL;
}

void TestFlow4()
{
	sorted_list_t *sorted_list3 = NULL;
	size_t list[] = {1,2,4,6};
	size_t find_num1 = 6;
	size_t find_num2 = 11;
	size_t num_of_tests = sizeof(list)/sizeof(list[0]);
	size_t i = 0;

	sorted_list3 = SortedListCreate(IsIntBefore,NULL);

	printf("\nCreate list and check find:\n");
	for (i = 0; i < num_of_tests; ++i)
	{
		SortedListInsert(sorted_list3, &list[i]);
	}

	if (!SortedListIsSameIter(SortedListFind(sorted_list3, SortedListBegin(sorted_list3), SortedListEnd(sorted_list3), &find_num1), SortedListBegin(sorted_list3)))
	{
		printf("\033[1;32m- find works - the data is founded\033[0m\n");
	}

	if (!SortedListIsSameIter(SortedListFind(sorted_list3, SortedListBegin(sorted_list3), SortedListEnd(sorted_list3), &find_num2), SortedListBegin(sorted_list3)))
	{
		printf("\033[1;32m- find works - data isn't exist in list\033[0m\n");
	}
	
	SortedListDestroy(sorted_list3); sorted_list3  = NULL;
}	

	








