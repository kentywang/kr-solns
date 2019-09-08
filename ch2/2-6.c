#include <stdio.h>

/*
             543210
0x1F being 00011111 (31 in decimal)
We want       ---
into     10101010 (0xAA or 170)
makes    10101111 (0xAF or 175)

We have 0...0??? of bitfield x from the example.
We need to | (or ^) that with ?...?000 of bitfield y.

To get ?...?000, we need to get a mask of 1...1000 ANDed with bitfield y.
To get mask of 1...1000, we need to left shift 1...1 n times.
To get 1...1, we need to get the one's complement of 0.

EDIT: Misunderstood the problem.
*/

int setbits(int x, int p, int n, int y);
int getbits(int x, int p, int n);

int main()
{
  printf("%d\n", setbits(0x1F, 3, 3, 0xAA));
  return 0;
}

int setbits(int x, int p, int n, int y)
{
  return getbits(x, p, n) ^ ((~0 << n) & y);
}

int getbits(int x, int p, int n)
{
  return (x >> (p + 1 - n)) & ~(~0 << n);
}