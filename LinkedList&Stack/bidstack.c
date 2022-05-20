//
// Created by Marcos Seco Anderson on 20/05/2022.
//

#include "bidstack.h"

void createEmptyStack(tStack *stack){
    /*Creates an empty stack. PostCD: The stack has no elements.*/
    stack->top = SNULL;
}

bool push(tItemS d,tStack *stack){
    /*Inserts an element at the top of the stack. If the element could be inserted,
     * the value true is returned; otherwise false is returned.*/
    if(stack->top == SMAX -1)
        return false;
    else{
        stack->top++;
        stack->data[stack->top] = d;
        return true;
    }
}

void pop(tStack *stack){
    /*Removes from the stack the element located at its top.
     * PreCD: The stack is not empty.*/
    stack->top--;
}

tItemS peek(tStack stack){
    /*Recovers the content of the element at the top of the without removing it.
     * PreCD: The stack is not empty.*/
    return stack.data[stack.top];
}

bool isEmptyStack(tStack stack){
    /*Determines whether the stack is empty or not*/
    return(stack.top == SNULL);
}