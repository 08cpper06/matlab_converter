#ifndef MC_MAP_H_
#define MC_MAP_H_

#include <stdbool.h>

typedef struct MapNode MapNode;
typedef struct MapRoot MapRoot;

struct MapNode {
    char* 	key;
    int 	val;
};

struct MapRoot {
    MapNode* 	tree;
    int 	size;
};

MapRoot* mc_create_map(const char* key[], int* val, int n);

int mc_find_data(MapRoot* node, const char* key);

void mc_free_map(MapRoot* _list);

#endif
