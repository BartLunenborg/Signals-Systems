/** @file   main.c
 *  @brief  Problem 6 of lab 1
 *  @author Bart Lunenborg, s3410579
 */

#include <stdio.h>
#include "sinusoid.h"

int main(int argc, char *argv[]) {
  int f_s;
  Sinusoid a, b;
  scanf("%d %lf %lf %lf %lf %lf %lf", &f_s, &a.a, &a.f, &a.phi, &b.a, &b.f, &b.phi);

  printf("%s\n", areAliases(a, b, f_s) ? "YES" : "NO");

  return 0;
}
