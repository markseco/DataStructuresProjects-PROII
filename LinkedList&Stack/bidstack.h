//
// Created by Marcos Seco Anderson on 20/05/2022.
//

#ifndef PRACTICE2_LINKEDLIST_STACK_BIDSTACK_H
#define PRACTICE2_LINKEDLIST_STACK_BIDSTACK_H

#include "types.h"
#include <stdbool.h>

#define SNULL -1
#define SMAX 25

typedef struct{
    tUserId bidder;
    tProductPrice productPrice;
}tItemS;
typedef int tPosS;

typedef struct{
    tItemS data[SMAX];
    tPosS top;
}tStack;

/*Function Declaration*/

void createEmptyStack(tStack *stack);
/*Creates an empty stack. PostCD: The stack has no elements.*/
bool push(tItemS d, tStack *stack);
/*Inserts an element at the top of the stack. If the element could be inserted, the value true is returned; otherwise false is returned.*/
void pop(tStack *stack);
/*Removes from the stack the element located at its top. * PreCD: The stack is not empty.*/
tItemS peek(tStack stack);
/*Recovers the content of the element at the top of the without removing it. * PreCD: The stack is not empty.*/
bool isEmptyStack(tStack stack);
/*Determines whether the stack is empty or not*/

#endif //PRACTICE2_LINKEDLIST_STACK_BIDSTACK_H
