/*
 * Filename: checkTables.c
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: The function of checkTables().
 * Date: 2019.8.24
 * Sources of Help: PA3 Writeup
 */ 

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

#include "pa3.h"
#include "test.h"


/*
 * Function Name: checkTables()
 * Function Prototype: int checkTables(char* str, table_t *htbl, 
 *                          table_t *rtbl, table_t, *eotbl)
 * Description: This function reports the number of tables the input string 
 *              was seen in.
 * Parameters: str      -  the pointer to the string to find
 *             htbl     -  the pointer to given hash table
 *             rtbl     -  the pointer to given reverse hash table
 *             eotbl    -  the pointer to given even&odd hash table
 * Side Effects: None
 * Error Conditions: Null
 * Return Value: the number of the appearance of the string
 */


int checkTables(char * str, table_t *htbl, table_t *rtbl, 
        table_t *eotbl){

    int count = 0;
    //check if the string is in htb
    if(retrieveBit(htbl,str) !=0){
        count += 1;
        //check if the string is in rtbl
        if(retrieveBit(rtbl,str) !=0){
            count += 1;
            //check if the string is in eotbl
            linkedList_t * head;
            head = retrieveLinkedList(eotbl,str);
            //if the head is not null, count plus 1
            if(head != NULL){
                count +=1;
            }
            //iterate through the linked list to find the str
            while(head != NULL){
                //if the string was found, return EXACT_MATCH
                if(strcmp(head->value,str)==0){
                    count = EXACT_MATCH;
                }
                head = head->next;
            }

        }
    }
    return count;
}


