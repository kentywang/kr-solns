#include <ctype.h>
#include <stdio.h>
#include <math.h>

int main()
{
  double atof(char[]);

  printf("%e\n", atof("4.321e-33"));

  return 0;
}

double atof(char s[])
{
  double val, power;
  int i, sign;

  int exp_sign = 0;
  int exp_power = 0;

  for (i = 0; isspace(s[i]); i++)
    ;

  sign = (s[i] == '-') ? -1 : 1;

  if (s[i] == '+' || s[i] == '-')
    i++;

  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');

  if (s[i] == '.')
    i++;

  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0;
  }

  if (s[i++] == 'e') {
    if (s[i] == '-') {
      exp_sign = -1;
      i++;
    } else {
      exp_sign = 1;
      if (s[i] == '+')
        i++;
    }

    while (isdigit(s[i])) {
      exp_power = 10 * exp_power + (s[i] - '0');
      i++;
    }
  }

  return sign * val / power * pow(10, exp_sign * exp_power);
}