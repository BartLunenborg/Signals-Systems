// Bart Lunenborg, s3410579

#include <stdio.h>
#include <stdlib.h>
#include "sinusoid.h"

int main(int argc, char *argv[]) {
  int f_s, n, m;
  scanf("%d %d %d", &f_s, &n, &m);

  Sinusoid* sinusoids = malloc(m * sizeof(Sinusoid));
  for (int i = 0; i < m; i++) {
    scanf("%lf %lf %lf", &sinusoids[i].a, &sinusoids[i].f, &sinusoids[i].phi);
  }

  int* samples = sample(f_s, n, sinusoidsAdd(sinusoids, m));
  printArr(samples, n);

  free(sinusoids);
  free(samples);
  return 0;
}
