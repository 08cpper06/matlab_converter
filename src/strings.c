#include "strings.h"
#include "lexer.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int mc_consume(char** _p)
{
    if (**_p != '\0')
	*_p = *_p + mc_char_size(*_p);
    return (int)**_p;
}

int mc_char_size(char* _p)
{
    // TODO : support utf-8
    return 1;
}

bool mc_skip_space(char** _p)
{
    bool flag = false;
    while (mc_is_skip(*_p)) {
	++(*_p);
	flag = true;
    }
    return flag;
}

bool mc_is_skip(char* _p)
{
    if (isspace((int)*_p) && *_p != '\n') return true;
    return false;
}

bool is_contains(int _c, const char* _cmp)
{
    for (char* p = (char*)_cmp; *p != '\0'; ++p)
	if (_c == (int)(*p))
	    return true;
    return false;
}

bool is_startwith(char* _head, const char* _word)
{
    for(;;) {
	// reach the end of _word
	if (!*_word) break;
	// reach the end of _head before reach the end of _word.
	if (!*_head) return false;
	if (*_head != *_word) return false;
	++_head; ++_word;
    }
    return true;
}

Vector* mc_create_vector(int _size)
{
    Vector* vec = (Vector*)calloc(sizeof(Vector), 1);
    vec->buffer = (char*)calloc(sizeof(char), _size);
    vec->size = 0;
    vec->capacity = _size;
    return vec;
}

void mc_free_vector(Vector* _v)
{
    free(_v->buffer);
    free(_v);
}

void mc_set_vector(Vector* _v, void* _p, int _n)
{
    // too short memory size
    if (_v->capacity < _n) {
	// reallocate necessary buffer size
	void* ptr = realloc(_v->buffer, _v->capacity * 2);
	if (!ptr)
	    mc_error("cannot realloc memory for vector's buffer(%d) at set_vec", _v->size);
	_v->buffer = ptr;
	_v->capacity = _v->capacity * 2;
    }
    memcpy(_v->buffer, _p, _n);
    _v->size = _n;
}

// append buffer
void mc_append_vector(Vector* _v, void* _p, int _n)
{
    int rest = _v->capacity - _v->size;
    // too short memory size
    if (rest <= _n) {
	// reallocate necessary buffer size
	void* ptr = realloc(_v->buffer, _v->capacity * 2);
	if (!ptr)
	    mc_error("cannot realloc memory for vector's buffer(%d) at append_vec", _v->size);
	_v->buffer = ptr;
	_v->capacity = _v->capacity * 2;
    }
    char* buf = (char*)(_v->buffer);
    char* head = &(buf[_v->size]);
    memcpy(head, _p, _n);
    _v->size += _n;
}

// _v2 is appended to the end of _v1
Vector* mc_merge_vector(Vector* _v1, Vector* _v2)
{
    Vector* vec = mc_create_vector(_v1->size + _v2->size);
    memcpy(vec->buffer, _v1->buffer, _v1->size);
    char* p = (char*)(vec->buffer);
    memcpy(&(p[_v1->size]), _v2->buffer, _v2->size);
    return vec;
}

// copy
Vector* mc_copy_vector(Vector* _v)
{
    Vector* _v2 = mc_create_vector(_v->size);
    memcpy(_v2->buffer, _v->buffer, _v->size);
    return _v2;
}
