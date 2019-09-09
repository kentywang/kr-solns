#include <stdio.h>

/*
x = x & (x - 1)

bits:  111 (-1)   010 (2)    000 (0)
2s c:  001 (1)    110 (-2)   000 (0)

(0x50)              (0x40)
01010000 minus 1 => 01000000

01010000 & 01000000 => 01000000, thus rightmost (and only) 1-bit deleted.

Explanation:
x - 1 always toggles the rightmost bit. It'll toggle the 2nd rightmost bit
if and only if the previous toggle was from a 0 to a 1. It'll toggle the 3rd
rightmost bit under the same condition. Thus we stop the cascade toggling
only after we hit a bit that is 1. (The same effect happens when doing x + 1,
but the terminating condition is when we hit a 0.)

ANDing the result of that effect with the original value means all the
toggled bits are guaranteed to be zeroed. Of the toggled bits, the original
values are (from right to left) a sequence of 0s ending with a 1. Since these
bits are inverted in the x-1 expression, &ing them makes them all 0. It makes
no difference for the bits that were already 0, but the final toggled bit is
a 1, and that's what changes with the &.

The original bitcount takes O(n) steps, where n is the bitfield size of the
integer x. We can use the above phenomenon to reduce the program to O(m)
steps, where m <= n and m is the number of 1-bits.
*/

int bitcount(int x);

int main()
{
  printf("%d\n", bitcount(0xFFAA)); // 4+4+2+2 = 12 bits

  return 0;
}

int bitcount(int x)
{
  int b;

  for (b = 0; x != 0; x &= x - 1)
    b++;

  return b;
}