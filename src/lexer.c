#include "lexer.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>

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

static const char* g_keywords_key_list[] = {
    "break",
    "case",
    "catch",
    "classdef",
    "continue",
    "else",
    "elseif",
    "end",
    "for",
    "function",
    "global",
    "if",
    "otherwise",
    "parfor",
    "persistent",
    "return",
    "spmd",
    "switch",
    "try",
    "while",
};

// 
static int g_keywords_val_list[] = {
    TK_BREAK,
    TK_CASE,
    TK_CATCH,
    TK_CLASSDEF,
    TK_CONTINUE,
    TK_ELSE,
    TK_ELSEIF,
    TK_END,
    TK_FOR,
    TK_FOR,
    TK_FUNCTION,
    TK_GLOBAL,
    TK_IF,
    TK_OTHERWISE,
    TK_PARFOR,
    TK_PERSiSTENT,
    TK_RETURN,
    TK_SPMD,
    TK_SWITCH,
    TK_TRY,
    TK_WHILE,
};

static const char* g_signs_key_list[] = {
    "==",
    "~=",
    "<=",
    ">=",

    "&&",
    "||",

    ".\'",
    ".^",
    ".*",
    "./",
    ".\\"
};

static int g_signs_val_list[] = {
    TK_CMP_EQUAL,
    TK_CMP_NOT_EQUAL,
    TK_CMP_LESS,
    TK_CMP_MORE,

    TK_CMP_AND,
    TK_CMP_OR,

    TK_TRANS,

    TK_EACH_POWER,
    TK_EACH_MUL,
    TK_EACH_R_DIV,
    TK_EACH_L_DIV,
};

static MapNode* keywords;
static MapNode* signs;

void mc_init_map(const char* _ver)
{
    if (keywords) 
	mc_free_map(keywords);
    keywords = mc_create_map(g_keywords_key_list, g_keywords_val_list);
    if (signs) 
	mc_free_map(signs);
    signs = mc_create_map(g_signs_key_list, g_signs_val_list);
}

void mc_free_token(Token* _tok)
{
    mc_free_vector(_tok->str);
    free(_tok);
}

static bool mc_check_token_size(Token* tok) 
{
    switch (tok->type) {
    case TK_INTEGER:
    case TK_ALPHABET:
    case TK_NONE:
	return true;
    default:
	return false;
    }
}

static TokenType mc_check_type(char* _p) {
    if (isdigit((int)*_p)) return TK_INTEGER;

    if (*_p == '.') return TK_DOT;
    if (*_p == ';') return TK_SEMICOLON;
    if (*_p == ';') return TK_COLON;
    if (*_p == '@') return TK_AT_MARK;
    if (*_p == '\n') return TK_NEW_LINE;
    if (*_p == '\0') return TK_EOF;

    if (is_contains((int)*_p, "=+-/*|&^~<>~\\"))
	return TK_BIN_OP;
    if (is_contains((int)*_p, "()"))
	return TK_PAREN;
    if (is_contains((int)*_p, "{}"))
	return TK_BRACE;
    if (is_contains((int)*_p, "[]"))
	return TK_BRAKET;

    if (('a' <= *_p && *_p <= 'z') ||
	('A' <= *_p && *_p <= 'Z'))
	return TK_ALPHABET;
    return TK_NONE;
}

static int mc_try_tokenize_others(char** loc, Token** _tok)
{
    char* p = *loc;
    Token* tok = mc_create_token();
    if (*_tok) {
	(*_tok)->next = tok;
	tok->prev = *_tok;
    }
    // get first char
    mc_skip_space(&p);
    mc_set_vector(tok->str, p, mc_char_size(p));
    tok->type = mc_check_type(p);
    tok->loc = p;
    mc_consume(&p);
    mc_skip_space(&p);
    
    // loop until different char type
    while((mc_check_type(p) == tok->type) && mc_check_token_size(tok)) {
	mc_append_vector(tok->str, p, mc_char_size(p));
	mc_consume(&p);
	if (mc_is_skip(p)) {
	    mc_skip_space(&p);
	}
    }
    *loc = p;
    *_tok = tok;
    return 1;
}

static int mc_try_skip_comment(char** loc, Token** _tok)
{
    // TODO : skip comment
    char* p = *loc;
    if (*p != '%') return 0;
    while(*p != '\n')
	mc_consume(&p);
    // skip '\n'
    mc_consume(&p);
    mc_skip_space(&p);
    *loc = p;
    return 0;
}

static int mc_try_tokenize_string(char** loc, Token** _tok)
{
    char* p = *loc;
    if (*p != '\'' && *p != '\"') return 0;
    Token* tok = mc_create_token();
    if (*_tok) {
	(*_tok)->next = tok;
	tok->prev = *_tok;
    }
    char c = *p;
    tok->loc = p;
    tok->type = TK_QUATE;
    mc_set_vector(tok->str, p, mc_char_size(p));
    mc_consume(&p);
    {// " or '
	Token* new_tok = mc_create_token();
	new_tok->prev = tok;
	tok->next = new_tok;
	tok = tok->next;
    }

    tok->loc = p;
    tok->type = TK_STRING;
    while(c != *p && *p != '\0') {
	mc_append_vector(tok->str, p, mc_char_size(p));
	mc_consume(&p);
    }

    if (*p == '\0') {
	mc_error_at(*loc, "reached EOF before %c", tok->str->buffer[0]);
	// unreachable
	return 0;
    }

    {// string component
	Token* new_tok = mc_create_token();
	new_tok->prev = tok;
	tok->next = new_tok;
	tok = tok->next;
    }
    tok->loc = p;
    tok->type = TK_QUATE;
    mc_set_vector(tok->str, p, mc_char_size(p));
    mc_consume(&p);

    *loc = p;
    *_tok = tok;
    return 1;
}


// ==============================
// |                            |
// |   main tokenize function   |
// |                            |
// ==============================
Token* mc_tokenize(File* _file, Env* _env)
{
    char* loc = _file->buffer;
    Token* root = NULL;
    Token* tok = NULL;
    while(*loc != '\0' && (loc - _file->buffer) < _file->size) {
	// skip comment
	if (mc_try_skip_comment(&loc, &tok))
	    goto UPDATE;

	// tokenize multi-char words (such as "function" and "+=")
	// TODO : tokenize multi-char words
	
	// TODO : tokenize transpose-op & ctranspose-op (chech whether prev char is non-space)
	
	// tokenize string
	if (mc_try_tokenize_string(&loc, &tok))
	    goto UPDATE;
	// tokenize single-char words
	if (mc_try_tokenize_others(&loc, &tok))
	    goto UPDATE;
	
	mc_error_at(loc, "reached unknown token");
UPDATE:
	// update
	if (!root) 
	    // loop until reaching root
	    for (root = tok; root->prev; root = root->prev);
    }
    // if list has no TK_EOF token, push back EOF
    if (tok->type != TK_EOF && *loc == '\0') {
	Token* new_tok = mc_create_token();
	new_tok->prev = tok;
	tok->next = new_tok;

	new_tok->type = TK_EOF;
	mc_set_vector(new_tok->str, loc, 1);
    }
    return root;
}
