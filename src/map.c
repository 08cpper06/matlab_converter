#include "map.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MapRoot* mc_create_map(const char* key[], int* val, int n)
{
    MapNode* node = (MapNode*)calloc(sizeof(MapNode), n);
    for (int i = 0; key[i] != NULL; ++i) {
	node[i].key = (char*)key[i];
	node[i].val = val[i];
    }
    MapRoot* root = (MapRoot*)calloc(sizeof(MapRoot), 1);;
    root->tree = node;
    root->size = n;
    return root;
}

int mc_find_data(MapRoot* node, const char* key)
{
    int i, n = node->size;
    for (i = 0; i < n; ++i) 
	if(strcmp(node->tree[i].key, key)) break;
    
    if (i == n) return -1;
    return node->tree[i].val;
}

void mc_free_map(MapRoot* _list)
{
    free(_list->tree);
    free(_list);
}

