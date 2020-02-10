#include <stdio.h>
#include "bit_array.h"

#define SUCCESS printf("\033[1;32mTest is passed\033[0m\n")
#define FAILURE printf("\033[1;31mTest is failed\033[0m\n")


typedef enum {IS_POSITIVE = 1, IS_NEGATIVE = -1} check_sign;

#define BASE 2
#define STR_LENGTH 150


/*private functions*/
size_t Atoi(char* str);

size_t BitArrCountBitsOnLUT(bit_array_t bit_array);
size_t BitArrBitMirrorLUT(bit_array_t bit_array);

/*tests functions*/
void TestBitArrSetOn();
void TestBitArrSetOff();
void TestBitArrSet();
void TestBitArrSetAll();
void TestBitArrResetAll();
void TestBitArrFlipBit();
void TestBitArrRotateLeft();
void TestBitArrMirror();
void TestBitArrMirrorLUT();
void TestLutCountBitsOn();
void TestBitArrRotateRight();
void TestBitArrIsBitOn();
void TestBitArrIsBitOff();
void TestBitArrAreAllBitsOn();
void TestBitArrAreAllBitsOff();
void TestBitArrCountBitsOn();
void TestLutCountBitsOn();
void TestBitArrCountBitsOff();
void TestBitArrToString();


 
int main()
{
	
	TestBitArrSetOn();
	TestBitArrSetOff();
	TestBitArrSet();
	TestBitArrSetAll();
	TestBitArrResetAll();
	TestBitArrFlipBit();
	TestBitArrRotateLeft();
	TestBitArrMirror();
	TestBitArrMirrorLUT();
	TestBitArrRotateRight();
	TestBitArrIsBitOn();
	TestBitArrIsBitOff();
	TestBitArrAreAllBitsOn();
	TestBitArrAreAllBitsOff();
	TestLutCountBitsOn();
	TestBitArrCountBitsOff();
	TestBitArrToString();
	
	return 0;
}

void TestBitArrSetOn()
{
	bit_array_t test_array[] = {0x1, 0x3, 0x8000000000000000};

	size_t tests_indexes[] = {0, 1, 63};

	size_t expected_results[] = {0x1, 0x3,  0x8000000000000000};

	size_t num_of_tests = sizeof(tests_indexes)/sizeof(tests_indexes[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrSetOn:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == BitArrSetOn(test_array[i],tests_indexes[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}
}


void TestBitArrSetOff()
{
	bit_array_t test_array[] = {0x1, 0x3, 0x8000000000000000};

	size_t tests_indexes[] = {0, 1, 63};

	size_t expected_results[] = {0x0, 0x1,  0x0};

	size_t num_of_tests = sizeof(tests_indexes)/sizeof(tests_indexes[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrSetOff:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == BitArrSetOff(test_array[i],tests_indexes[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}
}


void TestBitArrSet()
{
	
	bit_array_t test_array[] = {0x0, 0x1, 0x8000000000000000};
	size_t tests_indexes[] = {0,1,63};
	bit_status_t statuses [] = {0,0,1};
	bit_array_t expected_results[] =  {0x0, 0x1, 0x8000000000000000};
	size_t num_of_tests = sizeof(tests_indexes)/sizeof(tests_indexes[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrSet:\n");	

	for (i = 0; i < num_of_tests; ++i)
	{
		if ((expected_results[i]) == (BitArrSet(test_array[i],tests_indexes[i], statuses[i]))) 
		{
			SUCCESS;
		}
		else
		{
			FAILURE;
		}
	}

}


void TestBitArrSetAll()
{

	bit_array_t test_array[] = {0x2, 0x7, 0x8000000000000000};

	size_t expected_results[] = {(~0x0), (~0x0), (~0x0)};

	size_t num_of_tests = sizeof(test_array)/sizeof(test_array[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrSetAll:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == BitArrSetAll(test_array[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}

}


void TestBitArrResetAll()
{

	bit_array_t test_array[] = {0x0, 0x7, 0x8000000000000000};

	size_t expected_results[] = {0x0, 0x0, 0x0};

	size_t num_of_tests = sizeof(test_array)/sizeof(test_array[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrResetAll:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == BitArrResetAll(test_array[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}		
}



void TestBitArrFlipBit()
{
	bit_array_t test_array[] = {0x0, 0x1, 0x8000000000000000};

	size_t num_of_tests = sizeof(test_array)/sizeof(test_array[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrFlipBit:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(~test_array[i] == BitArrFlipBit(test_array[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}
}


void TestBitArrRotateLeft()
{

	bit_array_t test_array[] = {0x0, 0x0000000000000001, 0x8000000000000000};

	size_t number_of_rotates[] = {1, 1,  2};

	size_t expected_results[] = {0x0, 0x2, 0x2};

	size_t num_of_tests = sizeof(test_array)/sizeof(test_array[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrRotateLeft:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == BitArrRotateLeft(test_array[i],number_of_rotates[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}
}


void TestBitArrMirror()
{
	bit_array_t test_array[] = {0x0, 0x1, 0x8000000000000000};

	size_t expected_results[] = {0x0, 0x8000000000000000, 0x1};

	size_t num_of_tests = sizeof(test_array)/sizeof(test_array[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrMirror:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == BitArrMirror(test_array[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}	
}


void TestBitArrMirrorLUT()
{

	bit_array_t test_array[] = {0x0, 0x8000000000000000};

	size_t expected_results[] = {0x0, 0x1};

	size_t num_of_tests = sizeof(test_array)/sizeof(test_array[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrMirror:\n\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == (size_t)BitArrBitMirrorLUT(test_array[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}		
}


void TestBitArrRotateRight()
{

	bit_array_t test_array[] = {0x3, 0x0, 0x8000000000000000};

	size_t number_of_rotates[] = {1, 2,  1};

	size_t expected_results[] = {0x8000000000000001,0x0, 0x4000000000000000};

	size_t num_of_tests = sizeof(test_array)/sizeof(test_array[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrRotateRight:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == BitArrRotateRight(test_array[i],number_of_rotates[i]))
		{
			SUCCESS;
			
		}
		
		else
		{
			FAILURE;
		}
	}	
}



void TestLutCountBitsOn()
{

	bit_array_t test_array[] = {0x1, 0x9, 0xffffffffffffffff};

	size_t expected_results[] = {1, 2, 64};

	size_t num_of_tests = sizeof(test_array)/sizeof(test_array[0]);
	size_t i = 0;
	
	printf("\nTest for LutCountBitsOn:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == BitArrCountBitsOnLUT(test_array[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}		
}

void TestBitArrIsBitOn()
{
	bit_array_t test_array[] = {0x1, 0x7, 0x8000000000000000};

	size_t tests_indexes[] = {0, 1, 63};

	int expected_results[] = {0x1, 0x1,  0x1};

	size_t num_of_tests = sizeof(tests_indexes)/sizeof(tests_indexes[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrIsBitOn:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == BitArrIsBitOn(test_array[i],tests_indexes[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}	
		
}



void TestBitArrIsBitOff()
{
	bit_array_t test_array[] = {0x1, 0x3, 0x8000000000000000};

	size_t tests_indexes[] = {0, 1, 63};

	int expected_results[] = {0x0, 0x0,  0x0};

	size_t num_of_tests = sizeof(tests_indexes)/sizeof(tests_indexes[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrIsBitOff:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == BitArrIsBitOff(test_array[i],tests_indexes[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}	
		
}


void TestBitArrAreAllBitsOn()
{
	bit_array_t test_array[] = {0x1, 0x3, 0x8000000000000000, 0xFFFFFFFFFFFFFFFF};

	size_t expected_results[] = {0x0, 0x0,  0x0,0x1};

	size_t num_of_tests = sizeof(test_array)/sizeof(test_array[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrAreAllBitsOn:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == (size_t)BitArrAreAllBitsOn(test_array[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}
}



void TestBitArrAreAllBitsOff()
{
		bit_array_t test_array[] = {0x1, 0x3, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF};

	size_t expected_results[] = {0x0, 0x0,  0x1,0x0};

	size_t num_of_tests = sizeof(test_array)/sizeof(test_array[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrAreAllBitsOff:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == (size_t)BitArrAreAllBitsOff(test_array[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}
}

void TestBitArrCountBitsOn()
{
	bit_array_t test_array[] = {0x1, 0x3, 0x8000000000000000};

	size_t expected_results[] = {1, 2, 1};

	size_t num_of_tests = sizeof(test_array)/sizeof(test_array[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrCountBitsOn:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == BitArrCountBitsOn(test_array[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}
}




void TestBitArrCountBitsOff()
{
	bit_array_t test_array[] = {0x1, 0x3, 0x8000000000000000};

	size_t expected_results[] = {63, 62, 63};

	size_t num_of_tests = sizeof(test_array)/sizeof(test_array[0]);
	size_t i = 0;
	
	printf("\nTest for BitArrCountBitsOff:\n");
	
	for (i = 0; i < num_of_tests; i++)
	{
		if(expected_results[i] == BitArrCountBitsOff(test_array[i]))
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}
}


size_t Atoi(char* str)
{
	size_t result = 0;
	size_t sign = IS_POSITIVE;
	
	/*if the number is negative, change the sign from positive to negative*/
	if ('-' == *str) 
	{
		sign  = IS_NEGATIVE;
		++str;
	}

	while ('\0'!= *str)
	{
		result *= BASE;
		
		/*converts str to int*/
		if (('0' <= *str) && ('9' >= *str))
		{
			result += (int)(*str-'0');
		}
		else if (('A' <= *str) && ('Z' >= *str)) 	
		{
			result += (int)(*str + 10 -'A');
		}
		
		++str;
	}

	return sign == IS_POSITIVE ? result : -result; 
}




void TestBitArrToString()
{
		
	size_t test_array[] = {0x0, 0x1, 0x3, 0x8000000000000000};
	size_t num_of_tests = sizeof(test_array)/sizeof(test_array[0]);
	char str_buffer[STR_LENGTH];
	size_t i = 0;
	
	printf("\nTest for BitArrToString:\n");	

	for (i = 0; i < num_of_tests; i++)
	{
		if((size_t)Atoi(BitArrToString(test_array[i],str_buffer)) == test_array[i])
		{
			SUCCESS;
		}
		
		else
		{
			FAILURE;
		}
	}
}






