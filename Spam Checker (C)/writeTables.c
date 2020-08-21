/*
 * Filename: writeTables.c
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: The function of writeTables().
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
 * Function Name: writeTables()
 * Function Prototype: void writeTables(FILE *outFile table_t *htbl, 
 *                          table_t *rtbl, table_t, *eotbl)
 * Description: This function serializes the three hash tables and writes them
 *              to outFile so that they can later be read and deserialized 
 *              back into hashtables in their original format.              
 * Parameters: outFile  -  the pointer to the outFile
 *             htbl     -  the pointer to given hash table
 *             rtbl     -  the pointer to given reverse hash table
 *             eotbl    -  the pointer to given even&odd hash table
 * Side Effects: None
 * Error Conditions: Null
 * Return Value: Null
 */


void writeTables(FILE *outFile, table_t *htbl, table_t *rtbl, 
                table_t *eotbl){
    //get the sizes for different tables
    int size = htbl->size;
    int size_bit = (size+SEVEN)/EIGHT;
    //first write htbl and rtbl
    fwrite(&size, sizeof(int),1, outFile);
    fwrite(htbl->bitArray, sizeof(char), size_bit, outFile);
    fwrite(rtbl->bitArray, sizeof(char), size_bit, outFile);
    //then write eotbl
    //iterate through the table and get string in each bucket
    for(int i = 0; i < size; i++){
        //while the node is not null, write the string in the outfile
        while(eotbl->llArray[i] != NULL){      
            fputs(eotbl->llArray[i]->value,outFile);
            fputc(CHAR_NULL,outFile);
            eotbl->llArray[i] = eotbl->llArray[i]->next;
        }
        fputc(CHAR_NULL,outFile);
    }

    return;
}


