#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "strings.h"
#include "lexer.h"





int main(int argc, char** argv) {
    if (argc <= 1)
	mc_error("no input file");
//	printf("no input file\n");
//	exit(1);
    File* in = mc_load_file(argv[1]);

    Token* root = mc_tokenize(in);
    Token* p = root;
    while (p) {
	printf("%s\n", p->str->buffer);
	p = p->next;
    }

    /*
    char* p = in->buffer;
    int c = (int)*p;
    do{
	printf("%s", &c);
    } while((c = mc_consume(&p)) != '\0');
    */

    free(in->buffer);
    free(in);
    return 0;
}
