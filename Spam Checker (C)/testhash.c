/*
 * Filename: testhash
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: Unit test program to test the function hash().
 * Date: 2019.8.24
 * Sources of Help: PA3 Writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"
#include "pa3Strings.h"


static int hashC(char * str) {
    int hash = HASH_START_VAL;
    int strLen = strlen(str);\
    int i;
    for( i = 0; i < strLen; i++){
        hash = hash * HASH_PRIME + str[i];
    }
    return hash;
}

/*
 * Unit Test for hash.s
 *
 * int hash( char * str );
 *
 */
void testhash() {

  char * str = "ABCD";
  /* Validate the hash value. */
  TEST( hash(str) == hashC(str) );
  
  str = "";
  TEST( hash(str) == hashC(str) );

  str = "asadasd";
  TEST( hash(str) == hashC(str) );

  str = " ";
  TEST( hash(str) == hashC(str) );

  str = "cse30";
  TEST( hash(str) == hashC(str) );

  str = "@@@";
  TEST( hash(str) == hashC(str) );

}

int main() {
  fprintf( stderr, "Testing hash...\n\n" );
  testhash();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
