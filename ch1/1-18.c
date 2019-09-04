#include <stdio.h>
#define MAXLINE 1000

// Strategy: Save line from input and its length. Then iterate backwards to
// trim trailing whitespace by inserting the null character at the first non-
// whitespace character encountered.

// [A][ ][B][ ][ ][\0][?][?]
//  0  1  2  3  4   5  6  7

int setline_getlen(char line[], int maxline);
int trim(char line[], int to);

int main()
{
  int len;
  char line[MAXLINE];
  
  while ((len = setline_getlen(line, MAXLINE)) > 0) {
    len = trim(line, len);
    if (len > 0)
      printf("\nLength: %d\nString:\n%s\n\n", len, line);
  }
  
  return 0;
}

int trim(char s[], int s_length)
{
  int i;

  // Assumes length supplied doesn't factor in null character.
  for (i = s_length-1; i >= 0; --i) {
    if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n') {
      // Increment i to add null character after last non-whitespace char.
      ++i;
      s[i] = '\0';
      return i; // This is the trimmed length.
    }
  }

  return 0; // Or i, which is also zero here.
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