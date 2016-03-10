#include <stdio.h>

int x[] = {
     1,
     2,
     3,
     0xffffffff,
     0xfffffffe,
     0,
     184,
     340057058
};
int y[] = {
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0
};

int f(int a) {
  int b = 0x80000000;
  int out = 0;
  while (a != 0) {
    int c = a & b;
    if (c != 0) {
      out += 1;
    }
    a = a<<1;
  }
  return out;
}

void main() {
  for (int i=8; i>0; i--) {
    y[i] = f(x[i]);
  }
  for (int i=0; i<8;i++) {
    printf("%d\n", x[i]);
  }
  for (int i=0; i<8;i++) {
    printf("%d\n", y[i]);
  }
}
