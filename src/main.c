#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "strings.h"
#include "lexer.h"




int main(int argc, char** argv) {
    if (argc <= 1)
	mc_error("no input file");

    File* in = mc_load_file(argv[1]);
    Env* _env = mc_create_env(argc, argv);
    if (!_env) mc_error("could not get environment information");

    Token* root = mc_tokenize(in, _env);
    if (!root) mc_error("<< debug >>\nno token");

    Token* p = root;
    while (p) {
	if (p->type != TK_NEW_LINE) {
	    printf("%s\n", p->str->buffer);
	}
	p = p->next;
	if (p->type == TK_EOF) break;
    }

    mc_free_env(_env);
    free(in->buffer);
    free(in);
    return 0;
}
