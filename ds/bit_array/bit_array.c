/**
 * @author Mai Aloni 
 * @version 07-08-2019
 *
 * compile: gd -I include/  tests/test_bit_array.c bit_array.c
 */

#include <stdio.h> /*size_t*/
#include <limits.h> /*_CHAR__BIT_*/
#include "bit_array.h" 

#define BITS_IN_BYTE  (__CHAR_BIT__)
#define BITS_IN_WORD (sizeof(size_t) * BITS_IN_BYTE)
#define WORD_SIZE sizeof(size_t)
#define BYTES_IN_WORD (sizeof(size_t))
#define MAX_ASCII 256

bit_array_t BitArrSetOn(bit_array_t bit_array, size_t index)
{
	size_t mask = 1ul;
	
	/*'|' operator helps us to set the specific position to 1 since (1 | 0) == 1*/	
	return bit_array|= mask << index;
}


bit_array_t BitArrSetOff(bit_array_t bit_array, size_t index)
{

	size_t mask = 1ul;
	
	/*'&' operator helps us to set the specific position to zero since (1 & 0) == 0*/
	return bit_array&= ~(mask << index);
}
   

bit_array_t BitArrSet(bit_array_t bit_array, size_t index, bit_status_t status)
{
	switch (status)
	{
		case ON:
					bit_array = BitArrSetOn(bit_array, index);
					break;

		case OFF:
					bit_array = BitArrSetOff(bit_array, index);
					break;
	}
	
	return bit_array;
}


bit_array_t BitArrSetAll(bit_array_t bit_array)
{	
	return bit_array |= ~(0LU);
}


bit_array_t BitArrResetAll(bit_array_t bit_array)
{
	bit_array = 0x0ul;
	
	return bit_array;
}


bit_array_t BitArrFlipBit(bit_array_t bit_array)
{
	return ~bit_array;
}


bit_array_t BitArrRotateLeft(bit_array_t bit_array, size_t number_of_rotates)
{
	size_t num_of_rotates = number_of_rotates % BITS_IN_WORD; 

	return ((bit_array << num_of_rotates) | bit_array >> 
      			(BITS_IN_WORD - num_of_rotates));

}


bit_array_t BitArrRotateRight(bit_array_t bit_array, size_t number_of_rotates)
{
	size_t num_of_rotates = number_of_rotates % BITS_IN_WORD;

	return ((bit_array >> num_of_rotates) | bit_array << 
            (BITS_IN_WORD - num_of_rotates));
}
	

bit_array_t BitArrMirror(bit_array_t bit_array)
{

	size_t mask = 1;
	size_t mirrored_num = 0;
	size_t i = 0;
	
	
	for(i = 0; i < BITS_IN_WORD; i++)
	{
		mirrored_num <<= mask;

		if (1 == (bit_array & mask))
		{
			mirrored_num |= 1;
		}

		bit_array >>= mask;
	}
	
	/*shift left according count*/
	/*mirrored_num <<= BITS_IN_WORD;*/
	
	return mirrored_num;
}



int BitArrIsBitOn(bit_array_t bit_array, size_t index)
{

	return(!BitArrIsBitOff(bit_array,index));
}


int BitArrIsBitOff(bit_array_t bit_array, size_t index)
{	
	size_t mask = 1ul;
	
	return (0 == (bit_array & (mask << index)));
}


int BitArrAreAllBitsOn(bit_array_t bit_array)
{
	return (bit_array == ~(0x0ul)); 
}


int BitArrAreAllBitsOff(bit_array_t bit_array)
{
	return (bit_array == 0LU);
}


size_t BitArrCountBitsOn(bit_array_t bit_array)
{
	size_t count_set_bits = 0;
	
	while (0 != bit_array)
	{
	
		bit_array &= (bit_array - 1);
		++count_set_bits;
	}
	
	return count_set_bits;
}


size_t BitArrCountBitsOff(bit_array_t bit_array)
{
	return BITS_IN_WORD-(BitArrCountBitsOn(bit_array));
}



char *BitArrToString(bit_array_t bit_array, char *string)
{
	size_t mask = 1LU; 
	char *str_ptr = string; 
	size_t i = 0;

	string += BITS_IN_WORD; 
	*string = '\0';
	--string;
	
	for (i = 0; i < BITS_IN_WORD; i++)
	{
		*string = (mask & bit_array) + '0';
		bit_array >>= 1;		
		--string;
	}
	
	return str_ptr;
}

static size_t CountBitsOnLUT(unsigned char index) 
{
	unsigned char count_set_bits_lut[MAX_ASCII] = 
	{	
		0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 
		3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 
		3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 
		4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 
		3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 
		6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 
		4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 
		6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 
		3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 
		4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 
		6, 7, 6, 7, 7, 8
	};

	return count_set_bits_lut[index];

}


size_t BitArrCountBitsOnLUT(bit_array_t bit_array)
{
	size_t count = 0;
	size_t i = 0;
	unsigned char *ptr_char_lut = (unsigned char*)&bit_array;
	
	for (i = 0; i < BITS_IN_BYTE; i++)
	{
		count += CountBitsOnLUT(*ptr_char_lut);
		ptr_char_lut++;
	}
	
	return count;
}


static unsigned char BitMirrorLUT(unsigned char index) 
{

	unsigned char bit_mirror_table[MAX_ASCII] =
	{
		0x0, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50,
		0xd0, 0x30, 0xb0, 0x70, 0xf0, 0x8, 0x88, 0x48, 0xc8, 0x28, 0xa8,
		0x68, 0xe8, 0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8, 0x4,
		0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4, 0x14, 0x94, 0x54, 0xd4,
		0x34, 0xb4, 0x74, 0xf4, 0xc, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c,
		0xec, 0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc, 0x2, 0x82,
		0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2, 0x12, 0x92, 0x52, 0xd2, 0x32,
		0xb2, 0x72, 0xf2, 0xa, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea, 
		0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa, 0x6, 0x86, 0x46, 
		0xc6, 0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6,
		0x76, 0xf6, 0xe, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee, 0x1e,
		0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe, 0x1, 0x81, 0x41, 0xc1,
		0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71,
		0xf1, 0x9, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9, 0x19, 0x99, 
		0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9, 0x5, 0x85, 0x45, 0xc5, 0x25, 
		0xa5, 0x65, 0xe5, 0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
		0xd, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d,
		0xdd, 0x3d, 0xbd, 0x7d, 0xfd, 0x3, 0x83, 0x43, 0xc3, 0x23, 0xa3,
		0x63, 0xe3, 0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3, 0xb,
		0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb, 0x1b, 0x9b, 0x5b, 0xdb,
		0x3b, 0xbb, 0x7b, 0xfb, 0x7, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 
		0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7, 0xf, 0x8f, 
		0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f, 0x5f, 0xdf, 0x3f,
		0xbf, 0x7f, 0xff, 
	};

	return bit_mirror_table[index];
}




size_t BitArrBitMirrorLUT(bit_array_t bit_array)
{
	unsigned char *ptr_byte = (unsigned char*)&bit_array; 
	unsigned char temp_byte = 0;
	size_t i = 0;

	for (i = 0; i < (WORD_SIZE/2); ++i)
	{
		temp_byte = BitMirrorLUT(ptr_byte[i]);
		ptr_byte[i] = BitMirrorLUT(ptr_byte[BYTES_IN_WORD - 1 - i]);
		ptr_byte[BYTES_IN_WORD - 1 - i] = temp_byte;
	}

	return bit_array;
}











