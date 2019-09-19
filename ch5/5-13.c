#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000   // max #lines to be sorted
#define MAXLEN 1000   // max length of any input line

/*
We could scan through the text once to figure out how many lines there are,
then jump to the last nth line to begin printing. This would incur constant
storage cost, and we wouldn't store more than one line at a time.

But the book wants us to store more than one line, so let's process this
in one scan. This means we'll store every line, then print the last n lines.
*/

char **readlines(char *lineptr[], int nlines);
void tail(char *start[], char *end[], int nlines);

// Array of pointers, each can point to variable char array size.
char *text[MAXLINES];

int main(int argc, char *argv[])
{
  int n = 10; // Default.
  char **lastline; // Why doesn't "char (*lastline)[]" work?

  // Process arg.
  while (--argc)
    switch (**++argv) {
    case '-':
      n = atoi(++argv[0]);
      break;
    default:
      printf("Unexpected argument.\n");
      return -1;
    }

  if (lastline = readlines(text, MAXLINES)) {
    tail(text, lastline, n);
    return 0;
  }

  return -1;
}

int get_line(char *, int);
char *alloc(int);

// 5.13 Modification: Returns pointer to last line, or 0 if error.
char **readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = get_line(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return 0;
    else {
      line[len-1] = '\0';   // replace newline with null char
      strcpy(p, line);
      *lineptr++ = p;
      nlines++;
    }
  return lineptr;
}

/* get_line: read a line into s, return length */
int get_line(char *s, int lim)
{
  int c, i;

  // Using char X in lieu of EOF.
  for (i = 0; i<lim-1 && (c=getchar()) != 'X' && c != '\n'; i++)
    s[i] = c;
  if (c == '\n')
    {
      s[i] = c;
      ++i;
    }
  s[i] = '\0';
  return i;
}

#define ALLOCSIZE 50000           // size of available space

static char allocbuf[ALLOCSIZE];  // storage for alloc 
static char *allocp = allocbuf;   // next free position

char *alloc(int n)
{
  if (allocbuf + ALLOCSIZE - allocp >= n)   // if it fits
    {
      allocp += n;
      return allocp - n;  
    }
  else
    return 0;
}

void tail(char *start[], char *end[], int nlines)
{
  char **lineptr = end - nlines; // Why doesn't "char *lineptr[]" work?

  // If we're before the first line, increment until at first line.
  while (lineptr < start)
    lineptr++;

  // Reach but don't print the line at the end pointer, since it's empty.
  while (lineptr < end)
    printf("%s\n", *lineptr++);
}