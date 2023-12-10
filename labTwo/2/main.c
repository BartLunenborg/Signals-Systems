/** @file   main.c
 *  @brief  Problem 1 of lab 2
 *  @author Bart Lunenborg, s3410579
 */

#include "signals.h"

int main(int argc, char *argv[]) {
  
  Signal h_1 = readSignal();
  Signal h_2 = readSignal();
  Signal h_3 = filter(h_1, h_2);

  Signal x = readSignal();
  Signal y = filter(x, h_3);
  printSignal(y) ;

  freeSignal(h_1);
  freeSignal(h_2);
  freeSignal(h_3);
  freeSignal(x);
  freeSignal(y);
  return 0;
}
