/*
 * Filename: testwriteTables
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: Unit test program to test the function writeTables().
 * Date: 2019.8.24
 * Sources of Help: PA3 Writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"
#include "pa3Strings.h"


/*
 * Unit Test for writeTables.c
 *
 * void writeTables(File *outFile, table_t *htbl, table_t *rtbl,
 *                  table_t *eotbl)
 */
void testwriteTables() {

  //initialize all the required variables

  table_t htbl;
  htbl.hashFunction = hash;
  htbl.size = 50;
  htbl.bitArray = calloc(1,(50+7)/8);

  table_t rtbl;
  rtbl.hashFunction = revHash;
  rtbl.size = 50;
  rtbl.bitArray = calloc(1,(50+7)/8);

  
  table_t eotbl;
  eotbl.hashFunction = evenOddHash;
  eotbl.size = 50;
  eotbl.llArray = calloc(4,50);

  FILE *input =fopen("Email10", "r");
  //"Email1" contains only one line "abc"
  populateTables(&htbl,&rtbl,&eotbl,input);
  fclose(input);

  FILE *output = fopen("out", "w");

  writeTables(output,&htbl,&rtbl,&eotbl);
  


  fclose(output);
    

}

int main() {
  fprintf( stderr, "Testing writeTables...\n\n" );
  testwriteTables();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
