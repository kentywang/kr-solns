#include <stdio.h>
#define MAXLINE 1000

void expand(char s1[], char s2[]);

int main()
{
  char s[MAXLINE];
  expand("-a-g-z0-9-", s);
  printf("%s\n", s);

  return 0;
}

void expand(char s1[], char s2[])
{
  int i, j, k;
  for (i = 0, j = 0; s1[i] != '\0'; ++i) {
    if (
      // This could cause issues when looking outside of array's actual range.
      // Actually, it shouldn't, since if s1[i+1] is not '\0', we stop.
      s1[i+1] == '-' &&
      s1[i+2] >= s1[i] &&
      (
        (
          s1[i] >= 'a' &&
          s1[i] <= 'z' &&
          s1[i+2] <= 'z'
        ) ||
        (
          s1[i] >= 'A' &&
          s1[i] <= 'Z' &&
          s1[i+2] <= 'Z'
        ) ||
        (
          s1[i] >= '0' &&
          s1[i] <= '9' &&
          s1[i+2] <= '9'
        )
      )
    ) {
      // Stop one element short, letting the next iteration complete it.
      for (k = 0; s1[i] + k <= s1[i+2] - 1; ++k)
        s2[j++] = s1[i] + k;
      // We iterated over the start char, now jump over the - and process
      // the end char. We increment here once, since the loop already
      // increments once by default, summing to two increments.
      ++i;
    }
    else
      s2[j++] = s1[i];
  }
  s2[j] = '\0';
}