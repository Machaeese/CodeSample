/*
 * Filename: prependNode.c
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: The function of prependNode().
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
 * Function Name: prependNode()
 * Function Prototype: void prependNode(linkedList_t ** head, char * str )
 * Description: This function takes in a pointer to the head of a linked 
 *              list (i.e. a pointer to a pointer to a linkedList_t) and 
 *              a string to insert and then pushes the element onto the 
 *              front of the linked list.
 * Parameters:  head - the given pointer points to the pointer to linkedlist
 *              str - the given pointer points to an array
 * Side Effects: None
 * Error Conditions: error with dynamica allocating memory
 * Return Value: error message or null
 */


void prependNode (linkedList_t ** head, char * str){
    //create a new node and initialize it
    linkedList_t *node;
    //allocate space for the node
    node = (linkedList_t *)malloc(sizeof(linkedList_t));
    //check if the malloc fails
    if(node == 0){
        perror(MEM_ERR);
        return;
    }
    //allocate space for the str
    char *string;
    string = (char *) malloc(strlen(str)+1);
    //check if the malloc fails
    if(string == 0){
        free(node);
        perror(MEM_ERR);
        return;
    }
    //store the input string into the new memory
    strncpy(string, str, strlen(str)+1);
    //let the node's value points to string
    node->value = string;
    //connect the new node with the list
    node->next = *head;
    *head = node;
   
    return;
}




