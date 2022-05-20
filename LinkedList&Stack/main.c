#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "productList.h"

#define MAX_BUFFER 255

void str_to_enum(char *category, tItemL *data){
    //this function converts a string into an enum of the type declared to this ADT
    if(strcmp(category, "book") == 0){
        data->productCategory = book;
    }else if(strcmp(category, "painting") == 0){
        data->productCategory = painting;
    }
}

char *enum_to_str(tProductCategory category){
    //this function converts an enum into a string
    if(category == 0)
        return "book";
    else
        return "painting";
}

void deleteStack(tStack *stack){
    //this function deletes a given stack
    while(!isEmptyStack(*stack)){
        pop(stack);
    }
}

void CaseN(char *param1, char *param2, char *param3, char *param4, tList *list){
    /*The product must be added to the product list, with its corresponding product identifier,
     * the user identifier of irs seller, its category and price. Its bid counter will be initialized
     * to 0, and an empty bid stack will be created and associated to it.*/
    tItemL data;
    strcpy(data.productId, param1); //
    strcpy(data.seller, param2);
    str_to_enum(param3, &data);

    //Insertion of a new product in the list

    data.productPrice = strtof(param4, NULL); //we convert the value of type str to a float
    data.bidCounter = 0;
    createEmptyStack(&data.bidStack);

    if(findItem(data.productId, *list) != LNULL || !insertItem(data, list)) {
        //If a product with the same identifier already exists or the insertion cannot be completed
        printf("+ Error: New not possible\n");
    }else{
        printf("* New: product %s seller %s category %s price %.2f\n", data.productId, data.seller, enum_to_str(data.productCategory),  data.productPrice);
    }
}

void CaseS(tList L){
/*The whole list of current products will be displayed*/
    if(!isEmptyList(L)){
        //Check if the list is empty
        tPosL p = first(L);
        int numBooks = 0, numPaints = 0;
        float totalCostBooks = 0, totalCostPaintings = 0, avgPriceBooks = 0, avgPricePaintings = 0;
        tPosL greatest_increase_item_position = NULL;
        float greatest_increase_percentage = 0;


        /*This while loop goes through the list and prints its contents, and also stores in variables and computes the values asked
          to print in the table.*/
        while (p != LNULL) {
            tItemL product = getItem(p, L);

            if (product.productCategory == book){
                //Count the number of books
                numBooks++;
                //Compute the total value of the paintings
                totalCostBooks = totalCostBooks + product.productPrice;
            }else if (product.productCategory == painting){
                //Count the number of paintings
                numPaints++;
                //Compute the total value of the paintings
                totalCostPaintings = totalCostPaintings + product.productPrice;
            }


            if(isEmptyStack(product.bidStack))
                //If there are no bids
                printf("Product %s seller %s category %s price %.2f. No bids\n", product.productId, product.seller, enum_to_str(product.productCategory) ,product.productPrice);
            else {
                tItemS top_bid = peek(product.bidStack);
                printf("Product %s seller %s category %s price %.2f bids %d top bidder %s\n", product.productId,
                       product.seller, enum_to_str(product.productCategory), product.productPrice, product.bidCounter, top_bid.bidder);

                if( ((top_bid.productPrice / product.productPrice) * 100) - 100 > greatest_increase_percentage) {
                    greatest_increase_item_position = p;
                    //Calculation of the greatest increase percentage
                    greatest_increase_percentage = ((top_bid.productPrice / product.productPrice) * 100) -100;
                }

            }

            p = next(p, L);
        }

        // this computes the mean value of the books and paintings
        if (numBooks > 0)
            avgPriceBooks = totalCostBooks / (float)numBooks;
        if (numPaints > 0)
            avgPricePaintings = totalCostPaintings / (float)numPaints;

        //printing the table

        printf("\nCategory  Products    Price  Average\n");
        printf("Book      %8d %8.2f %8.2f\n", numBooks, totalCostBooks, avgPriceBooks);
        printf("Painting  %8d %8.2f %8.2f\n", numPaints, totalCostPaintings, avgPricePaintings);

        if(greatest_increase_percentage == 0)
            //If there is no bid
            printf("Top bid not possible\n");
        else{
            tItemL greatest = getItem(greatest_increase_item_position, L);
            tItemS top_bid = peek(greatest.bidStack);
            printf("Top bid: Product %s seller %s category %s price %.2f bidder %s top price %.2f increase %.2f%%\n", greatest.productId,
                   greatest.seller, enum_to_str(greatest.productCategory), greatest.productPrice, top_bid.bidder, top_bid.productPrice, greatest_increase_percentage);
        }
    } else
        //If the list is empty
        printf("+ Error: Stats not possible\n");
}

void CaseB(tProductId param1, tUserId param2, tProductPrice  newPrice, tList *L){
    /*The product is located and, if the new bid value exceeds its
     * current highest bid, then: the new bid is added to its stack and
     * its bid counter is updated.*/
    tPosL pos;
    tItemL data;
    tProductPrice  top_bid;
    tItemS new_bid;


    pos = findItem(param1, *L); //The product is located
    if(pos == LNULL)
        //If there is no product with such identifier ERROR
        printf("+ Error: Bid not possible\n");
    else{
        data = getItem(pos, *L);
        //Check if the Stack is empty if it is the top_bid is the productPrice, else the biggest bid is selected
        if(isEmptyStack(data.bidStack))
            top_bid = data.productPrice;
        else
            top_bid = peek(data.bidStack).productPrice;

        strcpy(new_bid.bidder, param2);
        new_bid.productPrice = newPrice;

        if(top_bid >= newPrice || strcmp(param2, data.seller) == 0 || newPrice <= data.productPrice || !push(new_bid, &data.bidStack))
            //If the bidder and the seller are the same person, the bid value is not higher than the current highest bid, or the stack is full: error
            printf("+ Error: Bid not possible\n");
        else{
            data.bidCounter++; //The bid counter is updated
            updateItem(data, pos, L);
            printf("* Bid: product %s bidder %s category %s price %.2f bids %d\n", data.productId, new_bid.bidder,
                   enum_to_str(data.productCategory), new_bid.productPrice, data.bidCounter);

        }
    }
}

void CaseD(tProductId param1, tList *list){
    /*The system will locate and remove that product form the
     * list, also deleting all its associated bis.*/
    tPosL p = findItem(param1,*list);
    if ( p == LNULL)
        //If there is no product with the given identifier ERROR
        printf("+ Error: Delete not possible\n");
    else{
        tItemL data = getItem(p, *list);
        printf("* Delete: product %s seller %s category %s price %.2f bids %d\n",data.productId, data.seller, enum_to_str(data.productCategory), data.productPrice, data.bidCounter);
        //Delete all its associated bids and remove the product from the list
        deleteStack(&data.bidStack);
        deleteAtPosition(p,list);
    }

}

void CaseA(tProductId param1, tList *list){
    /*The product is located. The winning bidder and the final price */
    tPosL p = findItem(param1, *list);
    if(p == LNULL){
        //If there is no product with the given identifier ERROR
        printf("+ Error: Award not possible\n");
    }else{
        tItemL data = getItem(p, *list);
        if(isEmptyStack(data.bidStack)) //If the Stack is empty ERROR
            printf("+ Error: Award not possible\n");
        else{
            tItemS max_bid = peek(data.bidStack);
            //The winning bidder is selected
            printf("* Award: product %s bidder %s category %s price %.2f\n", data.productId, max_bid.bidder, enum_to_str(data.productCategory), max_bid.productPrice);
            //Since the product has been sold, it must be removed from the product list after emptying its bid stack
            deleteStack(&data.bidStack);
            deleteAtPosition(p, list);
        }
    }
}

void CaseW(tProductId param1, tUserId param2, tList *list){
    /*The product is located, the current highest bid is
     * deleted, the bid counter is decreased.*/
    tPosL p = findItem(param1, *list);
    if(p==LNULL){
        //If there is no product with the given identifier ERROR
        printf("+ Error: Withdraw not possible\n");
    }else{
        tItemL data = getItem(p, *list);
        tItemS max_bid = peek(data.bidStack);
        if(isEmptyStack(data.bidStack) || strcmp(max_bid.bidder, param2) != 0){
            //If the bid stack is empty, or the UserID is not that of the highest bid
            printf("+ Error: Withdraw not possible\n");
        }else{
            printf("* Withdraw: product %s bidder %s category %s price %.2f bids %d\n",data.productId, max_bid.bidder, enum_to_str(data.productCategory), max_bid.productPrice, data.bidCounter);
            //The current highest bid is deleted and the bid counter is decreased
            data.bidCounter--;
            pop(&data.bidStack);
            updateItem(data, p, list);
        }

    }
}

void CaseR(tList *list){
    /*The function removes all the products with no bids,
     * if there is no product without bids an error message is printed */
    if(!isEmptyList(*list)){
        int counter = 0; //It is used to see if there are product without bids
        tPosL pos = first(*list); //Initialise the pointer to point to the first element of the list
        tPosL prev_p = LNULL; //It will be used as an auxiliary pointer to actualize the position
        tItemL data;
        while(pos != LNULL){
            data = getItem(pos, *list);
            if(data.bidCounter == 0){
                //products with no bids will be removed from the list
                prev_p = previous(pos, *list);//Initialising the auxiliary pointer to the previous position
                deleteStack(&data.bidStack);//Deletes the stack
                deleteAtPosition(pos, list);//Deletes the element at that position
                pos = next(prev_p, *list);//Updates the value of the pointer to the next position
                printf("Removing product %s seller %s category %s price %.2f bids %d\n",data.productId, data.seller, enum_to_str(data.productCategory),data.productPrice, data.bidCounter);
                counter++;
            }else{
                pos = next(pos, *list);//Updates the value of the pointer to the next position
            }
        }
        if(counter == 0)
            printf("+ Error: Remove not possible\n");//If there is no product without bids

    }else
        printf("+ Error: Remove not possible\n");//If it is empty list
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *list) {

    switch (command) {
        case 'N':
            printf("********************\n");
            printf("%s %c: product %s seller %s category %s price %s\n", commandNumber, command, param1, param2, param3, param4);
            CaseN(param1, param2, param3, param4, list);
            break;
        case 'S':
            printf("********************\n");
            printf("%s %c \n", commandNumber, command);
            CaseS(*list);
            break;
        case 'B':
            printf("********************\n");
            printf("%s %c: product %s bidder %s price %s \n", commandNumber, command, param1, param2, param3);
            CaseB(param1, param2, strtof(param3, NULL), list);
            break;
        case 'D':
            printf("********************\n");
            printf("%s %c: product %s\n", commandNumber, command, param1);
            CaseD(param1,list);
            break;
        case 'A':
            printf("********************\n");
            printf("%s %c: product %s\n", commandNumber, command, param1);
            CaseA(param1,list);
            break;
        case 'W':
            printf("********************\n");
            printf("%s %c: product %s bidder %s\n", commandNumber, command, param1, param2);
            CaseW(param1, param2, list);
            break;
        case 'R':
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            CaseR(list);
            break;
        default:
            break;
    }
}

void readTasks(char *filename, tList *list) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4, list);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {
    tList list;
    createEmptyList(&list);
    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name, &list);

    return 0;
}
