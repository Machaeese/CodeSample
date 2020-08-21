/*
 * Filename: testrevHash
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: Unit test program to test the function revHash().
 * Date: 2019.8.24
 * Sources of Help: PA3 Writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"
#include "pa3Strings.h"


static int revHashC(char * src) {
    int hash = HASH_START_VAL;
    int srcLen = strlen(src);
    int i;
    for( i = srcLen - 1; i >= 0; i--){
        hash = hash * HASH_PRIME + src[i];
    }
    return hash;
}

/*
 * Unit Test for revHash.s
 *
 * int revHash( char * src );
 *
 */
void testrevHash() {

  char * src = "ABCD";
  /* Validate the hash value. */
  TEST( revHash(src) == revHashC(src) );

  src = "sdf";
  TEST( revHash(src) == revHashC(src) );

  src = " ";
  TEST( revHash(src) == revHashC(src) );

  src = "?!";
  TEST( revHash(src) == revHashC(src) );

  src = "CSE30";
  TEST( revHash(src) == revHashC(src) );

  src = "%^#@";
  TEST( revHash(src) == revHashC(src) );

  src = "lool";
  TEST( revHash(src) == revHashC(src) );

}

int main() {
  fprintf( stderr, "Testing revHash...\n\n" );
  testrevHash();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
