/** @file   main.c
 *  @brief  Problem 7 of lab 2
 *  @author Bart Lunenborg, s3410579
 */

#include "signals.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Given threshold T, Signal h and x, 
 * prints the indexes of y where the Pearson correlation >= T.
 */
int main(int argc, char *argv[]) {
  float threshold;
  scanf("%f", &threshold);
  threshold -= 0.000001;

  Signal h = readSignal();
  Signal x = readSignal();
  Pearson p = pearsonCorrelate(x, h);
  for (int i = 0; i < p.length; i++) {
    if (p.corrs[i] > threshold) {
      printf("%d %.5lf\n", i, p.corrs[i]);
    }
  }

  free(x.signal);
  free(h.signal);
  free(p.corrs);
  return 0;
}
