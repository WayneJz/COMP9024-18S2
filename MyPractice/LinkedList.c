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
// if indicated index beyond the max index, delete the tail (last node) of the linked list
void deleteNode(NodeT *preExistNode, int index){
    NodeT *p = preExistNode;
    int i = 0;
    while (i < index){
        if (p->next == NULL){
            break;
        }
        p = p->next;
        i += 1;
    }
    NodeT *toDelete = p->next;
    p->next = p->next->next;
    free(toDelete);
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


// Reverse the linked list
NodeT *reverseNode(NodeT *preExistNode){
    NodeT *p = preExistNode;
    NodeT *originNext;
    NodeT *newNext = NULL;      // initialize with NULL, as head's next will be the end of linked list

    while (p != NULL){
        originNext = p->next;     // store the original next
        p->next = newNext;      // adjust current's next equals to the new next (for head is NULL)
        newNext = p;            // change new next to the current node
        p = originNext;         // move p to its origin next
    }
    return newNext;
}


// Iterate and print all nodes of the linked list
void printNode(NodeT *allNode){
    NodeT *p = allNode;
    while (p != NULL){
        printf("%d\n", p->data);
        p = p->next;
    }
}