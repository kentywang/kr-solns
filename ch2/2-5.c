#include <stdio.h>

int any(char s1[], char s2[]);
char in_string(char s[], char c);

int main()
{
  printf("%d\n", any("ABCDEFG", "BF"));
  
  return 0;
}

int any(char s1[], char s2[])
{
  int i;

  for  (i = 0; s1[i] != '\0'; ++i)
    if (in_string(s2, s1[i]))
      return i;

  return -1;
}

char in_string(char s[], char c)
{
  int i;

  for (i = 0; s[i] != '\0'; ++i)
    if (s[i] == c)
      return 1;

  return 0;
}