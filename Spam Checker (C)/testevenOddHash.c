/*
 * Filename: testevenOddHash
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: Unit test program to test the function evenOddHash().
 * Date: 2019.8.24
 * Sources of Help: PA3 Writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"
#include "pa3Strings.h"


/*
 * Unit Test for evenOddHash.s
 *
 * long evenOddHash( char * src );
 *
 */
void testevenOddHash() {

  char * src = "";
  /* Validate the hash value. */
  TEST( evenOddHash(src) == 11 );

  src = "1";
  TEST( evenOddHash(src) == 456 );

  src = "12";
  TEST( evenOddHash(src) == 16922);

  src = "21";
  TEST( evenOddHash(src) == 16958);

  src = "!@!";
  TEST( evenOddHash(src) == 603645);
 
  src = "@!@";
  TEST( evenOddHash(src) == 647200);

  src = " ";
  TEST( evenOddHash(src) == 439);



}

int main() {
  fprintf( stderr, "Testing evenOddHash...\n\n" );
  testevenOddHash();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
