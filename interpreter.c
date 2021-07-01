#include "interpreter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int detectWordInterpreter();
int declaration();
int wordSeperator(char line[], char * words[]);

int interpreter(char fileName[]){

    FILE *lxFile;
    lxFile = fopen(fileName, "r");
    char line[255];
    char words[100][100];


    while (!feof(lxFile)) {
        if (fgets(line, 255, lxFile) == NULL) {
            break;
        }
        detectWordInterpreter(line, lxFile, words);
    }
        return 0;
}

int detectWordInterpreter(char line[],  FILE *lxFile, char words[]){

    wordSeperator(line, words);

    for(int i=0;i < 2;i++)
        if (!strcmp(words[i], "Keyword")){
            if (!strcmp(words[i+1], "int")){
                declaration(line, lxFile);
            }
            else if (!strcmp(words[i+1], "move")){

            }
            else if (!strcmp(words[i+1], "add")){

            }
            else if (!strcmp(words[i+1], "sub")){

            }
            else if (!strcmp(words[i+1], "out")){

            }

        }
    return 0;
}

int declaration(char line[], FILE *lxFile){

    fgets(line, 255, lxFile);

    return 0;
}

int * wordSeperator(char line[], char words[]){

    int i,j,ctr;

    j=0; ctr=0;
    for(i=0;i<=(strlen(line)); i++)
    {
        // if space or NULL found, assign NULL into words[ctr]
        if(line[i] == ' ' || line[i] == '\0' || line[i] == '\n')
        {
            words[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            words[ctr][j] = line[i];
            j++;
        }
    }

    return 0;
}