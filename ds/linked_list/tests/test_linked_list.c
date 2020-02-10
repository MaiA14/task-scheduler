#include "linked_list.h"
#include <stdio.h>
#include <string.h>


void FlowCreateNodeAfterCount();
void FlowCreateNodeBeforeCount();
void FlowCreateNodeRemoveAfterCount();
void FlowCreateNodeRemoveBeforeCount();
void FlowCreateNodeFindData();
void FlowCreateNodeForEach();
void FlowCreateNodeFlipList();
void FlowCreateListFindIntersection();
void FlowCreateListHasLoop();

static int CompareChars(const void *list_data, const void *sent_data);

int main()
{
	FlowCreateNodeAfterCount();
	FlowCreateNodeBeforeCount();
	FlowCreateNodeRemoveAfterCount();
	FlowCreateNodeRemoveBeforeCount();
	FlowCreateNodeFindData();
	FlowCreateNodeForEach();
	FlowCreateNodeFlipList();
	FlowCreateListFindIntersection();
	FlowCreateListHasLoop();
	
	
	return 0;
}


void FlowCreateNodeAfterCount()
{	
	slist_node_t *head  = NULL;
	slist_node_t *new_node = NULL;
	size_t expected_count = 2;

	char ch1 = 'a';
	char ch2 = 'b';

	head = SlistCreateNode(&ch1, NULL);
	new_node = SlistCreateNode(&ch2, NULL);
	
	SlistInsertAfterNode(head, new_node);

	printf("\n1) Create a new list, add new node after and count number of nodes:\n");
	if (expected_count != SlistCount(head))
	{
		printf("\033[1;31mWrong value of inserted node after\033[0m\n");
	}
	
	else
	{	printf("\033[1;32mInserting new node after is succeded\033[0m\n\n");
	}
	
	SlistFreeAll(head);
	head = NULL;
}


void FlowCreateNodeBeforeCount()
{	
	slist_node_t *head  = NULL;
	slist_node_t *new_node = NULL;
	slist_node_t *new_node2 = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 4;
	size_t expected_count = 3;

	head = SlistCreateNode(&num1, NULL);
	new_node = SlistCreateNode(&num2, NULL);
	new_node2 = SlistCreateNode(&num3, NULL);

	head->next_node = new_node;
	
	printf("2) Create a new list, add new node and count number of nodes:\n");
	if (head != SlistInsertNode(head, new_node2))
	{
		printf("\033[1;31mWrong value of inserted node before\033[0m\n");
	}
	
	if 	(expected_count != SlistCount(head))
	{
		printf("\033[1;31mWrong length of linked list\033[0m\n");
	}
	else
	{
		printf("\033[1;32mInserting new node before is succeded\033[0m\n\n");
	}
	
	
	SlistFreeAll(head);
	head = NULL;
}

void FlowCreateNodeRemoveAfterCount()
{
	slist_node_t *head  = NULL;
	slist_node_t *new_node = NULL;
	slist_node_t *new_node2 = NULL;
	size_t expected_count = 2;

	double num1 = 3.25;
	double num2 = 4.5;
	double num3 = 6.7;
	
	head = SlistCreateNode(&num1, NULL);
	new_node = SlistCreateNode(&num2, NULL);
	new_node2 = SlistCreateNode(&num3, NULL);
			
	head->next_node = new_node;
	new_node->next_node = new_node2;

	printf("3) Create a new node, remove node after and count number of nodes:\n");

	if (new_node != SlistRemoveAfter(head))
	{
		printf("\033[1;31mWrong value of remove node after\033[0m\n");
	}

	
	if 	(expected_count != SlistCount(head))
	{
		printf("wrong number of nodes after remove after\n");
	}
	
	else
	{
		printf("\033[1;32mRemoving node after is succeded\033[0m\n\n");
	}
	
	SlistFreeAll(new_node);
	SlistFreeAll(head);
	head = NULL;
}


void FlowCreateNodeRemoveBeforeCount()
{
	slist_node_t *head  = NULL;
	slist_node_t *new_node = NULL;
	slist_node_t *new_node2 = NULL;
	size_t expected_count = 2;

	float num1 = 3.25;
	float num2 = 4.5;
	float num3 = 6.7;
	
	head = SlistCreateNode(&num1, NULL);
	new_node = SlistCreateNode(&num2, NULL);
	new_node2 = SlistCreateNode(&num3, NULL);
			
	head->next_node = new_node;
	new_node->next_node = new_node2;

	printf("4) Create a new list, remove node before and count number of nodes:\n");

	if (new_node2 != SlistRemove(new_node))
	{
		printf("\033[1;31mWrong value of remove node before\033[0m\n");
	}

	if 	(expected_count != SlistCount(head))
	{
		printf("\033[1;31mwrong number of nodes after remove after\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32mRemoving node before is succeded\033[0m\n\n");
	}
	
	SlistFreeAll(new_node2);
	SlistFreeAll(head);
	head = NULL;
}


static int CompareChars(const void *list_data, const void *sent_data)
{
	return (!(*(char *)list_data == *(char *)sent_data));
}


void FlowCreateNodeFindData()
{
	slist_node_t *head  = NULL;
	slist_node_t *new_node = NULL;
	slist_node_t *new_node2 = NULL;
	slist_node_t *find_res = NULL;
	
	char ch1 = 'a';
	char ch2 = 'b';
	char ch3 = 'c';
	char char_to_find = 'c';
	
	head = SlistCreateNode(&ch1, NULL);
	new_node = SlistCreateNode(&ch2, NULL);
	new_node2 = SlistCreateNode(&ch3, NULL);
			
	head->next_node = new_node;
	new_node->next_node = new_node2;

	find_res = SlistFind(head, &char_to_find, CompareChars);
	
	printf("5) Create a new list, find if the data is exist in list:\n");
	if (char_to_find != (*(char*)find_res->data))
	{
		printf("\033[1;31mData isn't exist in list\033[0m\n");
	}
	else
	{
		printf("\033[1;32mThe data the user sent is exist in list\033[0m\n\n");
	}
	
	SlistFreeAll(head);
	head = NULL;
	find_res = NULL;
}


static int AddInt(void *data, void *integer)
{
	if ((NULL == data) || (NULL == integer))
	{
		return -1;
	}
	
	*(int *)data = *(int *)data  + 1;
	
	return 0;
}


void FlowCreateNodeForEach()
{
	slist_node_t *head  = NULL;
	slist_node_t *new_node = NULL;
	slist_node_t *new_node2 = NULL;
	
	int num1 = 2;
	int num2 = 7;
	int num3 = 5;
	int add_int = 1;
	int check_for_each = 0;
	
	head = SlistCreateNode(&num1, NULL);
	new_node = SlistCreateNode(&num2, NULL);
	new_node2 = SlistCreateNode(&num3, NULL);
			
	head->next_node = new_node;
	new_node->next_node = new_node2;
	
	check_for_each = SlistForEach(head, AddInt, &add_int);
	
	printf("6) Create a new list, add 1 to each data integer in the list:\n");
	
	if (0 != check_for_each)
	{
		printf("\033[1;31mFailure in action function\033[0m\n");
	}
	
	if ((3 != num1) && (8 != num2) && (6 != num3))
	{
		printf("\033[1;31mProblem in changing the data\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32mChanges apply successfuly\033[0m\n\n");
	}
	
	SlistFreeAll(head);
	head = NULL;
}



void FlowCreateNodeFlipList()
{
	slist_node_t *head  = NULL;
	slist_node_t *new_node = NULL;
	slist_node_t *new_node2 = NULL;
	
	int num1 = 2;
	int num2 = 7;
	int num3 = 5;
	
	head = SlistCreateNode(&num1, NULL);
	new_node = SlistCreateNode(&num2, NULL);
	new_node2 = SlistCreateNode(&num3, NULL);
			
	head->next_node = new_node;
	new_node->next_node = new_node2;
	
	printf("7) Create a new list and flip it\n");
	
	if (NULL == SlistFlip(head))
	{
		printf("\033[1;31mThere is no list\033[0m\n");
	}
	
	if ((new_node2->next_node != new_node) && (new_node->next_node != head))
	{
		printf("\033[1;31mFlip is failed\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32mFlip passed successfuly\033[0m\n\n");
	}

	SlistFreeAll(new_node2);
	head = NULL;
}


void FlowCreateListFindIntersection()
{
	slist_node_t *head1  = NULL;
	slist_node_t *new_node = NULL;
	slist_node_t *new_node2 = NULL;
	slist_node_t *head2 = NULL;
	slist_node_t *new_node3 = NULL;
	slist_node_t *new_node4 = NULL;
	
	int num = 2;
	
	head1 = SlistCreateNode(&num, NULL);
	new_node = SlistCreateNode(&num, NULL);
	new_node2 = SlistCreateNode(&num, NULL);
	head2 = SlistCreateNode(&num, NULL);
	new_node3 = SlistCreateNode(&num, NULL);
	new_node4 = SlistCreateNode(&num, NULL);
	
	head1->next_node = new_node;
	new_node->next_node = new_node2;
	new_node2->next_node = new_node4;
	
	head2->next_node = new_node3;
	new_node3->next_node = new_node2;
	
	printf("8) Create a new list and return the intersection\n");
	
	if (new_node2 != SlistFindIntersection(head1,head2))
	{
		printf("\033[1;31mThere is no intersection\033[0m\n");
	}
	else
	{
		printf("\033[1;32mFound intersection\033[0m\n\n");
	}
	
	new_node2->next_node = new_node4;
	
	SlistFreeAll(head2);
	head2 = NULL;

}


void FlowCreateListHasLoop()
{
	slist_node_t *head  = NULL;
	slist_node_t *new_node = NULL;
	slist_node_t *new_node2 = NULL;
	slist_node_t *new_node3 = NULL;
	slist_node_t *new_node4 = NULL;
	
	int num = 2;
	
	head = SlistCreateNode(&num, NULL);
	new_node = SlistCreateNode(&num, NULL);
	new_node2 = SlistCreateNode(&num, NULL);
	new_node3 = SlistCreateNode(&num, NULL);
	new_node4 = SlistCreateNode(&num, NULL);
			
	head->next_node = new_node;
	new_node->next_node = new_node2;
	new_node2->next_node = new_node3;
	new_node3->next_node = new_node4;
	new_node4->next_node = new_node;
	
	printf("9) Create a new list and check if it has a loop\n");
	
	if (1 != SlistHasLoops(head))
	{
		printf("\033[1;31mThere is no loop\033[0m\n");
	}
	
	else
	{
		printf("\033[1;32mLoop is founded\033[0m\n\n");
	}
	
	head = NULL;

}













