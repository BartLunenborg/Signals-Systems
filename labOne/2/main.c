// Bart Lunenborg, s3410579
// Converts the input of 2 Polar coordinates (r, \theta)
// and prints them as 2 Cartesian coordinates (x, y)

#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
  double r, theta;
  scanf("%lf %lf", &r, &theta);
  printf("%.2f %.2f\n", r*cos(theta), r*sin(theta));
  return 0;
}
