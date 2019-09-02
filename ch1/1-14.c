#include <stdio.h>

// Doing all ASCII characters.

#define IN 1
#define OUT 0
#define CHAR_COUNT 256

main()
{
  int c, i, j;
  int freqs[CHAR_COUNT];

  for (i = 0; i < 256; ++i)
    freqs[i] = 0;

  while ((c = getchar()) != EOF)
    // Should work because value of c is between 0 & 255, unless of course
    // EOF or other metavalues.
    ++freqs[c];

  for (i = 0; i < CHAR_COUNT; ++i) {
    printf("%c: ", i);
    for (j = 0; j < freqs[i]; ++j)
      putchar('|');
    putchar('\n');
  }
}