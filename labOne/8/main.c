/** @file   main.c
 *  @brief  Problem 8 of lab 1
 *  @author Bart Lunenborg, s3410579
 */

#include <stdio.h>
#include <stdlib.h>
#include "sinusoid.h"

int main(int argc, char *argv[]) {
  int n, period;
  scanf("%d", &n);

  Sinusoid* sinusoids = malloc(n * sizeof(Sinusoid));
  for (int i = 0; i < n; i++) {
    scanf("%lf %d %lf", &sinusoids[i].a, &period, &sinusoids[i].phi);
    sinusoids[i].f = 1 / (double) period;
  }
  printf("%d\n", fundamentalPeriod(sinusoids, n));

  free(sinusoids);
  return 0;
}
