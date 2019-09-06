/*
New strat: 

If char is non-blank and buffer of spaces/tabs is empty, print immediately.
If char is non-blank and buffer of spaces/tabs isn't empty, flush out
populated parts of buffer first before printing.
If char is blank, put in buffer.

Buffer should always be smaller or equal to the stipulated max line length,
so we should never overflow its size.

If we exceed the line length and buffer is not full, reset the buffer index,
print a newline char, and then restart loop on same new char.
If we exceed the line length and buffer is full, we had a full line of
spaces, so do the same as above but don't print a newline char.

(A: non-blank, S: space, N: newline)
     ><
ASSASSA  => ASSANA
     ><
SSSSSSSA => SA
     ><
AAAAAAA  => AAAAAANA

POST-SOLUTION: There's a potential issue where if you end with a newline at
the demarcation of the line length, it prints two newlines back to back. But
the book doesn't specify that this isn't wanted.
*/

#include <stdio.h>
#define LINE_LENGTH 6

void flush_buffer_to(int buffer_index, int buffer[]);

int main()
{
  int c, buffer[LINE_LENGTH], fill, line_col;

  line_col = 1;
  fill = 0;
  while ((c = getchar()) != EOF) {
    if (line_col > LINE_LENGTH) {
      line_col = 1;

      if (fill < LINE_LENGTH) // Buffer isn't full, so add newline.
        putchar('\n');

      fill = 0;
    } // Continue execution below, even if passed through conditional above.

    if (c != '\t' && c != ' ') {
      // We don't increment line_col here, because newline doesn't count.
      if (c == '\n') {
        line_col = 1;
        putchar('\n');
        fill = 0;
      } else if (fill == 0) {
        putchar(c);
        ++line_col;
      } else { 
        // -1 because converting to index.
        flush_buffer_to(fill - 1, buffer);
        fill = 0;
        putchar(c);
        ++line_col;
      }
    } else { // Char is blank!
      buffer[fill] = c;
      ++fill;

      ++line_col;
    }
  }
}

void flush_buffer_to(int buffer_index, int buffer[])
{
  int i;
  for (i = 0; i <= buffer_index; ++i)
    putchar(buffer[i]);
}