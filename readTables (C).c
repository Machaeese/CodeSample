/*
 * Filename: readTables.c
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: The function of readTables().
 * Date: 2019.8.24
 * Sources of Help: PA3 writeup
 */ 

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

#include "pa3.h"
#include "test.h"


/*
 * Function Name: readTables()
 * Function Prototype: void readTables(FILE *inFile table_t *htbl, 
 *                          table_t *rtbl, table_t, *eotbl)
 * Description: This function reads from inFile and populate the three 
 *              hashtables serialized in writeTables().           
 * Parameters: inFile   -  the pointer to the inFile
 *             htbl     -  the pointer to given hash table
 *             rtbl     -  the pointer to given reverse hash table
 *             eotbl    -  the pointer to given even&odd hash table
 * Side Effects: None
 * Error Conditions:  Error with dynamically allocating memory
 * Return Value: Null
 */


void readTables(FILE *inFile, table_t *htbl, table_t *rtbl, 
                table_t *eotbl){
    //get the size of the file
    int size;
    fread(&size,sizeof(int),1,inFile);
    int size_bit = (size+SEVEN)/EIGHT;

    //initialize the htbl
    htbl->size = size;
    htbl->hashFunction = hash;
    htbl->bitArray = calloc(size_bit,sizeof(char));
    //check if there's any allocatin failure
    if(htbl->bitArray == NULL){
        perror(MEM_ERR);
        return;
    }
    fread(htbl->bitArray,sizeof(char),size_bit,inFile);

    //initialize the rtbl
    rtbl->size = size;
    rtbl->hashFunction = revHash;
    rtbl->bitArray = calloc(size_bit,sizeof(char));
    //check if there's any allocatin failure
    if(rtbl->bitArray == NULL){
        free(htbl->bitArray);
        perror(MEM_ERR);
        return;
    }
    fread(rtbl->bitArray,sizeof(char),size_bit,inFile);


    //initialize the eotbl
    eotbl->size = size;
    eotbl->hashFunction = evenOddHash;
    eotbl->llArray = calloc(size,POINTER_SIZE);
    //check if there's any allocatin failure
    if(eotbl->llArray == NULL){
        free(htbl->bitArray);
        free(rtbl->bitArray);
        perror(MEM_ERR);
        return;
    }

    //initialize some varibles for read eotbl
    char buffer[BUFSIZ];
    //the llArray index
    int index=0;
    //a pointer points to the current character
    char *str;
    //recording the length of current string
    int count;       
    //get the length of remaining part(chars after the last '\0') of buffer
    int remain=0;
    //the size returned by fread()
    int valid;
    //the length of the email string
    int len=0;
    int flag = 0;

     

    //while there's more to read in file
    while(!feof(inFile)){
        valid = fread(&buffer[remain],sizeof(char),BUFSIZ-remain,inFile);
        valid = valid + remain;
        //initialize all the local variables before loop again
        str = &buffer[0];
        count = 0;
        flag = 0;
        //check if the end of the buffer is null or not
        if(buffer[valid-1] == CHAR_NULL){
            flag = 1;
        }
        remain = 0;

        //every time we move the ptr, add count, iterate through the buffer
        while(count<valid){
            //if the char is '\0', move forward
            if(*str == CHAR_NULL){
                 index++;
                 str++;
                 count++;
            }
            //otherwise call prepend node
            else{
                 prependNode(&(eotbl->llArray[index]),str);
                 len = strlen(str);
                 count = count + len + 1;
                 str = str + len + 1;
                 len = 0;
            }
            //if there's no more '\0', reset the buffer
            if(flag == 0 && strchr(str+1, CHAR_NULL) == NULL){
                 //if some chars are left, move them into the front of the new
                 //buffer
                 remain = valid - count;
                 memmove(&buffer[0],str+1,remain);
                 break;
             }
          }
      }
    return;
}


