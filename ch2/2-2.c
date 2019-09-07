#include <stdio.h>
#define LIM 10

/*
Edit: This doesn't work as intended, since we still loop within as long as
the first condition is fulfilled. We need to keep a state variable that gets
checked in each loop. Thus, thank the lord for logical operators.
*/

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