#include <stdio.h>
// Potential issue: temp might clash with some real variable name.
#define swap(t, x, y) {\
  t temp = x;\
  x = y;\
  y = temp;\
}

int main()
{
  int x = 4;
  int y = 7;

  swap(int, x, y);

  printf("x: %d, y: %d\n", x, y);

  return 0;
}