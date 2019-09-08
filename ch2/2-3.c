#include <stdio.h>
#include <ctype.h>
#define MAXLINE 80

/*
String                    Hexadecimal Decimal
"AF05B8" or "0xaf05b8" => 0xAF05B8 => 11470264
*/

int htoi(char hex_string[]);
int hex_char_to_int(char c);

int main()
{
  char s[MAXLINE] = "0xaf05b8";

  printf("%d\n", htoi(s));

  return 0;
}

int htoi(char s[])
{
  int c, result;

  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    c = 2;
  else c = 0;

  for (result = 0; s[c] != '\0'; ++c) {
    result = result * 16 + hex_char_to_int(s[c]);
  }
  return result;
}

int hex_char_to_int(char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'A' && c <= 'F')
    return 10 + c - 'A';
  if (c >= 'a' && c <= 'f')
    return 10 + c - 'a';

  return c;
}