#include "lexer.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

static bool mc_is_alphabet(char* _p) 
{
    if (('a' <= *_p && *_p <= 'z') ||
	('A' <= *_p && *_p <= 'Z'))
	return TK_ALPHABET;
    return TK_NONE;
}

static int mc_try_tokenize_identifer(char** loc, Token** _tok)
{
    char* p = *loc;
    if (mc_is_alphabet(p) == TK_NONE) return 0;
    Token* tok = mc_create_token();
    if (*_tok) {
	(*_tok)->next = tok;
	tok->prev = *_tok;
    }
    mc_skip_space(&p);
    tok->str = mc_create_vector(mc_char_size(p));
    mc_set_vector(tok->str, p, mc_char_size(p));
    tok->type = mc_is_alphabet(p);
    tok->loc = p;
    mc_consume(&p);
    mc_skip_space(&p);
    
    // loop until different char type
    while((mc_is_alphabet(p) == tok->type)) {
	mc_append_vector(tok->str, p, mc_char_size(p));
	mc_consume(&p);
	if (mc_is_skip(p))
	    mc_skip_space(&p);
    }
    mc_skip_space(&p);
    *loc = p;
    *_tok = tok;
    return 1;
}

static TokenType mc_check_type(char* _p) {
    if (*_p == '.') return TK_DOT;
    if (*_p == ';') return TK_SEMICOLON;
    if (*_p == ':') return TK_COLON;
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

    return TK_NONE;
}

static int mc_try_tokenize_single_signs(char** loc, Token** _tok)
{
    char* p = *loc;
    if (mc_check_type(p) == TK_NONE)
	return 0;
    Token* tok = mc_create_token();
    if (*_tok) {
	(*_tok)->next = tok;
	tok->prev = *_tok;
    }
    // get first char
    tok->str = mc_create_vector(mc_char_size(p));
    mc_set_vector(tok->str, p, mc_char_size(p));
    tok->type = mc_check_type(p);
    tok->loc = p;
    mc_consume(&p);
    mc_skip_space(&p);
    *loc = p;
    *_tok = tok;
    return 1;
}

static int mc_try_skip_comment(char** loc, Token** _tok)
{
    char* p = *loc;
    if (*p != '%') return 0;
    mc_consume(&p);
    while(*p != '\n' && *p != '\0')
	mc_consume(&p);

    Token* tok = mc_create_token();
    if (*_tok) {
	(*_tok)->next = tok;
	tok->prev = *_tok;
    }
    tok->str = mc_create_vector(1);
    mc_set_vector(tok->str, p, 1);
    tok->loc = p;
    if (*p == '\0') {
	tok->type = TK_EOF;
    }
    else {
	tok->type = TK_NEW_LINE;
	// skip '\n'
	mc_consume(&p);
	mc_skip_space(&p);
    }
    *loc = p;
    return 0;
}

static int mc_try_tokenize_multi_signs(char** loc, Token** _tok, Env* _env)
{
    if (!_env) mc_error("_env is null ptr at mc_try_tokenize_keywords()");
    bool list[256];
    int n = _env->multi_signs_size, count = 0, idx = 0, len = 0;
    if (n > 256) mc_error("the list of keyword is too big list");
    // check each keyword
    for (int i = 0; i < n; ++i) {
	if (is_startwith(*loc, _env->multi_signs_key[i]->buffer)) {
	    ++count;
	    list[i] = true;
	} else list[i] = false;
    }
    if (!count) return 0;
    if (count == 1) {
	for (idx = 0; idx < n; ++idx) 
	    if (list[idx]) break;
    } else {
	for (int i = 0; i < n; ++i) {
	    if (list[i] && len < _env->multi_signs_key[i]->size) {
		idx = i;
		len = _env->multi_signs_key[i]->size;
	    }
	}
    }
    // update loc, _tok and add token list
    Token* tok = mc_create_token();
    {
	tok->type = _env->multi_signs_val[idx];
	tok->loc = *loc;
	tok->str = mc_copy_vector(_env->multi_signs_key[idx]);
	tok->prev = *_tok;
	if (*_tok)
	    (*_tok)->next = tok;
    }
    *_tok = tok;
    *loc += _env->multi_signs_key[idx]->size - 1;
    mc_skip_space(loc);
    return 1;
}

static int mc_try_tokenize_transpose(char** _loc, Token** _tok)
{
    if (!(*_tok)) return 0;

    char* p = *_loc;
    if (*p != '\'') {
	if (*p != '.') return 0;
	else if (*(p + 1) != '\'') return 0;
    }

    p = (*_tok)->loc;
    switch ((*_tok)->type) {// prev token
	case TK_NUMBER:
	case TK_ALPHABET:
	case TK_BRACE:
	    if (*p == '{') return 0;
	case TK_BRAKET:
	    if (*p == '[') return 0;
	    break;
	default:
	    return 0;
    }
    // not space between previous and current token
    p = (*_tok)->loc;
    for (; p != *_loc; ++p) if (mc_is_skip(p)) return 0;
    

    Token* tok = mc_create_token();
    if (*_tok) {
	(*_tok)->next = tok;
	tok->prev = *_tok;
    }
    if (*p == '\'')
	tok->type = TK_CTRANS;
    else if (*p == '.' && *(p + 1) == '\'')
	tok->type = TK_TRANS;
    tok->loc = *_loc;
    if (tok->type == TK_TRANS) {
	tok->str = mc_create_vector(3);
	mc_set_vector(tok->str, p, 2);
	*_loc += 2;
    } if (tok->type == TK_CTRANS) {
	tok->str = mc_create_vector(2);
	mc_set_vector(tok->str, p, 1);
	*_loc += 1;
    }
    *_tok = tok;
    mc_skip_space(_loc);
    return 1;
}

static int mc_try_tokenize_keywords(char** loc, Token** _tok, Env* _env)
{
    if (!_env) mc_error("_env is null ptr at mc_try_tokenize_keywords()");
    bool list[256];
    int _max = strlen(*loc) + 1;
    int n = _env->keywords_size, count = 0, idx = 0, len = 0;
    if (n > 256) mc_error("the list of keyword is too big list");
    // check each keyword
    for (int i = 0; i < n; ++i) {
	if (_max >= _env->keywords_key[i]->size
	    && is_startwith(*loc, _env->keywords_key[i]->buffer)
	) {
	    ++count;
	    list[i] = true;
	} else list[i] = false;
    }
    if (!count) return 0;
    if (count == 1) {
	for (idx = 0; idx < n; ++idx) 
	    if (list[idx]) break;
    } else {
	for (int i = 0; i < n; ++i) {
	    if (list[i] && len < _env->keywords_key[i]->size) {
		idx = i;
		len = _env->keywords_key[i]->size;
	    }
	}
    }
    // update loc, _tok and add token list
    Token* tok = mc_create_token();
    {
	tok->type = _env->keywords_val[idx];
	tok->loc = *loc;
	tok->str = mc_copy_vector(_env->keywords_key[idx]);
	tok->prev = *_tok;
	if (*_tok)
	    (*_tok)->next = tok;
    }
    *_tok = tok;
    *loc += _env->keywords_key[idx]->size - 1;
    mc_skip_space(loc);
    return 1;
}

// <DIGIT>  ::= ('0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9')+
static Vector* mc_try_parse_digit(char** _loc)
{
    char* p = *_loc;
    while(isdigit((int)*p)) ++p;
    // could not parse
    if (p == *_loc) {
	return NULL;
    }
    Vector* vec = mc_create_vector((int)(p - *_loc + 1));
    mc_append_vector(vec, *_loc, (int)(p - *_loc));
    *_loc = p;
    return vec;
}

// <REAL>   ::= <DIGIT> '.'? <DIGIT> ('e' | 'E') ('+' | '-') <DIGIT>
// 	      | <DIGIT> '.'
// 	      | <DIGIT>? '.' <DIGIT>
static Vector* mc_try_parse_real(char** loc)
{
    char* p = *loc;
    Vector* v = mc_try_parse_digit(&p);
    if (*p == '.') {
	if (!v) {
	    // ex) ".112"
	    v = mc_create_vector(1);
	    mc_append_vector(v, p, 1);
	    ++p;
	    Vector* v2 = mc_try_parse_digit(&p);
	    if (!v2) mc_error("only \'.\' is not valid number");
	    Vector* tmp = mc_merge_vector(v, v2);
	    mc_free_vector(v);
	    mc_free_vector(v2);
	    v = tmp;
	} else {
	    mc_append_vector(v, p, 1);
	    ++p;
	    Vector* v2 = mc_try_parse_digit(&p);
	    if (v2) {// ex) "323.22"
		Vector* tmp = mc_merge_vector(v, v2);
		mc_free_vector(v);
		mc_free_vector(v2);
		v = tmp;
	    }// else ex) "323."
	}
    } else if (!v) return NULL;
    if (*p == 'e' || *p == 'E') {
	if (*(p + 1) != '+' && *(p + 1) != '-') {
	    mc_free_vector(v);
	    return NULL;
	}
	mc_append_vector(v, p, 2);
	p += 2;
	Vector* v2 = mc_try_parse_digit(&p);
	if (!v2) {
	    mc_free_vector(v);
	    mc_free_vector(v2);
	    return NULL;
	}
	Vector* tmp = mc_merge_vector(v, v2);
	mc_free_vector(v);
	mc_free_vector(v2);
	v = tmp;
    }
    *loc = p;
    return v;
}

// <NUMBER> ::= <REAL> (('+' | '-') <REAL> ('i' | 'j'))?
static int mc_try_tokenize_number(char** _loc, Token** _tok)
{
    char* p = *_loc;
    Vector* v = mc_try_parse_real(&p);
//    Vector* v = mc_try_parse_digit(&p);
    if (!v) return 0;

    Token* tok = mc_create_token();
    if (*_tok) {
	(*_tok)->next = tok;
    }
    tok->prev = *_tok;
    tok->loc = *_loc;
    tok->type = TK_NUMBER;
    tok->str = v;

    *_tok = tok;
    mc_skip_space(&p);
    *_loc = p;
    return 1;
}

static int mc_try_tokenize_string(char** loc, Token** _tok)
{
    char* p = *loc;
    if (*p != '\'' && *p != '\"') return 0;
    Token* tok = mc_create_token();
    if (*_tok) {
	(*_tok)->next = tok;
    }
    tok->prev = *_tok;
    char c = *p;
    tok->loc = p;
    tok->type = TK_QUATE;
    tok->str = mc_create_vector(mc_char_size(p));
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
    tok->str = mc_create_vector(1);
    while(c != *p && *p != '\0') {
	if (*p == '\n')
	    mc_error("reach \'\n\' before the end of string(%c)", c);
	mc_append_vector(tok->str, p, mc_char_size(p));
	mc_consume(&p);
    }

    if (*p == '\0')
	mc_error_at(*loc, "reached EOF before %c", tok->str->buffer[0]);

    {// string component
	Token* new_tok = mc_create_token();
	new_tok->prev = tok;
	tok->next = new_tok;
	tok = tok->next;
    }
    tok->loc = p;
    tok->type = TK_QUATE;
    tok->str = mc_create_vector(mc_char_size(p));
    mc_set_vector(tok->str, p, mc_char_size(p));
    mc_consume(&p);
    mc_skip_space(&p);

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

	// tokenize keywords
	if (mc_try_tokenize_keywords(&loc, &tok, _env))
	    goto UPDATE;
	
	// tokenize multi-char signs
	if (mc_try_tokenize_multi_signs(&loc, &tok, _env))
	    goto UPDATE;
	
	// tokenize transpose-op & ctranspose-op (chech whether prev char is non-space)
	if (mc_try_tokenize_transpose(&loc, &tok))
	    goto UPDATE;

	// tokenize number
	if (mc_try_tokenize_number(&loc, &tok))
	    goto UPDATE;
	
	// tokenize string
	if (mc_try_tokenize_string(&loc, &tok))
	    goto UPDATE;

	// tokenize identifer
	if (mc_try_tokenize_identifer(&loc, &tok))
	    goto UPDATE;

	// tokenize single-char words
	if (mc_try_tokenize_single_signs(&loc, &tok))
	    goto UPDATE;

	
	mc_error_at(loc, "reached unknown token(\'%s\')", *loc);
UPDATE:
	mc_fit_vector(tok->str);
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
	new_tok->str = mc_create_vector(1);
	mc_set_vector(new_tok->str, loc, 1);
    }
    return root;
}

