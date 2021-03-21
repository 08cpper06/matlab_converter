#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "strings.h"
#include "lexer.h"




int main(int argc, char** argv) {
    if (argc <= 1)
	mc_error("no input file");

    File* in = mc_load_file(argv[1]);

    Token* root = mc_tokenize(in, NULL);
    Token* p = root;
    while (p) {
	printf("%s\n", p->str->buffer);
	p = p->next;
	if (p->type == TK_EOF) break;
    }

    free(in->buffer);
    free(in);
    return 0;
}
