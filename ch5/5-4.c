#include <stdio.h>

int strend(char *s, char *t);

int main()
{
  char a[] = "I love corgis";
  printf("%d\n", strend(a, "corgis"));

  return 0;
}

int strend(char *s, char *t)
{
  char *starting_element_t = t;

  while (*s)
    ++s;

  while (*t)
    ++t;

  // We should be on the null char of both s and t now.

  while (t >= starting_element_t && *s == *t) {
    --s;
    --t;
  }

  return t < starting_element_t ? 1 : 0;
}