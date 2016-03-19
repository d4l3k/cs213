#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "list.h"

void print (element_t ev) {
  intptr_t e = (intptr_t) ev;
  printf ("%ld\n", e);
}

void prints (element_t ev) {
  char* e = (char*) ev;
  printf ("%s\n", e);
}

void str2n (element_t* rv, element_t av) {
  char*  a = (char*)  av;
  intptr_t* r = (intptr_t*) rv;
  char*pEnd;
  *r = strtol(a, &pEnd, 10);
  if (pEnd == a) {
    *r = -1;
  }
}

void strs (element_t* rv, element_t av, element_t bv) {
  char *  a = (char *)  av;
  intptr_t  b = (intptr_t)  bv;
  char** r = (char**) rv;
  if (b < 0) {
    *r = a;
  } else {
    *r = NULL;
  }
}

int isPositive (element_t av) {
  intptr_t a = (intptr_t) av;
  return a >= 0;
}

int isNotNull (element_t av) {
  char* a = (char*) av;
  return a != NULL;
}

void trunct (element_t* rv, element_t av, element_t bv) {
  char *  a = (char *)  av;
  intptr_t  b = (intptr_t)  bv;
  char** r = (char**) rv;
  a[(int)b] = 0;
  *r = a;
}

void max (element_t* rv, element_t av, element_t bv) {
  intptr_t  a = (intptr_t)  av;
  intptr_t  b = (intptr_t)  bv;
  intptr_t* r = (intptr_t*) rv;
  *r = a > b ? a : b;
}

int main(int argc, char *argv[]) {
  struct list* l0 = list_create();
  for (int i=1;i<argc; i++) {
    list_append(l0, (element_t)argv[i]);
  }

  struct list* l1 = list_create();
  list_map1 (str2n, l1, l0);

  struct list* l2 = list_create();
  list_map2 (strs, l2, l0, l1);


  struct list* l3 = list_create();
  list_filter (isPositive, l3, l1);


  struct list* l4 = list_create();
  list_filter (isNotNull, l4, l2);


  struct list* l5 = list_create();
  list_map2 (trunct, l5, l4, l3);

  list_foreach (prints, l5);

  element_t maxv = 0;
  list_foldl (max, &maxv, l3);

  printf("%d\n", maxv);

  list_destroy (l0);
  list_destroy (l1);
  list_destroy (l2);
  list_destroy (l3);
  list_destroy (l4);
  list_destroy (l5);
}
