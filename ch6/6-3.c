#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define MAXOCCUR 1000

struct tnode               // the tree node:
{
  char *word;              // points to the text
  int lines[MAXOCCUR];
  struct tnode *left;      // left child
  struct tnode *right;     // right child
};

struct tnode *addtree(struct tnode *, char *, int ln);
void treeprint(struct tnode *);
int getword(char *, int);

static int line_no = 1;

/* word frequency count*/
int main(void)
{
  struct tnode *root;
  char word[MAXWORD];

  root = NULL;
  while (getword(word, MAXWORD) != '\\'/*EOF*/)
    if (isalpha(word[0]))
      root = addtree(root, word, line_no);
  treeprint(root);
  return 0;
}

struct tnode *talloc(void);
char *str_dup(char *);

/* addtree: add a node with 2, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int ln)
{
  int cond;

  if (p == NULL)               // a new word has arrived
    {
      p = talloc();            // make a new node
      p->word = str_dup(w);
      p->lines[0] = ln;
      p->lines[1] = 0; // Use 0 as signal for end of lines list.
      p->left = p->right = NULL;
    }
  // repeated word
  else if ((cond = strcmp(w, p->word)) == 0) {
    // Find the end of the list or the current line.
    int i;
    for (i = 0; p->lines[i] != ln && p->lines[i] != 0; ++i)
      ;
    // We ignore if we already have a line for the word.
    if (p->lines[i] == 0) {
      p->lines[i++] = ln;
      p->lines[i] = 0;
    }
  }
  else if (cond < 0)
    p->left = addtree(p->left, w, ln);
  else
    p->right = addtree(p->right, w, ln);
  return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
  if (p != NULL)
    {
      treeprint(p->left);

      printf("Word: %s\nLines\n", p->word);
      for (int i = 0; p->lines[i]; ++i)
        printf("%d\n", p->lines[i]);

      treeprint(p->right);
    }
}

#include <stdlib.h>
/* talloc: make a tnode */
struct tnode *talloc(void)
{
  return (struct tnode *) malloc(sizeof(struct tnode));
}

char *str_dup(char *s)   // make a duplicate of s
{
  char *p;

  p = (char *) malloc(strlen(s)+1);   // +1 for '\0'
  if (p != NULL)
    strcpy(p, s);
  return p;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  while (isspace(c = getch()))
    if (c == '\n')
      ++line_no;
  if (c != '\\'/*EOF*/)
    *w++ = c;
  if (!isalpha(c))
    {
      *w = '\0';
      return c;
    }
  for ( ; --lim > 0; w++)
    if (!isalnum(*w = getch()))
      {
  ungetch(*w);
  break;
      }
  *w = '\0';
  return word[0];
}

#define BUFFSIZE 100

char buf[BUFFSIZE];  // buffer for ungetch
int bufp = 0;        // next free posotion in buf

int getch(void)      // get a (possibly pushed back) character
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  // push back on input
{
  if (bufp >= BUFFSIZE)
    printf("ungetch: too many characters\n");
  else buf[bufp++] = c;
}