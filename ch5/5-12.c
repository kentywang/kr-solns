#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 20
#define TAB_STOP_SIZE 4

/*
Assuming "list of tab stops" is like this:
-10 +6

Skipping the entab part.
*/

int detab(char line[], int m, int n);

int main(int argc, char *argv[])
{
  char line[MAXLINE];

  // Set defaults.
  int m = 0;
  int n = TAB_STOP_SIZE;

  // Process args.
  while (--argc)
    switch (**++argv) {
    case '-':
      m = atoi(++argv[0]);
      break;
    case '+':
      n = atoi(++*argv); // Same as ++argv[0].
      break;
    default:
      printf("Unexpected argument.\n");
      return -1;
    }
  // printf("m: %d, n: %d\n", m, n);

  while (detab(line, m, n))
    printf("%s\n", line);

  return 0;
}

int detab(char s[], int m, int n)
{
  int i, c, spaces_to_add;

  spaces_to_add = n;
  i = 0;
  while (i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n') {
    if (c == '\t' && i >= m - 1) {
      while (spaces_to_add > 0 && i < MAXLINE - 1) {
        s[i] = ' ';

        --spaces_to_add;
        ++i;
      }

      // Spaces count is now 0, so reset.
      spaces_to_add = n;
    }
    else {
      s[i] = c;

      // Below are the increments/decrements for the next loop.
      if (spaces_to_add == 1)
        // Reset spaces count.
        spaces_to_add = n;
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
