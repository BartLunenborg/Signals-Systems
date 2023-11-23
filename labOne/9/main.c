/** @file   main.c
 *  @brief  Problem 8 of lab 1
 *  @author Bart Lunenborg, s3410579
 */

#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
  double f_0, f_1;
  scanf("%lf %lf", &f_0, &f_1);

  // we use the identity cos(a) + cos(b) = 2 * cos((a+b)/2) * cos((a-b)/2)
  printf("%.2lf %.2lf\n", fabs((f_0 - f_1) / 2), (f_0 + f_1) / 2);
  return 0;
}
