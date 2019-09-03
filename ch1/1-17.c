#include <stdio.h>
#define MAXLINE 1000

int setline_getlen(char line[], int maxline);

main()
{
  int len;
  char line[MAXLINE];
  
  while ((len = setline_getlen(line, MAXLINE)) > 0)
    if (len > 80) // The only difference from 1.16 is here.
      printf("\nLength: %d\nString:\n%s\n", len, line);
  
  return 0;
}

int setline_getlen(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}