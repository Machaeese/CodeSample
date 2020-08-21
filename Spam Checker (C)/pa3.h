/*
 * File: pa3.h
 * Description: Header file that contains function prototypes and
 *              constants.
 *
 * XXX Only add constants to this file at the bottom.
 * DO NOT EDIT FUNCTION PROTOTYPES OR PREDEFINED CONSTANTS
 *
 */

#ifndef PA3_H       /* Macro Guard */
#define PA3_H
#include <stdio.h>

typedef struct llist {
  struct llist * next;
  char * value;
} linkedList_t;

/* Struct Definitions */
typedef struct Table {
  // Pointer to the hash function to call for this table
 int (*hashFunction)(char *string);
  
  long size;                    // Number of entries in the table
  union {                       // bitArray and llArray share the same 4 bytes
    char *bitArray;             // For the first two tables
    linkedList_t **llArray;     // For the last table
  };

} table_t;

/* Checking Table */
#define EXACT_MATCH 4

/* Hashing */
#define HASH_START_VAL 11
#define HASH_PRIME     37

/* Table Size */
#define DEFAULT_SIZE 5000
#define MIN_SIZE 10
#define MAX_SIZE 25000

/* getopt constants */
#define SEARCH_FLAGS "i:h"
#define CREATE_FLAGS "i:ho:s:"

#define LONG_HELP_FLAG "help"
#define LONG_INFILE_FLAG "infile"
#define LONG_OUTPUT_FLAG "output"
#define LONG_SIZE_FLAG "size"

#define SIZE_FLAG 's'
#define OUTPUT_FLAG 'o'
#define INFILE_FLAG 'i'
#define HELP_FLAG 'h'

// These macros combine to convert __LINE__ which is a number to a string,
// then the preprocessor concatenates all three to be file:lineNo for the 
// OOM perror call.
#define STR_HELP( x ) #x
#define MEM_ERR __FILE__ ":" STR_HELP( __LINE__ )

/* C Function Prototypes */
int retrieveBit( table_t *table, char *string );
void bitTableAddString( table_t *table, char *string );
int evenOddHash( char * str );
void populateTables( table_t * htbl, table_t * rtbl, table_t * eotbl,
    FILE * dataFile );
int checkTables( char * str, table_t * htbl, table_t * rtbl, table_t * eotbl );
void prependNode( linkedList_t ** head, char * str );
void readTables( FILE * inFile, table_t * htbl, table_t * rtbl,
    table_t * eotbl );
void writeTables( FILE * outFile, table_t * htbl, table_t * rtbl,
    table_t * eotbl );
void launchUserQuery(table_t * htbl, table_t * rtbl, table_t * eotbl);
void freeLinkedList( linkedList_t * head );

/* Assembly Function Prototypes */
int hash( char * str );
int revHash( char * str );
long rangeCheck( long num, long min, long max );
long getRemainder( long dividend, long divisor );
linkedList_t *retrieveLinkedList( table_t *table, char *string );
void llTableAddString( table_t *table, char *string );


/*define additional magic numbers*/
#define DIVISOR  2
#define POINTER_SIZE 4
#define SEVEN    7
#define EIGHT    8
#define NEW_LINE '\n'
#define CHAR_NULL '\0'
#define READ    "r"
#define WRITE   "w"
#define NEWLINE "\n"
#define BASE    10
#define TWO      2
#define SPACE   " "



#endif
