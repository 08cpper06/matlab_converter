#include "bit_array.h"
#include <stdio.h>
#include <stdlib.h>

BitArray mc_create_bit_array(int n)
{
    BitArray arr;
    arr.buffer_size = (n + 8 - 1) / 8;
    arr.buffer = (unsigned char*)calloc(sizeof(unsigned char), arr.buffer_size);
    arr.length = n;
    return arr;
}

void mc_free_bit_array(BitArray* arr)
{
    if (!arr) return;
    free(arr->buffer);
    arr->buffer_size = 0;
    arr->length = 0;
}

void mc_set_bit_array(BitArray* arr, int idx)
{
    int n = idx / 8;
    if (arr->buffer_size < n || idx > arr->length)return;
    arr->buffer[n] |= 0x01 << (idx % 8);
}

void mc_unset_bit_array(BitArray* arr, int idx)
{
    int n = idx / 8;
    if (arr->buffer_size < n || idx > arr->length)return;
    arr->buffer[n] &= ~(0x01 << (idx % 8));
}

bool mc_get_bit_array(BitArray arr, int idx) 
{
    int n = idx / 8;
    if (arr.buffer_size < n || idx > arr.length)return false;
    return arr.buffer[n] & 0x01 << (idx % 8);
}

void mc_print_bit_array(BitArray arr)
{
    printf("[");
    char c = ' ';
    for (int i = 0; i < arr.length; ++i) {
	if (c == ',')
	    printf("%c", c);
	c = ',';
	printf("%c", mc_get_bit_array(arr, i) ? '1' : '0');
    }
    printf("]\n");
}
