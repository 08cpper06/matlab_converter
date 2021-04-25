#include "bit_array.h"


BitArray create_bit_array(int n)
{
    BitArray arr;
    arr.buffer_size = (n + 8 - 1) / 8;
    arr.buffer = (unsigned char*)calloc(sizeof(unsigned char), arr.buffer_size);
    arr.length = n;
    return arr;
}

void set_bit_array(BitArray* arr, int idx)
{
    int n = idx / 8;
    if (arr->buffer_size < n || idx > arr->length)return;
    arr->buffer[n] |= 0x01 << (idx % 8);
}

void unset_bit_array(BitArray* arr, int idx)
{
    int n = idx / 8;
    if (arr->buffer_size < n || idx > arr->length)return;
    arr->buffer[n] &= ~(0x01 << (idx % 8));
}

bool get_bit_array(BitArray arr, int idx) 
{
    int n = idx / 8;
    if (arr.buffer_size < n || idx > arr.length)return false;
    return arr.buffer[n] & 0x01 << (idx % 8);
}

void print_bit_array(BitArray arr)
{
    printf("[");
    char c = ' ';
    for (int i = 0; i < arr.length; ++i) {
	if (c == ',')
	    printf("%c", c);
	c = ',';
	printf("%c", get_bit_array(arr, i) ? '1' : '0');
    }
    printf("]\n");
}
