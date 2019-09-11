#include <stdio.h>
#define MAXLINE 1000

/*
00 (0)
01 (1)
10 (-2)
11 (-1)

The book example of itoa can't handle the largest negative number of because
it converts any negative number to positive, meaning the largest negative
would get converted to itself.

To counter this, we would just leave n untouched but take the absolute value
of the modulo within the do-while loop. And we need to make sure the while
condition accepts that n is less than zero.
*/

void itoa(char n, char s[]);

int main()
{
  char s[MAXLINE];
  itoa(-128, s);
  printf("%s\n", s);

  return 0;
}

void itoa(char n, char s[])
{
  int i, m;
  int sign = n;

  i = 0;
  do {
    m = n % 10;
    
    if (m < 0)
      m = -m;

    s[i++] = m + '0';

  } while ((n /= 10) != 0);

  if (sign < 0)
    s[i++] = '-';

  s[i] = '\0';
}