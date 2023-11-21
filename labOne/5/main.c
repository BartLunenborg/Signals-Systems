// Bart Lunenborg, s3410579

#include <stdio.h>
#include <stdlib.h>
#include "sinusoid.h"

int main(int argc, char *argv[]) {
  int f_s, n, m;
  scanf("%d %d %d", &f_s, &n, &m);

  Sinusoid* sss = calloc(n, sizeof(Sinusoid));
  for (int i = 0; i < m; i++) {
    scanf("%lf %lf %lf", &sss[i].a, &sss[i].f, &sss[i].phi);
  }

  int* samples = sampleSinusoids(f_s, n, sss, m);
  printArr(samples, n);

  free(sss);
  free(samples);
  return 0;
}
