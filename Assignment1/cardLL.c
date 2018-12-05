// Linked list of transport card records implementation ... Assignment 1 COMP9024 18s2
// Written by Zhou JIANG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cardLL.h"
#include "cardRecord.h"

// linked list node type
// DO NOT CHANGE
typedef struct node {
    cardRecordT data;
    struct node *next;
} NodeT;

// linked list type
typedef struct ListRep {
    NodeT *head;

/* Add more fields if you wish */

} ListRep;

/*** Your code for stages 2 & 3 starts here ***/

// Time complexity: O(1)
// Explanation: This is constant complexity as it initializes memory and LL

List newLL() {
    // allocate memory for empty linked list type
    List linkedList = malloc(sizeof(ListRep));
    assert(linkedList != NULL);
    // initialize head node equals to null
    linkedList->head = NULL;
    return linkedList;
}

// Time complexity: O(n)
// Explanation: This is linear complexity as it uses one loop to iterate the LL
// for deleting every node and free the allocated spaces

void dropLL(List listp) {
    NodeT *dropP, *current;
    dropP = listp->head;
    while (dropP != NULL){
        // if not using current to store the node,
        // simply freeing dropP will lose link to next node
        current = dropP;
        dropP = dropP->next;
        // after set pointer to next, current can be freed
        free(current);
    }
    // set head to null at the end, delete entry for the LL
    listp->head = NULL;
    free(listp);
}

// Time complexity: O(1) if specified node stored in head
//                  O(n) otherwise
// Explanation: Generally this is linear complexity as it uses one loop to iterate
// the LL to check and remove the specified node and free the allocated space

void removeLL(List listp, int cardID) {
    // must reassure that LL is not empty
    assert(listp != NULL);
    NodeT *rmP, *toDelete;
    rmP = listp->head;
    // situation 1: cardID stored in head
    if (rmP->data.cardID == cardID){
        if (rmP->next != NULL){
            // move the head to next node then free the head
            listp->head = rmP->next;
        }
        else{
            // if only one head, no successor nodes,
            // then set head to null
            listp->head = NULL;
        }
        // free the memory allocated for specified node before return
        free(rmP);
        printf("Card removed.\n");
        return;
    }
    // situation 2: cardID stored in other nodes
    while (rmP->next != NULL){
        // check if next data equals to given cardID, if yes,
        // then skip and delete next node and points to next-next node
        if (rmP->next->data.cardID == cardID){
            toDelete = rmP->next;
            if (rmP->next->next != NULL){
                rmP->next = rmP->next->next;
            }
            else{
                // if given cardID stored in tail, no successors
                rmP->next = NULL;
            }
            // free the memory allocated for specified node
            free(toDelete);
            printf("Card removed.\n");
            return;
        }
        rmP = rmP->next;
    }
    // situation 3: cannot find cardID in head or nodes after checks
    printf("Card not found.\n");
}

// Time complexity: O(1) if specified cardID should become the head of LL
//                  O(n) otherwise
// Explanation: Generally this is linear complexity as it uses one loop to iterate
// the LL to check the cardID and insert the specified node into proper position

void insertLL(List listp, int cardID, float amount) {
    NodeT *insP, *current = listp->head;
    insP = malloc(sizeof(NodeT));
    assert(insP != NULL);
    // initialize the pointer with data
    insP->data.cardID = cardID;
    insP->data.balance = amount;
    insP->next = NULL;
    // situation 1: empty LL, given card becomes the head
    if (current == NULL){
        listp->head = insP;
        printf("Card added.\n");
        return;
    }
    // situation 2: headID greater than cardID, new head exchanges
    else if (current->data.cardID > cardID){
        listp->head = insP;
        insP->next = current;
        printf("Card added.\n");
        return;
    }
    // situation 3: iterate LL and insert cardID in nodes
    while (current != NULL){
        // if cardID exists, do the transaction update and display
        if (current->data.cardID == cardID){
            current->data.balance += amount;
            printf("-----------------\n");
            printf("Card ID: %d\n", current->data.cardID);
            if (current->data.balance >= 0.0){
                printf("Balance: $%.2f\n", current->data.balance);
            }
            else{
                printf("Balance: -$%.2f\n", current->data.balance * -1);
            }
            if (current->data.balance < 5.00){
                printf("Low balance\n");
            }
            printf("-----------------\n");
            return;
        }
        if (current->data.cardID < cardID){
            // if cardID greater than current but no successors
            // insert after the current node
            if (current->next == NULL){
                current->next = insP;
                insP->next = NULL;
                break;
            }
            // if cardID between current and successor nodes
            // insert between them
            else if(current->next->data.cardID > cardID){
                insP->next = current->next;
                current->next = insP;
                break;
            }
        }
        current= current->next;
    }
    printf("Card added.\n");
}

// Time complexity: O(n)
// Explanation: This is linear complexity as it uses one loop to iterate
// the LL to sum up the balance and the number of cards

void getAverageLL(List listp, int *n, float *balance) {
    int sumCard = 0;
    float sumBalance = 0;
    NodeT *avgP;
    avgP = listp->head;
    // iterate whole linked list, extract balance and calculate
    // the number of cards
    while (avgP != NULL) {
        sumCard += 1;
        sumBalance += avgP->data.balance;
        avgP = avgP->next;
    }
    // after iterate, assign balance and the number of cards
    // back to the pointers
    *n = sumCard;
    *balance = sumBalance;
}

// Time complexity: O(n)
// Explanation:This is linear complexity as it uses one loop to iterate
// the LL to extract each cardID and the balance to display

void showLL(List listp) {
    NodeT *showP;
    showP = listp->head;
    // iterate the LL and print cardID and balance
    while (showP != NULL){
        printf("-----------------\n");
        printf("Card ID: %d\n", showP->data.cardID);
        if (showP->data.balance >= 0.0){
            printf("Balance: $%.2f\n", showP->data.balance);
        }
        else{
            float showLLBalance;
            showLLBalance = showP->data.balance * -1;
            printf("Balance: -$%.2f\n", showLLBalance);
        }
        if (showP->data.balance < 5.00){
            printf("Low balance\n");
        }
        printf("-----------------\n");
        showP = showP->next;
    }
}
