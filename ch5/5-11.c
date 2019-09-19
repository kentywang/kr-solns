#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 20
#define TAB_STOP_SIZE 4

/*
Assuming "list of tab stops" is like this:
4 8 16 ...

Skipping the entab part.
*/

int detab(char line[], int num_stops, int *tab_stops);
void to_int_arr(int tab_stops[], int num_stops, char *tab_stop_strings[]);

int main(int argc, char *argv[])
{
  char line[MAXLINE];
  int tab_stops[--argc];

  to_int_arr(tab_stops, argc, ++argv);
  
  // int i = 0;
  // while (i < argc)
  //   printf("%d\n", tab_stops[i++]);

  while (detab(line, argc, tab_stops) > 0)
    printf("%s\n", line);

  return 0;
}

void to_int_arr(int tab_stops[], int num_stops, char *tab_stop_strings[])
{
  while (num_stops--) {
    *tab_stops++ = atoi(*tab_stop_strings++);
  }
}

int detab(char s[], int num_stops, int *tab_stops)
{
  int i, c, spaces_to_add;

  spaces_to_add = num_stops ? *tab_stops : TAB_STOP_SIZE;
  i = 0;
  while (i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n') {
    if (c == '\t') {
      while (spaces_to_add > 0 && i < MAXLINE - 1) {
        s[i] = ' ';

        --spaces_to_add;
        ++i;
      }

      // Spaces count is now 0, so reset.
      spaces_to_add = num_stops ? *++tab_stops : TAB_STOP_SIZE;
    }
    else {
      s[i] = c;

      // Below are the increments/decrements for the next loop.
      if (spaces_to_add == 1)
        // Reset spaces count.
        spaces_to_add = num_stops ? *++tab_stops : TAB_STOP_SIZE;
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
