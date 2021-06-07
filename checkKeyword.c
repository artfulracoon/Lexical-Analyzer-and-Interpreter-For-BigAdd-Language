#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "checkKeyword.h"

int trueDigits(char digit[]);

int checkKeyword(char word[], char fileName[]) { // Checks if word is a known keyword, if it is return 0, else return 1

    FILE *lxFile = fopen(fileName, "a");

    if (!strcmp(word, "int")) {
        fprintf(lxFile, "%s\n", "Keyword int");
        fclose(lxFile);
        return 0;
    } else if (!strcmp(word, "move")) {
        fprintf(lxFile, "%s\n", "Keyword move");
        fclose(lxFile);
        return 0;
    } else if (!strcmp(word, "to")) {
        fprintf(lxFile, "%s\n", "Keyword to");
        fclose(lxFile);
        return 0;
    } else if (!strcmp(word, "add")) {
        fprintf(lxFile, "%s\n", "Keyword add");
        fclose(lxFile);
        return 0;
    } else if (!strcmp(word, "sub")) {
        fprintf(lxFile, "%s\n", "Keyword sub");
        fclose(lxFile);
        return 0;
    } else if (!strcmp(word, "from")) {
        fprintf(lxFile, "%s\n", "Keyword from");
        fclose(lxFile);
        return 0;
    } else if (!strcmp(word, "out")) {
        fprintf(lxFile, "%s\n", "Keyword out");
        fclose(lxFile);
        return 0;
    } else if (!strcmp(word, "loop")) {
        fprintf(lxFile, "%s\n", "Keyword loop");
        fclose(lxFile);
        return 0;
    } else if (!strcmp(word, "newline")) {
        fprintf(lxFile, "%s\n", "Keyword newline");
        fclose(lxFile);
        return 0;
    } else if (!strcmp(word, "times")) {
        fprintf(lxFile, "%s\n", "Keyword times");
        fclose(lxFile);
        return 0;
    }


if (!trueDigits(word)) {
        fprintf(lxFile, "%s", "IntConstant ");
        fprintf(lxFile, "%s\n", word);
        fclose(lxFile);
        return 0;
    }

    fclose(lxFile);
    return 1;
}


int trueDigits(char digit[]) { // returns 0 if word is actually a valid digit, else return 1

    if (strlen(digit) > 100){
        return 1;
    }

    if (digit[0] == '-') {
        for (int j = 1; j < strlen(digit); j++) {
            if (!isdigit(digit[j])) {
                return 1;

            }
        }
    } else if (isdigit(digit[0])) {
        for (int k = 1; k < strlen(digit); k++) {
            if (digit[k] == '\n')
                continue;
            if (!isdigit(digit[k])) {
                return 1;
            }
        }
    } else {
        return 1;
    }
    return 0;
}