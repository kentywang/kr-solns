#include <stdio.h>

// If we allow nested loops, the logic is much cleaner. And if we convert to
// a functional style, it's even easier to reason about.

void process_normal(void);
void process_quote(char type);
void process_enter_comment(void);
void process_comment(void);
void process_exit_comment(void);
void check_normal(char c);

int main()
{
  process_normal();

  return 0;
}

void process_normal(void)
{
  int c;
  c = getchar();
  if (c == EOF)
    return;

  // We're sure c is within 8 bits now (I think?).
  // Returning here, because hopefully tail-recursion optimized.
  return check_normal(c);
}

void check_normal(char c)
{
  if (c == '/')
    return process_enter_comment();

  // Not a start to a comment, so char definitely printable.
  putchar(c);

  if (c == '\'' || c == '"')
    return process_quote(c); // We just printed left quote.

  return process_normal();
}

// Last char seen when entering this is always /.
void process_enter_comment(void)
{
  int c;
  c = getchar();
  if (c == EOF)
    return;

  if (c == '*')
    // We are in a comment!
    return process_comment();

  // Not the start of a comment, so we're safe to print the previous /.
  putchar('/');

  return check_normal(c);
}

void process_comment(void)
{
  int c;
  c = getchar();
  if (c == EOF)
    return;

  if (c == '*')
    return process_exit_comment();

  return process_comment();
}

// Last char seen when entering this is always *.
void process_exit_comment(void)
{
  int c;
  c = getchar();
  if (c == EOF)
    return;

  if (c == '/') {
    // We're out of the comment!
    putchar(' ');
    return process_normal();
  }

  if (c == '*')
    return process_exit_comment();

  return process_comment();
}

void process_quote(char type)
{
  int c;
  c = getchar(); 
  if (c == EOF)
    return;

  putchar(c);

  if (c == type)
    return process_normal(); // We just printed right quote, so now done.
  
  return process_quote(type);
}