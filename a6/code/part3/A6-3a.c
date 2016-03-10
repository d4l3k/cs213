#include <stdio.h>

int c[] = {0,0,0,0,0,0,0,0,0,0};
int *d = c;

void foo(int a, int b) {
  d[b] += a;
}
void main() {
  int a = 1;
  int b = 2;
  foo(3, 4);
  foo(a,b);

  for (int i=0; i<10;i++) {
    printf("%d\n", c[i]);
  }
}
