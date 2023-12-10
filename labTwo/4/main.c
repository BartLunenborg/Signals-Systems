/** @file    main.c
 *  @brief   Problem 1 of lab 2
 *  @author  Bart Lunenborg, s3410579
 */

#include "signals.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  Signal *signals = malloc(3 * sizeof(Signal));
  signals[0] = readSignal();
  signals[1] = readSignal();

  signals[2] = firFilterH(signals[0], signals[1]);
  if (signals[2].length > 0) {
    printSignal(signals[2]);
  } else {
    printf("NO FIR\n");
  }

  freeSignals(signals, 3);
  return 0;
}
