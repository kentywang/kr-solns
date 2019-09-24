#include <stdio.h>
#include <ctype.h>
#include <string.h>

int identity(int);

int main(int argc, char *argv[])
{
  int c;
  int (*f)(int);

  f = strcmp(argv[0], "./lower") == 0 ? &tolower :
      strcmp(argv[0], "./upper") == 0 ? &toupper :
                                        &identity;

  while ((c = getchar()) != EOF)
    putchar(f(c));

  return 0;
}

int identity(int x)
{
  return x;
}