#include <stdio.h> 
#include <stdlib.h> 
#include "hw2.h"
#include "linkedlist.h"

int main() 
{ 
    list_t* myList = CreateList(&mapping_tComparator, &mapping_tPrinter, &mapping_tDeleter);
    
    mapping_t* keyword1 = CreateMapping("for,0,91,1\n");
    InsertInOrder(myList, (void*) keyword1, 0);

    printf("******FOR******\n");    
    PrintLinkedList(myList);

    char temp[] = "else,0,43,0\n";
    mapping_t* keyword2 = CreateMapping(temp);
    InsertInOrder(myList, (void*) keyword2, 0);

    printf("******ELSE -> FOR******\n");    
    PrintLinkedList(myList);

    char* temp2 = "int,35,0,0\n";
    mapping_t* keyword3 = CreateMapping(temp2);
    InsertInOrder(myList, (void*) keyword3, 0);
    char temp3[15] = "return,35,0,1\n";
    mapping_t* keyword4 = CreateMapping(temp3);
    InsertInOrder(myList, (void*) keyword4, 0);

    printf("******ELSE -> FOR -> INT -> RETURN******\n");    
    PrintLinkedList(myList);

    keyword1 = CreateMapping("for,31,90,0\n");
    InsertInOrder(myList, (void*) keyword1, 1);

    printf("******FOR Updated******\n");    
    PrintLinkedList(myList);

    DestroyList(myList);

    printf("******After Destroy List******\n");
    //This should print nothing!
    PrintLinkedList(myList);
    printf("******************************\n");

    return 0; 
} 
