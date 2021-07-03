#ifndef LXFORBIGADD_OPERATIONS_H
#define LXFORBIGADD_OPERATIONS_H

char *wordSeparator(char line[], int index);

int declaration(char line[], FILE *lxFile);

int assignment(char line[], FILE *lxFile);

int addition(char line[], FILE *lxFile);

int subtraction(char line[], FILE *lxFile);

int printOut(char line[], FILE *lxFile);

int loop(char line[], FILE *lxFile, char fileName[]);
#endif //LXFORBIGADD_OPERATIONS_H
