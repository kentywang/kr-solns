#include <stdio.h>
#define LIM 10

int main()
{
  int c;
  int i = 0;
  char s[LIM];

  while (i < LIM - 1)
    if ((c = getchar()) != '\n')
      if (c != EOF) {
        s[i] = c;
        ++i;
      }

  s[i] = '\0';

  printf("%s\n", s);
  
  return 0;
}