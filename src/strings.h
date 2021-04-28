#ifndef MC_STRINGS_H_
#define MC_STRINGS_H_

#include <stdbool.h>

typedef struct Vector Vector;

struct Vector {
    char* 	buffer;
    int 	size;
    int 	capacity;
};

int mc_consume(char** _p);

int mc_char_size(char* _p);

// support ' ', '\t'
bool mc_skip_space(char** _p);

bool mc_is_skip(char* _p);

bool is_contains(int _c, const char* _cmp);

bool is_startwith(char* _head, const char* _word);

// vector
Vector* mc_create_vector(int _size);
void mc_free_vector(Vector* _v);

// set value
void mc_set_vector(Vector* _v, void* _p, int _n);

// append buffer
void mc_append_vector(Vector* _v, void* _p, int _n);

// _v2 is appended to the end of _v1
Vector* mc_merge_vector(Vector* _v1, Vector* _v2);

void mc_fit_vector(Vector* _v);

// copy
Vector* mc_copy_vector(Vector* _v);

#endif
