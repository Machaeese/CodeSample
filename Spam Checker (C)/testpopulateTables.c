/*
 * Filename: testpopulateTables
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: Unit test program to test the function populateTables().
 * Date: 2019.8.24
 * Sources of Help: PA3 Writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"
#include "pa3Strings.h"


/*
 * Unit Test for populateTables.c
 *
 * void populateTables(table_t *htbl, table_t *rtbl, table_t *eotbl, 
 *                      FILE *dataFile)
 */
void testpopulateTable() {

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


  FILE * input = fopen("Email1","r");
  populateTables(&htbl,&rtbl,&eotbl,input);
  TEST(htbl.bitArray[0] == 0x2);
  TEST(rtbl.bitArray[4] == 0x20);
  TEST(strcmp(eotbl.llArray[37]->value, "abc") == 0);
  TEST(strcmp(eotbl.llArray[1]->value, "cba") == 0);
  fclose(input);

    

}

int main() {
  fprintf( stderr, "Testing populateTable...\n\n" );
  testpopulateTable();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
