#ifdef BIT_ARRAY_H__
#define BIT_ARRAY_H__


typedef struct BitArray BitArray;


struct BitArray {
    unsigned char*	buffer;
    unsigned int 	buffer_size;
    unsigned int 	length;
};


BitArray create_bit_array(int n);

void set_bit_array(BitArray* arr, int idx);

void unset_bit_array(BitArray* arr, int idx);

bool get_bit_array(BitArray arr, int idx);

void print_bit_array(BitArray arr);


#endif
