#ifndef MC_FILE_H_
#define MC_FILE_H_

#include <stdbool.h>


typedef struct {
    char* filepath;

    char* buffer;
} File;


// load file with convrting to utf-8
File* mc_load_file(const char* _path);

// check file or directory
// if return 0, not exists
// if return 1, exist as file
// if return 2, exist as directory
int mc_is_exist(const char* _path);




#endif
