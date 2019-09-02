#include <stdio.h>

main()
{
  long blanks, tabs, newlines;
  long c;

  blanks = 0;
  tabs = 0;
  newlines = 0;

  c = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ')
      ++blanks;
    if (c == '\t')
      ++tabs;
    if (c == '\n')
      ++newlines;
  }

  printf("%ld blanks, %ld tabs, %ld newlines\n", blanks, tabs, newlines);
}