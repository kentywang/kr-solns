#include <stdio.h>

char *str_cat(char *s, char *t);

int main()
{
   // If any less than 23 or just a[], it should fail. Needs more space.
  char a[23] = "I love corgis";
  printf("%s\n", str_cat(a, " so much!"));

  return 0;
}

char *str_cat(char *s, char *t)
{
  char *original_s_start = s;

  while (*s)
    ++s;

  // We should be on the null char of s now.

  // Assign object at t to s, then stop if it was the null char assigned.
  while (*s++ = *t++)
    ;

  return original_s_start;
}