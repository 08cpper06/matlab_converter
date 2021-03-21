#include "map.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MapNode* mc_create_map(const char* key[], int* val)
{
    MapNode* node = (MapNode*)calloc(sizeof(MapNode), sizeof(val)/sizeof(val[0]) - sizeof(val[0]));
    for (int i = 0; key[i] != NULL; ++i) {
	node[i].key = (char*)key[i];
	node[i].val = val[i];
    }
    return node;
}

int mc_find_data(MapNode* node, const char* key)
{
    int n = sizeof(node) / sizeof(node[0]);
    int i;
    for (i = 0; i < n; ++i) 
	if(strcmp(node[i].key, key)) break;
    
    if (i == n) return -1;
    return node[i].val;
}

void mc_free_map(MapNode* _list)
{
    free(_list);
}

