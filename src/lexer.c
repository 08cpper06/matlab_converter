#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

// error
void mc_error(char* _fmt, ...)
{
    va_list ap;
    va_start(ap, _fmt);
    vfprintf(stderr, _fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

void mc_error_at(char* _loc, char* _fmt, ...)
{
    va_list ap;
    va_start(ap, _fmt);
    char* head = _loc;
    for ( ; head[-1] != '\n'; --head);

    char* end = _loc;
    for ( ; *end != '\n'; ++end);
    fprintf(stderr, "%.*s\n", (int)(end - head), head);
    fprintf(stderr, "%*s^ ", (int)(_loc - head), "");
    vfprintf(stderr, _fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

Token* mc_create_token()
{
    Token* tok = (Token*)calloc(sizeof(Token), 1);
    tok->str = mc_create_vector(32);
    tok->type = TK_NONE;
    tok->next = NULL;
    tok->prev = NULL;
    return tok;
}

void mc_free_token(Token* _tok)
{
    mc_free_vector(_tok->str);
    free(_tok);
}

static TokenType mc_check_type(char* _p) {
    if (isdigit((int)*_p)) return TK_INTEGER;

    if (is_contains((int)*_p, "=+-/*|!&%^~"))
	return TK_BIN_OP;
    // unreachable
    return TK_NONE;
}

// return end node
static Token* mc_check_token(Token* tok) 
{
    Token* tok2 = tok->prev;
    if (!tok2)
	return tok;
    
    return tok;
}

// ==============================
// |                            |
// |   main tokenize function   |
// |                            |
// ==============================
Token* mc_tokenize(File* _file)
{
    char* loc = _file->buffer;
    Token* root = NULL;
    Token* old = NULL;
    while(*loc != '\0') {
	Token* tok = mc_create_token();
	tok->prev = old;
	if (old) {
	    old->next = tok;
	} else {
	    root = tok;
	}
	// get first char
	mc_skip_space(&loc);
	mc_set_vector(tok->str, loc, 1);
	tok->type = mc_check_type(loc);
	mc_consume(&loc);
	mc_skip_space(&loc);
	
	// loop until different char type
	while(mc_check_type(loc) == tok->type) {
	    mc_append_vector(tok->str, loc, 1);
	    mc_consume(&loc);
	    mc_skip_space(&loc);
	}

	// check wether mergeable or dividable
	tok = mc_check_token(tok);
	
	// update
	old = tok;
    }
    Token* tok = (Token*)calloc(sizeof(Token), 1);
    tok->prev = old;
    tok->type = TK_EOF;
    return root;
}
