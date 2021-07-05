#include "parser.h"
#include "lexer.h"
#include "memory.h"
#include "list.h"


STRoot * mc_create_parse_tree()
{
    STRoot* root = mc_calloc(1, sizeof(STRoot));
    root->table = mc_create_list();
    root->root = NULL;
    return root;
}


void mc_free_parse_tree(STRoot* _root)
{
    if (!_root) return;
    if (_root->table) mc_free_list(_root->table);
    if (_root->root) {
		// TODO: scan multiple-node tree
    }
    mc_free(_root);
}

int mc_try_parse_expr(Token** _t, STNode** _parent);

// <bin-op-expr> = <var>
// <bin-op-pri1> = '*' | '/'
// <bin-op-pri2> = '+' | '-' 
// <bin-op-pri3> = '='
int mc_try_parse_bin_op_pri_1(Token** _t, STNode** _parent);

// ==============================
// |                            |
// |     main parse function    |
// |                            |
// ==============================
STRoot* mc_parse(Token* _token)
{
	STRoot* root = mc_create_parse_tree();
	if (!root) mc_error("could not allocate syntax tree root");
	Token* p = _token;
	STNode* node = root->root;
	while (p) {
		mc_try_parse_expr(&p, &node);
	}
	return root;
}


int mc_try_parse_expr(Token** _t, STNode** _parent)
{
	if (mc_try_parse_bin_op_pri_1(_t, _parent))
		return 1;
	;
	return 0;
}

int mc_try_parse_bin_op_pri_1(Token** _t, STNode** _parent)
{
	//
	return 0;
}
