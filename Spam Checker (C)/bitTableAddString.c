/*
 * Filename: bitTableAddString.c
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: The function of bitTableAddString().
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
 * Function Name: bitTableAddString()
 * Function Prototype: void bitTableAddString(table_t *table, char *string )
 * Description: This function calls table->hashFunction() to hash string. 
 * Parameters:  table  - the given pointer points to the table
 *              string - the given pointer points to the stirng
 * Side Effects: None
 * Error Conditions: Null
 * Return Value: Null
 */


void bitTableAddString (table_t * table, char * string){
    
    int hash_key;
    
    //get the hash_key by calling the corresponding hash function
    hash_key = table->hashFunction(string);

    int table_size = table->size;
    
    //get the processed hash_key and name it idx
    int idx;     
    idx = ((hash_key % table_size) + table_size) % table_size;    

    //set bit idx%8 of the char at index idx/8 in bitArray
    table->bitArray[idx/EIGHT] |= 1 << (idx%EIGHT);

    
    return;
}


