#ifndef MC_PARSER_H__
#define MC_PARSER_H__

#include "lexer.h"
#include "list.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct NameInfo NameInfo;
typedef struct STNode STNode;
typedef struct STRoot STRoot;


typedef enum {
    AST_NONE,
} ASTType;

struct NameInfo {
    int*	dimension;
    int 	dim_size;

    // mangle or nomangle is undecided now
    Vector*	name;
    bool 	is_checked_define;// if this is function or not defined, searching for the other file

    // TODO: add variable (and function) info
    // int type
    // union VarInfo; // <- has values
};

struct STNode {
    ASTType	type;
    Token* 	token;
    STNode* 	parent;

    List*	child;// STNode* array
    size_t 	size;
};


struct STRoot {
    STNode* 	root;

    // name list
    List* 	table;// NameInfo array
};


STRoot * mc_create_parse_tree();
void mc_free_parse_tree(STRoot* _root);



STRoot* mc_parse(Token* _tokens);


void mc_unparse(STRoot* _root);



#endif
