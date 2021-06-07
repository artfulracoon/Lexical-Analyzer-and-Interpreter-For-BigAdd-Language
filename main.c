#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "detectWord.h"

int main() {

    FILE *lxFile; // .lx file pointer.
    FILE *baFile; // .ba file pointer.

    char line[255]; //  The line that was read from the file.

    char fileNameInput[255];
    char file_lx[255];
    char file_ba[255];

    int lineNum = 0;

    int inLoop = 0;
    int *pInLoop = &inLoop;

    int inComment = 0;
    int *pInComment = &inComment;

    int inString = 0;
    int *pInString = &inString;

    printf("%s\n", "Please enter the .ba file name without including .ba: ");
    scanf("%s", fileNameInput);

    printf("\n");

    strcpy(file_lx, fileNameInput);
    strcat(file_lx, ".lx");

    strcpy(file_ba, fileNameInput);
    strcat(file_ba, ".ba");

    if ((lxFile = fopen(file_lx, "w")) == NULL) {
        // Gives error if the file specified could not be opened.
        printf("Encountered an error while trying to create / rewrite the .lx file!\n");
        exit(1);
    }
    printf("%s", file_lx);
    printf("%s\n\n", " is created successfully.");
    fclose(lxFile); // We opened the .lx file in write mode and closed it so it will start anew everytime.

    if ((baFile = fopen(file_ba, "r")) == NULL) {
        // Gives error if the file specified could not be opened.
        printf("Encountered an error while trying to open the .ba file specified!\n");
        exit(1);
    }

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
    }

    if (*pInComment) {
        printf("\n%s\n", "COMMENT DID NOT END BUT THE FILE ENDED");
    }

    if (*pInString) {
        printf("\n%s\n", "STRING DID NOT END BUT THE FILE ENDED");
    }
    printf("\n%s", "The program has ended. You can safely close this window.");
    scanf("%s", fileNameInput);
    return 0;
}