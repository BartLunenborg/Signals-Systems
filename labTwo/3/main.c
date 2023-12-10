/** @file   main.c
 *  @brief  Problem 1 of lab 2
 *  @author Bart Lunenborg, s3410579
 */

#include "signals.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int size;
  scanf("%d", &size);

  Signal* signals = malloc(++size * sizeof(Signal));
  for (int i = 0; i < size; i++) {
    signals[i] = readSignal();
  }

  Signal old = filter(signals[0], signals[1]);
  Signal new;
  for (int i = 2; i < size; i++) {
    new = filter(old, signals[i]);
    freeSignal(old);
    old = new;
  }
  printSignal(new);

  freeSignal(new);
  freeSignals(signals, size);
  return 0;
}
