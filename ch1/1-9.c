#include <stdio.h>

#define NOT_A_CHAR -1

main()
{
  int curr, prev;

  prev = NOT_A_CHAR;
  while ((curr = getchar()) != EOF) {
    // && and else haven't been introduced yet.
    if (curr != ' ')
       // If not space, just print.
      putchar(curr);

    if (curr == ' ')
      if (prev != ' ')
        // If space, only print if prev wasn't space.
        putchar(curr);
    
    prev = curr;
  }
}