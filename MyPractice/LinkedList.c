// Created by Zhou JIANG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "LinkedList.h"


// New node creator
NodeT *createNode(int newData){
    NodeT *newNode = malloc(sizeof(NodeT));
    assert(newNode != NULL);
    newNode->data = newData;
    newNode->next = NULL;
    return newNode;
}


// Append node into the tail of the linked list
void appendNode(NodeT *preExistNode, NodeT *newNode){
    NodeT *p = preExistNode;
    while (p->next != NULL){
        p = p->next;
    }
    p->next = newNode;
}


// Append node into the head of the linked list
void prependNode(NodeT *preExistNode, NodeT *newNode){
    NodeT *p = preExistNode;
    newNode->next = p->next;
    p->next = newNode;
}


// Return the length of the linked list
int length(NodeT *preExistNode){
    int len = 0;
    while (preExistNode != NULL){
        len += 1;
        preExistNode = preExistNode->next;
    }
    return len;
}


// Insert node into the indicated position
// if indicated index beyond the max index, append the node into the tail of the linked list
void insertNode(NodeT *preExistNode, int index, NodeT *newNode){
    NodeT *p = preExistNode;
    int i = 0;
    while (i < index){
        if (p->next == NULL){
            return appendNode(preExistNode, newNode);
        }
        p = p->next;
        i += 1;
    }
    newNode->next = p->next;
    p->next = newNode;
}


// Edit node with new data by indicated position
// if indicated index beyond the max index, edit the last node (tail) of the linked list
void editNode(NodeT *preExistNode, int index, int newData){
    NodeT *p = preExistNode;
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
bool deleteNode(NodeT *preExistNode, int index){
    NodeT *p = preExistNode;
    int i = 0;
    while (i < index){
        if (p->next == NULL){
            return false;
        }
        p = p->next;
        i += 1;
    }
    NodeT *toDelete = p->next;
    p->next = p->next->next;
    free(toDelete);
    return true;
}


// Delete node by indicated data (first-occurrence)
bool deleteNodeByData(NodeT *preExistNode, int indicatedData){
    NodeT *p = preExistNode;
    while (p->next != NULL){
        if (p->next->data == indicatedData){
            NodeT *toDelete = p->next;
            p->next = p->next->next;
            free(toDelete);
            return true;
        }
        p = p->next;
    }
    return false;
}


// Delete duplicated nodes (only reserve first-occurrence data node)
void deleteDuplicateNode(NodeT *preExistNode){
    NodeT *p = preExistNode;
    while (p != NULL){
        int currentData = p->data;
        NodeT *dupCheck = p;
        while (dupCheck->next != NULL){
            if (dupCheck->next->data == currentData){
                NodeT *toDelete = dupCheck->next;
                dupCheck->next = dupCheck->next->next;
                free(toDelete);
            }
            dupCheck = dupCheck->next;
        }
        p = p->next;
    }
}


// Return true if the linked list is totally sorted
bool isSorted(NodeT *allNode){
    NodeT *p = allNode;
    while (p->next != NULL){
        if (p->data > p->next->data){
            return false;
        }
        p = p->next;
    }
    return true;
}


// Swap two nodes
void swapNode(NodeT *previous, NodeT *a, NodeT *b){
    assert(previous != NULL && previous->next == a && a != NULL && b != NULL);
    a->next = b->next;
    b->next = a;
    previous->next = b;
}


// Bubble sort implementation
void bubbleSort(NodeT *allNode){
    int i;
    for (i = 0; i < length(allNode); i ++){
        NodeT *p = allNode;
        while (p != NULL && p->next != NULL && p->next->next != NULL){
            if (p->next->data > p->next->next->data){
                swapNode(p, p->next, p->next->next);
            }
            p = p->next;
        }
    }
}


// Reverse the linked list
NodeT *reverseNode(NodeT *preExistNode){
    NodeT *p = preExistNode;
    NodeT *originNext;
    NodeT *newNext = NULL;      // initialize with NULL, as head's next will be the end of linked list

    while (p != NULL){
        originNext = p->next;     // store the original next
        p->next = newNext;      // adjust current's next equals to the new next (for head is NULL)
        newNext = p;            // change new next to the current node, for next iteration
        p = originNext;         // move p to its origin next
    }
    return newNext;
}


// Iterate and print all nodes of the linked list
void printNode(NodeT *allNode){
    NodeT *p = allNode;
    printf("Display the linked list below:\n");
    while (p->next != NULL){
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("%d\n", p->data);
}


// Release all nodes
void dropNode(NodeT *allNode){
    printf("Nodes have been released:\n");
    while (allNode != NULL){
        NodeT *temp = allNode->next;
        printf("%d ", allNode->data);
        free(allNode);
        allNode = temp;
    }
    printf("\n");
}