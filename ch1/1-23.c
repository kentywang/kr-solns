/*

Comments can appear anywhere a blank, tab, or newline can.

[a][/][*]...[*][/][=][b] => [a][ ][=][b]

[a]['][/][*][\n][*][/]['] => unchanged

If we're not in a comment:
  If last_c is /:
    If the char is *:
      Set in_comment to TRUE. Set last_c to UNASSIGNED.
    Else:
      Print / and the char. Set last_c to UNASSIGNED.
  If last_c is not /:
    If the char is /:
      Set last_c to /.
    Else:
      Print char.
Else (we're in a comment):
  If last_c is *:
    If the char is /:
      Set in_comment to FALSE. Set last_c to UNASSIGNED. Print blank.
    Else:
      Do nothing.
  If last_c is not *:
    If the char is *:
      Set last_c to *.
    Else:
      Do nothing.

This doesn't handle quotes, but the basic pattern is similar.
*/

#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define UNASSIGNED -1

int main()
{
  int c;
  // Stores quote, slash, asterisk, or UNASSIGNED. Handling quotes takes
  // precedence, then comment characters, since comments can't be in quotes.

  // When outside of quotes or comments, freely store ' or " or * whenever
  // encountered. But in quote, ignore storing for comments.
  int last_c;
  // Don't need 16-bits for these. Char is the smallest type we know so far.
  char in_comment, in_quote;

  last_c = UNASSIGNED;
  in_comment = in_quote = FALSE;
  while ((c = getchar()) != EOF) {
    // printf("\nChar: %c, last_c: %d, in_comment: %d, in_quote: %d\n", c, last_c, in_comment, in_quote);
    if (in_quote == FALSE) {
      if (in_comment == FALSE) {
        if (last_c == '/') {
          if (c == '*') {
            in_comment = TRUE;
            last_c = UNASSIGNED;
          } else {
            putchar('/');
            putchar(c);

            if (c == '\'' || c == '"') {
              in_quote = TRUE;
              last_c = c;
            } else last_c = UNASSIGNED;
          }
        } else {
          if (c == '/')
            last_c = '/';
          else {
            putchar(c);

            if (c == '\'' || c == '"') {
              in_quote = TRUE;
              last_c = c;
            }
          }
        }
      } else if (last_c == '*') {
        if (c != '*') {
          // Reset last_c if anything but *. If *, keep it *.
          last_c = UNASSIGNED;
        
          if (c == '/') {
            in_comment = FALSE;
            putchar(' ');
          }
        }
      } else if (c == '*') {
        last_c = '*';
      }
    } else {
      putchar(c);

      if ((c == '\'' && last_c == '\'') || (c == '"' && last_c == '"')) {
        in_quote = FALSE;
        last_c = UNASSIGNED;
      }
    }
    
  }

  return 0;
}
