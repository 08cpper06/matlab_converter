#include "option.h"
#include "strings.h"
#include "file.h"
#include "lexer.h"
#include "memory.h"
#include "env.h"
#include <stdio.h>
#include <string.h>


int mc_parse_cmd_option(const char* opt_name, int _argc, char** _argv)
{
    int i;
    for (i = 0; i < _argc; ++i) 
		if (!strcmp(_argv[i], opt_name)) break;

    if (i == _argc) {
		if (!strcmp(opt_name, "-src"))
			return 1;
		else
			return -1;
    }
    return i + 1;
}

static int run_001_routine(int _argc, char** _argv)
{
    int i = mc_parse_cmd_option("-src", _argc, _argv);
    if (i < 0)
		mc_error("no input file");
    // revise path
    Vector vec;
    vec.size = vec.capacity = strlen(_argv[i]) + 1;
    vec.buffer = _argv[i];
    (void) mc_check_path(&vec);

    File* in = mc_load_file(vec.buffer);
    char* p = in->buffer;
    while (*p) {
		printf("%.*s\n", mc_char_size(p), p);
		mc_consume(&p);
    }
    return 0;
}
static int run_002_routine(int _argc, char** _argv)
{
    int i = mc_parse_cmd_option("-src", _argc, _argv);
    if (i < 0)
		mc_error("no input file");
    File* in = mc_load_file(_argv[i]);
    Env* _env = mc_create_env(_argc, _argv);
    if (!_env) mc_error("could not get environment information");

    Token* root = mc_tokenize(in, _env);
    
    Token* p = root;
    while (p) {
		if (p->type != TK_NEW_LINE) {
			printf("%.*s\n", (int)(p->end - p->loc), p->loc);
		}
		p = p->next;
		if (p->type == TK_EOF) break;
    }

    mc_all_free();

    // check memory leak
    if (mc_check_mem_leak() > 0)
		mc_print_mem_leak();
    return 0;
}
static int run_004_routine(int _argc, char** _argv)
{
    int i = mc_parse_cmd_option("-src", _argc, _argv);
    if (i < 0) mc_error("not input file");

    File* in = mc_load_file(_argv[i]);

    Env* _env = mc_create_env(_argc, _argv);
    if (!_env) mc_error("could not get environment information");

    Token* root = mc_tokenize(in, _env);
    if (!root) mc_error("could not tokenize");

    Vector* buf = mc_untokenize(root, in, _env);
    if (!buf) mc_error("could not untokenize");
    if (!buf->buffer) mc_error("untokenized string is null");

    printf("%s\n", buf->buffer);

    mc_all_free();

    // check memory leak
    if (mc_check_mem_leak() > 0)
		mc_print_mem_leak();
    return 0;
}

static int run_convert_routine(int _argc, char** _argv)
{
    // TODO: implement
    mc_error("run mode: \"convert\" is not implement yet");
}

static int run_estimate_version_routine(int _argc, char** _argv)
{
    // TODO: implement
    mc_error("run mode: \"estimate_version\" is not implement yet");
}

int run_main_routine(int _argc, char** _argv)
{
    if (_argc == 1)
		mc_error("no input file");
    int i = mc_parse_cmd_option("-mode", _argc, _argv);
    if (i < 0) mc_error("please specify \"-mode <rum_mode>\"\n");

    if (!strcmp(_argv[i], "debug_001"))
		return run_001_routine(_argc, _argv);
    if (!strcmp(_argv[i], "debug_002"))
		return run_002_routine(_argc, _argv);
    if (!strcmp(_argv[i], "debug_004"))
		return run_004_routine(_argc, _argv);
    if (!strcmp(_argv[i], "convert"))
		return run_convert_routine(_argc, _argv);
    if (!strcmp(_argv[i], "estimate_version"))
		return run_estimate_version_routine(_argc, _argv);

    mc_error("unknown run mode!!");
}
