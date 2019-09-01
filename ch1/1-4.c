#include <stdio.h>

main()
{
  int celsius; /* We don't need float for C. */
  float fahr;

  int lower, upper, step;

  lower = -100;
  upper = 100;
  step = 20;

  printf("%4c %6c\n---- ------\n", 'C', 'F');

  celsius = lower;
  while (celsius <= upper) {
    fahr = (9.0/5.0) * celsius + 32.0;
    printf("%4d %6.1f\n", celsius, fahr);
    celsius = celsius + step;
  }
}