/** @file   main.c
 *  @brief  Problem 7 of lab 1
 *  @author Bart Lunenborg, s3410579
 */

#include <stdio.h>
#include "sinusoid.h"


int main(int argc, char *argv[]) {
  Sinusoid s;
  int x_0, x_1, x_2;
  scanf("%lf %lf %lf %d %d %d", &s.a, &s.f, &s.phi, &x_0, &x_1, &x_2);
  printf("%.2lf\n", observedSignal(x_0, x_1, x_2, s).a);

  return 0;
}
