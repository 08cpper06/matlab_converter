#ifndef MC_LEXER_H_
#define MC_LEXER_H_

#include "file.h"
#include "strings.h"

typedef struct Token Token;
typedef struct Span Span;

typedef enum {
    TK_NONE,
    TK_INTEGER,
    TK_REAL,
    TK_BIN_OP,
    TK_EOF,
} TokenType;


struct Token {
    TokenType 	type;
    Vector*	str;
    Token*	next;
    Token*	prev;
};



// error
_Noreturn void mc_error(char* _fmt, ...);
_Noreturn void mc_error_at(char* _loc, char* _fmt, ...);

Token* mc_create_token();
void mc_free_token(Token* _tok);

// Tokenize from File*
Token* mc_tokenize(File* _file);


#endif
