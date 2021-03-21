#ifndef MC_MAP_H_
#define MC_MAP_H_

#include <stdbool.h>

typedef struct MapNode MapNode;

struct MapNode {
    char* 	key;
    int 	val;
};

MapNode* mc_create_map(const char* key[], int* val);

int mc_find_data(MapNode* node, const char* key);

void mc_free_map(MapNode* _list);

#endif
