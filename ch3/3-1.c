#include <stdio.h>
#include <time.h>
#define ARR_LEN 1000000

int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

int main()
{
  clock_t t1, t2;
  int v[ARR_LEN];
  int result;

  for (int i = 0; i < ARR_LEN; ++i)
    v[i] = 3 * i;

  t1 = clock();
  result = binsearch(6963, v, ARR_LEN); // A: 2321
  t2 = clock();
  printf("Original, answer: %6d, time: %f\n", result, (double) (t2 - 1) / CLOCKS_PER_SEC);

  t1 = clock();
  result = binsearch2(6963, v, ARR_LEN); // A: 2321
  t2 = clock();
  printf("Modified, answer: %6d, time: %f\n", result, (double) (t2 - 1) / CLOCKS_PER_SEC);

  return 0;
}

int binsearch2(int x, int v[], int n)
{
  int low, mid, high;

  low = mid = 0;
  high = n - 1;

  // We need x != v[high] check because otherwise we'd get stuck in a loop
  // with two remaining elements and the element to find isn't the lower one. 
  while (x != v[low] && x != v[high] && low < high) {
    mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else // x is either at v[mid] or above.
      low = mid;
  }

  if (x == v[low])
    return low;
  else if (x == v[high])
    return high;
  return -1;
}

int binsearch(int x, int v[], int n)
{
  int low, mid, high;

  low = 0;
  high = n - 1;

  while (low <= high) {
    mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else
      return mid;
  }

  return -1;
}