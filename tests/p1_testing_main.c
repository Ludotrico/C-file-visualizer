#include <stdio.h>
#include <stdlib.h>

#include "helpers2.h"
#include "hw2.h"
#include "linkedlist.h"

int main() {
    list_t* list = GenerateDefaultFormatMappings();
    node_t* head = list->head;

    // Test PrintFormatKeyword
    printf("****PRINTFORMATKEYWORD*****\n\n");
    // Verify on the terminal that the keyword is printed in red
    PrintFormatKeyword(head->data);
    printf("\n");

    // Test for FindNextToken
    printf("****FINDNEXTTOKEN*****\n\n");
    char* testStr = "int first_sum = sum_array(first_nums, 5);";
    printf("The starting address of testStr is %s\n", testStr);
    fflush(stdout);
    char** myToken = &testStr;
    int x = FindNextToken(testStr,myToken);
    if(x != 0)
        printf("The token starts at %p, has length %d. The token itself is %.*s\n", &myToken, x, x, *myToken);
    else
        printf("There are no tokens in the string.\n"); 

    // Test for MatchKeyword
    printf("****MATCHKEYWORD*****\n\n");
    char* token = "int";
    mapping_t* mapping = MatchKeyword(token, 3, list);
    if (mapping == NULL) {
        printf("Mapping was not found for keyword \"int\"\n");
    } else {
        char* mapping_token = mapping->keyword;
        while (*mapping_token != '\0') {
            if (*mapping_token != *token) {
                printf("Mapping token does not match \"int\"\n");
                return 1;
            }
            mapping_token++;
            token++;    
        }
        printf("Mapping token keyword matches \"int\"\n");
    }
    //PrintLinkedList(list);

    DestroyDefaultFormatMappings(list);
    return 0;
}
