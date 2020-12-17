// DO NOT MODIFY THIS FILE
// Any additions should be placed in helpers2.h

#ifndef HW_2_H
#define HW_2_H

#define USAGE_MSG "53color [-h] [-k format_file] [-l line_count] c_file\n"                                                \
                  "\n  -h    Displays the help menu"                                                                      \
                  "\n  -k    format_file Specifies the name of the keyword mapping file"                                  \
                  "\n  -l    line_count Specifies the number of lines to print interactively. If unspecified, 24 is used" 


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "linkedlist.h"
#include "helpers2.h"

typedef struct {
    int fg_color;
    int bg_color;
    int is_bold;
} format_info_t;

typedef struct {
    char* keyword;
    format_info_t format;
} mapping_t;

// Part 1 Functions to implement
void PrintFormatKeyword(mapping_t* mapping);
int FindNextToken(char* start, char** token);
mapping_t* MatchKeyword(char* token, int token_length, list_t* list);

// Part 2 Functions to implement
void mapping_tPrinter(void* val_ref);
int mapping_tComparator(void* lhs, void* rhs);
void mapping_tDeleter(void* val_ref);
void DestroyList(list_t* list);
mapping_t* CreateMapping(char* line);

#endif
