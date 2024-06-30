#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct Line {
    char *line;
    struct Line *prev;
} Line;

int main(int argc, char *argv[]) {
    if (argc >= 4) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(EXIT_FAILURE);
    }

    FILE *input = NULL;
    if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(EXIT_FAILURE);
        }
    } else {
        input = stdin;
    }

    FILE *output = NULL;
    if (argc >= 3) {
        output = fopen(argv[2], "w");

        struct stat istat, ostat;
        fstat(fileno(input), &istat);
        fstat(fileno(output), &ostat);

        if (istat.st_ino == ostat.st_ino) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(EXIT_FAILURE);
        }
    } else {
        output = stdout;
    }

    Line *prev = NULL;
    Line *head = NULL;

    // Read forward
    char *line = NULL;
    size_t linecap = 0;
    while (getline(&line, &linecap, input) > 0) {
        head = malloc(sizeof(Line));
        if (head == NULL) {
            fprintf(stderr, "malloc failed\n");
            fclose(input);
            fclose(output);
            exit(EXIT_FAILURE);
        }

        head->line = strdup(line);
        head->prev = prev;
        prev = head;
    }

    // Dump backward
    while (head != NULL) {
        fprintf(output, "%s", head->line);
        head = head->prev;
    }

    fclose(input);
    fclose(output);

    return 0;
}
