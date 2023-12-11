/** @file   main.c
 *  @brief  Problem 6 of lab 2
 *  @author Bart Lunenborg, s3410579
 */

#include "signals.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  Signal h = readSignal();
  Signal x = readSignal();
  Pearson p = pearsonCorrelate(x, h);
  printPearson(p);

  free(x.signal);
  free(h.signal);
  free(p.corrs);
  return 0;
}
