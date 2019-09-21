#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
enum { YES, NO };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype; /* type of last token */
char token[MAXTOKEN]; /* last token string */
char prev_token[MAXTOKEN];
char name[MAXTOKEN]; /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000]; /* output string */

int main()
{
    int type;
    int prev = NO;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = (prev == YES ? type : gettoken())) != '\n') {
            if (prev == YES) {
                prev = NO;
                strcpy(token, prev_token);
            }
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                if ((type = gettoken()) == PARENS || type == BRACKETS)
                    sprintf(temp, "(*%s)",out);
                else
                    sprintf(temp, "*%s",out);
                prev = YES;
                strcpy(prev_token, token);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                printf("invalid input at %s\n",token);
        }
        printf("%s\n", out);
    }

    return 0;
}

int gettoken(void) /* returns next token */
{
  int c, getch(void); /* getch: get a (possibly pushed back) character */
  void ungetch(int); /* ungetch: push character back on input */
  /* functions from K&R, 2nd ed., ch 4.3, p. 79 */
  /* reproduced at bottom of page */
  char *p = token;

  while ( (c=getch())==' ' || c=='\t' ) /* skip white space */
    ;
  if ( c=='(' ) {
    if ( (c=getch())==')' ) {
      strcpy(token, "()");
      return tokentype = PARENS;
    }
    else {
      ungetch(c);
      return tokentype = '(';
    }
  }
  else if ( c=='[' ) {
    for (*p++ = c; (*p++ = getch()) != ']'; )
      ; 
    *p = '\0'; 
    return tokentype = BRACKETS;
  }
  else if ( isalpha(c) ) {
    for (*p++ = c; isalnum(c=getch());)
      *p++ = c; 
    *p = '\0';
    ungetch(c); 
    return tokentype = NAME;
  }
  else
  return tokentype = c;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* pretend to push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else buf[bufp++] = c;
}

void clear_buf(void)
{
  bufp = 0;
}