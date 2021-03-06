#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "detectWord.h"
#include "interpreter.h"

int main(int argc, char *argv[]) {

    FILE *lxFile; // .lx file pointer.
    FILE *baFile; // .ba file pointer.

    char line[255]; //  The line that was read from the file.

    char fileNameInput[255];

    if (argc == 2){
        strcpy(fileNameInput, argv[1]);
    }

    else{
        printf("%s", "Parameter problem occured!\nGiven parameter number: ");
        printf("%d", argc-1);
        printf("%s", "\nExpected: 1\nPress enter to exit...");
        getchar();
        exit(1);
    }

    char file_lx[255];
    char file_ba[255];

    int lineNum = 1;

    int inLoop = 0;
    int *pInLoop = &inLoop;

    int inComment = 0;
    int *pInComment = &inComment;

    int inString = 0;
    int *pInString = &inString;

    char word[255];
    int size = 0;
    for (int i = 0; i < strlen(fileNameInput); ++i) {

        if (i+1 == strlen(fileNameInput)) {
            word[i+1] = '\0';
        }

        word[i-size] = fileNameInput[i];
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

    if ((lxFile = fopen(file_lx, "w")) == NULL) {
        // Gives error if the file specified could not be opened.
        printf("Encountered an error while trying to create / recreate the .lx file!\n");
        printf("Press enter to exit...\n");
        getchar();
        exit(1);
    }
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

    if (*pInLoop > 0) {
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