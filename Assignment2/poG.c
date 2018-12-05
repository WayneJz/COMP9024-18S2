/* Partial Order Graphs ... Assignment 2 COMP9024 18s2
 * Written by Zhou JIANG
 *
 * NOTE: MUST USE stack.c/.h Graph.c/.h WHICH HAVE BEEN MODIFIED BY ME
 *
 * NOTE: COMPILING IT WITH dcc poG.c Graph.c stack.c -o poG MAY RESULT IN MEMORY LEAK
 * NOTE: USE gcc poG.c Graph.c stack.c -o poG INSTEAD
 *
 * Time Complexity Explanation: n: the number of divisors  m: the digits of divisors
 *
 * Task A: Time Complexity: O(n^2 * m^2)
 * Explanation: Using two "for" loops nested to check if number A is a divisor of
 * number B, then calls function "digitCompare" inside the loops, where "digitCompare"
 * also has two "for" loops nested to compare if all digits in number A occur in
 * number B, so the maximum complexity is O(n^2 * m^2)
 *
 * Task B: Time Complexity: O(n^2)
 * Explanation: Applying DFS uses two loops nested (one in main and one in
 * function "stackDFS"), then using two "for" loops nested to output all paths from
 * the path array as it is a two-dimensional array. so the maximum complexity is O(n^2)
 * please note that function "stackDFS" has two loops but they are not nested
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "Graph.h"
#include "stack.h"

#define MAXDIGITS 10    // The max input = 2147483647, which is a 10-digit number
#define MAXDIV 1000     // Assume that input at most has 1000 divisors

int visited[MAXDIV][MAXDIV];
int path[MAXDIV][MAXDIV];
int pathLength[MAXDIV][1];
int pathTag = 0;

int digitCompare(int, int);
int stackDFS(Graph, stack, int, Vertex, int, int);
void visitedClear(int);
void pathInit();


// Time complexity: O(n^2)
// Explanation: This is quadratic time complexity as there are two "for" loops
// which are nested to compare each pair of digits of two numbers

int digitCompare(int divisor, int num){
    // Extract all digits of two numbers by dividing them by 10^n
    // then store digits in arrays
    int divArr[MAXDIGITS], numArr[MAXDIGITS];
    int tagDiv = 0, tagNum = 0;
    int i = 10, m, n;

    while (divisor > 0){
        divArr[tagDiv] = divisor % i;
        divisor /= 10;
        tagDiv += 1;
    }
    while (num > 0){
        numArr[tagNum] = num % i;
        num /= 10;
        tagNum += 1;
    }

    // Check if all digits in divisor can be found in its successor
    // if one digit cannot be found, return 1
    for (m = 0; m < tagDiv; m ++){
        bool numFound = false;
        for (n = 0; n < tagNum; n ++){
            if (divArr[m] == numArr[n]){
                numFound = true;
                break;
            }
        }
        if (numFound == false){
            return 1;
        }
    }
    return 0;
}


// Time complexity: O(n)
// Explanation: This is linear time complexity as there are no nested loops
// use recursion DFS to search for any successors
// use stack to store the current path, then if no successors, pop a stack and find
// other paths (meanwhile block the previous path to avoid infinite recursion)

int stackDFS(Graph graph, stack s, int nV, Vertex current, int currentLength, int maxLength){
    int i;
    // find any successors that is adjacent and has not been blocked
    // if found then push into stack and recursively search this successors
    for(i = 0; i < nV; i ++){
        if (adjacent(graph, current, i) == 1 && visited[current][i] == 0){
            StackPush(s, i);
            return stackDFS(graph, s, nV, i, currentLength + 1, maxLength);
        }
    }

    // if no successors, or all successors are blocked (have been searched)
    // and stack is not empty
    if (StackIsEmpty(s) == 0){
        // if path length is no less than max length
        // iterate the stack, and store the path into an array
        // then update the max length
        if (currentLength >= maxLength){
            int *stackP = StackIterate(s);
            int j = 0;
            // -1 is a symbol return from stackIterate indicating where stack ends
            while ( *(stackP + j) != -1 ){
                path[pathTag][j] = *(stackP + j);
                j += 1;
            }
            pathLength[pathTag][0] = currentLength;
            pathTag += 1;
            maxLength = currentLength;
        }
        // Pop the stack, and if stack is empty return the max length for further use
        // if stack is not empty, find the top element, then block the previous path
        // and meanwhile unblock any path has been search from the layer of last element
        // If not do this, the number of paths will be less than the actual
        // Finally, recursively search the top element of stack to find other paths
        int last = StackPop(s);
        if (StackIsEmpty(s) == 1){
            return maxLength;
        }
        int previous = StackTop(s);
        visited[previous][last] = 1;
        visitedClear(last);
        return stackDFS(graph, s, nV, previous, currentLength - 1, maxLength);
    }
    // if stack is empty (recursion ends) then return the max length for further use
    return maxLength;
}


// Time complexity: O(n^2) if option == -1 (clear all visited paths, -1 is a symbol)
//                  O(n) otherwise (clear any visited paths from the layer of last element)
// Explanation 1: This is quadratic time complexity if option == -1
// as there are two "for" loops nested to clear all paths in a 2-dimension array
// Explanation 2: This is linear time complexity if option otherwise
// as there is a "for" loop to clear all paths from specified layer

void visitedClear(int option){
    int i, j;
    if (option == -1){
        for (i = 0; i < MAXDIV; i ++) {
            for (j = 0; j < MAXDIV; j ++) {
                visited[i][j] = 0;
            }
        }
    }
    else{
        for (j = 0; j < MAXDIV; j ++) {
            visited[option][j] = 0;
        }
    }
}


// Time complexity: O(n^2)
// Explanation: This is quadratic time complexity
// as there are two "for" loops nested to initialize the path array

void pathInit(){
    int i, j;
    for (i = 0; i < MAXDIV; i ++) {
        for (j = 0; j < MAXDIV; j ++) {
            path[i][j] = -1;
        }
    }
}


// Time complexity: O(n^2)
// Explanation: This is quadratic time complexity for main function
// as there are at most two loops nested, details of explanation see below

int main(int argc, char *argv[]) {
    assert (argc == 2);
    int poMax = atoi(argv[1]);
    int divisor[MAXDIV];
    int divIndex = 0;
    int i, m, n;

    // Time complexity: O(n)
    // Explanation: This is linear time complexity as there is a "while" loop
    // to find all divisors of the given number then store then in divisor array

    for (i = 1; i <= poMax; i ++){
        if (poMax % i == 0){
            divisor[divIndex] = i;
            divIndex += 1;
        }
        if (divIndex > MAXDIV){
            break;
        }
    }

    Graph graph = newGraph(divIndex + 1);
    Edge edge;

    printf("Partial order:\n");

    // Time complexity: O(n^2)
    // Explanation: This is quadratic time complexity as there are two "for" loops
    // nested to check if two numbers can form an edge, which should satisfy:
    // 1. the number is a divisor of its successor
    // 2. all digits of the number occur in its successor
    // if satisfy, print the successors and insert the edges

    for (m = 0; m < divIndex; m ++){
        printf("%d:", divisor[m]);
        for (n = m + 1; n < divIndex; n ++){
            if (divisor[n] % divisor[m] == 0 && digitCompare(divisor[m], divisor[n]) == 0){
                printf(" %d", divisor[n]);
                edge.v = m;
                edge.w = n;
                insertEdge(graph, edge);
            }
        }
        printf("\n");
    }
    printf("\n");

    pathInit();
    int maxLength = 0;

    // Time complexity: O(n)
    // Explanation: This is linear time complexity as there is a "for" loop
    // to search all paths from different nodes, using stack to store current path
    // returns the max length for further search
    // drop stacks after each staring node has been searched

    for (i = 0; i < divIndex; i ++){
        // -1 is a symbol that clears (unblocks) all visited path
        visitedClear(-1);
        stack s = newStack();
        StackPush(s, i);
        maxLength = stackDFS(graph, s, divIndex, i, 1, maxLength);
        dropStack(s);
    }

    printf("Longest monotonically increasing sequences:\n");

    // Time complexity: O(n^2)
    // Explanation: This is quadratic time complexity as there are two loops
    // nested to print all paths from path array
    // As it is a stack, the path should be reversely print, use a "while" loop
    // to find where the path ends, then use "for" loop to reversely print all paths

    for (i = 0; i < pathTag + 1; i ++){
        if (pathLength[i][0] == maxLength){

            // As path is initialized with -1
            // then -1 is a symbol where the path ends
            int endTag = 0;
            while (path[i][endTag] != -1) {
                endTag += 1;
            }
            // reversely print all paths
            // if node is not the last one, print '<' after it
            int k;
            for (k = endTag - 1; k >= 0; k --){
                printf("%d", divisor[path[i][k]]);
                if (k != 0){
                    printf(" < ");
                }
            }
            printf("\n");
        }
    }
    // free the graph at the end
    freeGraph(graph);
    return 0;
}