#include <stdio.h>

#define MAXLEN 1000

int getint(int *);

int main(void)
{
  int a[MAXLEN], n, temp;

  for (n = 0; n < MAXLEN && (temp = getint(&a[n])) != EOF && temp != 0; n++)
    ;

  for (int i = 0; i < n; i++)
    printf("%d\n", a[i]);

  return 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
  int c, d, sign;

  while (isspace(c = getch())) // skip whitespaces
    ;
  if (!isdigit(c) && c != EOF && c!= '+' && c != '-')
    {
      ungetch(c);   // it's not a number
      return 0;
    }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    // 5.1
    if (!isdigit(d = getch())) {
      if (d == EOF) {
        ungetch(c); // Put back sign char.
        return d;
      }

      ungetch(d); // Put back whatever that non-digit, non-EOF char was.
      ungetch(c); // Put back sign char.
      return 0;
    }
  }
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

#define BUFFSIZE 100

char buf[BUFFSIZE];  // buffer for ungetch
int bufp = 0;        // next free position in buf

int getch(void)      // get a (possibly pushed back) character
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  // push back on input
{
  if (bufp >= BUFFSIZE)
    printf("ungetch: too many characters\n");
  else buf[bufp++] = c;
}
