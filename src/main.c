#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "strings.h"
#include "lexer.h"
#include "memory.h"
#include "option.h"



// <<< program option list >>>
// -mode 	| the possible run mode(the following)
// 		| "convert"		: convert mode(only one file)
// 		| "debug_001"		: output separated each charactor for debug
// 		| "debug_002"		: output token list for debug
// 		| "estimate_version"	: estimate input file version
// ================================================================================
// << option by run mode >>
// [mode: "convert"]
// -src 	| convert target file(first argument is interpreted as this option if "-src" is omited.)
// -path	| additional path for searching script
// -to		| output file version
// -from	| input file version
//
// [mode: "estimate_version"]
// -src 	| convert target file(first argument is interpreted as this option if "-src" is omited.)
//
// [mode: "debug_001"]
// -src 	| convert target file(first argument is interpreted as this option if "-src" is omited.)
// 
// [mode: "debug_002"]
// -src 	| convert target file(first argument is interpreted as this option if "-src" is omited.)

// ex)
// ./matlab_converter test.m -mode debug_001
// ./matlab_converter -src test.m -mode debug_002

int main(int argc, char** argv) {
    // defined in "option.c"
    return run_main_routine(argc, argv);
}
