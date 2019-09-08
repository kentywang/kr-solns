#include <stdio.h>

/*
We just really need to add a function to find if a char is in a string.
*/

void squeeze(char s1[], char s2[]);
char in_string(char s[], char c);

int main()
{
  char s[6] = "hello";
  
  squeeze(s, "le");

  printf("%s\n", s);
  
  return 0;
}

void squeeze(char s1[], char s2[])
{
  int i, j;

  for  (i = j = 0; s1[i] != '\0'; ++i)
    if (!in_string(s2, s1[i]))
      s1[j++] = s1[i];

  s1[j] = '\0';
}

char in_string(char s[], char c)
{
  int i;

  for (i = 0; s[i] != '\0'; ++i)
    if (s[i] == c)
      return 1;

  return 0;
}