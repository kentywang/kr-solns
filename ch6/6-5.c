#include <stdio.h>
#include <stdlib.h>

/*
Assuming we had a lookup function that returned the a struct containing
the element before the matching one, and a boolean value indicating if the
element is the first in the list, in which was the element _is_ the match.

If the list was doubly-linked, we wouldn't need to alter the lookup function.
*/

struct lookup_return {
  struct nlist *np;
  char first_element;
};

void undef(char *name)
{
  struct lookup_return lr;
  struct nlist *q;

  // We're copying the return of lookup to lp, instead of using a pointer.
  // For demonstration purposes, although it's just as valid and makes sense
  // since we're only storing a pointer and a char in it.
  if ((lr = lookup_prev(name)) != NULL) {
    if (lr.first_element) {
      hashtab[hash(name)] = lr.np->next;
      free((void *) lr.np->name);
      free((void *) lr.np->defn);
      free((void *) lr.np);
    } else {
      free((void *) lr.np->next->name);
      free((void *) lr.np->next->defn);

      // Save ref to match's next before we forget it.
      q = lr.np->next->next;

      free((void *) lr.np->next);

      lr.np->next = q;
    }
  }

  printf("Nothing to undefine.\n");
}