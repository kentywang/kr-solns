#include <stdio.h>

// Statuses
#define BALANCED -2
#define UNBALANCED -1
#define OK -3

// Other
#define ERROR 1

/*

- parens
- brackets
- braces
- single/double quotes (remember unbalanced within is allowed, so ignore)
- comments (remember unbalanced within is allowed, so ignore)
- escape sequences (need to know when is real end quote)

We don't need a stack data structure when we can use call stacks!

Balanced:
(hello['(((\'((('{__comment_here_with_{{{__}])

Unbalanced:
(])
(()

Using \n instead of EOF for easier testing.

EDIT: Turns out I could've done it by just keeping track of the counts of
the left and right braces, making sure the right never exceeds the left and
that we end with an equal count.

*/

char get_end_brace(char type);
int check_brace(char c, char type);
int check_normal(char c);
int process_brace(char type);
int process_comment(void);
int process_enter_comment(void);
int process_escape_quote(char type);
int process_exit_comment(void);
int process_normal(void);
int process_quote(char type);

int main()
{
  if (process_normal() == UNBALANCED) {
    printf("Unbalanced!\n");
    return 0;
  }

  printf("All balanced.\n");
  return 0;
}

char get_end_brace(char type)
{
  if (type == '(')
    return ')';
  if (type == '[')
    return ']';
  if (type == '{')
    return '}';
  return ERROR;
}

int process_normal(void)
{
  int c;
  c = getchar();
  if (c == '\n')
    return BALANCED;

  // We're sure c is within 8 bits now (I think?).
  // Returning here, because hopefully tail-recursion optimized.
  return check_normal(c);
}

int check_normal(char c)
{
  int d;

  if (c == '/') {
    d = process_enter_comment();

    if (d == UNBALANCED)
      return UNBALANCED;
    if (d == OK)
      return process_normal();

    // This is the 2nd character that was mistook for entering a comment.
    return check_normal(d);
  }
  if (c == '\'' || c == '"')
    return process_quote(c);
  if (c == ')' || c == ']' || c == '}')
    return UNBALANCED;
  if (c == '(' || c == '[' || c == '{') { // Build stack.
    if (process_brace(c) == UNBALANCED)
      return UNBALANCED;
  }

  return process_normal();
}

int process_brace(char type)
{
  int c;
  c = getchar();
  if (c == '\n')
    return UNBALANCED; // Unterminated brace!

  return check_brace(c, type);
}

// Notice if we're in this brace search, we don't tail-recurse on comments,
// quotes, or other opening braces because we want to keep the stack.
int check_brace(char c, char type)
{
  int d;

  if (c == '/') {
    d = process_enter_comment();

    if (d == UNBALANCED)
      return UNBALANCED;
    if (d == OK)
      return process_brace(type);

    // This is the 2nd character that was mistook for entering a comment.
    return check_brace(d, type); // We're still in the brace.
  }
  if (c == '\'' || c == '"') {
    if (process_quote(c) == UNBALANCED)
      return UNBALANCED;

    return process_brace(type); // We're still in the brace.
  }
  if (c == '(' || c == '[' || c == '{') {
    if (process_brace(c) == UNBALANCED)
      return UNBALANCED;

    return process_brace(type); // We're still in the brace.
  }
  if (c == get_end_brace(type))
    return OK; // This brace is balanced. Continue.
  if (c == ')' || c == ']' || c == '}')
    return UNBALANCED; // A different ending brace!

  return process_brace(type);
}

// Last char seen when entering this is always /.
// This can return either UNBALANCED (unterminated comment), BALANCED (if
// EOF), OK (if terminated comment), or a character.
int process_enter_comment(void)
{
  int c;
  c = getchar();
  if (c == '\n')
    return BALANCED;

  if (c == '*')
    // We are in a comment!
    return process_comment();

  // Not the start of a comment. Let calling function handle new char.
  return c;
}

int process_comment(void)
{
  int c;
  c = getchar();
  if (c == '\n')
    return UNBALANCED; // Unterminated comment!

  if (c == '*')
    return process_exit_comment();

  return process_comment();
}

// Last char seen when entering this is always *.
int process_exit_comment(void)
{
  int c;
  c = getchar();
  if (c == '\n')
    return UNBALANCED; // Unterminated comment!

  if (c == '/')
    // We're out of the comment!
    return OK;

  if (c == '*')
    return process_exit_comment();

  return process_comment();
}

int process_quote(char type)
{
  int c;
  c = getchar(); 
  if (c == '\n')
    return UNBALANCED; // Unterminated quote!

  if (c == type)
    return OK;

  if (c == '\\')
    return process_escape_quote(type);
  
  return process_quote(type);
}

// Last char seen when entering this is always \.
int process_escape_quote(char type)
{
  int c;
  c = getchar(); 
  if (c == '\n')
    return UNBALANCED; // Unterminated quote!

  // No matter what character is here, we're still in the quote.
  return process_quote(type);
}