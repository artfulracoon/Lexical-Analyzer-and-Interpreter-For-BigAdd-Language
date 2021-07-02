#include "interpreter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int detectWordInterpreter();

int declaration();

char *wordSeparator(char line[], int index);

int assignment(char line[], FILE *lxFile);

int addition(char line[], FILE *lxFile);

int subtraction(char line[], FILE *lxFile);

int printOut(char line[], FILE *lxFile);


char variables[100][100];
int varIndex = 0;
int varValues[100];

int interpreter(char fileName[]) {

    FILE *lxFile;
    lxFile = fopen(fileName, "r");
    char line[255];

    while (!feof(lxFile)) {
        if (fgets(line, 255, lxFile) == NULL) {
            break;
        }
        detectWordInterpreter(line, lxFile);
    }
    return 0;
}

int detectWordInterpreter(char line[], FILE *lxFile) {
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
        }

    }

    return 0;
}

int printOut(char line[], FILE *lxFile) {

    fgets(line, 255, lxFile);
    char *word1 = wordSeparator(line, 0);
    char *word2 = "";
    while (strcmp(line, "EndOfLine\n") && strcmp(line, "EndOfLine")) {
        if (!strcmp(word1, "Separator")) {
            fgets(line, 255, lxFile);
            word1 = wordSeparator(line, 0);
            continue;
        } else if (strcmp(word1, "Keyword") && strcmp(word1, "IntConstant") && strcmp(word1, "StringConstant") &&
                   strcmp(word1, "Identifier")) {
            printf(" %s", "After sub Keyword, An IDENTIFIER or INTCONSTANT must follow!");
            exit(1);
        } else {
            word2 = wordSeparator(line, strlen(word1) + 1);
        }

        if (!strcmp(word1, "StringConstant")) {
            int indexLocal = strlen(word1) + 2;
            while (strcmp(word2, "")) {
                strcpy(word2, wordSeparator(line, indexLocal));
                printf("%s ", word2);
                indexLocal += strlen(word2) + 1;
            }
        } else if (!strcmp(word1, "IntConstant")) {
            printf("%s ", word2);
        } else if (!strcmp(word1, "Keyword")) {
            if (strcmp(word2, "newline")) {
                printf(" %s", "Only newline keyword can be used as a keyword while printing to console!");
                exit(1);
            }
            printf("\n");
        } else if (!strcmp(word1, "Identifier")) {
            for (int i = 0; i < varIndex; ++i) {
                if (!strcmp((const char *) &variables[i], word2)) {
                    printf("%d ", varValues[i]);
                }
            }
        } else if (!strcmp(word1, "Separator")) {

        }

        fgets(line, 255, lxFile);
        word1 = wordSeparator(line, 0);
    }
    return 0;
}

int subtraction(char line[], FILE *lxFile) {
    char *int_value = malloc(100);
    fgets(line, 255, lxFile);
    char *word1 = wordSeparator(line, 0);
    if (strcmp(word1, "Identifier") && strcmp(word1, "IntConstant")) {
        printf(" %s", "After sub Keyword, An IDENTIFIER or INTCONSTANT must follow!");
        exit(1);
    }
    if (!strcmp(word1, "IntConstant")) {
        int_value = wordSeparator(line, strlen(word1) + 1);
    } else {
        char *word2_1 = wordSeparator(line, strlen(word1) + 1);
        for (int i = 0; i < varIndex; ++i) {
            if (!strcmp((const char *) &variables[i], word2_1)) {
                char * str = malloc(100);
                sprintf(str, "%d", varValues[i]);
                strcpy(int_value, str);
                break;
            }
        }
    }
    fgets(line, 255, lxFile);
    char *word3 = wordSeparator(line, 0);
    if (strcmp(word3, "Keyword")) {
        printf(" %s", "After INTCONSTANT OR IDENTIFIER, Keyword FROM must follow!");
        exit(1);
    }
    char *word4 = wordSeparator(line, strlen(word3) + 1);
    if (strcmp(word4, "from")) {
        printf(" %s", "After INTCONSTANT OR IDENTIFIER, Keyword FROM must follow!");
        exit(1);
    }
    fgets(line, 255, lxFile);
    char *word5 = wordSeparator(line, 0);
    if (strcmp(word5, "Identifier")) {
        printf(" %s", "After FROM Keyword, an IDENTIFIER must follow!");
        exit(1);
    }
    char *var_name = wordSeparator(line, strlen(word5) + 1);
    for (int i = 0; i < varIndex; ++i) {
        if (!strcmp((const char *) &variables[i], var_name)) {
            varValues[i] = varValues[i] - atoi(int_value);
            break;
        }
    }
    return 0;
}

int addition(char line[], FILE *lxFile) {
    char *int_value = malloc(100);
    fgets(line, 255, lxFile);
    char *word1 = wordSeparator(line, 0);
    if (strcmp(word1, "Identifier") && strcmp(word1, "IntConstant")) {
        printf(" %s", "After add Keyword, An IDENTIFIER or INTCONSTANT must follow!");
        exit(1);
    }
    if (!strcmp(word1, "IntConstant")) {
        int_value = wordSeparator(line, strlen(word1) + 1);
    } else {
        char *word2_1 = wordSeparator(line, strlen(word1) + 1);
        for (int i = 0; i < varIndex; ++i) {
            if (!strcmp((const char *) &variables[i], word2_1)) {
                char * str = malloc(100);
                sprintf(str, "%d", varValues[i]);
                strcpy(int_value, str);
                break;
            }
        }
    }
    fgets(line, 255, lxFile);
    char *word3 = wordSeparator(line, 0);
    if (strcmp(word3, "Keyword")) {
        printf(" %s", "After INTCONSTANT OR IDENTIFIER, Keyword TO must follow!");
        exit(1);
    }
    char *word4 = wordSeparator(line, strlen(word3) + 1);
    if (strcmp(word4, "to")) {
        printf(" %s", "After INTCONSTANT OR IDENTIFIER, Keyword TO must follow!");
        exit(1);
    }
    fgets(line, 255, lxFile);
    char *word5 = wordSeparator(line, 0);
    if (strcmp(word5, "Identifier")) {
        printf(" %s", "After TO Keyword, an IDENTIFIER must follow!");
        exit(1);
    }
    char *var_name = wordSeparator(line, strlen(word5) + 1);
    for (int i = 0; i < varIndex; ++i) {
        if (!strcmp((const char *) &variables[i], var_name)) {
            varValues[i] = atoi(int_value) + varValues[i];
            break;
        }
    }
    return 0;
}

int assignment(char line[], FILE *lxFile) {
    char *word2 = "";
    fgets(line, 255, lxFile);
    char *word1 = wordSeparator(line, 0);
    if (strcmp(word1, "Identifier") && strcmp(word1, "IntConstant")) {
        printf(" %s", "After MOVE Keyword, An IDENTIFIER or INTCONSTANT must follow!");
        exit(1);
    }
    if (!strcmp(word1, "IntConstant")) {
        word2 = wordSeparator(line, strlen(word1) + 1);
    } else {
        char *word2_1 = wordSeparator(line, strlen(word1) + 1);
        for (int i = 0; i < varIndex; ++i) {
            if (!strcmp((const char *) &variables[i], word2_1)) {
                word2 = (char *) varValues[i];
                break;
            }
        }
    }
    fgets(line, 255, lxFile);
    char *word3 = wordSeparator(line, 0);
    if (strcmp(word3, "Keyword")) {
        printf(" %s", "After INTCONSTANT OR IDENTIFIER, Keyword TO must follow!");
        exit(1);
    }
    char *word4 = wordSeparator(line, strlen(word3) + 1);
    if (strcmp(word4, "to")) {
        printf(" %s", "After INTCONSTANT OR IDENTIFIER, Keyword TO must follow!");
        exit(1);
    }
    fgets(line, 255, lxFile);
    char *word5 = wordSeparator(line, 0);
    if (strcmp(word5, "Identifier")) {
        printf(" %s", "After TO Keyword, an IDENTIFIER must follow!");
        exit(1);
    }
    char *word6 = wordSeparator(line, strlen(word5) + 1);
    for (int i = 0; i < varIndex; ++i) {
        if (!strcmp((const char *) &variables[i], word6)) {
            varValues[i] = atoi(word2);
            break;
        }
    }
    return 0;
}

int declaration(char line[], FILE *lxFile) {

    fgets(line, 255, lxFile);
    char *word1 = wordSeparator(line, 0);
    if (strcmp(word1, "Identifier")) {
        printf(" %s", "After INT Keyword, An IDENTIFIER must follow!");
        exit(1);
    }
    char *word2 = wordSeparator(line, strlen(word1) + 1);
    strcpy(variables[varIndex], word2);
    varIndex++;
    return 0;
}

char *wordSeparator(char line[], int index) {
    char *word = malloc(100);
    int j = 0;

    line[index];

    for (; index <= (strlen(line)); index++) {
        // if space or NULL found, assign NULL into words[ctr]
        if (line[index] == ' ' || line[index] == '\0' || line[index] == '\n') {
            word[j] = '\0';
            return word;
        } else {
            word[j] = line[index];
            j++;
        }
    }

    return "FIN";
}