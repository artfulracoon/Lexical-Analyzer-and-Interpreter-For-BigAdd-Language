#include "interpreter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations.h"

int detectWordInterpreter(char line[], FILE *lxFile, char fileName[]);

int interpreter(char fileName[]) {

    FILE *lxFile;
    lxFile = fopen(fileName, "r");
    char line[255];

    while (!feof(lxFile)) {
        if (fgets(line, 255, lxFile) == NULL) {
            break;
        }
        detectWordInterpreter(line, lxFile, fileName);
    }
    return 0;
}

int detectWordInterpreter(char line[], FILE *lxFile, char fileName[]) {
    char *word1 = wordSeparator(line, 0);

    if (!strcmp(word1, "Keyword")) {

        char *word2 = wordSeparator(line, strlen(word1) + 1);

        if (!strcmp(word2, "int")) {
            declaration(line, lxFile);
        } else if (!strcmp(word2, "move")) {
            assignment(line, lxFile);
        } else if (!strcmp(word2, "add")) {
            addition(line, lxFile);
        } else if (!strcmp(word2, "sub")) {
            subtraction(line, lxFile);
        } else if (!strcmp(word2, "out")) {
            printOut(line, lxFile);
        } else if (!strcmp(word2, "loop")) {
            loop(line, lxFile, fileName);
        }
    }

    return 0;
}