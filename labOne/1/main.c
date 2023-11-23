// Bart Lunenborg, s3410579
// Converts the input of 2 Cartesian coordinates (x, y)
// and returns them as 2 Polar coordinates (r, \theta)

#include <stdio.h>
#include <math.h>

void convertToPolar(int x, int y, double* r, double* theta) {
  *r = sqrt(x*x + y*y);
  *theta = atan2(y == 0 ? -0.0 : y, x);
}

int main(int argc, char *argv[]) {
  double x, y, r, theta;
  scanf("%lf %lf", &x, &y);

  convertToPolar(x, y, &r, &theta);
  printf("%.2f %.2f\n", r, theta);

  return 0;
}
