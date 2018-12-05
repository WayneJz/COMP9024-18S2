// Stack ADT header file ... COMP9024 18s2

typedef struct StackRep *stack;

stack newStack();             // set up empty stack
void  dropStack(stack);       // remove unwanted stack
int   StackIsEmpty(stack);    // check whether stack is empty
void  StackPush(stack, int);  // insert an int on top of stack
int   StackPop(stack);        // remove int from top of stack
int   StackTop(stack);        // return the top element of a stack (without deleting it)
int * StackIterate(stack);    // return pointer of array containing all elements in a stack