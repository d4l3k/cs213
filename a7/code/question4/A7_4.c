int d[] = {0,0,0,0};

int foo(int a, int b, int c) {
  void *jumps[] = {&&P330, &&P384, &&P334, &&P384, &&P33C, &&P384, &&P354, &&P384, &&P36C};
  if (a < 10 || a > 18) {
    goto L6;
  }
  goto *jumps[a-10];

P330:
  c += b;
  goto L7;

P334:
  c = -c+b;
  goto L7;

P33C:
  if (b-c <= 0) {
    c = 0;
  } else {
    c = 1;
  }
  goto L7;

P354:
  if (b-c <= 0) {
    c = 0;
  } else {
    c = 1;
  }
  goto L7;

P36C:
  if (c == b) {
    c = 1;
  } else {
    c = 0;
  }
  goto L7;

P384:
L6:
  c = 0;
  goto L7;

L7:
  return c;
}
void main() {
  d[3] = foo(d[0], d[1], d[2]);
}
