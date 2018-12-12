// Created by Zhou JIANG

#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node *next;
}NodeT;


NodeT *createNode(int);
void appendNode(NodeT*, NodeT*);
void prependNode(NodeT*, NodeT*);
void insertNode(NodeT*, int, NodeT*);
void editNode(NodeT*, int, int);
void deleteNode(NodeT*, int);
bool deleteNodeByData(NodeT*, int);
NodeT *reverseNode(NodeT*);
void printNode(NodeT*);
