/*
 * Filename: 
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: The function of freeLinkedList().
 * Date: 2019.8.24
 * Sources of Help: PA3 Writeup
 */ 

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "pa3.h"
#include "test.h"


/*
 * Function Name: freeLinkedList()
 * Function Prototype: void freeLinkedList(linkedList_t * head )
 * Description: This function frees all elements in the input linked list. 
 * Parameters:  head - the pointer to the linked list
 * Side Effects: None
 * Error Conditions: Null
 * Return Value: Null
 */


void freeLinkedList (linkedList_t * head){
   
    linkedList_t* copy;
    copy = head;
    //check if the head is null, then return immidiately
    if(head == NULL){
        return;
    }
    //iterate through the list until the last node
    while(head != NULL){
        copy = head;
        //first free the value of the node
        free(head->value);
        head = head->next;
        //then the node itself
        free(copy);
    }
    return;
}


