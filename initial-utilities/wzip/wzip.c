#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    // Run-length encoding
    int length = 0;
    char c;
    char buffer;
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            exit(EXIT_FAILURE);
        }
        while (fread(&buffer, sizeof(char), 1, fp) == 1) {
            if (length == 0) {
                c = buffer;
                length = 1;
            } else if (c == buffer) {
                length++;
            } else {
                fwrite(&length, sizeof(int), 1, stdout);
                fwrite(&c, sizeof(char), 1, stdout);
                c = buffer;
                length = 1;
            }
        }
        fclose(fp);
    }
    if (length > 0) {
        fwrite(&length, sizeof(int), 1, stdout);
        fwrite(&c, sizeof(char), 1, stdout);
    }

    return 0;
}
