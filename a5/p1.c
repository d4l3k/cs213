int **s;

#include <stdio.h>
#include <stdlib.h>

void main() {
  s = malloc(sizeof(int)*2);
  s[0] = malloc(sizeof(int)*2);
  s[1] = malloc(sizeof(int)*2);
  s[0][0] = 1;
  s[0][1] = 2;
  s[1][0] = 3;
  s[1][1] = 4;

  s[1][0] = s[0][1];
  s[0][0] = s[1][1];

  printf("%d %d %d %d\n", s[0][0], s[0][1], s[1][0], s[1][1]);
}
