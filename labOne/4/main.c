// Bart Lunenborg, s3410579

#include <stdio.h>
#include <stdlib.h>
#include "phasor.h"

int main(int argc, char *argv[]) {
  double f_s, n, a, f, phi;
  scanf("%lf %lf %lf %lf %lf", &f_s, &n, &a, &f, &phi);
  int* samples = sample(f_s, n, a, f, phi);
  printArr(samples, n);
  free(samples);
  return 0;
}
