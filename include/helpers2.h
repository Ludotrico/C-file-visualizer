


#ifndef HELPERS_2_H
#define HELPERS_2_H

#include "hw2.h"

// Declare all helper functions for hw2 in this file

int isCharacter(int c);
int areEquivalent(char* token, int length, char* target);
int processLine(FILE* fp, int maxLines, list_t * linkedList, int isCommented);
#endif