#include <stdio.h>

/*
Return type of getfloat remains the same as getint's.
*/

#define MAXLEN 1000

int getfloat(double *);

int main(void)
{
  double a[MAXLEN];
  int n, temp;

  for (n = 0; n < MAXLEN && (temp = getfloat(&a[n])) != EOF && temp != 0; n++)
    ;

  for (int i = 0; i < n; i++)
    printf("%f\n", a[i]);

  return 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

int getfloat(double *pn)
{
  int c, d, sign, power;

  while (isspace(c = getch())) // skip whitespaces
    ;
  if (!isdigit(c) && c != EOF && c!= '+' && c != '-' && c != '.')
    {
      ungetch(c);   // it's not a number
      return 0;
    }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    if (!isdigit(d = getch()) && d != '.') {
      if (d == EOF) {
        ungetch(c); // Put back sign char.
        return d;
      }

      ungetch(d); // Put back whatever that non-digit, non-EOF char was.
      ungetch(c); // Put back sign char.
      return 0;
    }
    c = d;
  }
    // printf("\nStep 1: %c\n", c);
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');

  if (c == '.') {
    if (!isdigit(d = getch())) {
      if (d == EOF)
        return d;

      ungetch(d); // Put back whatever that non-digit, non-EOF char was.
      return 0;
    }
    c = d;
  }

  for (power = 1; isdigit(c); c = getch(), power *= 10)
    *pn = 10 * *pn + (c - '0');
  // printf("\nStep 3: %f\n", *pn);
  *pn = *pn * sign / power;
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
