#include <stdio.h>

main()
{
	printf("hello, world\c\n");
}

// Looks like if the escape character is not recognized, it just prints the
// original character.