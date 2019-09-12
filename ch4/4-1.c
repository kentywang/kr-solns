#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int strrindex(char s[], char t[]);

int main()
{ //               Indices: 0    5    0 2  5    0  3
  printf("%d\n", strrindex("I love love love corgis!", "love")); // 12

  return 0;
}

int strrindex(char s[], char t[])
{
  // Temporal index on s. Starts on last index.
  int a = strlen(s) - 1;
  // Last index of t.
  const int b = strlen(t) - 1;

  int j; // Temporal index on t.
  int k; // Number of matched characters. Should only ever reach b + 1.
  for (; a >= 0; --a) {
    for (j = b, k = 0; j >= 0 && a-k >= 0 && s[a-k] == t[j]; --j, k++)
      ;
    if (k > b)
      // Index returned is current index on s minus length of t, shifted by 1.
      return a - b;
  }

  return -1;
}