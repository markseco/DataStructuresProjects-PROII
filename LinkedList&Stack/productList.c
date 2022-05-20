//
// Created by Marcos Seco Anderson on 20/05/2022.
//

#include "productList.h"

void createEmptyList(tList *L){
    /*Creates an empty list.
      Post-condition: The list is initialised and has no elements.*/
    *L = LNULL;
}

bool isEmptyList(tList L){
    /*Determines if the list is empty or not.*/
    return(L == LNULL);
}

tPosL first(tList L){
    /*Returns the first element of the list.
      Pre-condition: the list is not empty.*/
    return L;
}

tPosL last(tList L){
    /*Returns the position of the last element of the list.
      Pre-condition: the list is not empty.*/
    tPosL pl;
    for(pl = L; pl->next != LNULL; pl = pl->next);
    return pl;
}

tPosL next(tPosL p, tList L){
    /*Returns the position in the list of the element following that one at the indicated position
     (or LNULL if the specified position has no next element)
     Pre-condition: The indicated position is a valid position in the list*/
    return(p->next);
}

tPosL previous(tPosL p, tList L){
    /*Returns the position in the list of the element pecriding the one at the indicated position
      (or LNULL if the specified position has no previous element)
      Pre-condition: The indicated position is a valid position in the list.*/
    tPosL r;
    r = L;
    if(p != L){
        while(r->next != p)
            r = r->next;
        return r;
    }else
        return LNULL;

}

bool createNode(tPosL *p){
    /*Allocates a space in memory for a pointer to a type tNode
     and returns true if there was enough space in memory to do that.*/
    *p = malloc(sizeof(struct tNode));
    return(*p != LNULL);
}

tPosL findPosition(tList L, tItemL d){
    tPosL p;

    for(p = L; (p!=LNULL) && strcmp(p->data.productId, d.productId) < 0;p = p->next);

    return p;
}

bool insertItem(tItemL d, tList *L){
    // Inserts an element in the List ordered by the field productId.
    tPosL n, pos, prev;

    /*we check there is enough memory to insert the new element
     if there is not enough memory we return false, otherwise we create a new node*/
    if(!createNode(&n))
        return false;
    /*New node values insertion*/
    n->data = d;
    n->next = LNULL;

    /*If the list is empty the new item is inserted in the first position*/
    if(*L == LNULL){
        *L = n;
    }
    else if(strcmp(n->data.productId, (*L)->data.productId) < 0) {
        /*if the id is smaller than the first element it is inserted at the beginning of the list*/
        n->next = *L;
        *L = n;
    }
    else{
        pos = findPosition(*L, d);
        if(pos == LNULL){
            /*if the new productId is the largest we initialize the
             previous node next parameter to point to the new element */
            pos = last(*L);
            pos->next = n;
        }else if(strcmp(pos->data.productId, n->data.productId) == 0) /*there can't be two elements with the same product id*/
            return false;
        else{
            /*Else we initialize the previous node next parameter to point to the new element*/
            prev = previous(pos, *L);
            prev->next = n;
            n->next = pos;
        }
    }
    return true;
}

void deleteAtPosition(tPosL p, tList *L){
    /* Deletes the element at the given position from the list.
     * Pre-Condition: The indicated position is a valid position in the list. And the bid stack of the product at
     * that position is empty.
     * Post-Condition: The positions of the elements in the list following that of the deleted one may have varied*/
    tPosL q;
    if(p == *L){
        *L = p->next; //if we want to delete the first element
    }else if(p == last(*L)){
        //The last one is deleted
        q = previous(p, *L);
        q->next = LNULL;
    }
    else{
        //Any other valid position
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    free(p);
}


tItemL getItem(tPosL p, tList L){
    /* Returns the content of the element at the indicated position.
     * Pre-Condition: The indicated position is a valid position in the list.*/
    return(p->data);
}

void updateItem(tItemL d, tPosL p, tList *L){
    /* Modifies the content of the element at the indicated position.
     * Pre-Condition: The indicated position is a valid position in the list.
     * Post-Condition: The order of the element in the list has not been modified.*/
    p->data = d;
}

tPosL findItem(tProductId d,tList L){
    /* Returns the position of the first element in the list whose product identifier
     matches the given one (or LNULL if there is no such element).*/
    tPosL p;
    for(p = L; (p!=LNULL) && strcmp(p->data.productId, d) < 0;p = p->next);
    if((p != LNULL) && (strcmp(p->data.productId, d) == 0))
        return p;
    else
        return LNULL;
}
