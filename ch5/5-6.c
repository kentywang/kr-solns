#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 100

int my_getline(char *s, int lim);
int atoi(const char *s);
char *itoa(int n);
void reverse(char *s);
int strindex(const char *s, const char *t);

int main()
{
  char s[MAXLINE];
  printf("%d\n", my_getline(s, MAXLINE));
  printf("%s\n", s);

  printf("%d\n", atoi("-123"));

  printf("%s\n", itoa(-456));

  printf("%d\n", strindex("Power overwhelming", "over")); // 6

  return 0;
}

int my_getline(char *s, int lim)
{
  char *orig_s = s;
  int c;

  for (; lim-1 > 0 && (c = getchar()) != EOF && c != '\n'; --lim, s++)
    *s = c;

  if (c == '\n')
    *s++ = c;

  *s = '\0';

  return s - orig_s;
}

int atoi(const char *s)
{
  int sign;
  int n = 0;

  if (*s == '-') {
    sign = -1;
    ++s;
  } else sign = 1;

  while (*s >= '0' && *s <= '9') {
    n = 10 * n + *s - '0';
    ++s;
  }

  return sign * n;
}

char *itoa(int n)
{
  void reverse(char *s);
  char s[MAXLINE];
  char *p, *p_start;

  p_start = p = s;

  int neg_sign = n < 0;

  do {
    *p++ = abs(n) % 10 + '0';
  } while (n /= 10);

  if (neg_sign)
    *p++ = '-';

  *p = '\0';

  reverse(p_start);

  return p_start;
}

void reverse(char *s) // ab a abc
{
  char *start, *end;
  start = end = s;

  while (*end)
    end++;

  while (--end > start) { // Omit null char.
    char temp = *start;
    *start++ = *end;
    *end = temp;
  }
}

int strindex(const char *s, const char *t)
{
  const char *orig_s = s;
  const char *orig_t = t;

  // Block-scoped variable.
  for (const char *inner_s = s; *s; inner_s = ++s, t = orig_t)
    while (*inner_s++ == *t++)
      if (!*t) // If the chars are equal and t's next char is \0, we're done.
        return s - orig_s; 

  return -1;
}