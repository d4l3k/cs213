#include <stdio.h>

int a[8] = {0,11,2,0,1,2,0,1};
int b[8] = {2,12,0,2,1,0,2,1};
int c[8] = {99,6,2,1,0,2,1,0};
int i = 5;
int *d = c;

int main () {
  a[i] = a[i+1] + b[i+2];
  d[i] = a[i] + b[i];
  d[i] = a[b[i]] + b[a[i]];
  d[b[i]] = b[a[i & 3] & 3] - a[b[i & 3] & 3] + d[i];
  for (int i=0; i<8; i++)
    printf ("a[%d]==%d\n", i, a[i]);
  for (int i=0; i<8; i++)
    printf ("b[%d]==%d\n", i, b[i]);
  for (int i=0; i<8; i++)
    printf ("c[%d]==%d\n", i, c[i]);
}

