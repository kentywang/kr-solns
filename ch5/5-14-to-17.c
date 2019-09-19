#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort2(void *lineptr[], int left, int right, int reverse,
  int (*comp)(void *, void *));

int numcmp(char *, char *);

int main(int argc, char *argv[])
{
  int nlines;
  int c;
  int reverse = 0;
  int numeric = 0;

  while (--argc && (*++argv)[0] == '-')
    while (c = *++argv[0])
      switch (c) {
      case 'n':
        numeric = 1;
        break;
      case 'r':
        reverse = 1;
        break;
      default:
        printf("Unexpected argument.\n");
        return -1;
      }

  if((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
      qsort2((void **) lineptr, 0, nlines-1, reverse,
       (int (*)(void*, void*))(numeric ? numcmp : strcmp));
      writelines(lineptr, nlines);
      return 0;
    }
  else
    {
      printf("input too big to sort\n");
      return 1;
    }
}

void qsort2(void *v[], int left, int right, int reverse,
  int(*comp)(void *, void *))
{
  int i, last;
  void swap(void *v[], int, int);

  if(left >= right)
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for(i = left + 1; i <= right; i++)
    // 5-14
    if ((reverse ? (*comp)(v[left], v[i]) : (*comp)(v[i], v[left])) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort2(v, left, last - 1, reverse, comp);
  qsort2(v, last + 1, right, reverse, comp);
}

#include <stdlib.h>

int numcmp(char *s1, char *s2)
{
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

void swap(void *v[], int i, int j)
{
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}


#define MAXLEN 1000   // max length of any input line
int get_line(char *, int);
char *alloc(int);

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

  for (i = 0; i<lim-1 && (c=getchar()) != 'X' /*EOF*/ && c != '\n'; i++)
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

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
  int i;

  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}