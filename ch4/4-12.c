#include <stdio.h>
#define MAXLINE 1000

void itoa(int n, char s[]);

int main()
{
  char s[MAXLINE];
  itoa(-256, s);
  printf("%s\n", s);

  return 0;
}

extern int itoa_iter(int n, char s[], int i);

void itoa(int n, char s[])
{
  int m;
  int next_open_index = 0;

  if (n < 0)
    s[next_open_index++] = '-';

  if (n / 10)
    next_open_index = itoa_iter(n / 10, s, next_open_index);

  m = n % 10;

  if (m < 0)
      m = -m;

  s[next_open_index++] = m + '0';
  s[next_open_index] = '\0';
}

int itoa_iter(int n, char s[], int i)
{
  int m;

  if (n / 10)
    i = itoa_iter(n / 10, s, i);

  m = n % 10;

  if (m < 0)
      m = -m;

  s[i++] = m + '0';

  return i;
}