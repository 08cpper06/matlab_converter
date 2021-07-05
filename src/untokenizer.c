#include "lexer.h"
#include "strings.h" 
#include "memory.h"
#include <stdio.h>
#include <string.h>

// header file: "lexer.h"

Vector* mc_untokenize(Token* _token, File* _file, Env* _env)
{
    Token* p = _token, *next = NULL;
    char* bgn, *end;
    Vector* vec = mc_create_vector(32);
    if (!vec) mc_error("could not allocate vec in mc_untokenize()");
    // copy from head of file to first token
    bgn = _file->buffer;
    end = p->loc;
    if (bgn != end)
		mc_append_vector(vec, bgn, end - bgn);
    while (p->type != TK_EOF) {
		if (p->type == TK_NEW_LINE) {
			mc_append_vector(vec, p->loc, 1);
			// insert skipped char in source code
			next = p->next;
			if (next->type == TK_EOF) {
				bgn = p->loc + 1;
				end = p->loc + strlen(p->loc);
				mc_append_vector(vec, bgn, end - bgn);
			} else {
				bgn = p->loc + 1;
				end = next->loc;
				if (bgn != end) 
					mc_append_vector(vec, bgn, end - bgn);
			}
		} else {
			if (p->str)
				mc_append_vector(vec, p->str->buffer, p->str->size);
			else
				mc_append_vector(vec, p->loc, (int)(p->end - p->loc));
			// insert skipped char in source code
			next = p->next;
			if (next->type == TK_EOF) {
				bgn = p->end;
				end = p->loc + strlen(p->loc);
				mc_append_vector(vec, bgn, end - bgn);
			} else {
				bgn = p->end;
				end = next->loc;
				if (bgn != end) 
					mc_append_vector(vec, bgn, end - bgn);
			}
		}
		p = p->next;
    }
    return vec;
}
