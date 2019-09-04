#include <stdio.h>
#define MAXLINE 1000

// [A][B][C][D][\0][?][?]
//  0  1  2  3   4  5  6 

int setline_getlen(char line[], int maxline);
void reverse(char s[], int s_length);

int main()
{
  int len;
  char line[MAXLINE];

  while ((len = setline_getlen(line, MAXLINE)) > 0) {
    reverse(line, len);
    printf("\nLength: %d\nString:\n%s\n\n", len, line);
  }

  return 0;
}

void reverse(char s[], int j)
{
  int i;
  char temp;
  --j; // Converting length to last element index.

  for (i = 0; i < j; ++i) { // Only iterate halfway, lest undo the reversal!
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;

    --j;
  }
}

// Unchanged.
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