#include <stdio.h> /*printf*/
#include <string.h> /*memcpy*/
#include "circular_buffer.h" 


struct c_buff
{
	char *end;
	char *read;
	char *write;
	char status;
	char start[1];
};


enum errors_e
{
		C_BUFF_IS_NOT_EMPTY = 0,
		C_BUFF_IS_EMPTY = 1
};

void FlowCreateCBufferCheckIsEmptyFreeSpaceDestroy();
void FlowCreateCBufferWrite();
void FlowCreateCBufferRead();

int main()
{
	
	FlowCreateCBufferCheckIsEmptyFreeSpaceDestroy();
	FlowCreateCBufferWrite(); 
	FlowCreateCBufferRead();
	
	return 0;
}


void FlowCreateCBufferCheckIsEmptyFreeSpaceDestroy()
{
	c_buff_t *c_buff = CBuffCreate(30);

	printf("1) Create circular buffer, check if it empty, check capacity and free space\n");
	
	if (C_BUFF_IS_EMPTY == CBuffIsEmpty(c_buff))
	{
		(printf("\033[1;32m- Circular buffer is empty\033[0m\n"));
	}
	else
	{
		(printf("- Circular buffer is not empty\n"));
	}
	
	if (30 == CBuffCapacity(c_buff))
	{
		(printf("\033[1;32m- The Capacity as it shown is correct\033[0m\n"));
	}
	else
	{
		printf("\033[1;31m- Wrong Capacity\033[0m\n\n");
	}
	
	if (0 != CBuffFreeSpace(c_buff))
	{
		printf("\033[1;32m- There is no free space in buffer, as expected\033[0m\n\n");
	}
	
	CBuffDestroy(c_buff);
}


void FlowCreateCBufferWrite()
{
	size_t data = 6;

	c_buff_t *c_buff = CBuffCreate(50);

	printf("2) Create circular buffer, and start to write\n");
	
	if (6 != (CBuffWrite(c_buff, &data, 6)))
	{
		printf("\033[1;31m- Wrong write value\033[0m\n\n");
	}
	else
	{
		(printf("\033[1;32m- Write function works\033[0m\n"));
	}

	CBuffDestroy(c_buff);
	
	c_buff = CBuffCreate(10);
	
	if (6 != (CBuffWrite(c_buff, &data, 6)))
	{
		printf("\033[1;31m- Wrong write value\033[0m\n\n");
	}
	else
	{
		(printf("\033[1;32m- Write function works\033[0m\n\n"));
	}
	
	c_buff->read += 10;
	
	if (6 != (CBuffWrite(c_buff, &data, 6)))
	{
		printf("\033[1;31m- can't read this number of bytes\033[0m\n\n");
	}

	CBuffDestroy(c_buff);
}


void FlowCreateCBufferRead()
{
	size_t i = 0;
	size_t data[] = {1,2,3,4,5};
	size_t data_len = sizeof(data)/sizeof(data[0]);
	size_t buffer[30];	

	c_buff_t *c_buff = CBuffCreate(sizeof(data) + 3);

	printf("3) Create circular buffer, write and then read\n");
	for (i = 0; i < data_len ; ++i)
	{
		CBuffWrite(c_buff, &data[i], sizeof(size_t));
	}
	
	for (i = 0; i < data_len ; ++i)
	{
		CBuffRead(c_buff, &buffer[i], sizeof(size_t));

		if (buffer[i] != data[i])
		{	
			printf("\033[1;31m- Read function isn't workin\033[0m\n\n");
		}
		else
		{
			(printf("\033[1;32m- Read function works\033[0m\n"));
		}
	}

	CBuffDestroy(c_buff);
}


