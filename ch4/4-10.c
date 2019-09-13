#include <stdio.h>
#include <stdlib.h>  // for atof()
#define MAXOP 100    // max size of operand or operator
#define MAXLINE 1000
#define NUMBER '0'   // signal that a number wes found

/*
Instead of ridding getch and ungetch, I just repurposed them to be the way we
interact with the fetched line. Less code change.
*/

int getop(char []);
int get_line(char s[], int lim); // Renamed to avoid naming conflict.
void push(double);
double pop(void);
void process_line(void);

char line[MAXLINE];
int next_char_index = 0; // Index on line to know which character to get next.

int main(void)
{

  while (get_line(line, MAXLINE) > 0) {
    process_line();
    next_char_index = 0;
  }
  return 0;
}

void process_line(void)
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
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
        return; // Returns!!
      default:
        printf("error: unknown command %s\n", s);
        break;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////

#include <ctype.h>
#include <string.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numberic operand */
int getop(char s[])
{
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';

  if (!isdigit(c) && c !='.' && c != '-') // 4.3
    return c;                  // not a number
  i = 0;
  if (isdigit(c))              // collect integer part
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')                // collect fraction part
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF) // Wouldn't this mean the next loop would overshoot the EOF?
    ungetch(c);
  return NUMBER;
}

/////////////////////////////////////////////////////////////////////////////

int getch(void)      // get a (possibly pushed back) character
{
  int len = strlen(line);
  if (next_char_index >= len)
    return EOF;
  return line[next_char_index++];
}

void ungetch(int c)  // push back on input
{
  next_char_index--;
}

// 4.7
void ungets(char s[])
{
  int i;
  for (i = strlen(s) - 1; i >= 0; --i) {
    ungetch(s[i]);
  }
}

/////////////////////////////////////////////////////////////////////////////

#define MAXVAL 100
#define VARIABLES_LENGTH 26
#define VARIABLE_IS_ASSIGNED 999 /* Could clash with garbage in array. */

int sp = 0;
double val[MAXVAL];
double variables_assigned[VARIABLES_LENGTH];
double variables[VARIABLES_LENGTH];

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

/////////////////////////////////////////////////////////////////////////////

int get_line(char s[], int lim)
{
  int c, i;

  i = 0;
  while(--lim > 0 && ((c=getchar()) != EOF && c != '\n'))
    s[i++] = c;
  if (c == '\n')
    s[i++] = '\n';
  s[i] = '\0';
  return i;              
}
