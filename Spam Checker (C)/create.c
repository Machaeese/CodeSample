/*
 * Filename: create.c
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: The function of main().
 * Date: 2019.8.24
 * Sources of Help: PA3 Writeup
 */ 

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>


#include "pa3.h"
#include "test.h"
#include "pa3Strings.h"


/*
 * Function Name: main()
 * Function Prototype: void main(int argc, char*argv[])
 * Description: This is the main driver for the create portion of your 
 *              program. Its main tasks are to parse the command line 
 *              arguments, build the hashtables of email data, and serialize 
 *              the hashtables to a file.
 * Parameters: argc    - the total number of inputs
 *             *argv[] - the array of the input
 * Side Effects: None
 * Error Conditions: command line argument error;
 *                   missing either of infile flag or output flag;
 *                   extra arguments after flags;
 *                   
 * Return Value: Null
 */


int main( int argc, char *argv[]){
    //create the getopt_longOpts struct
    static struct option getopt_longOpts[]={
        {   .name = LONG_HELP_FLAG,
            .has_arg = 0,
            .flag = 0,
            .val = HELP_FLAG
        },
        {   .name = LONG_SIZE_FLAG,
            .has_arg = 1,
            .flag = 0,
            .val = SIZE_FLAG
        },
        {   .name = LONG_INFILE_FLAG,
            .has_arg = 1,
            .flag = 0,
            .val = INFILE_FLAG
        },
        {   .name = LONG_OUTPUT_FLAG,
            .has_arg = 1,
            .flag = 0,
            .val = OUTPUT_FLAG
        },{0,0,0,0}
    };

    //initialize some of local variables
    int opt = 0;
    char *endptr;
    int size = DEFAULT_SIZE;
    int infile_flag = 0;
    int output_flag = 0;
    FILE *input;
    FILE *output;
    
    
    while((opt = getopt_long(argc,argv,CREATE_FLAGS,
        getopt_longOpts,0)) != -1){

        switch(opt){   
            case SIZE_FLAG :
                //check if there's any input size
                if(optarg != NULL){
                    size = strtol(optarg, &endptr, BASE);
                    //check if the input size has any non-numerica characters
                    if(*endptr != CHAR_NULL){
                        fprintf(stderr,INVALID_NUM,optarg);
                        fprintf(stderr,SHORT_CREATE_USAGE);
                        return EXIT_FAILURE;
                    }
                    char buffer[BUFSIZ];
                    //check if the input size is too big to be 
                    //converted into long
                    if(errno != 0){
                        snprintf(buffer,BUFSIZ,TOO_LARGE_NUM,optarg,BASE);
                        perror(buffer);
                        fprintf(stderr,SHORT_CREATE_USAGE);
                        return EXIT_FAILURE;
                    }
                    //check if the input size is in the range
                    if(rangeCheck(size,MIN_SIZE,MAX_SIZE) == 0){
                        fprintf(stderr,TABLE_SIZE_ERR,MIN_SIZE,MAX_SIZE);
                        fprintf(stderr,SHORT_CREATE_USAGE);
                        return EXIT_FAILURE;
                    }
                } 
                break;

            case INFILE_FLAG :
                errno = 0;
                input = fopen(optarg,READ);
                //check if the the input file could open
                if(errno != 0){
                    perror(FILTER_ERR);
                    fprintf(stderr,SHORT_CREATE_USAGE);
                    return EXIT_FAILURE;
                }
                infile_flag = 1;
                break;

            case OUTPUT_FLAG :
                errno = 0;
                output = fopen(optarg,WRITE);
                //check if the input file could open
                if(errno != 0){
                    perror(WTABLE_FILE_ERR);
                    fprintf(stderr,SHORT_CREATE_USAGE);
                    return EXIT_FAILURE;
                }
                output_flag = 1;
                break;

            case HELP_FLAG :
                fprintf(stdout,LONG_CREATE_USAGE);
                return EXIT_SUCCESS;

            default :
                fprintf(stderr,SHORT_CREATE_USAGE);
                return EXIT_FAILURE;
        }


        
    }
    //check if both input flag and output flag are valid
    if(infile_flag == 0 || output_flag == 0){
        fprintf(stderr,ARG_ERR);
        return EXIT_FAILURE;
    }
    //check if there are too much arguments parsed in
    if(optind < argc){
        fprintf(stderr,EXTRA_ARGS,argv[0]);
        return EXIT_FAILURE;
    }
    
    //initialize three tables
    table_t htbl;
    htbl.hashFunction = hash;
    htbl.size = size;
    htbl.bitArray = calloc((size+SEVEN)/EIGHT,1);
    //check if there's any allocation failure
    if(htbl.bitArray == NULL){
        perror(MEM_ERR);
    }

    table_t rtbl;
    rtbl.hashFunction = revHash;
    rtbl.size = size;
    rtbl.bitArray = calloc((size+SEVEN)/EIGHT,1);
    //check if there's any allocation failure
    if(rtbl.bitArray == NULL){
        perror(MEM_ERR);
    }

    table_t eotbl;
    eotbl.hashFunction = evenOddHash;
    eotbl.size = size;
    eotbl.llArray = calloc(size,POINTER_SIZE);
    //check if there's any allocation failure
    if(eotbl.bitArray == NULL){
        perror(MEM_ERR);
    }

    //populate the table
    populateTables(&htbl,&rtbl,&eotbl,input);
    fclose(input);
    //write out the table
    writeTables(output,&htbl,&rtbl,&eotbl);
    fclose(output);

    //free the memory allocated
    free(htbl.bitArray);
    free(rtbl.bitArray);
    //iterate through the linked_List_t pointer array to
    for(int i = 0; i < size; i++){
        freeLinkedList(eotbl.llArray[i]);
    }

}
