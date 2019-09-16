#include <stdio.h>

char *my_strncpy(char *s, const char *ct, int n);
char *my_strncat(char *s, const char *ct, int n);
int my_strncmp(const char *cs, const char *ct, int n);

int main()
{
  char a[] = "I love corgis";

  printf("%s\n", my_strncpy(a, "Woofawoof", 4)); // Woof
  printf("%s\n", my_strncat(a, "Meowameow", 4)); // WoofMeow
  printf("%d\n", my_strncmp(a, "Woogwhatever", 4)); // -1
  return 0;
}

char *my_strncpy(char *s, const char *ct, int n)
{
  char *starting_element_s = s;

  while (n-- && (*s++ = *ct++))
    ;

  // We copied the nth char of ct into s. Add null char to complete.
  *s = '\0';

  return starting_element_s;
}

char *my_strncat(char *s, const char *ct, int n)
{
  char *starting_element_s = s;

  while (*s)
    s++;

  // s now points to null char.
  while (n-- && (*s++ = *ct++))
    ;

  *s = '\0';

  return starting_element_s;
}

int my_strncmp(const char *cs, const char *ct, int n)
{
  for (; n && *cs == *ct; ++cs, ++ct, --n)
    ;

  if (n)
    return *cs - *ct;

  return 0;
}