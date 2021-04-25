#ifndef TRIE_TREE_H__
#define TRIE_TREE_H__


typedef struct TrieTree TrieTree;
typedef struct TrieTreeNode TrieTreeNode;
typedef struct TrieTreeFindState TrieTreeFindState;


struct TrieTree {
    BitArray 	array;
    char*	wordlist;
};

struct TrieTreeFindState {
    char* 	itr;
    int 	val;
    bool	is_finish_scan;
    bool	is_fit;
};

TrieTree* create_trie_tree();

void add_trie_tree(const char* key, int val);

int find_trie_tree(const char* key);

TrieTreeFindState find_sequential_trie_tree(char c, TrieTreeFindState state);

void print_trie_tree(TrieTree* tree);

#endif
