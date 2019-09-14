#include <stdio.h>
#include <stdlib.h>  // for atof()

#define MAXOP 100    // max size of operand or operator
#define NUMBER '0'   // signal that a number wes found

int getop(char []);
void push (double);
double pop (void);

/* reverse Polish calculator */
int main(void)
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF)
    {
      switch (type)
  {
  case NUMBER:
    push(atof(s));
    break;
  case '+':
    push(pop() + pop());
    break;
  case '-':
    op2 = pop();
    push(pop() - op2);
    break;
  case '*':
    push (pop() * pop());
    break;
  case '/':
    op2 = pop();
    if (op2 != 0.0)
      push (pop() / op2);
    break;
  case '\n':
    printf("\t%.8g\n", pop());
    break;
  default:
    printf("error: unknown command %s\n", s);
    break;
  }
    }  
  return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, con't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
  if (sp > 0)
    return val[--sp];
  else
    {
      printf("error: stack empty\n");
      return 0.0;
    }
}

#include <ctype.h>
#define GET -129 // Should be outside of range of any char.
#define NIL -130

int getch(int c);

/* getop: get next operator or numberic operand */
int getop(char s[])
{
  int i, c;

  while ((s[0] = c = getch(GET)) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.')
    return c;                  // not a number
  i = 0;
  if (isdigit(c))              // collect integer part
    while (isdigit(s[++i] = c = getch(GET)))
      ;
  if (c == '.')                // collect fraction part
    while (isdigit(s[++i] = c = getch(GET)))
      ;
  s[i] = '\0';
  if (c != EOF)
    getch(c);
  return NUMBER;
}

#define BUFFSIZE 100

int getch(int c)      // get a (possibly pushed back) character
{
  static char buf[BUFFSIZE];  // buffer for ungetch
  static int bufp = 0;        // next free posotion in buf

  if (c == GET)
    return (bufp > 0) ? buf[--bufp] : getchar();

  if (bufp >= BUFFSIZE)
    printf("ungetch: too many characters\n");
  else buf[bufp++] = c;

  return NIL;
}