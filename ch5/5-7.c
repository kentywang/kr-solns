#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXLINES 5000   // max #lines to be sorted
#define MAXLEN 1000   // max length of any input line

char *lineptr[MAXLINES];  // pointers to text lines
char fulltext[MAXLINES * MAXLEN];

int readlines(char *lineptr[], int nlines);
int new_readlines(char *lineptr[], int nlines, char *fulltext);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(void)
{
  int nlines;    // number of input lines read
  clock_t t1, t2;

  t1 = clock();
  if((nlines = new_readlines(lineptr, MAXLINES, fulltext)) >= 0) {
    t2 = clock();
    // readlines: 0.003959, new_readlines: 0.004136. Pretty similar times.
    printf("Readlines time: %f\n", (double) (t2 - 1) / CLOCKS_PER_SEC);

    qsort(lineptr, 0, nlines-1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}

int get_line(char *, int);
char *alloc(int);

int new_readlines(char *lineptr[], int maxlines, char *fulltext)
{
  int len, nlines;
  char line[MAXLEN];
  char *textlimit = fulltext + MAXLINES * MAXLEN;

  nlines = 0;
  while ((len = get_line(line, MAXLEN)) > 0)
    if (nlines >= maxlines || fulltext + len > textlimit ) // EDIT: Left out OR condition.
      return -1;
    else {
      line[len-1] = '\0';   // delete newline
      strcpy(fulltext, line);
      lineptr[nlines++] = fulltext;
      fulltext += len;
    }
  return nlines;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = get_line(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else
      {
  line[len-1] = '\0';   // delete newline
  strcpy(p, line);
  lineptr[nlines++] = p;
      }
  return nlines;
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

/* writelies: wtire output lines */
void writelines(char *lineptr[], int nlines)
{
  int i;

  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
  int i, last;
  void swap(char *v[], int i, int j);

  if (left >= right)  // do nothing if array contains fewer than two elements
    return;
  swap(v, left, (left + right )/2);
  last = left;
  for (i = left+1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}