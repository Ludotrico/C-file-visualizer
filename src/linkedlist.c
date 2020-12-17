/*
    What is a linked list?
    A linked list is a set of dynamically allocated nodes, arranged in
    such a way that each node contains one value and one pointer.
    The pointer always points to the next member of the list.
    If the pointer is NULL, then it is the last node in the list.

    A linked list is held using a local pointer variable which
    points to the first item of the list. If that pointer is also NULL,
    then the list is considered to be empty.
    -------------------------------               ------------------------------              ------------------------------
    |HEAD                         |             \ |              |             |            \ |              |             |
    |                             |-------------- |     DATA     |     NEXT    |--------------|     DATA     |     NEXT    |
    |-----------------------------|             / |              |             |            / |              |             |
    |LENGTH                       |               ------------------------------              ------------------------------
    |COMPARATOR                   |
    |PRINTER                      |
    |DELETER                      |
    -------------------------------                                         
*/
#include "linkedlist.h"
#include "hw2.h"

list_t* CreateList(int (*compare)(void*, void*), void (*print)(void*),
                   void (*delete)(void*)) {
    list_t* list = malloc(sizeof(list_t));
    list->comparator = compare;
    list->printer = print;
    list->deleter = delete;
    list->length = 0;
    list->head = NULL;
    return list;
}

void PrintLinkedList(list_t* list) {
    node_t* head = list->head;
    while (head != NULL) {
        list->printer(head->data);
        fprintf(stderr, "\n");
        head = head->next;
    }
}

void InsertAtHead(list_t* list, void* val_ref) {
    if (list->length == 0) list->head = NULL;

    node_t** head = &(list->head);
    node_t* new_node;
    new_node = malloc(sizeof(node_t));

    new_node->data = val_ref;

    new_node->next = *head;

    // moves list head to the new node
    *head = new_node;
    list->length++;
}

void InsertAtTail(list_t* list, void* val_ref) {
    if (list->length == 0) {
        InsertAtHead(list, val_ref);
        return;
    }

    node_t* head = list->head;
    node_t* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(node_t));
    current->next->data = val_ref;
    current->next->next = NULL;
    list->length++;
}


// Part 2 Function to update
void InsertInOrder(list_t* list, void* val_ref, int overwrite) {
    /*
    if (list->length == 0) {
        InsertAtHead(list, val_ref);
        return;
    }

    node_t** head = &(list->head);
    node_t* new_node;
    new_node = malloc(sizeof(node_t));
    new_node->data = val_ref;
    new_node->next = NULL;
    int comparision = list->comparator(new_node->data, (*head)->data);
    node_t * tmp;

    //New node is smaller than head
    if (comparision == 0) {
        tmp = (*head);
        new_node->next = (*head)->next;
        *head = new_node;
        free(tmp);
    } else if (comparision < 0) {
        new_node->next = *head;
        *head = new_node;
    } else if ((*head)->next == NULL) {
        (*head)->next = new_node;
    } else {
        node_t* prev = *head;
        node_t* current = prev->next;
        while (current != NULL) {
            comparision = list->comparator(new_node->data, current->data);
            if (comparision == 0) {
                tmp = current;
                new_node->next = current->next;
                prev->next = new_node;
                free(current);
            } else if (comparision > 0) {
                if (current->next != NULL) {
                    prev = current;
                    current = current->next;
                } else {
                    current->next = new_node;
                    break;
                }
            } else {
                prev->next = new_node;
                new_node->next = current;
                break;
            }
        }
    }
    list->length++;
    */

    if (list->length == 0) {
        InsertAtHead(list, val_ref);
        return;
    }

    node_t** head = &(list->head);
    node_t* new_node;
    new_node = malloc(sizeof(node_t));
    new_node->data = val_ref;
    new_node->next = NULL;
    node_t * curr = list->head;
    node_t * tmp;
    int comparison;
    int count = 0;

 

    
    if (list->comparator(new_node->data, (*head)->data) == 0) {
        //New node is equal to head
        if (!overwrite) {
            return;
        }

        //tmp = (*head);
        new_node->next = (*head)->next;
        *head = new_node;
        list->length--;
        //free(tmp);
    } else if (list->comparator(new_node->data, (*head)->data) < 0) {
        //New node is less than head
        new_node->next = *head;
        *head = new_node;
    } else if ((*head)->next == NULL) {
        //New node is greater than head but length of list is 1
        (*head)->next = new_node;
    } else {
        //New node is greater than head but length of list > 1
        node_t* prev = *head;
        node_t* current = prev->next;
        while (current != NULL) {
            comparison = list->comparator(new_node->data, current->data);
            if (comparison == 0) {
                //New node is equal to curr
                if (!overwrite) {
                    return;
                }
                //tmp = current;
                new_node->next = current->next;
                prev->next = new_node;
                //free(current);
                list->length--;
                break;
            }  else if (comparison < 0) {
                //New node is less than curr
                prev->next = new_node;
                new_node->next = current;
                break;
            } else  {
                //New node is grater than curr, keep searching
                if (current->next != NULL) {
                    prev = current;
                    current = current->next;
                } else {
                    current->next = new_node;
                    break;
                }
            }
        }
    }
    list->length++;
}
