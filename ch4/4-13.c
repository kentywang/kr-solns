#include <stdio.h>
#include <string.h>

void reverse(char s[]);

int main()
{
  char s[] = "hello";
  reverse(s);
  printf("%s\n", s);

  return 0;
}

void reverse(char s[])
{
  // EDIT: Moved declaration into function.
  void reverse_iter(char s[], int start, int end);

  reverse_iter(s, 0, strlen(s) - 1); // Ignore null char at end.
}

void reverse_iter(char s[], int start, int end)
{
  if (end - start >= 1) {
    int temp = s[start];
    s[start] = s[end];
    s[end] = temp;

    reverse_iter(s, start + 1, end - 1);
  }
}