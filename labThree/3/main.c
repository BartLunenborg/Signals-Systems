/** @file   main.c
 *  @brief  Problem 3 of lab 3
 *  @author Bart Lunenborg, s3410579
 */

#include "signals.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  Signal *signals = malloc(3 * sizeof(Signal));
  signals[0] = readSignal();
  signals[1] = readSignal();

  signals[2] = pearsonCorrelate(signals[1], signals[0]);
  printPearson(signals[2]);

  freeSignals(signals, 3);
  return 0;
}
