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
int length(DNodeT*);
void insertNode(DNodeT*, int, DNodeT*);
void editNode(DNodeT*, int, int);
bool deleteNode(DNodeT*, int);
bool deleteNodeByData(DNodeT*, int);
void deleteDuplicateNode(DNodeT*);
bool isSorted(DNodeT*);
void swapNode(DNodeT*, DNodeT*);
void bubbleSort(DNodeT*);
DNodeT *reverseNode(DNodeT*);
void printNode(DNodeT*);
void reversePrint(DNodeT*);
void dropNode(DNodeT*);