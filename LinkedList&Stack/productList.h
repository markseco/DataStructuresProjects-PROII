//
// Created by Marcos Seco Anderson on 20/05/2022.
//

#ifndef PRACTICE2_LINKEDLIST_STACK_PRODUCTLIST_H
#define PRACTICE2_LINKEDLIST_STACK_PRODUCTLIST_H

#include "types.h"
#include "bidstack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define LNULL NULL

/* Write your code here... */

typedef struct {
    tUserId seller;
    tProductId productId;
    tProductCategory productCategory;
    tProductPrice productPrice;
    tBidCounter bidCounter;
    tStack bidStack;
} tItemL;

typedef struct tNode * tPosL;
struct tNode{
    tItemL data;
    tPosL next;
};
typedef tPosL tList;


/*Functions Declaration*/
void createEmptyList(tList *L);
/*Creates an empty list.
  Post-condition: The list is initialised and has no elements.*/

bool isEmptyList(tList L);
/*Determines if the list is empty or not.*/

bool createNode(tList *L);
/*Allocates a space in memory for a pointer to a type tNode
    and returns true if there was enough space in memory to do that.*/


tPosL first(tList L);
/*Returns the first element of the list.
  Pre-condition: the list is not empty.*/

tPosL last(tList L);
/*Returns the position of the last element of the list.
  Pre-condition: the list is not empty.*/

tPosL next(tPosL p, tList L);
/*Returns the position in the list of the element following that one at the indicated position
     (or LNULL if the specified position has no next element)
     Pre-condition: The indicated position is a valid position in the list*/


tPosL previous(tPosL p, tPosL L);
/*Returns the position in the list of the element pecriding the one at the indicated position
  (or LNULL if the specified position has no previous element)
  Pre-condition: The indicated position is a valid position in the list.*/


bool insertItem(tItemL data, tList *L);
/*Inserts an element containing the provided data item in the list.
 If the specified position is LNULL, then the element is added at the end of the list
 otherwise, it will be placed right before the element currently holding that position.
 If the element could be inserted the value true is returned, false otherwise.
 Pre-condition: The specified position is a valid position or a LNULL position.
 Post-condition: The position of the elements in the list following that of the inserted one may have varied*/


tItemL getItem(tPosL p, tList L);
/* Returns the content of the element at the indicated position.
     * Pre-Condition: The indicated position is a valid position in the list.*/


void deleteAtPosition(tPosL p, tList *L);
/* Deletes the element at the given position from the list.
     * Pre-Condition: The indicated position is a valid position in the list.
     * Post-Condition: The positions of the elements in the list following that of the deleted one may have varied*/


void updateItem(tItemL d, tPosL p, tList *L);
/* Modifies the content of the element at the indicated position.
     * Pre-Condition: The indicated position is a valid position in the list.
     * Post-Condition: The order of the element in the list has not been modified.*/


tPosL findItem(tProductId d, tList L);
/* Returns the position of the first element in the list whose product identifier
    matches the given one (or LNULL if there is no such element).*/

#endif //PRACTICE2_LINKEDLIST_STACK_PRODUCTLIST_H
