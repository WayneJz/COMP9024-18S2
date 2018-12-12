// Created by Zhou JIANG

#include <stdbool.h>

typedef struct DNode{
    int data;
    struct DNode *next;
    struct DNode *previous;
}DNodeT;


DNodeT *createNode(int);
void appendNode(DNodeT*, DNodeT*);
void prependNode(DNodeT*, DNodeT*);
void insertNode(DNodeT*, int, DNodeT*);
void editNode(DNodeT*, int, int);
bool deleteNode(DNodeT*, int);
bool deleteNodeByData(DNodeT*, int);
bool isSorted(DNodeT*);
void swapNodeData(DNodeT*, DNodeT*);
void bubbleSort(DNodeT*);
DNodeT *reverseNode(DNodeT*);
void printNode(DNodeT*);
void reversePrint(DNodeT*);
void dropNode(DNodeT*);