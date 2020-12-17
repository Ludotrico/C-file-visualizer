// Your Name
// NetId

#include "hw2.h"

// Part 1  Functions to implement
void PrintFormatKeyword(mapping_t* mapping) {
    if (mapping == NULL) 
        return;
    
    if (mapping->format.fg_color && !mapping->format.bg_color) { 
        printf("\e[%d;%dm%s\e[0m", mapping->format.is_bold, mapping->format.fg_color, mapping->keyword);
    } else if (!mapping->format.fg_color && mapping->format.bg_color) { 
        printf("\e[%d;%dm%s\e[0m", mapping->format.is_bold, mapping->format.bg_color, mapping->keyword);
    } else {
         printf("\e[%d;%d;%dm%s\e[0m", mapping->format.is_bold, mapping->format.fg_color, mapping->format.bg_color, mapping->keyword);
    }
    


    
}

int FindNextToken(char* start, char** token) {
    if ((start == NULL)) {
        return 0;
    }


    int length = 0;
    int foundCharacter = 0;
    char* startOfToken = NULL;
    while ( ((*start) != '\0')) {
        if (isCharacter(*start)) {
            if (!foundCharacter) {
                startOfToken = start;
            }
            foundCharacter = 1;
            length++;
        } else if (foundCharacter) {
            break;
        }
        
        start++;
        
    }
    (*token) = startOfToken;

    return length;
}

mapping_t* MatchKeyword(char* token, int token_length, list_t* list) {
    if ((token == NULL) || (list == NULL)) {
        return NULL; 
    } 
    node_t* head = list->head;
    while (head != NULL) {
        mapping_t * mapping = (mapping_t*)head->data;
        if (areEquivalent(token, token_length, mapping->keyword)) {
            return mapping;
        }
        head = head->next;
    }

    return NULL;
}

// Part 2 Functions to implement

void mapping_tPrinter(void* val_ref) {
    mapping_t * val = (mapping_t*)val_ref;
    fprintf(stderr, "Keyword: %s\n", val->keyword);
    fprintf(stderr, "FG color: %d\n", val->format.fg_color);
    fprintf(stderr, "BG color: %d\n", val->format.bg_color);
    fprintf(stderr, "Bold bit: %d\n", val->format.is_bold);
}


int mapping_tComparator(void* lhs, void* rhs) {
    mapping_t * lhsMap = (mapping_t*)lhs;
    mapping_t * rhsMap =  (mapping_t*)rhs;
    int count = 0;

    while (isCharacter(*(lhsMap->keyword))) {
        if (*(lhsMap->keyword) < *(rhsMap->keyword)) {
            (rhsMap->keyword)-=count;
            (lhsMap->keyword)-=count;
            return -1;
        } else if (*(lhsMap->keyword) > *(rhsMap->keyword)) {
            (rhsMap->keyword)-=count;
            (lhsMap->keyword)-=count;
            return 1;
        }
        (rhsMap->keyword)++;
        (lhsMap->keyword)++;
        count++;
    }

    return 0; //==  
}

void mapping_tDeleter(void* val_ref) {
    mapping_t * val = (mapping_t*)val_ref;


    free(val->keyword);

    free(val);
}

void DestroyList(list_t* list) {
    if (list == NULL) {
        return;
    }
    node_t * head = list->head;
    node_t * tmp;
    
    while (head != NULL) {
        mapping_tDeleter(head->data);
        tmp = head;         
        head = head->next;

        free(tmp);
    }

    free(list);

}

mapping_t* CreateMapping(char* line) {
    char * keywordTmp = &(*line);
    mapping_t * map = malloc(sizeof(mapping_t));
    int keywordLength = 0;
    
    char * FGtmp;
    char * FGstr;
    int FGlength = 0;
    
    char * BGtmp;
    char * BGstr;
    int BGlength = 0;
    
    //int,35,0,0
    
    //Keyword
    while (isCharacter(*line)) {
        line++;
        keywordLength++;
    }
    line++;
    FGtmp = &(*line);
    
    map->keyword = malloc(sizeof(char) * keywordLength);
    int i;
    for (i = 0; i <= keywordLength; i++) {
        if (i == keywordLength) {
            *(map->keyword) = '\0';
        } else {
            *(map->keyword) = *keywordTmp;
            (map->keyword)++;
            keywordTmp++;
        }
    }
    
    (map->keyword)-=keywordLength;
    
    
    //FG color
    while (isCharacter(*line)) {
        line++;
        FGlength++;
    }
    line++;
    BGtmp = &(*line);
    
    
    FGstr = malloc(sizeof(char)*(FGlength+1));
    for (i = 0; i <= FGlength; i++) {
        if (i == FGlength) {
            *FGstr = '\0';
        } else {
            *FGstr = *FGtmp;
            FGstr++;
            FGtmp++;
        }
    }
    FGstr -= FGlength;
    map->format.fg_color = atoi(FGstr);
    
    
    //BG color
    while (isCharacter(*line)) {
        line++;
        BGlength++;
    }
    line++;
    
    BGstr = malloc(sizeof(char)*(BGlength+1));
    for (i = 0; i <= BGlength; i++) {
        if (i == BGlength) {
            *BGstr = '\0';
        } else {
            *BGstr = *BGtmp;
            BGstr++;
            BGtmp++;
        }
    }
    BGstr -= BGlength;
    map->format.bg_color = atoi(BGstr);
    
    //Bold bit
    if (*line == '0') {
        map->format.is_bold = 0;
    } else {
        map->format.is_bold = 1;
    }
    
    return map;
    
}


