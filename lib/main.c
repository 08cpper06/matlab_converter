#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bit_array.h"
#include "trie_tree.h"



int main() {
    BitArray arr = create_bit_array(64);
    print_bit_array(arr);
    set_bit_array(&arr, 4);
    print_bit_array(arr);
    unset_bit_array(&arr, 4);
    print_bit_array(arr);
    return 0;
}
