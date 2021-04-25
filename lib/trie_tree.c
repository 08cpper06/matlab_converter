#include "trie_tree.h"


static int get_node_num(BitArray arr, int idx)
{
    int size = array.buffer_size;
    unsigned int* buf = array.buffer;
    int n = size / sizeof(unsigned int), rest = size % sizeof(unsigned int);
    int count = 0;
    for (int i = 0; i < n; ++i) {
	*buf   = (*buf & 0x55555555) + (*buf >> 1 & 0x55555555);
	*buf   = (*buf & 0x33333333) + (*buf >> 2 & 0x33333333);
	*buf   = (*buf & 0x0f0f0f0f) + (*buf >> 4 & 0x0f0f0f0f);
	*buf   = (*buf & 0x00ff00ff) + (*buf >> 8 & 0x00ff00ff);
	count += (*buf & 0x0000ffff) + (*buf >>16 & 0x0000ffff);
	buf++;
    }
    unsigned char c = array.buffer[array.buffer_size - 1];
    if (c & 0x01) ++count;
    if (c & 0x02) ++count;
    if (c & 0x04) ++count;
    if (c & 0x08) ++count;
    if (c & 0x10) ++count;
    if (c & 0x20) ++count;
    if (c & 0x40) ++count;
    if (c & 0x80) ++count;
    return count;
}

/*
TrieTree* create_trie_tree()
{
    TrieTree* tree = (TrieTree*)calloc(sizeof(TrieTree*), 1);
    tree.array = create_bit_array(2);
    // to bit array: [0, 1]
    set_bit_array(&(tree.array), 0);
    tree.wordlist = (char*)calloc(sizeof(char), 2);
    return tree;
}

void add_trie_tree(const char* key, int val)
{
    if ()
}

int find_trie_tree(const char* key)
{
    ;
}

TrieTreeFindState find_sequential_trie_tree(char c, TrieTreeFindState state)
{
    ;
}*/

static void print_array(TrieTree* tree, int offset) 
{
    printf("[");
    char c = ' ';
    for (int i = 0; i < arr.length; ++i) {
	if (c == ',')
	    printf("%c", c);
	c = ',';
	// printf("%c", get_bit_array(arr, i) ? '1' : '0');
    }
    printf("]\n");
}

void print_trie_tree(TrieTree* tree)
{
    int offset = 3, ch_n = 0;
    while(offset < tree->array.length) {
	for (;!get_bit_array(tree->array, ch_n + offset); ++ch_n);
	if (!ch_n) continue;
	for(int i = 0; i < ch_n; ++i) {
	    // print list
	    ;

	}// end of for
    }// end of while
}
