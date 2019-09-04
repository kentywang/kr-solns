#include <stdio.h>
#define MAXLINE 20
#define TAB_STOP_SIZE 4

/*

Since the tab stop size should never change once it's running, it should
be a symbolic constant.

[A][\t][C][D][\0][?]
 0   1  2  3   4  5

becomes:

|           |            |  (ticks denote tab stops)
[A][ ][ ][ ][C][D][\0][?]
 0  1  2  3  4  5   6  7

Edge case: converting ending tab to space would overflow array.

[A][B][\t][\0]  becomes:  [A][B][ ][\0]
 0  1   2   3              0  1  2   3

*/

int detab(char line[]);

int main()
{
  char line[MAXLINE];

  while (detab(line) > 0)
    printf("%s\n", line);

  return 0;
}

int detab(char s[])
{
  int i, c, spaces_to_add;

  spaces_to_add = TAB_STOP_SIZE;
  i = 0;
  while (i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n') {
    if (c == '\t') {
      while (spaces_to_add > 0 && i < MAXLINE - 1) {
        s[i] = ' ';

        --spaces_to_add;
        ++i;
      }

      spaces_to_add = TAB_STOP_SIZE; // Spaces count is 0, so reset.
    }
    else {
      s[i] = c;

      // Below are the increments/decrements for the next loop.
      if (spaces_to_add == 1)
        spaces_to_add = TAB_STOP_SIZE; // Reset spaces count.
      else 
        --spaces_to_add;

      ++i;
    }
  }
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}