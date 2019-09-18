#include <stdio.h>
#include <stdlib.h>  // for atof()
#define MAXOP 100    // max size of operand or operator
#define NUMBER '0'   // signal that a number wes found

/*
For some reason, we have to escape the asterisk (\*) on the command line.
*/

int getop(char [], int *argc_ptr, char **argv_ptr[]);
void push(double);
double pop(void);

int main(int argc, char *argv[])
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s, &argc, &argv)) != EOF) {
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
        return 0; // Returns!!
      default:
        printf("error: unknown command %s\n", s);
        return -1;
    }
  }

  return -2;
}

/////////////////////////////////////////////////////////////////////////////

#include <ctype.h>
#include <string.h>

/* getop: get next operator or numberic operand */
int getop(char s[], int *argc_ptr, char **argv_ptr[])
{
  int i, c;
  if (!--*argc_ptr)
    return '\n';
  printf("getop argc: %d\n, argv[0]: %s\n", *argc_ptr, (*argv_ptr)[0]);

  // *(++*argv_ptr)[0] wouldn't work. Why?
  s[0] = c = (*++*argv_ptr)[0]; // or **++*argv_ptr?
    ;
  s[1] = '\0';
  printf("getop c: %c\n", c);
  if (!isdigit(c) && c !='.' && c != '-') // 4.3
    return c;                  // not a number
  i = 0;
  if (isdigit(c))              // collect integer part
    while (isdigit(s[++i] = c = *++(*argv_ptr)[0])) // or *++**argv_ptr?
      ;
  if (c == '.')                // collect fraction part
    while (isdigit(s[++i] = c = *++(*argv_ptr)[0]))
      ;
  s[i] = '\0';
  // if (c != EOF) // Wouldn't this mean the next loop would overshoot the EOF?
  //   ungetch(c);
  return NUMBER;
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
