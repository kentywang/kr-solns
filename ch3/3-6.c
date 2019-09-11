#include <stdio.h>
#define MAXLINE 1000

void itoa(char n, char s[], int minwidth);

int main()
{
  char s[MAXLINE];
  itoa(-128, s, 6); // __-128
  printf("%s\n", s);

  return 0;
}

void itoa(char n, char s[], int w)
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

  while (i < w)
    s[i++] = '_';
  
  s[i] = '\0';
}