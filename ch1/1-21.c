#include <stdio.h>
#define MAXLINE 80
#define TAB_STOP_SIZE 4

/*
When a tab or a space will produce the same spacing, prefer the tab. No
reason behind that; we just need to make a choice and keep it consistent.

This is harder to do without storing an array, but we shall try.

              |           |           |
              [A][ ][ ][ ][ ][ ][E][ ][\n]
char_pos:      1  2  3  4  5  6  7  8   0
char_pos % 4:  1  2  3  0  1  2  3  0
spaces_seen:      1  2  3  1  2     1

becomes:      [A][\t][ ][ ][E][\t]
               0   1  2  3  4   5

POST-SOLUTION: That was hard. Very hard.

*/

int main()
{

  int c;

  int char_pos; // Starts on 1.

  // Since we can't guarantee we'll have spaces until the tab stop, we
  // keep track of how many we've seen so far so that if we run into a
  // non-space, we can "back-populate" the array with spaces.
  int spaces_seen;

  // Keeps track if current state of iteration is on the last character of a
  // tab zone.
  int zero_if_last_pos;

  char_pos = 0;
  while ((c = getchar()) != EOF) {
    ++char_pos; // Moves to position we're examining _after_ getting its char.

    if (c != ' ') {
      putchar(c);

      if (c == '\n')
        char_pos = 0;
    }
    else {
      zero_if_last_pos = char_pos % TAB_STOP_SIZE;
      spaces_seen = 1;

      while (zero_if_last_pos > 0 && ((c = getchar()) != EOF) && c == ' ') {
        ++char_pos;
        zero_if_last_pos = char_pos % TAB_STOP_SIZE;
        ++spaces_seen;
      }
      if (zero_if_last_pos == 0)
        putchar('X');
      else {
        while (spaces_seen > 0) {
          putchar(' ');
          --spaces_seen;
        }
        if (c != ' ') { // Takes care of newline char too.
          putchar(c);
          ++char_pos;
        }
        if (c == '\n')
          char_pos = 0;
      }
    }
  }

  return 0;
}
