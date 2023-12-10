/** @file   main.c
 *  @brief  Problem 1 of lab 2
 *  @author Bart Lunenborg, s3410579
 */

#include "signals.h"

int main(int argc, char *argv[]) {
  
  Signal h = readSignal();
  Signal x = readSignal();
  Signal y = filter(x, h);
  printSignal(y);

  freeSignal(h);
  freeSignal(x);
  freeSignal(y);
  return 0;
}
