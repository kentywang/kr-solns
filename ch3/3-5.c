#include <stdio.h>
#define MAXLINE 1000

void itob(int base10integer, char string[], int base);

int main()
{
  char s[MAXLINE];
  itob(-255, s, 16);
  printf("%s\n", s);

  return 0;
}

void itob(int n, char s[], int b)
{
  int i, m;
  int negative = n < 0;

  i = 0;
  do {
    m = n % b;
    
    if (m < 0)
      m = -m;

    // Let's use capital letters if we run out of numbers to represent digits.
    if (m > 9)
      s[i++] = m + 'A' - 10;
    else
      s[i++] = m + '0';

  } while ((n /= b) != 0);

  if (negative)
    s[i++] = '-';

  s[i] = '\0';
}