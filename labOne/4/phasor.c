// Bart Lunenborg, s3410579
// Functions for Phasor operations

#include <stdio.h>
#include <math.h>
#include "phasor.h"

// Convert a Vector to a Phasor
void convertToPolar(Vector vec, Phasor* ph) {
  ph->a = sqrt(vec.x*vec.x + vec.y * vec.y);
  ph->phi = atan2(vec.y, vec.x);
  ph->phi = vec.y == 0 && vec.x < 0 ? -ph->phi : ph->phi;
}

// Add two Phasors of the form x(t) = a*cos(2*\pi*f*t+phi) with equal f
void phasorAdd(Phasor ph_0, Phasor ph_1, Phasor* ph_2) {
  Vector vec_0 = {ph_0.a * cos(ph_0.phi), ph_0.a * sin(ph_0.phi)};
  Vector vec_1 = {ph_1.a * cos(ph_1.phi), ph_1.a * sin(ph_1.phi)};
  Vector vec_2 = {vec_0.x + vec_1.x, vec_0.y + vec_1.y};
  convertToPolar(vec_2, ph_2);
}

// Print a Phasor of the form x(t) = a*cos(2*\pi*f*t+phi)
void phasorPrint(Phasor ph) {
  if (fabs(ph.a) <= 1e-5) {
    printf("x(t)=0.00\n");    
  } else {
    printf("x(t)=%.2f*cos(2*pi*%.2f*t%+.2f)\n", ph.a, ph.f, ph.phi);
  }
}
