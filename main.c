#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "detectWord.h"
#include "interpreter.h"

int main() {

    FILE *lxFile; // .lx file pointer.
    FILE *baFile; // .ba file pointer.

    char line[255]; //  The line that was read from the file.

    char fileNameInput[255];
    char file_lx[255];
    char file_ba[255];

    int lineNum = 1;

    int inLoop = 0;
    int *pInLoop = &inLoop;

    int inComment = 0;
    int *pInComment = &inComment;

    int inString = 0;
    int *pInString = &inString;

    printf("%s", ">");







    //fgets(fileNameInput, 255, stdin);
    strcpy(fileNameInput, "la test\n");








    char word[255];
    int size = 0;
    for (int i = 0; i < strlen(fileNameInput); ++i) {
        if (fileNameInput[i] == ' ' || fileNameInput[i] == '\n'){
            word[i-size] ='\0';
            if (size == 0 && strcmp(word, "la")){
                printf("%s", "la KEYWORD NOT USED!\n");
                printf("Press enter to exit...\n");
                getchar();
                exit(1);
            }
            if (size != 0){
                break;
            }
            size = i + 1;
        }

        word[i-size] = fileNameInput[i];
        if (i == strlen(fileNameInput)-1 && size == 0){
            printf("%s", "la KEYWORD NOT USED!\n");
            printf("Press enter to exit...\n");
            getchar();
            exit(1);
        }
    }


    strcpy(file_lx, word);
    strcat(file_lx, ".lx");

    strcpy(file_ba, word);
    strcat(file_ba, ".ba");

    if ((baFile = fopen(file_ba, "r")) == NULL) {
        // Gives error if the file specified could not be opened.
        printf("Encountered an error while trying to read the .ba file specified!\n");
        printf("Press enter to exit...\n");
        getchar();
        exit(1);
    }
    printf("%s", file_ba);
    printf("%s\n\n", " is found.");

    if ((lxFile = fopen(file_lx, "w")) == NULL) {
        // Gives error if the file specified could not be opened.
        printf("Encountered an error while trying to create / recreate the .lx file!\n");
        printf("Press enter to exit...\n");
        getchar();
        exit(1);
    }
    printf("%s", file_lx);
    printf("%s\n\n", " is created successfully.");
    fclose(lxFile); // We opened the .lx file in write mode and closed it so it will start anew everytime.

    while (!feof(baFile)) {
        if (fgets(line, 255, baFile) == NULL){
            continue;
        }
        detectKeyword(line, pInLoop, pInComment, pInString, lineNum, file_lx);
        lineNum++;
        // Gets a line from the file and assigns it to a char array named line.
    }
    fclose(baFile);

    if (*pInLoop) {
        printf("\n%s\n", "LOOP DID NOT END BUT THE FILE ENDED");
        printf("Press enter to exit...\n");
        getchar();
        exit(1);
    }

    if (*pInComment) {
        printf("\n%s\n", "COMMENT DID NOT END BUT THE FILE ENDED");
        printf("Press enter to exit...\n");
        getchar();
        exit(1);
    }

    if (*pInString) {
        printf("\n%s\n", "STRING DID NOT END BUT THE FILE ENDED");
        printf("Press enter to exit...\n");
        getchar();
        exit(1);
    }

    interpreter(file_lx);


    printf("\n%s", "The program has ended. Press enter to exit...\n");
    getchar();
    exit(0);
}