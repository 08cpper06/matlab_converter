#ifndef MC_LIST_H__
#define MC_LIST_H__


typedef struct ListNode ListNode;
typedef struct List List;


struct ListNode {
    void* 	ptr;
    ListNode* 	next;
    ListNode* 	prev;
};

struct List {
    ListNode* 	first;
    ListNode* 	last;
    int 	size;
};

List* mc_create_list();
void mc_free_list(List* _list);

void* mc_back(List* _list);
void* mc_front(List* _list);

void* mc_pop_back(List* _list);
void* mc_pop_front(List* _list);

void mc_push_back(void* _ptr, List* _list);
void mc_push_front(void* _ptr, List* _list);


#endif
