#include "list.h"
#include "memory.h"
#include "lexer.h"


List* mc_create_list()
{
    List* _list = (List*)mc_calloc(1, sizeof(List));
    if (_list)
		mc_error("could not allocate List structure");
    _list->first = NULL;
    _list->last = NULL;
    _list->size = 0;
    return _list;
}

void mc_free_list(List* _list)
{
    ListNode* node = _list->first;
    ListNode* tmp = node->next;
    for (;;) {
		mc_free(node);
		if (!tmp)
			break;
		node = tmp;
    }
    mc_free(_list);
}

void* mc_back(List* _list)
{
    if (!_list)
		mc_error("provided NULL to back()");
    return _list->last;
}

void* mc_front(List* _list)
{
    if (!_list)
		mc_error("provided NULL to front()");
    return _list->first;
}

void* mc_pop_back(List* _list)
{
    if (!_list || _list->size == 0)
		return NULL;
    void* p = mc_back(_list);

    ListNode* node = _list->last;
    _list->last = node->prev;
    if (_list->last)
		_list->last->next = NULL;
    mc_free(node);
    _list->size -= 1;
    return p;
}

void* mc_pop_front(List* _list)
{
    if (!_list || _list->size == 0)
		return NULL;
    void* p = mc_front(_list);

    ListNode* node = _list->last;
    _list->first = node->next;
    if (_list->first)
		_list->first->prev = NULL;
    mc_free(node);
    _list->size -= 1;
    return p;
}

static ListNode* insert(void* _ptr, ListNode* _prev, ListNode* _next)
{
    ListNode* node = mc_calloc(1, sizeof(ListNode));
    if (!node)
		mc_error("could not allocate ListNode");
    node->prev = _prev;
    node->next = _next;
    node->ptr  = _ptr;

    if (_prev)
		_prev->next = node;
    if (_next)
		_prev->prev = node;
    return node;
}

void mc_push_back(void* _ptr, List* _list)
{
    ListNode* prev = NULL;
    if (_list->last)
		prev = _list->last->prev;
    ListNode* node = insert(_ptr, _list->last, prev);
    _list->last = node;
    _list->size += 1;
}

void mc_push_front(void* _ptr, List* _list)
{
    ListNode* next = NULL;
    if (_list->first)
		next = _list->first->next;
    ListNode* node = insert(_ptr, next, _list->first);
    _list->first = node;
    _list->size += 1;
}
