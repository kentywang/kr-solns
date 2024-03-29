#include <stdio.h>
#include <stdlib.h>  // for atof()
#include <math.h>

/*
I'd love to split this into multiple files for compilation, but I still
need to understand how headers, defines, and declarations work across files.

4.6
I interpret this problem to mean that when a user enters a letter, then
number at the top of the stack is examined and associated with that letter,
so that in the future the letter is always an alias for the number. More work
needed to allow multiple sets to a same variable, since we need a language
to differentiate between setting and getting.

*/

#define MAXOP 100    // max size of operand or operator
#define NUMBER '0'   // signal that a number wes found

int getop(char []);
void push(double);
double pop(void);
void print_top(void);
void dupe_top(void);
void swap_operands(void);
void clear_stack(void);
void set_variable(int letter, double value);
double get_variable(int letter);
int is_assigned(int letter);

/* reverse Polish calculator */
int main(void)
{
  int type;
  double op2;
  char s[MAXOP];
  double temp;

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
        set_variable('x', pop());
        printf("\t%.8g\n", get_variable('x'));
        break;
      case '%': // 4.3
        op2 = pop();
        push((int) pop() % (int) op2);
        break;
      // 4.4
      // case 'p':
      //   print_top();
      //   break;
      // case 'd':
      //   dupe_top();
      //   break;
      // case 's':
      //   swap_operands();
      //   break;
      // case 'c':
      //   clear_stack();
      //   break;
      // 4.5
      // case 's':
      //   push(sin(pop()));
      //   break;
      // case 'e':
      //   push(exp(pop()));
      //   break;
      // case 'p':
      //   // Ensure 2nd operand is passed as 2nd arg to pow().
      //   // (Since evaluation order is not specified.)
      //   op2 = pop();
      //   push(pow(pop(), op2));
      //   break;
      // 4.6
      case 'a':
      case 'b':
      case 'c':
      case 'x':
        if (is_assigned(type))
          push(get_variable(type));
        else { 
          temp = pop();
          push(temp);
          set_variable(type, temp);
        }

        break;
      default:
        printf("error: unknown command %s\n", s);
        break;
    }
  }  
  return 0;
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

void print_top(void)
{
  printf("\t%.8g\n", val[sp-1]);
}

void dupe_top(void)
{
  if (sp > 0) {
    val[sp] = val[sp-1];
    sp++;
  } else
  printf("error: stack empty\n");
}

void swap_operands(void)
{
  double temp;

  if (sp > 1) {
    temp = val[sp-1];
    val[sp-1] = val[sp-2];
    val[sp-2] = temp; 
  } else
  printf("error: not enough operands to swap\n");
}

void clear_stack(void)
{
  sp = 0;
}

int is_assigned(int letter)
{
  return variables_assigned[letter - 'a'] == VARIABLE_IS_ASSIGNED ? 1 : 0;
}

void set_variable(int letter, double value)
{
  letter -= 'a';
  variables[letter] = value;
  variables_assigned[letter] = VARIABLE_IS_ASSIGNED;
}

double get_variable(int letter)
{
  return variables[letter - 'a'];
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
  if (c == '-') { // 4.3
    c = getch(); // Peek at next character

    if (!isdigit(c) && c !='.') {
      if (c != EOF)
        ungetch(c);
      else
        ungetch('\n'); // 4.9
      return '-';
    }

    s[++i] = c; // This is a number, so add first digit to string. 
  }
  if (isdigit(c))              // collect integer part
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')                // collect fraction part
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF) // Wouldn't this mean the next loop would overshoot the EOF?
    ungetch(c);
  else
    ungetch('\n'); // 4.9
  return NUMBER;
}

/////////////////////////////////////////////////////////////////////////////

// #define BUFFSIZE 100

// char buf[BUFFSIZE];  // buffer for ungetch
// int bufp = 0;        // next free posotion in buf

// int getch(void)      // get a (possibly pushed back) character
// {
//   return (bufp > 0) ? buf[--bufp] : getchar();
// }

// void ungetch(int c)  // push back on input
// {
//   if (bufp >= BUFFSIZE)
//     printf("ungetch: too many characters\n");
//   else buf[bufp++] = c;
// }

// // 4.7
// void ungets(char s[])
// {
//   int i;
//   for (i = strlen(s) - 1; i >= 0; --i) {
//     ungetch(s[i]);
//   }
// }

// 4.8 Revisions
#define UNASSIGNED -1

char buffer = UNASSIGNED;

int getch(void)      // get a (possibly pushed back) character
{
  int c;
  if (buffer != UNASSIGNED) {
    c = buffer;
    buffer = UNASSIGNED;
    return c;
  } else
    return getchar();
}

void ungetch(int c)  // push back on input
{
  if (buffer != UNASSIGNED)
    printf("ungetch: already buffered\n");
  else
    buffer = c;
}