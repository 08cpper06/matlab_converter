#include "lexer.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


// error
void mc_error(char* _fmt, ...)
{
    va_list ap;
    va_start(ap, _fmt);
    vfprintf(stderr, _fmt, ap);
    fprintf(stderr, "\n");
    mc_all_free();
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
    Token* tok = (Token*)mc_calloc(1, sizeof(Token));
    tok->str = NULL;
    tok->type = TK_NONE;
    tok->next = NULL;
    tok->prev = NULL;
    return tok;
}

void mc_free_token(Token* _tok)
{
    if (_tok->str) mc_free_vector(_tok->str);
    mc_free(_tok);
}

/*
static const char* g_token_type_names[] = {
    "TK_NONE",// none is skipped by tokenizer
    "TK_NUMBER",

    "TK_ALPHABET",

    "TK_COMMENT",

    "TK_BIN_OP",
    "TK_STRING",

    "TK_CTRANS",
    
    "TK_PAREN",
    "TK_BRACE",
    "TK_BRAKET",
    "TK_COLON",
    "TK_DOT",
    "TK_SEMICOLON",
    "TK_AT_MARK",
    "TK_QUATE",

    "TK_BREAK",
    "TK_CASE",
    "TK_CATCH",
    "TK_CLASSDEF",
    "TK_CONTINUE",
    "TK_ELSE",
    "TK_ELSEIF",
    "TK_END",
    "TK_FOR",
    "TK_FUNCTION",
    "TK_GLOBAL",
    "TK_IF",
    "TK_OTHERWISE",
    "TK_PARFOR",
    "TK_PERSiSTENT",
    "TK_RETURN",
    "TK_SPMD",
    "TK_SWITCH",
    "TK_TRY",
    "TK_WHILE",

    "TK_CMP_EQUAL",
    "TK_CMP_NOT_EQUAL",
    "TK_CMP_LESS",
    "TK_CMP_MORE",

    "TK_CMP_AND",
    "TK_CMP_OR",

    "TK_TRANS",

    "TK_EACH_POWER",
    "TK_EACH_MUL",
    "TK_EACH_R_DIV",
    "TK_EACH_L_DIV",

    "TK_NEW_LINE",
    "TK_EOF"
};

static void add_xml_new_line_tag(FILE* fp, Token* _tok, int* _depth)
{
    if (!_tok) mc_error("current token is null at add_xml_rest_str_tag()");
    if (depth > 1) {
	--(*_depth);
	for (int i = 0; i < *_depth; ++i) fprintf(fp, "\t");
	fprintf(fp, "</line>\n");
    }
    for (int i = 0; i < *_depth; ++i) fprintf(fp, "\t");
    fprintf(fp, "<line>\n");
    ++(*_depth);
}

static void add_xml_other_tag(FILE* fp, Token* _tok, int* _depth)
{
}

static void add_xml_rest_str_tag(FILE* fp, Token* _tok, int* _depth)
{
    if (!_tok) mc_error("current token is null at add_xml_rest_str_tag()");
    Token* next = _tok->next;
    if (!next) mc_error("next token is null at add_xml_rest_str_tag()");
    char* bgn = _tok->loc + strlen(_tok->str->size);
    char* end = next->loc;
    if (!(end - bgn)) return;
    for (int i = 0; i < *_depth; ++i) fprintf(fp, "\t");
    fprintf(fp, "<token type=\"TK_NONE\" value=\"%.*s\"/>\n", end - bgn, bgn);
    // "%.*s" => "%#X" (char -> hex)
//    fprintf(fp, "<token type=\"TK_NONE\" value=\"");
//    for (; bgn != end; ++bgn)
//	fprintf(fp, "%#X", (int)*bgn);
//    fprintf(fp, "\"/>\n");
}

void mc_write_token_list(File* _file, Token* _tokens, const char* _path)
{
    Token* t = _tokens;
    char* p  =  _file->buffer;

    FILE* fp = fopen(_path, "w");
    if (!fp) mc_error("could not open file: \"%s\"", _path);
    int depth = 1;
    fprintf(fp, "<root>\n");

    while (t) {
	// add tag (struct Token)
	switch (t->type) {
	    case TK_NEW_LINE:
		add_xml_new_line_tag(fp, t, &depth);
		break;
	    case TK_EOF: break;
	    default:
		add_xml_other_tag(fp, t, &depth);
		break;
	}

	// add tag (skip char, comment)
	add_xml_rest_str_tag(fp, t, &depth);

	t = t->next;
    }
    fprintf(fp, "</root>\n");
    fclose(fp);
}*/
