#include <stdio.h>
#define MAXLINE 1000

// Renamed because naming conflict with something.
int setline_getlen(char line[], int maxline);
// void copy(char to[], char from[]);

main()
{
  int len;
  char line[MAXLINE];
  
  while ((len = setline_getlen(line, MAXLINE)) > 0)
    if (len > 0)
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

// void copy(char to[], char from[])
// {
//   int i;

//   i = 0;
//   while ((to[i] = from[i]) != '\0')
//     ++i;
// }