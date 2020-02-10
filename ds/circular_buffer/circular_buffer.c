/**
 * @author Mai Aloni 
 * @version 16-08-2019
 *
 * compile: gd -I include/  tests/test_circular_buffer.c circular_buffer.c
 */

#include <stdlib.h> /*malloc,free*/
#include <string.h> /*memcpy*/
#include <assert.h>/*assert*/

#include "circular_buffer.h" /*declarations of circular buffer functions*/

struct c_buff
{
	char *end;
	char *read;
	char *write;
	char is_closer_to_end;
	char start[1];
};


enum errors_e
{
	C_BUFF_CANT_WRITE_EMPTY_DATA = -1,
	C_BUFF_CANT_READ_EMPTY_DATA = -1,
	C_BUFF_IS_NOT_EMPTY = 0,
	C_BUFF_IS_EMPTY = 1
};


enum is_closer_to_end
{
	READ = 0,
	WRITE = 1
};



static void InitCBuff(c_buff_t *c_buff ,size_t capacity);


c_buff_t *CBuffCreate(size_t capacity)
{	
	c_buff_t *c_buff = malloc(sizeof(struct c_buff) + capacity -  1);
	
	if (NULL == c_buff)
	{
		free(c_buff);
		return NULL;
	}
	
	InitCBuff(c_buff, capacity);

 	return c_buff;
}


static void InitCBuff(c_buff_t *c_buff ,size_t capacity)
{
	c_buff->end = c_buff->start + capacity;
	c_buff->read = c_buff->start;
	c_buff->write = c_buff->start;
	c_buff->is_closer_to_end = WRITE;
}


void CBuffDestroy(c_buff_t *c_buff)
{
	assert (NULL != c_buff);

	free(c_buff);
	c_buff = NULL;
}


size_t CBuffCapacity(const c_buff_t *c_buff)
{
	assert (NULL != c_buff);

	return (size_t)(c_buff->end - c_buff->start);
}


size_t CBuffFreeSpace(const c_buff_t *c_buff)
{
	size_t free_space = 0;
	
	assert (NULL != c_buff);
	
	if (WRITE  == c_buff->is_closer_to_end)
	{
		free_space = ((c_buff->end - c_buff->write) +
		 (c_buff->read - c_buff->start));
	}
	
	else if (READ == c_buff->is_closer_to_end)
	{
		free_space = c_buff->read - c_buff->write;
	}
	
	return free_space;
}


ssize_t CBuffRead(c_buff_t *c_buff, void *buffer, size_t number_of_bytes)
{
	size_t diff_between_end_read =  (c_buff->end - c_buff->read);
	size_t past_written_data = CBuffCapacity(c_buff) - CBuffFreeSpace(c_buff);
	
	assert (NULL != c_buff);

	if (NULL == buffer)
	{
		return C_BUFF_CANT_READ_EMPTY_DATA;
	}

	if (number_of_bytes > past_written_data)
	{
		number_of_bytes = past_written_data;
	}

	if ((number_of_bytes < diff_between_end_read) |
			(WRITE == c_buff->is_closer_to_end)) 
	{
		memcpy(buffer, c_buff->read, number_of_bytes);
		c_buff->read += number_of_bytes;
	}

	else
	{
		memcpy(buffer,c_buff->read, diff_between_end_read);
		c_buff->read = c_buff->start;
		c_buff->is_closer_to_end = WRITE;
		memcpy(((char*)buffer + diff_between_end_read ), c_buff->read, 
				(number_of_bytes - diff_between_end_read));
		c_buff->read += (number_of_bytes - diff_between_end_read);
	}
	
	return number_of_bytes;
}	


ssize_t CBuffWrite(c_buff_t *c_buff, void *data ,size_t number_of_bytes)
{	
	size_t diff_between_write_end = c_buff->end - c_buff->write;
	size_t free_space = CBuffFreeSpace(c_buff);

	assert (NULL != c_buff);

	if (NULL == data)
	{
		return C_BUFF_CANT_WRITE_EMPTY_DATA;
	}

	/*space is not enough to write all the data. write part of the data*/
	if (number_of_bytes > free_space)
	{
		number_of_bytes = free_space;
	}
	
	/*able to write - there is enough space*/
	if ((number_of_bytes < diff_between_write_end) |
		 (READ == c_buff->is_closer_to_end))
	{
		memcpy(c_buff->write, data, number_of_bytes);
		c_buff->write += number_of_bytes;
	}
	
	else
	{	
		memcpy(c_buff->write, data, diff_between_write_end);
		c_buff->write = c_buff->start;
		c_buff->is_closer_to_end = READ;
		memcpy(c_buff->write ,((char*)data + diff_between_write_end), 
				(number_of_bytes - diff_between_write_end));
		c_buff->write += (number_of_bytes - diff_between_write_end);
	}

	return number_of_bytes;	
}


int CBuffIsEmpty(const c_buff_t *c_buff)
{
	assert (NULL != c_buff);
	
	return (((c_buff->write == c_buff->read) &&
	 		(WRITE == c_buff->is_closer_to_end)) ?
							     C_BUFF_IS_EMPTY : C_BUFF_IS_NOT_EMPTY);
}	







