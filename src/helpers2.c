// Define all helper functions for hw2 in this file
#include "hw2.h"


int isCharacter(int c) {
    int val = 0;
    if ((c >= 48) && (c <= 57)) {
        val = 1;
    }
     if ( c == 95 ) {
        val = 1;
    }
    if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122))) {
        val = 1;
    }

    return val;
}


int areEquivalent(char* token, int length, char* target) {
    int i;
    for (i = 0; i <= length; i++) {
        if ((i == length)) {
            if (isCharacter(*target) ) {
                return 0;
            } else {
                return 1;
            }
        } 
        if ((*token) != (*target)) {
            return 0;
        }
        token++;
        target++;
    }
    return 1;
    
}

int lineIsComment(char * line) {
    while ((*line != '\n') && (*line != '\0')) {
        if ( (*line == '/') && (*(line+1) =='/')) {
            return 1;
        } 
        line++;
    }
    return 0;
}



int lineBeginsCommentChunk(char * line) {
    while ((*line != '\n') && (*line != '\0')) {
        if ( (*line == '/') && (*(line+1) =='*')) {
            return 1;
        } 
        line++;
    }
    return 0;
}


int lineEndsCommentChunk(char * line) {
    while ((*line != '\n') && (*line != '\0')) {
        if ( (*line == '*') && (*(line+1) =='/')) {
            return 1;
        } 
        line++;
    }
    return 0;
}

int processLine(FILE* fp, int maxLines, list_t * linkedList, int isCommented) {
    char * line = NULL;
    size_t len = 0;
    ssize_t lineSize = 0;

    int currLineCount = 0;

    int tokenLength = 0;
    char **token = NULL;

    mapping_t * val = NULL;
    int i;
    //int isCommented = 0;

    char* tmp = NULL;
    char* tmpp = NULL;
    int isComment = 0;
    int endsCommentChunk = 0;

    while (currLineCount < maxLines) {
        lineSize = getline(&line, &len, fp);
        
        if (lineSize == -1) {

            return -1;
        }





        if (!isCommented) {
            isCommented = lineIsComment(line) || lineBeginsCommentChunk(line);
        } 
        isComment = lineIsComment(line);
        endsCommentChunk = lineEndsCommentChunk(line);
 
        


        tmp = &(*line);
        token = &tmp;

        while (1) {
            tokenLength = FindNextToken(line, token);
            /*
            printf("DEBUG: tokenLength: %d\n", tokenLength);
            printf("DEBUG: line: %s\n", line);
            printf("DEBUG: tokenStart: %s\n", *token);
            */
            
            if (tokenLength && !isCommented) {
                while (line != (*token)) {
                    //printf("DEBUG: in char loop\n");
                    printf("%c", *line);
                    line++;
                }

                val = MatchKeyword(*token, tokenLength, linkedList);
                if (val != NULL) {
                    PrintFormatKeyword(val);
                    line += tokenLength;
                }
                else {
                    for (i=0; i < tokenLength; i++) {
                        printf("%c", **token);
                        (*token)++;
                    }
                    line = *token;
                }
                
            } else {
                printf("%s", line);
                break;
            }

            
            
      
            
        }




        //printf("iscommented: %d\n", isCommented);

        if (isCommented) {
            
            //Chunk
            if (  endsCommentChunk  || isComment  ) {
                isCommented = 0;
            }
        }


        currLineCount++;
        //printf("%s", line);

    }

  


    return isCommented;

    
   
}