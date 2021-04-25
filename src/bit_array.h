#ifndef MC_BIT_ARRAY_H__
#define MC_BIT_ARRAY_H__


#include <stdbool.h>

typedef struct BitArray BitArray;


struct BitArray {
    unsigned char*	buffer;
    unsigned int 	buffer_size;
    unsigned int 	length;
};


BitArray mc_create_bit_array(int n);

void mc_set_bit_array(BitArray* arr, int idx);

void mc_unset_bit_array(BitArray* arr, int idx);

bool mc_get_bit_array(BitArray arr, int idx);

void mc_free_bit_array(BitArray* arr);

void mc_print_bit_array(BitArray arr);


#endif
