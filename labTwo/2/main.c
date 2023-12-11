/** @file   main.c
 *  @brief  Problem 2 of lab 2
 *  @author Bart Lunenborg, s3410579
 */

#include "signals.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  Signal *signals = malloc(5 * sizeof(Signal));
  for (int i = 0; i < 3; i++) {
    signals[i] = readSignal();
  }
  signals[3] = convolve(signals[0], signals[1]);
  signals[4] = convolve(signals[2], signals[3]);
  printSignal(signals[4]) ;

  freeSignals(signals, 5);
  return 0;
}
