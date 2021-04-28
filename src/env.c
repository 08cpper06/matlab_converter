#include "env.h"
#include "lexer.h"
#include "memory.h"
#include <stdlib.h>
#include <string.h>

#define KEYWORDS_NUM		20
#define MULTI_SIGNS_NUM		11

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

static void mc_init_map(const char* _ver, Env** _env)
{
    (void) _ver;
    if (!(*_env)) mc_error("env is null-ptr at mc_init_map()");
    (*_env)->keywords_key = (Vector**)mc_calloc(sizeof(Vector*), KEYWORDS_NUM);
    (*_env)->keywords_val = (int*)mc_calloc(sizeof(int), KEYWORDS_NUM);
    (*_env)->keywords_size = KEYWORDS_NUM;
    for (int i = 0; i < KEYWORDS_NUM; ++i) {
	int n = strlen(g_keywords_key_list[i]) + 1;
	(*_env)->keywords_key[i] = mc_create_vector(n);
	mc_set_vector((*_env)->keywords_key[i], (void*)g_keywords_key_list[i], n);
	(*_env)->keywords_val[i] = (int)g_keywords_val_list[i];
    }
    (*_env)->multi_signs_key = (Vector**)mc_calloc(sizeof(Vector*), MULTI_SIGNS_NUM);
    (*_env)->multi_signs_val = (int*)mc_calloc(sizeof(int), MULTI_SIGNS_NUM);
    (*_env)->multi_signs_size = MULTI_SIGNS_NUM;
    for (int i = 0; i < MULTI_SIGNS_NUM; ++i) {
	int n = strlen(g_signs_key_list[i]) + 1;
	(*_env)->multi_signs_key[i] = mc_create_vector(n);
	mc_set_vector((*_env)->multi_signs_key[i], (void*)g_signs_key_list[i], n);
	(*_env)->multi_signs_val[i] = (int)g_signs_val_list[i];
    }
}


Env* mc_create_env(int argc, char** argv)
{
    (void) argc;
    (void) argv;
    Env* env = (Env*)mc_malloc(sizeof(Env));
    if (!env) mc_error("cannot create env structure");
    mc_init_map(NULL, &env);
    return env;
}

void mc_free_env(Env* _env)
{
    for (int i = 0; i < _env->keywords_size; ++i)
	mc_free_vector(_env->keywords_key[i]);
    mc_free(_env->keywords_key);
    mc_free(_env->keywords_val);
    for (int i = 0; i < _env->multi_signs_size; ++i)
	mc_free_vector(_env->multi_signs_key[i]);
    mc_free(_env->multi_signs_key);
    mc_free(_env->multi_signs_val);

    mc_free(_env);
}
