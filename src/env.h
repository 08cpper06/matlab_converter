#ifndef MC_ENV_H__
#define MC_ENV_H__

#include "strings.h"


typedef struct Env Env;


struct Env {
    short 	from_ver;
    short 	to_ver; 
    
    Vector** 	keywords_key;
    int*	keywords_val;
    int		keywords_size;
    
    Vector** 	multi_signs_key;
    int*	multi_signs_val;
    int		multi_signs_size;
};

Env* mc_create_env(int argc, char** argv);

void mc_free_env(Env* _env);

#endif
