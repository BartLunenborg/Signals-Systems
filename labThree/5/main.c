/** @file   main.c
 *  @brief  Problem 5 of lab 3
 *  @author Bart Lunenborg, s3410579
 */

#include "signals.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  Signal *signals = malloc(3 * sizeof(Signal));
  signals[0] = readSignal();
  signals[1] = ntt(signals[0]);
  printSignal(signals[1]);

  //freeSignals(signals, 2);
  return 0;
}
