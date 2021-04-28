#ifndef MC_MEMORY_H__
#define MC_MEMORY_H__

#include <stddef.h>

// release all memory allocated by std library when throw error by mc_error() etc...

void* mc_malloc(size_t size);

void* mc_calloc(size_t n, size_t size);

void mc_free(void* ptr);

void mc_all_free();

// if return not 0, memory leak!!
int mc_check_mem_leak();

// if return not 0 by mc_check_mem_leak(), print information
void mc_print_mem_leak();


void mc_print_mem_info();


#endif
