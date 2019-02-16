/**
     main.c

     Program supplied as a starting point for
     Assignment 1: Transport card manager

     COMP9024 18s2
**/

// Written by Zhou JIANG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "cardRecord.h"
#include "cardLL.h"

void printHelp();
void CardLinkedListProcessing();

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int i, numberOfCards;
        float total_amount = 0.0;
        numberOfCards = atoi(argv[1]);   // convert char argument to int
        cardRecordT* card = malloc(numberOfCards*sizeof(cardRecordT));
        assert(card != NULL);
        // store the card data into allocated memory
        for (i = 0 ; i < numberOfCards; i++){
            card[i].cardID = readValidID();
            card[i].balance = readValidAmount();
        }
        // calculate total amount and print card data
        for (i = 0 ; i < numberOfCards; i++){
            printCardData(card[i]);
            total_amount += card[i].balance;
        }
        printf("Number of cards on file: %d\n", numberOfCards);
        // print average balance, with formatting
        float average_amount = total_amount / numberOfCards;
        if (average_amount < 0.0){
            printf("Average balance: -$%.2f\n", average_amount * -1);
        }
        else{
            printf("Average balance: $%.2f\n", average_amount);
        }
        // free the allocated memory
        free(card);
    }
    else {
        CardLinkedListProcessing();
    }
    return 0;
}

/* Code for Stages 2 and 3 starts here */

void CardLinkedListProcessing() {
    int op, ch;

    List list = newLL();   // create a new linked list

    while (1) {
        printf("Enter command (a,g,p,q,r, h for Help)> ");

        do {
            ch = getchar();
        } while (!isalpha(ch) && ch != '\n');  // isalpha() defined in ctype.h
        op = ch;
        // skip the rest of the line until newline is encountered
        while (ch != '\n') {
            ch = getchar();
        }

        switch (op) {

            case 'a':
            case 'A': {
                int LLCardId = readValidID();
                float LLCardAmount = readValidAmount();
                insertLL(list, LLCardId, LLCardAmount);
                break;
            }

            case 'g':
            case 'G': {
                int sumCard = 0;
                float sumBalance = 0.0;
                // provide the address for the pointers in getAverageLL
                getAverageLL(list, &sumCard, &sumBalance);
                printf("Number of cards on file: %d\n", sumCard);
                if (sumBalance < 0.0){
                    printf("Average balance: -$%.2f\n", (sumBalance * -1) / sumCard);
                }
                else{
                    printf("Average balance: $%.2f\n", sumBalance / sumCard);
                }
                break;
            }

            case 'h':
            case 'H':
                printHelp();
                break;

            case 'p':
            case 'P':
                showLL(list);
                break;

            case 'r':
            case 'R': {
                int rmCardID = readValidID();
                removeLL(list, rmCardID);
                break;
            }

            case 'q':
            case 'Q':
                dropLL(list);       // destroy linked list before returning
                printf("Bye.\n");
                return;
        }
    }
}

void printHelp() {
    printf("\n");
    printf(" a - Add card record\n" );
    printf(" g - Get average balance\n" );
    printf(" h - Help\n");
    printf(" p - Print all records\n" );
    printf(" r - Remove card\n");
    printf(" q - Quit\n");
    printf("\n");
}
