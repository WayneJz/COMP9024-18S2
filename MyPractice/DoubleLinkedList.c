// Created by Zhou JIANG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "DoubleLinkedList.h"


// New node creator
DNodeT *createNode(int newData){
    DNodeT *newNode = malloc(sizeof(DNodeT));
    assert(newNode != NULL);
    newNode->data = newData;
    newNode->next = NULL;
    newNode->previous = NULL;
    return newNode;
}


// Append node into the tail of the linked list
void appendNode(DNodeT *preExistNode, DNodeT *newNode){
    DNodeT *p = preExistNode;
    while (p->next != NULL){
        p = p->next;
    }
    p->next = newNode;
    newNode->previous = p;
}


// Pre-Append node into the head of the linked list
/*
    1. newNode next points to the head's original next
    2. newNode previous points to the head
    3. original next's (if exists) previous pointer points to newNode
    4. change head's next to newNode
*/
void prependNode(DNodeT *head, DNodeT *newNode){
    newNode->next = head->next;
    newNode->previous = head;
    if (head->next != NULL){
        head->next->previous = newNode;
    }
    head->next = newNode;
}


// Return the length of the linked list
int length(DNodeT *preExistNode){
    int len = 0;
    while (preExistNode != NULL){
        len += 1;
        preExistNode = preExistNode->next;
    }
    return len;
}


// Insert node into the indicated position
// if indicated index beyond the max index, append the node into the tail of the linked list
void insertNode(DNodeT *preExistNode, int index, DNodeT *newNode){
    DNodeT *p = preExistNode;
    int i = 0;
    while (i < index){
        if (p->next == NULL){
            return appendNode(preExistNode, newNode);
        }
        p = p->next;
        i += 1;
    }
    newNode->next = p->next;
    newNode->previous = p;
    p->next->previous = newNode;
    p->next = newNode;
}


// Edit node with new data by indicated position
// if indicated index beyond the max index, edit the last node (tail) of the linked list
void editNode(DNodeT *preExistNode, int index, int newData){
    DNodeT *p = preExistNode;
    int i = 0;
    while (i < index){
        if (p->next == NULL){
            break;
        }
        p = p->next;
        i += 1;
    }
    p->next->data = newData;
}


// Delete node by indicated position
// if indicated index beyond the max index, return false
bool deleteNode(DNodeT *preExistNode, int index){
    DNodeT *p = preExistNode;
    int i = 0;
    while (i < index){
        if (p->next == NULL){
            return false;
        }
        p = p->next;
        i += 1;
    }
    DNodeT *toDelete = p->next;
    p->next = p->next->next;
    p->next->previous = p;
    free(toDelete);
    return true;
}


// Delete node by indicated data (first-occurrence)
bool deleteNodeByData(DNodeT *preExistNode, int indicatedData){
    DNodeT *p = preExistNode;
    while (p->next != NULL){
        if (p->next->data == indicatedData){
            DNodeT *toDelete = p->next;
            p->next = p->next->next;
            p->next->previous = p;
            free(toDelete);
            return true;
        }
        p = p->next;
    }
    return false;
}


// Delete duplicated nodes (only reserve first-occurrence data node)
void deleteDuplicateNode(DNodeT *preExistNode){
    DNodeT *p = preExistNode;
    while (p != NULL){
        int currentData = p->data;
        DNodeT *dupCheck = p;
        while (dupCheck->next != NULL){
            if (dupCheck->next->data == currentData){
                DNodeT *toDelete = dupCheck->next;
                dupCheck->next = dupCheck->next->next;
                dupCheck->next->previous = dupCheck;
                free(toDelete);
            }
            dupCheck = dupCheck->next;
        }
        p = p->next;
    }
}


// Return true if the linked list is totally sorted
bool isSorted(DNodeT *allNode){
    DNodeT *p = allNode;
    while (p->next != NULL){
        if (p->data > p->next->data){
            return false;
        }
        p = p->next;
    }
    return true;
}


// Swap two nodes
/*
    HEAD <-> A <-> B <-> LAST

    1. HEAD's next pointer points to B
    2. A's next pointer points to LAST
    3. B's previous pointer points to HEAD
    4. LAST's (if exists) previous pointer points to A
    5. B's next pointer points to A
    6. A's previous pointer points to B
*/

void swapNode(DNodeT *a, DNodeT *b){
    assert(a != NULL && b != NULL);
    a->previous->next = b;
    a->next = b->next;
    b->previous = a->previous;
    if (b->next != NULL){
        b->next->previous = a;
    }
    b->next = a;
    a->previous = b;
}


// Bubble sort implementation
void bubbleSort(DNodeT *allNode){
    int i;
    for (i = 0; i < length(allNode); i ++){
        DNodeT *p = allNode;
        while (p != NULL && p->next != NULL){
            if (p->data > p->next->data){
                printf("swap %d %d\n", p->data, p->next->data);
                swapNode(p, p->next);
            }
            p = p->next;
        }
    }
}


// Reverse the linked list
DNodeT *reverseNode(DNodeT *preExistNode){
    DNodeT *p = preExistNode;
    DNodeT *originNext;
    DNodeT *newNext = NULL;     // initialize with NULL, as head's next will be the end of linked list

    while (p != NULL){
        originNext = p->next;   // store the original next
        p->next = newNext;      // adjust current's next equals to the new next (for head is NULL)
        p->previous = originNext;       // adjust current's previous equals to the original next
        newNext = p;    // change new next to the current node, for next iteration
        p = originNext;     // move p to its origin next
    }
    return newNext;
}


// Iterate and print all nodes of the linked list
void printNode(DNodeT *allNode){
    DNodeT *p = allNode;
    printf("Display the linked list below:\n");
    while (p->next != NULL){
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("%d\n", p->data);
}


// Iterate and reversely print all nodes of the linked list (not actually reverse it)
void reversePrint(DNodeT *allNode){
    DNodeT *p = allNode;
    while (p->next != NULL){
        p = p->next;
    }
    printf("Reversely display the linked list below:\n");
    while (p->previous != NULL){
        printf("%d -> ", p->data);
        p = p->previous;
    }
    printf("%d\n", p->data);
}


// Release all nodes
void dropNode(DNodeT *allNode){
    printf("Nodes have been released:\n");
    while (allNode != NULL){
        DNodeT *temp = allNode->next;
        printf("%d ", allNode->data);
        free(allNode);
        allNode = temp;
    }
    printf("\n");
}