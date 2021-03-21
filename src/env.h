#ifndef MC_ENV_H__
#define MC_ENV_H__


typedef struct Env Env;


struct Env {
    short from_ver;
    short to_ver; 

    
};

// TODO : define
Env* mc_create_env(int argc, char** argv);


#endif
