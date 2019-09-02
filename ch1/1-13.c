#include <stdio.h>

/*

Input:
I love corgis so so much!

Desired output:
1: |
2: ||
3:
4: |
5: |
6: |

Hard to do without functions (for dynamic array resizing), so I'm doing a version that only works if the maximum length of any word falls under a certain threshold.

*/

#define IN 1
#define OUT 0
#define WORD_LENGTH_LIMIT 20

main()
{
  int word_state, max_word_length, curr_word_length, c, i, j;
  int freqs[WORD_LENGTH_LIMIT];

  // Step 1. Initialize frequncies array.
  for (i = 0; i < WORD_LENGTH_LIMIT; ++i)
    freqs[i] = 0;

  // Step 2. Populate word length frequencies array by iterating through 
  // input.
  max_word_length = 0;
  word_state = OUT;
  while ((c = getchar()) != EOF) {
    if (word_state == OUT) {
      if (c != ' ' && c != '\t' && c != '\n') {
        word_state = IN;
        curr_word_length = 1;
      }

    } else { // Currently in a word.
      if (c == ' ' || c == '\t' || c == '\n') {
        word_state = OUT;

        ++freqs[curr_word_length];

        if (curr_word_length > max_word_length)
          max_word_length = curr_word_length;
      } else ++curr_word_length;
    }
  }

  // Step 3. Produce histogram by iterating through frequencies array.
  for (i = 1; i <= max_word_length; ++i) {
    printf("%2d: ", i);
    for (j = 0; j < freqs[i]; ++j)
      putchar('|');
    putchar('\n');
  }
}