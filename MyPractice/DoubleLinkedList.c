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


// Append node into the head of the linked list
void prependNode(DNodeT *preExistNode, DNodeT *newNode){
    DNodeT *p = preExistNode;
    newNode->next = p->next;    // newNode next points to the head's original next
    newNode->previous = p;      // newNode previous points to the head
    p->next->previous = newNode;    // original next's previous equals to newNode
    p->next = newNode;      // change head's next to newNode
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


// Swap data of two nodes (not actually swap the nodes)
void swapNodeData(DNodeT *a, DNodeT *b){
    assert(a != NULL && b != NULL);
    int dataA = a->data;
    a->data = b->data;
    b->data = dataA;
}


// Bubble sort implementation
void bubbleSort(DNodeT *allNode){
    while (isSorted(allNode) == false){
        DNodeT *p = allNode;
        while (p->next != NULL){
            if (p->data > p->next->data){
                swapNodeData(p, p->next);
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
    DNodeT *p = allNode;
    while (p != NULL){
        DNodeT *toDelete = p;
        p = p->next;
        free(toDelete);
    }
}