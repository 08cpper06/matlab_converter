#ifndef MC_OPTION_H__
#define MC_OPTION_H__




int run_main_routine(int _argc, char** _argv);

// return index
// if return < 0, could not find
int mc_parse_cmd_option(const char* opt_name, int _argc, char** _argv);

#endif
