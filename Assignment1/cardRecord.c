// Transport card record implementation ... Assignment 1 COMP9024 18s2
// Written by Zhou JIANG

#include <stdio.h>
#include "cardRecord.h"

#define LINE_LENGTH 1024
#define NO_NUMBER -999

// scan input line for a positive integer, ignores the rest, returns NO_NUMBER if none
int readInt(void) {
    char line[LINE_LENGTH];
    int  n;

    fgets(line, LINE_LENGTH, stdin);
    if ( (sscanf(line, "%d", &n) != 1) || n <= 0 )
        return NO_NUMBER;
    else
        return n;
}

// scan input for a floating point number, ignores the rest, returns NO_NUMBER if none
float readFloat(void) {
    char  line[LINE_LENGTH];
    float f;

    fgets(line, LINE_LENGTH, stdin);
    if (sscanf(line, "%f", &f) != 1)
        return NO_NUMBER;
    else
        return f;
}

int readValidID(void) {
    int card_id;
    printf("Enter card ID: ");
    card_id = readInt();
    while (card_id == NO_NUMBER || card_id < 10000000 || card_id > 99999999) {
        printf("Not valid. Enter a valid value: ");
        card_id = readInt();
    }
    return card_id;
}


float readValidAmount(void) {
    float card_amount;
    printf("Enter amount: ");
    card_amount = readFloat();
    while (card_amount == NO_NUMBER || card_amount < -2.35 || card_amount > 250) {
        printf("Not valid. Enter a valid value: ");
        card_amount = readFloat();
    }
    return card_amount;
}

void printCardData(cardRecordT card) {
    printf("-----------------\n");
    printf("Card ID: %d\n", card.cardID);
    if (card.balance >= 0.0){
        printf("Balance: $%.2f\n", card.balance);
    }
    else{
        float showBalance;
        showBalance = card.balance * -1;
        printf("Balance: -$%.2f\n", showBalance);
    }
    if (card.balance < 5.00){
        printf("Low balance\n");
    }
    printf("-----------------\n");
}
