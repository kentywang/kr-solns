#include <stdio.h>

float f_to_c(float);

int main()
{
  float fahr;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  printf("%3c %6c\n--- ------\n", 'F', 'C');

  fahr = lower;
  while (fahr <= upper) {
    printf("%3.0f %6.1f\n", fahr, f_to_c(fahr));
    fahr = fahr + step;
  }

  return 0;
}

float f_to_c(float f)
{
 return (5.0 / 9.0) * (f - 32.0);
}