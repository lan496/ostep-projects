#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1000

int main(int argc, char *argv[]) {
    // wcat file1 file2 ...
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wcat: cannot open file\n");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];
        while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
            printf("%s", buffer);
        }

        fclose(fp);
    }
    return 0;
}
