/*
 * Filename: evenOddHash.c
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: The function of evenOddHash().
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
 * Function Name: evenOddHash()
 * Function Prototype: int evenOddHash( char * str )
 * Description: This function is also similar to hash.s, the only difference
 *              is that to compute the hash key, it iterates through the 
 *              string first by by even and then by odd indices.
 * Parameters: str - the given pointer points to an array
 * Side Effects: None
 * Error Conditions: None
 * Return Value: the hash key value of str
 */


int evenOddHash (char* str){
    int hash = HASH_START_VAL;
    //get the length of the input string
    int strLen = strlen(str);
    //iterate through the even numbers first
    for(int i = 0; i < strLen; i++){
        if(i%DIVISOR == 0){
            hash = hash * HASH_PRIME + str[i];
        }
    }
    //then iterate trhough the odd numbers
    for(int i = 0; i < strLen; i++){
        if(i%DIVISOR == 1){
            hash = hash * HASH_PRIME + str[i];
        }
    }

    return hash;
}




