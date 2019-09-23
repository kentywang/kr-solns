#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// #define MAXWORD 100
#define DEFAULT_LEN 6

/*
Modified getword and main.
*/

struct tnode               // the tree node:
{
  char *word;              // points to the text
  int count;               // number of occurrences
  struct tnode *left;      // left child
  struct tnode *right;     // right child
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

/* word frequency count*/
int main(int argc, char *argv[])
{
  struct tnode *root;
  char word[DEFAULT_LEN];

  root = NULL;
  while (getword(word, (argc == 2 ? atoi(argv[1]) : DEFAULT_LEN)) != '\\'/*EOF*/)
    if (isalpha(word[0]))
      root = addtree(root, word);
  treeprint(root);
  return 0;
}

struct tnode *talloc(void);
char *str_dup(char *);

/* addtree: add a node with 2, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
  int cond;

  if (p == NULL)               // a new word has arrived
    {
      p = talloc();            // make a new node
      p->word = str_dup(w);
      p->count = 1;
      p->left = p->right = NULL;
    }
  else if ((cond = strcmp(w, p->word)) == 0)
    p->count++;               // repeated word
  else if (cond < 0)
    p->left = addtree(p->left, w);
  else
    p->right = addtree(p->right, w);
  return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
  if (p != NULL)
    {
      treeprint(p->left);
      printf("%4d %s\n", p->count, p->word);
      treeprint(p->right);
    }
}

#include <stdlib.h>
/* talloc: make a tnode */
struct tnode *talloc(void)
{
  return (struct tnode *) malloc(sizeof(struct tnode));
}

char *str_dup(char *s)    // make a duplicate of s
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
    ;
  if (c != '\\'/*EOF*/)
    *w++ = c;
  if (!isalpha(c))
    {
      *w = '\0';
      return c;
    }
  for ( ; --lim > 0; w++)
    if (!isalnum(*w = getch())) {
      ungetch(*w);
      break;
    }

  *w = '\0';

  // We've reached the limit. Find where word terminates to reset for next
  // word.
  if (!lim)
    while (!isspace(c = getch()))
      ;

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