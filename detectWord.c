#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "detectWord.h"
#include "checkKeyword.h"

int trueDigits(char digit[]);

int commentChecker(int inComment, char currentChar, char line[], int lineNum);
int stringChecker(int inString, char line[], int point, int lineNum);
int loopChecker(int inLoop, char currentChar, char line[], int lineNum, char fileName[]);

int detectKeyword(char line[], int *inLoop, int *inComment, int *inString, int lineNum, char fileName[]) {
    char word[255];
    int size = 0;
    int lineLen = strlen(line);
    int point = 0;
    FILE *lxFile;
    for (int i = 0; i < lineLen; ++i) {

        // STRING CHECKER
        if (line[i] == '\"'){
            *inString = stringChecker(*inString, line, i, lineNum);
        }
        if (*inString == 1) {
            word[i-size] = line[i];
            point = i-size+1;
            continue;
        }
        if (line[i] == '\"' && *inString == 0){
            word[i-size] = '\0';
            lxFile = fopen(fileName, "a");
            fprintf(lxFile, "%s", "StringConstant ");
            fprintf(lxFile, "%s", word);
            fprintf(lxFile, "%s\n", "\"");
            fclose(lxFile);
            size = i + 1;
            continue;
        }

        // COMMENT CHECKER
        *inComment = commentChecker(*inComment, line[i], line, lineNum);
        if (*inComment == 1) {
            continue;
        }


        // LOOP CHECKER
        *inLoop = loopChecker(*inLoop, line[i], line, lineNum, fileName);




        // WORD CHECKER

        if (line[i] == ' ' || line[i] == '.' || line[i] == '\n' || line[i] == ',' || line[i] == '\t' ) {
            word[i - size] = '\0';

            if (isdigit(word[i - size - 1]) && line[i] == '.' && i + 1 != lineLen) {
                printf("%s", "UNSUPPORTED INTEGER FORMAT DETECTED at line: ");
                printf("%d\n", lineNum);
                printf("%s\n", "The line: ");
                printf("%s\n", line);
                printf("Press enter to exit...\n");
                getchar();
                exit(1);
            }

            for (int j = 0; j < strlen(word); ++j) {
                if(isascii(word[j]) == 0 ){
                    printf("%s", "NON ASCII CHAR DETECTED at line: ");
                    printf("%d\n", lineNum);
                    printf("%s\n", "The line: ");
                    printf("%s", line);
                    printf("\n%s\n", "And the detected word is: ");
                    printf("%s\n\n", word);
                    printf("Press enter to exit...\n");
                    getchar();
                    exit(1);
                }
            }

            if (strlen(word) > 20){
                printf("%s", "IDENTIFIER NAME OR DIGIT NAME TOO LONG at line: ");
                printf("%d\n", lineNum);
                printf("%s\n", "The line: ");
                printf("%s\n", line);
                printf("\n%s\n", "And the detected word is: ");
                printf("%s\n\n", word);
                printf("Press enter to exit...\n");
                getchar();
                exit(1);
            }

            if (checkKeyword(word, fileName)) {
                lxFile = fopen(fileName, "a");
                if (isalpha(word[0])) {
                    fprintf(lxFile, "%s", "Identifier ");
                    fprintf(lxFile, "%s\n", word);
                    fclose(lxFile);
                }
            }

            if (line[i] == ','){
                lxFile = fopen(fileName, "a");
                fprintf(lxFile, "%s\n", "Separator");
                fclose(lxFile);
            }

            size = i + 1;
        }

        if (i == lineLen -1){
            word[i - size] = line[i];
            word[i - size+1] = '\0';
            if (checkKeyword(word, fileName)) {
                if (isalpha(word[0])) {
                    lxFile = fopen(fileName, "a");
                    fprintf(lxFile, "%s", "Identifier ");
                    fprintf(lxFile, "%s\n", word);
                    fclose(lxFile);
                }

            }
            size = i + 1;
        }

        if (line[i] == '.'){
            lxFile = fopen(fileName, "a");
            fprintf(lxFile, "%s\n", "EndOfLine");
            fclose(lxFile);
        }

        word[i - size] = line[i];
    }
    if(*inString == 1){
        word[point] = '\0';
        lxFile = fopen(fileName, "a");
        fprintf(lxFile, "%s", "StringConstant ");
        fprintf(lxFile, "%s", word);
        fprintf(lxFile, "%s\n", "\"");
        fclose(lxFile);
    }
    return 0;
}

int stringChecker(int inString, char line[], int point, int lineNum){

    if (inString == 0){
        // Currently not in string but string opener detected.
        if (point != 0 && line[point-1] != ' ' && line[point-1] != '\"'){
            printf("%s", "UNACCEPTED CHAR DETECTED at line: ");
            printf("%d\n", lineNum);
            printf("%s\n", "The line: ");
            printf("%s\n",line);
            printf("Press enter to exit...\n");
            getchar();
            exit(1);
        }
        return inString = 1;
    }

    if (inString == 1){
        // Currently in string but string closer detected.
        return inString = 0;
    }

    return inString;
}


int loopChecker(int inLoop, char currentChar, char line[], int lineNum, char fileName[]) {

    FILE * lxFile = fopen(fileName, "a");

    if (inLoop == 0 && currentChar == ']') {
        // if currently not in comment and char is comment closer
        printf("%s", "NO LOOP IS OPEN BUT A CLOSE LOOP CHAR IS DETECTED at line: ");
        printf("%d\n", lineNum);
        printf("%s\n", "The line: ");
        printf("%s\n", line);
    }

    if (currentChar == ']') {
        // if currently in loop and char is loop closer
        fprintf(lxFile, "%s\n", "CloseBlock");
        fclose(lxFile);
        return inLoop -= 1;
    }

    if (currentChar == '[') {
        // if currently not in loop and char is loop starter
        fprintf(lxFile, "%s\n", "OpenBlock");
        fclose(lxFile);
        return inLoop += 1;
    }

    return inLoop;
}

int commentChecker(int inComment, char currentChar, char line[], int lineNum) {

    if (inComment && currentChar == '}') {
        // if currently in comment and char is comment closer
        return inComment = 0;
    }

    if (inComment == 0 && currentChar == '{') {
        // if currently not in comment and char is comment starter
        return inComment = 1;
    }

    return inComment;
}