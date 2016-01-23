#include <stdlib.h>
#include <stdio.h>

int *val;

void sort (int n) {
  int t;
  for (int i=n-1; i>0; i--) {
    int *ip = val + i * sizeof(int);
    for (int j=i-1; j>=0; j--) {
      int *jp = val + j * sizeof(int);
      if (*ip < *jp) {
        t = *ip;
        *ip = *jp;
        *jp = t;
      }
    }
  }
}

int main (int argc, char** argv) {
  char* ep;
  int   n;
  n = argc - 1;
  val = malloc(n * sizeof(int));
  for (int i=0; i<n; i++) {
    int *ip = val + i * sizeof(int);
    *ip = strtol (argv[i+1], &ep, 10);
    if (*ep) {
      fprintf (stderr, "Argument %d is not a number\n", i);
      return -1;
    }
  }
  sort (n);
  for (int i=0; i<n; i++) {
    int *ip = val + i * sizeof(int);
    printf ("%d\n", *ip);
  }
}
