/*
 * Filename: testprependNode
 * Author: Jialu Xu
 * Userid: cs30s219ci
 * Description: Unit test program to test the function prependNode().
 * Date: 2019.8.24
 * Sources of Help: PA3 Writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"
#include "pa3Strings.h"


/*
 * Unit Test for prependNode.s
 *
 * long prependNode(likedList_t ** head, char * src );
 *
 */
void testprependNode() {

  //initialize all the required variables
  linkedList_t ** head;
  linkedList_t *llist = (linkedList_t*)malloc(sizeof(linkedList_t));
  char *content;
  content = "ucsd";
  llist->value = content;
  head = &llist;

  //the input string add
  char *add;
  add = "cse";

  
  prependNode(head,add);
  printf("%s\n",(*head)->value);
  TEST(strcmp((*head)->value, "cse") == 0);
  TEST(strcmp((*head)->next->value, "ucsd") == 0);

  add = "San";
  prependNode(head,add);
  TEST(strcmp((*head)->value, "San") == 0);
  TEST(strcmp((*head)->next->value, "cse") == 0);
  TEST(strcmp((*head)->next->next->value, "ucsd") == 0);

  add = "Diego";
  prependNode(head,add);
  TEST(strcmp((*head)->value, "Diego") == 0);
  TEST(strcmp((*head)->next->value, "San") == 0);
  TEST(strcmp((*head)->next->next->value, "cse") == 0);

  add = "San Diego";
  prependNode(head,add);
  TEST(strcmp((*head)->value, "San Diego") == 0);



    

}

int main() {
  fprintf( stderr, "Testing prependNode...\n\n" );
  testprependNode();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
