#include <stdio.h>
#define MAXLINE 1000

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main()
{
  char escaped[MAXLINE], unescaped[MAXLINE];
  
  escape("hello\tworld!\n", escaped);
  unescape("hello\\n\\tworld!", unescaped);

  printf("Escaped:\n%s\n", escaped);
  printf("Unescaped:\n%s\n", unescaped);

  return 0;
}

void unescape(char s[], char t[])
{
  int i, j;
  for (i = j = 0; s[i] != '\0'; ++i) {
    if (s[i] == '\\')
      switch (s[++i]) {
        case 't':
          t[j++] = '\t';
          break;
        case 'n':
          t[j++] = '\n';
          break;
        default: // EDIT: Print other escaped sequences literally.
          t[j++] = '\\';
          t[j++] = s[i];
          return;
      }
    else
      t[j++] = s[i];
  }
  // EDIT: Needs this, since null character is not escaped.
  t[j] = '\0';
}

void escape(char s[], char t[])
{
  int i, j;
  for (i = j = 0; s[i] != '\0'; ++i) {
    switch (s[i]) {
      case '\t':
        t[j++] = '\\';
        t[j++] = 't';
        break;
      case '\n':
        t[j++] = '\\';
        t[j++] = 'n';
        break;
      default:
        t[j++] = s[i];
        break;
    }
  }
  // EDIT: Forgot this.
  t[j] = '\0';
}