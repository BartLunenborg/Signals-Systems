// Bart Lunenborg, s3410579

#include <stdio.h>
#include <stdlib.h>
#include "phasor.h"

int main(int argc, char *argv[]) {
  Phasor ph;
  int f_s, n;
  scanf("%d %d %lf %lf %lf", &f_s, &n, &ph.a, &ph.f, &ph.phi);

  int* samples = sample(f_s, n, ph);
  printArr(samples, n);

  free(samples);
  return 0;
}
