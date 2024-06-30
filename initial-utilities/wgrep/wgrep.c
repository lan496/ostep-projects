#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep(FILE *fp, char *search_term) {
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        if (strstr(line, search_term) != NULL) {
            printf("%s", line);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 2) {
        grep(stdin, argv[1]);
    } else {
        for (int i = 2; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("wgrep: cannot open file\n");
                exit(EXIT_FAILURE);
            }
            grep(fp, argv[1]);
        }
    }
    return 0;
}
