/*
 * Filename: search.c
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
 * Description: This function performs the functionality for the search 
 *              program. It starts by parsing the command line arguments, 
 *              handling any errors encountered in the process; then it 
 *              creates the hash tables and fills them by reading from the 
 *              input file. Finally it performs an interactive search and 
 *              prints stats if needed.
 * Parameters: argc    - the total number of inputs
 *             *argv[] - the array of the input
 * Side Effects: None
 * Error Conditions:  Error calling fopen;
 *                    No input file specified;
 *                    Extra arguments for the input flags.
 * Return Value: Null
 */


int main( int argc, char *argv[]){

    //initialize some of local variables
    int opt = 0;
    int infile = 0;
    FILE *input;
        
    while((opt = getopt(argc,argv,SEARCH_FLAGS)) != -1){
        switch(opt){  

            case INFILE_FLAG :
                errno = 0;
                input = fopen(optarg,READ);
                //check if the the input file could open
                if(errno != 0){
                    perror(RTABLE_FILE_ERR);
                    fprintf(stderr,SHORT_SEARCH_USAGE);
                    return EXIT_FAILURE;
                }
                infile = 1;
                break;

            case HELP_FLAG :
                fprintf(stderr,LONG_SEARCH_USAGE);
                return EXIT_SUCCESS;

            default :
                fprintf(stderr,SHORT_SEARCH_USAGE);
                return EXIT_FAILURE;
        }
    }
    //check if both input flag and output flag are valid
    if(infile == 0){
        fprintf(stderr,MISSING_INFILE);
        fprintf(stderr,SHORT_SEARCH_USAGE);
        return EXIT_FAILURE;
    }
    //check if there are too much arguments parsed in
    if(optind < argc){
        fprintf(stderr,EXTRA_ARGS,argv[0]);
        fprintf(stderr,SHORT_SEARCH_USAGE);
        fclose(input);
        return EXIT_FAILURE;
    }
    
    //initialize three tables
    table_t htbl;
    table_t rtbl;
    table_t eotbl;

    //read tables from the input file
    readTables(input,&htbl,&rtbl,&eotbl);
    launchUserQuery(&htbl,&rtbl,&eotbl);


    //free the memory allocated
    free(htbl.bitArray);
    free(rtbl.bitArray);
    //iterate through the linked_List_t pointer array to
    int i;
    for(i = 0; i < eotbl.size; i++){
        freeLinkedList(eotbl.llArray[i]);
    }

    fclose(input);

    return EXIT_SUCCESS;
}
