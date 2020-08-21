/*
 * Filename: populateTables.c
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: The function of populateTables().
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
 * Function Name: populateTables()
 * Function Prototype: void populateTables(table_t *htbl, table_t *rtbl,
 *                      table_t, *eotbl, FILE *dataFile )
 * Description: This function populates 3 hash tables by reading in dataFile,
 *              grabbing each line using fgets(), and calling the proper 
 *              addString function for each of the 3 tables.
 * Parameters: htbl     -  the pointer to given hash table
 *             rtbl     -  the pointer to given reverse hash table
 *             eotbl    -  the pointer to given even&odd hash table
 *             dataFile -  the pointer to the given dataFile
 * Side Effects: None
 * Error Conditions: Null
 * Return Value: Null
 */


void populateTables(table_t *htbl, table_t *rtbl, table_t *eotbl,
        FILE *dataFile ){

    char input[BUFSIZ];
    char *str;
    //reads file
    while(fgets(input, BUFSIZ, dataFile) != NULL){
        //replace all new line character with null character
        str = strchr(input, NEW_LINE);
        if(str){
            *str = CHAR_NULL;
        }
        //convert all characters into lower case
        for(int i = 0; i < strlen(input); i++){
            input[i] = tolower(input[i]);
        }
        //populate the table
        bitTableAddString(htbl, input);
        bitTableAddString(rtbl, input);
        llTableAddString(eotbl, input);

    }



    return;
}


