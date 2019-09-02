#include <stdio.h>

#define IN 1
#define OUT 0

// If we're not in a word, then if the next char is not whitespace, we print
// it and also set the state var to IN. We ignore if it is whitespace.

// If we're in a word, then if the next char is whitespace, we always print a
// newline, and then set the state var to OUT. If not whitespace, just print.

main()
{
  int c, state;

  state = OUT;
  while ((c = getchar()) != EOF) {
    if (state == OUT) {
      if (c != ' ' && c != '\t' && c != '\n') {
        putchar(c);
        state = IN;
      }
    }
    else {
      if (c == ' ' || c == '\t' || c == '\n') {
        putchar('\n');
        state = OUT;
      }
      else putchar(c);
    }
  }
}