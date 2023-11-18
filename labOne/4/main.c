// Bart Lunenborg, s3410579
// Given f, A_0, \varphi_0, A_1, and \varphi_1; prints the sum
// of A_0*\cos*(2*\pi*f+varphi_0) + A_1*cos(2*\pi*f*t+varphi_1)
// as x(t) = A*cos(2*\pi*f*t+\varphi)

#include <stdio.h>
#include "phasor.h"

int main(int argc, char *argv[]) {
  Phasor ph_0, ph_1, ph_2;
  scanf("%lf %lf %lf %lf %lf", &ph_2.f, &ph_0.a, &ph_0.phi, &ph_1.a, &ph_1.phi);
  phasorAdd(ph_0, ph_1, &ph_2);
  phasorPrint(ph_2);
  return 0;
}
