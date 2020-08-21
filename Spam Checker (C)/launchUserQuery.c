/*
 * Filename: launchUserQuery.c
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: The function of launchUserQuery().
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
#include "pa3Strings.h"


/*
 * Function Name: launchUserQuery()
 * Function Prototype: void launchUserQuery(table_t *htbl, table_t *rtbl,
 *                      table_t, *eotbl)
 * Description: This function handles user interaction to search the tables 
 *              and prints out the result for each search.
 * Parameters: htbl     -  the pointer to given hash table
 *             rtbl     -  the pointer to given reverse hash table
 *             eotbl    -  the pointer to given even&odd hash table
 * Side Effects: None
 * Error Conditions: Null
 * Return Value: Null
 */


void launchUserQuery(table_t *htbl, table_t *rtbl, table_t *eotbl){

    //create the prompt
    fprintf(stdout,USER_PROMPT);

    char input[BUFSIZ];
    char *str;
    //reads user's input
    while(fgets(input, BUFSIZ, stdin) != NULL){
        //check if the input is "enter"
        if( strcmp(input, NEWLINE) == 0){
            fprintf(stdout,USER_PROMPT);
            //printf(NEWLINE);
            continue;
        }
        //replace all new line character with null character
        str = strchr(input, NEW_LINE);
        if(str){
            *str = CHAR_NULL;
        }
        //convert all characters into lower case
        int i;
        for(i = 0; i < strlen(input); i++){
            input[i] = tolower(input[i]);
        }

        //copy the valid input into find
        int len = strlen(input);
        char find[len+1];
        memcpy(find,&input[0],len);
        find[len] = CHAR_NULL;

        
        int num = checkTables(find,htbl,rtbl,eotbl);
        // if num is 4, that means every table contains the input
        if(num == EXACT_MATCH){
            fprintf(stdout,FOUND_IN_ALL,find);
        }
        //if num is less than 4 but greater than 0, some table cotains input
        if(num > 0 && num != EXACT_MATCH){
            fprintf(stdout,FOUND_IN_SOME,find,num);
        }
        //if num is 0, that means input is not in any table
        if(num == 0){
            fprintf(stdout,WORD_NOT_FOUND,find);
        }
        fprintf(stdout,USER_PROMPT);

    }
    printf(NEWLINE);
}

