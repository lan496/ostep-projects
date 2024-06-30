#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wunzip: cannot open file\n");
            exit(EXIT_FAILURE);
        }

        while (!feof(fp)) {
            int length;
            if (fread(&length, sizeof(int), 1, fp) < 1) {
                break;
            }

            char c;
            if (fread(&c, sizeof(char), 1, fp) < 1) {
                break;
            }

            for (int j = 0; j < length; j++) {
                printf("%c", c);
            }
        }

        fclose(fp);
    }

    return 0;
}
