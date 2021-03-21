#include "file.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


File* mc_load_file(const char* _path)
{
    FILE* fp = fopen(_path, "r");
    if (!fp) {
	switch (mc_is_exist(_path)) {
	    case 0:
		printf("%s cannot exist file\n", _path);
		break;
	    case 2:
		printf("%s is not file\n", _path);
		break;
	}
	exit(2);
    }
    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buf = (char*)calloc(length, 1);
    fread(buf, sizeof(char), length, fp);
    // expilictly insert NULL(fread() does not insert null to the end of buffer)
    buf[length - 1] = '\0';
    fclose(fp);

    File* out = (File*)calloc(sizeof(File), 1);
    out->filepath = (char*)_path;
    out->buffer = buf;
    out->size = length;
    return out;
}


int mc_is_exist(const char* _path)
{
    struct stat st;
    if (stat(_path, &st) != 0) 
        return 0;

    if ((st.st_mode & S_IFMT) == S_IFREG)
	return 1;
    if ((st.st_mode & S_IFMT) == S_IFDIR)
	return 2;
    return 0;
}
