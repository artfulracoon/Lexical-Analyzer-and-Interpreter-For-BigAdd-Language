#include "interpreter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int detectWordInterpreter();

int declaration();

char *wordSeparator(char line[], int index);

int assignment(char line[], FILE *lxFile);

int addition(char line[], FILE *lxFile);



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
            addition(line,lxFile);
        } else if (!strcmp(word2, "sub")) {

        } else if (!strcmp(word2, "out")) {

        }

    }

    return 0;
}

int addition(char line[], FILE *lxFile){
    char int_value;
    fgets(line, 255, lxFile);
    char *word1 = wordSeparator(line, 0);
    if(strcmp(word1, "Identifier") && strcmp(word1, "IntConstant")){
        printf(" %s", "After add Keyword, An IDENTIFIER or INTCONSTANT must follow!");
        exit(1);
    }
    if(!strcmp(word1, "IntConstant")){
        strcpy(&int_value, wordSeparator(line, strlen(word1) + 1));
    } else{
        char *word2_1 = wordSeparator(line, strlen(word1) + 1);
        for (int i = 0; i < varIndex; ++i) {
            if(!strcmp((const char *) &variables[i], word2_1)){
                int_value = (char) varValues[i];
                break;
            }
        }
    }
    fgets(line, 255, lxFile);
    char *word3 = wordSeparator(line, 0);
    if(strcmp(word3, "Keyword")){
        printf(" %s", "After INTCONSTANT OR IDENTIFIER, Keyword TO must follow!");
        exit(1);
    }
    char *word4 = wordSeparator(line, strlen(word3) + 1);
    if(strcmp(word4, "to")) {
        printf(" %s", "After INTCONSTANT OR IDENTIFIER, Keyword TO must follow!");
        exit(1);
    }
    fgets(line, 255, lxFile);
    char *word5 = wordSeparator(line, 0);
    if(strcmp(word5, "Identifier")){
        printf(" %s", "After TO Keyword, an IDENTIFIER must follow!");
        exit(1);
    }
    char *var_name = wordSeparator(line, strlen(word5) + 1);
    for (int i = 0; i < varIndex; ++i) {
        if(!strcmp((const char *) &variables[i], var_name)){
            int value = int_value - '0';
            varValues[i] = value + varValues[i];
            break;
        }
    }
    int value2 = varValues[0];
    return 0;
}

int assignment(char line[], FILE *lxFile){
    char word2;
    fgets(line, 255, lxFile);
    char *word1 = wordSeparator(line, 0);
    if(strcmp(word1, "Identifier") && strcmp(word1, "IntConstant")){
        printf(" %s", "After MOVE Keyword, An IDENTIFIER or INTCONSTANT must follow!");
        exit(1);
    }
    if(!strcmp(word1, "IntConstant")){
        strcpy(&word2, wordSeparator(line, strlen(word1) + 1));
    } else{
        char *word2_1 = wordSeparator(line, strlen(word1) + 1);
        for (int i = 0; i < varIndex; ++i) {
            if(!strcmp((const char *) &variables[i], word2_1)){
                word2 = (char) varValues[i];
                break;
            }
        }
    }
    fgets(line, 255, lxFile);
    char *word3 = wordSeparator(line, 0);
    if(strcmp(word3, "Keyword")){
        printf(" %s", "After INTCONSTANT OR IDENTIFIER, Keyword TO must follow!");
        exit(1);
    }
    char *word4 = wordSeparator(line, strlen(word3) + 1);
    if(strcmp(word4, "to")){
        printf(" %s", "After INTCONSTANT OR IDENTIFIER, Keyword TO must follow!");
        exit(1);
    }
    fgets(line, 255, lxFile);
    char *word5 = wordSeparator(line, 0);
    if(strcmp(word5, "Identifier")){
        printf(" %s", "After TO Keyword, an IDENTIFIER must follow!");
        exit(1);
    }
    char *word6 = wordSeparator(line, strlen(word5) + 1);
    for (int i = 0; i < varIndex; ++i) {
        if(!strcmp((const char *) &variables[i], word6)){
            int word8 = word2 - '0';
            varValues[i] = word8;
            break;
        }
    }
    return 0;
}

int declaration(char line[], FILE *lxFile) {

    fgets(line, 255, lxFile);
    char *word1 = wordSeparator(line, 0);
    if(strcmp(word1, "Identifier")){
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

    return NULL;
}