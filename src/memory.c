#include "memory.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifndef MC_THREAD_LOCAL
#define MC_THREAD_LOCAL __thread
#endif

typedef struct MemBlock MemBlock;
typedef struct MemListNode MemListNode;

struct MemBlock {
    int 		size;
    MemListNode* 	node;
};

struct MemListNode {
    MemBlock*		info;
    MemListNode* 	prev;
    MemListNode* 	next;
};


MC_THREAD_LOCAL MemListNode root = { NULL, NULL, NULL };
MC_THREAD_LOCAL MemListNode* last = NULL;
MC_THREAD_LOCAL int node_num = 0;

static _Noreturn void mc_mem_error(char* _fmt, ...)
{
    va_list ap;
    va_start(ap, _fmt);
    vfprintf(stderr, _fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

void* mc_malloc(size_t size)
{
    MemBlock* block = (MemBlock*)malloc(sizeof(MemBlock) + size);
    if (!block) mc_mem_error("cannot allocate MemBlock at mc_malloc()");
    MemListNode* node = (MemListNode*)malloc(sizeof(MemListNode));
    if (!node) mc_mem_error("cannot allocate MemListNode at mc_malloc()");
    
    block->size 	= size;
    block->node 	= node;

    node->info		= block;

    if (!last) last = &root;
    last->next		= node;
    node->prev		= last;
    last 			= node;
    ++node_num;
    return (void*)block + sizeof(MemBlock);
}

void* mc_calloc(size_t n, size_t size)
{
    MemBlock* block = (MemBlock*)malloc(sizeof(MemBlock) + n * size);
    if (!block) mc_mem_error("cannot allocate MemBlock at mc_calloc()");
    MemListNode* node = (MemListNode*)malloc(sizeof(MemListNode));
    if (!node) mc_mem_error("cannot allocate MemListNode at mc_calloc()");
    
    block->size 	= size;
    block->node 	= node;

    node->info		= block;

    if (!last) last = &root;
    last->next		= node;
    node->prev		= last;
    last 		= node;

    void* ret = (void*)block + sizeof(MemBlock);
    memset(ret, 0, n * size);
    ++node_num;
    return ret;
}

void mc_free(void* ptr)
{
    if (!ptr) return;
    MemBlock* block = (MemBlock*)(ptr - sizeof(MemBlock));
    MemListNode* node = block->node;
    MemListNode* prev = node->prev;
    MemListNode* next = node->next;
    if (next) next->prev = prev;
    if (prev) prev->next = next;
    if (last == node) last = prev;
    free(block);
    free(node);
    --node_num;
}

void mc_all_free()
{
    if (!last) return;
    for (;last->prev != &root;) {
		mc_free((void*)(last->info) + sizeof(MemBlock));
    }
    mc_free((void*)(last->info) + sizeof(MemBlock));
}

int mc_check_mem_leak()
{
    if (!last || last == &root) return 0;
    int size = 0;
    MemListNode* p = last;
    for (; p->prev;) {
		size += p->info->size;
		p = p->prev;
    }
    return size;
}

void mc_print_mem_leak()
{
    MemBlock* block = NULL;
    int size = 0;
    fprintf(stderr, "--- memory leak information ---\n");
    MemListNode* p = last;
    for (; p != &root;) {
		block = p->info;
		fprintf(stderr, "[size: %d]\n", block->size);
		size += block->size;
		p = p->prev;
    }
    fprintf(stderr, "%d bytes(the number of memory block: %d)\n", size, node_num);
    fprintf(stderr, "--- end of memory leak information ---\n");
}

void mc_print_mem_info()
{
    MemBlock* block = NULL;
    int size = 0;
    printf("--- memory information ---\n");
    MemListNode* p = last;
    for (; p != &root;) {
		block = p->info;
		size += block->size;
		p = p->prev;
    }
    printf("memory info structure: %lu bytes\n", (sizeof(MemBlock) + sizeof(MemListNode)) * node_num);
    printf("used memeory: %d bytes\n", size);
    printf("%lu bytes(the number of memory block: %d)\n", size + (sizeof(MemBlock) + sizeof(MemListNode)) * node_num, node_num);
    printf("--- end of memory information ---\n");
}

#undef MC_THREAD_LOCAL
