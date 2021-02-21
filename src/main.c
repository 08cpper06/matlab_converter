#include <stdio.h>
#include <stdlib.h>


char consume(char **p) {
    if (**p != '\0')
	++(*p);
    if (**p == '\r') perror("detect <LF>!!\n");
    return **p;
}

char* open(const char* path) {
    FILE* fp = fopen(path, "r");
    if (!fp) {
	printf("cannot open file %s\n", path);
	exit(2);
    }
    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    char* buf = (char*)calloc(1, length);
    fseek(fp, 0, SEEK_SET);
    fread(buf, sizeof(char), length, fp);
    // expilictly insert NULL(fread() does not insert null to buffer)
    buf[length - 1] = '\0';
    fclose(fp);
    return buf;
}

int main(int argc, char** argv) {
    if (argc <= 1){
	printf("no input file\n");
	exit(1);
    }
    char* p = open(argv[1]);
    char* buf = p;
    char c = *p;
    do{
	printf("%c", c);
    } while((c = consume(&p)) != '\0');

    free(buf);
    return 0;
}
