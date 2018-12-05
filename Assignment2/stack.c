// Stack ADT implementation ... COMP9024 18s2

// Provided by Micheal Thielscher, functionality added by Zhou JIANG

#include <stdlib.h>
#include <assert.h>
#include "stack.h"

#define MAXDIV 1000

typedef struct node {
    int data;
    struct node *next;
} NodeT;

typedef struct StackRep {
    int    height;
    NodeT *top;
} StackRep;

// set up empty stack
stack newStack() {
    stack S = malloc(sizeof(StackRep));
    S->height = 0;
    S->top = NULL;
    return S;
}

// remove unwanted stack
void dropStack(stack S) {
    NodeT *curr = S->top;
    while (curr != NULL) {
        NodeT *temp = curr->next;
        free(curr);
        curr = temp;
    }
    free(S);
}

// check whether stack is empty
int StackIsEmpty(stack S) {
    return (S->height == 0);
}

// insert an int on top of stack
void StackPush(stack S, int v) {
    NodeT *new = malloc(sizeof(NodeT));
    assert(new != NULL);
    new->data = v;
    new->next = S->top;
    S->top = new;
    S->height++;
}

// remove int from top of stack
int StackPop(stack S) {
    assert(S->height > 0);
    NodeT *head = S->top;
    S->top = S->top->next;
    S->height--;
    int d = head->data;
    free(head);
    return d;
}


// Added function: stack top
// Time complexity: O(1)
// Explanation : This is constant time complexity as there is no loop
// return the top element of the stack without popping it

int StackTop(stack S){
    assert(S->height > 0);
    return (S->top->data);
}


// Added function: stack iteration
// Time complexity: O(n)
// Explanation : This is linear time complexity as there is one "while" loop
// to iterate the whole stack and add all stack elements to an array
// return the pointer to the array

int * StackIterate(stack S){
    assert(S->height > 0);
    NodeT *head = S->top;
    static int element[MAXDIV];
    int i = 0;

    // iterate the whole stack and add elements into the array
    while (head != NULL){
        element[i] = head->data;
        head = head->next;
        i += 1;
    }

    // setting -1 as a symbol to indicate where the stack ends
    element[i] = -1;
    free(head);
    return element;
}