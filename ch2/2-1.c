#include <stdio.h>
#include <limits.h>
#include <float.h>

/*
Interesting, so incrementing a signed char at 127 makes it -128 instead of
attempting to overflow it. And incrementing an unsigned char at 255 makes it
0. Hence why a compiler warning when trying to set up a for loop with the
continuation condition outside the range of values for a given variable type.
It would never leave its range. It can only loop through it.
*/

void calc_char_range(void);
void calc_signed_char_range(void);
void calc_unsigned_char_range(void);
void calc_short_range(void);
void calc_int_range(void);
void get_long_range(void);

int main()
{
  printf("Long range: %ld\n", LONG_MAX);

  return 0;
}

void calc_char_range(void)
{
  int times;
  char s;

  times = 256;
  s = 0;
  while (times > 0) {
    printf("Char at %d: ", s);
    putchar(s);
    putchar('\n');

    ++s;
    --times;
  }
}

void calc_signed_char_range(void)
{
  int times;
  signed char s;

  times = 256;
  s = 0;
  while (times > 0) {
    printf("Char at %d: ", s);
    putchar(s);
    putchar('\n');

    ++s;
    --times;
  }
}

void calc_unsigned_char_range(void)
{
  int times;
  unsigned char s;

  times = 256;
  s = 0;
  while (times > 0) {
    printf("Char at %d: ", s);
    putchar(s);
    putchar('\n');

    ++s;
    --times;
  }
}

/*
Loops from 0 to -1 in 65536 prints, so a short int is by default in Clang
a 16-bit unsigned integer.
*/
void calc_short_range(void)
{
  int times;
  short int s;

  times = 1;
  s = 0;
  while (times <= 65536) { // Try storing least 2^16 values.
    printf("Short at %d: %d\n", times, s);

    ++s;
    ++times;
  }
}

/*
It seems ints are 32-bit signed, since their max is 2147483647 before
looping to -2147483648.
*/
void calc_int_range(void)
{
  int i;
  i = 2147483647;
  printf("%d\n", i);
  printf("%d\n", i + 1);
}

void get_long_range(void)
{
  // Looks like long is 64-bit signed.
  printf("Long range: %ld\n", LONG_MAX);
}