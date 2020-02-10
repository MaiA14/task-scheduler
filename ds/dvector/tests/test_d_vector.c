#include <stdio.h>
#include "d_vector.h" 

enum {SUCCESS ,FAILURE};

void FlowCreateVectorIsEmptyDestroy();
void FlowCreateVectorPopBackDestroy();
void FlowCreateVectorCheckSizePushBack();
void FlowCreateVectorCheckCapacity();
void FlowCreateVectorGetItemAddress();

int main()
{
	 FlowCreateVectorIsEmptyDestroy();
	 FlowCreateVectorPopBackDestroy();
	 FlowCreateVectorCheckSizePushBack();
	 FlowCreateVectorCheckCapacity();
	 FlowCreateVectorGetItemAddress();
	 
	return 0;
}


void FlowCreateVectorIsEmptyDestroy()
{
	d_vector_t *vector;
	const size_t tests_capacity[] = {10,100,300};
	const size_t tests_size_of_element[] = {sizeof(size_t),sizeof(char),sizeof(double)}; 
	size_t num_of_tests = sizeof(tests_capacity)/sizeof(tests_capacity[0]);
	size_t i = 0;
	int is_empty = 0;
	
	printf("\nCreate vector, then check if vector is destroy, then destroy the vector:\n");

	for (i = 0; i < num_of_tests; i++)
	{
		vector = DVectorCreate(tests_size_of_element[i],tests_capacity[i]);
		if (NULL != vector)
		{
			 (printf("\033[1;32mAllocation is succeded\033[0m\n"));
		}
		else
		{
			(printf("\033[1;31mUnable to allocate memory\033[0m\n"));
		}

		is_empty = DVectorIsEmpty(vector);

		if (0 == is_empty)
		{
			(printf("\033[1;32mVector is empty\033[0m\n\n"));
		}
		else
		{
			(printf("\033[1;31mVector is not empty\033[0m\n\n"));
		}

		DVectorDestroy(vector);
	}
}


void FlowCreateVectorPopBackDestroy()
{
	d_vector_t *vector;
	const size_t tests_capacity[] = {10,100,300};
	const size_t tests_size_of_element[] = {sizeof(size_t),sizeof(char),sizeof(double)}; 
	size_t num_of_tests = sizeof(tests_capacity)/sizeof(tests_capacity[0]);
	size_t i = 0;
	
	printf("\nCreate vector, then pop back, and destroy the vector:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		vector = DVectorCreate(tests_size_of_element[i],tests_capacity[i]);
		
		if (NULL != vector)
		{
			
			 printf("\033[1;32mAllocation is succeded\033[0m\n");
		}
		else
		{
			printf("\033[1;31mUnable to allocate memory\033[0m\n");
		}
	
		if (0 != DVectorPopBack(vector))
		{
			printf("\033[1;32mPop back successfuly\033[0m\n");
		}
		else
		{
			printf("\033[1;31mCan't pop back - Vector is empty\033[0m\n\n");
		}
		
		DVectorDestroy(vector);	
	}	
}


void FlowCreateVectorCheckSizePushBack()
{
	d_vector_t *vector;
	const size_t tests_capacity = 10;
	const size_t tests_size_of_element = sizeof(size_t); 
	size_t num_of_vectors = 3;
	
	size_t i = 0;
	size_t push_test = 100;
	
	printf("\nCreate vector, then check size, push back, and destroy the vector:\n");
	
	for (i = 0; i < num_of_vectors ; i++)
	{
		vector = DVectorCreate(tests_size_of_element,tests_capacity);
		
		if (0 != DVectorSize(vector))
		{
				printf("\033[1;31mIncorrecrt size of vector\033[0m\n\n");
		}
			
		else
		{
				printf("\033[1;32mCorrecrt size\033[0m\n");
		}
		
		
		if (0 != DVectorPushBack(vector,&push_test))
		{
				printf("\033[1;31mfailed to push back\033[0m\n\n");
		}
			
		else
		{
				printf("\033[1;32mPush back successfuly\033[0m\n\n");
		}
		
	}		
	
	DVectorDestroy(vector);	
}		


void FlowCreateVectorCheckCapacity()
{

	const size_t test_capacity1 = 30;
	const size_t test_size_of_element1 = sizeof(size_t); 
	d_vector_t *vector1 = DVectorCreate(test_capacity1, test_size_of_element1);
	
	const size_t test_capacity2 = sizeof(size_t);
	const size_t test_size_of_element2 = 30; 
	d_vector_t *vector2 = DVectorCreate(test_capacity2, test_size_of_element2);

	printf("\nCreate vector, then check its capacity:\n");
	
	if (test_size_of_element1 != DVectorCapacity(vector1))
	{
		printf("\033[1;31mError! unexpected capacity\033[0m\n\n");
	}
	
	else
	{
		printf("\033[1;32mCorrecrt capacity\033[0m\n");
	}

	DVectorDestroy(vector1);

	if (test_size_of_element2 != DVectorCapacity(vector2))
	{
		printf("\033[1;31mError! unexpected capacity\033[0m\n\n");
	}
	
	else
	{
		printf("\033[1;32mCorrecrt capacity\033[0m\n");
	}

	DVectorDestroy(vector2);
}


void FlowCreateVectorGetItemAddress()
{
	size_t i = 0;
	size_t push_itmes[] = {2,4,6,8};
	size_t num_of_push_items = sizeof(push_itmes)/sizeof(push_itmes[0]);	
	d_vector_t *vector = DVectorCreate(40, 20);

	printf("\nCreate vector, then get item address:\n");
	
	for (i = 0; i < num_of_push_items; i++)
	{
		DVectorPushBack(vector, &push_itmes[i]);
	}	
	
	if (DVectorGetItemAddress(vector,7) == NULL)
	{
		printf("\033[1;31mindex is bigger than number of elements\033[0m\n\n");
	}

	else
	{
		printf("\033[1;32mGet the correct address of index\033[0m\n");
	}
	
	DVectorDestroy(vector);
}


void FlowCreateVectorReserve()
{
	size_t i = 0;
	size_t push_itmes[] = {2,4,6,8};
	size_t num_of_push_items = sizeof(push_itmes)/sizeof(push_itmes[0]);	
	d_vector_t *vector = DVectorCreate(40, 20);

	printf("\nCrefffffffffffffm address:\n");
	
	for (i = 0; i < num_of_push_items; i++)
	{
		DVectorPushBack(vector, &push_itmes[i]);
	}	
	
	if (DVectorGetItemAddress(vector,7) == NULL)
	{
		printf("\033[1;31mindex is bigger than number of elements\033[0m\n\n");
	}

	else
	{
		printf("\033[1;32mGet the correct address of index\033[0m\n");
	}
	
	DVectorDestroy(vector);
}






	
		



