#include <stdio.h>

/*
01100101 (0x65)
rotate right 3 times:
10101100 (0xAC)

We just need these:
?...?000
0...0???

Getting the first is easy; just right shift.
The second is harder without knowing the size of the bitfield, but if we left-shift 0...0111 until its value changes unexpectedly, we can know the how 
many shifts to do to move ??? to the left.
Finally, OR the two.
*/

unsigned char rightrot(unsigned char x, int n);
int findrot(unsigned char x, int n);

int main()
{
  printf("%x\n", rightrot(0x65, 3));
}

unsigned char rightrot(unsigned char x, int n)
{
  return (x >> n) | (x << findrot(x, n));
}

// Finds number of shifts necessary to move the rightmost n bits of x to the
// leftmost side. We'll know when we overrotated when the integer value of
// the variable is lower (since 1100 < 1110).
// Initially I tried to compare a * 2 with a << 1, but I realized that won't
// work since both break down at the same time due to equal types.
int findrot(unsigned char x, int n)
{
  int count = 0;
  // Needs to be unsigned, or else one count short.
  unsigned char a = ~(~0 << n); // 0...0111

  // This needs explanation: a << 1 is extends a's char size to something
  // bigger. This lets it not hit the end condition until much later, so we
  // need to keep it as a char. Just casting it to char isn't enough, because
  // (in Clang at least) it defaults to signed.
  while ((unsigned char) (a << 1) > a) {
    a = a << 1;
    count++;
  }

  return count;
}