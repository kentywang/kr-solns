#include <stdio.h>

/*
76543210
10101010 (input, 0xAA)
  ---
10010010 (output, 0x92)

We need a mask of ??000??? to be ORed with a mask of 00¿¿¿000, where ¿ is the
inverse the bit at that location.

To get the first mask, we need ???????? to AND with mask 11000111.
To get 11000111, we need to left-shift n number of 1s p-n+1 times and invert it.
To get n number of 1s, we need to left-shift 1s n times and then invert.

To get the second mask, we need ¿¿¿¿¿¿¿¿ to AND with mask 00111000.
To get 00111000, we just do the same thing as for the other mask, but don't
invert at the end.
*/

unsigned int invert(unsigned int x, int p, int n);
unsigned int getmask(int p, int n);

int main()
{
  printf("%x\n", invert(0xAAu, 5, 3));
}

unsigned int invert(unsigned int x, int p, int n)
{
  unsigned int m = getmask(p, n);

  return (x & ~m) | (~x & m);
}

unsigned int getmask(int p, int n)
{
  return ~(~0 << n) << (p-n+1);
}