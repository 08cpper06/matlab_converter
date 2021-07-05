#ifndef MC_LEXER_H_
#define MC_LEXER_H_

#include "file.h"
#include "env.h"
#include "strings.h"


typedef struct Token Token;

// the following token type list for output
extern const char* g_token_type_names[];


typedef enum {
    TK_NONE,
    TK_NUMBER,

    TK_ALPHABET,

    TK_COMMENT,

    TK_BIN_OP,
    TK_STRING,

    TK_CTRANS,
    
    // () {} [] . : ;
    TK_PAREN,
    TK_BRACE,
    TK_BRAKET,
    TK_COLON,
    TK_DOT,
    TK_SEMICOLON,
    TK_AT_MARK,
    TK_QUATE,

    // keywords
    TK_BREAK,
    TK_CASE,
    TK_CATCH,
    TK_CLASSDEF,
    TK_CONTINUE,
    TK_ELSE,
    TK_ELSEIF,
    TK_END,
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

    // multi-char op
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

    // special char
    TK_NEW_LINE,
    TK_EOF

} TokenType;

struct Token {
    TokenType 	type;
    // if this is edited token by converter, str is not null.
    Vector*	str;
    Token*	next;
    Token*	prev;
    char* 	loc;
    char*	end;// from loc to end

    // TOOD: use the following
    // int 	line;
    // Token*	line_head;
};



// error
_Noreturn void mc_error(char* _fmt, ...);
_Noreturn void mc_error_at(char* _loc, char* _fmt, ...);

Token* mc_create_token();
void mc_free_token(Token* _tok);

// void mc_write_token_list(File* _file, Token* _tokens, const char* _path);


// Tokenize from File* at "tokenizer.c"
Token* mc_tokenize(File* _file, Env* _env);

// UnTokenize from token list
Vector* mc_untokenize(Token* _token, File* _file, Env* _env);

#endif
