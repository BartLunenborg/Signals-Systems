// Bart Lunenborg, s3410579
// Functions for Phasor operations

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "phasor.h"

double PI = 3.14159265358979;

void convertToPolar(Vector vec, Phasor* ph) {
  ph->a = sqrt(vec.x*vec.x + vec.y * vec.y);
  ph->phi = atan2(vec.y, vec.x);
  ph->phi = vec.y == 0 && vec.x < 0 ? -ph->phi : ph->phi;
}

void phasorAdd(Phasor ph_0, Phasor ph_1, Phasor* ph_2) {
  Vector vec_0 = {ph_0.a * cos(ph_0.phi), ph_0.a * sin(ph_0.phi)};
  Vector vec_1 = {ph_1.a * cos(ph_1.phi), ph_1.a * sin(ph_1.phi)};
  Vector vec_2 = {vec_0.x + vec_1.x, vec_0.y + vec_1.y};
  convertToPolar(vec_2, ph_2);
}

void phasorPrint(Phasor ph) {
  if (fabs(ph.a) <= 1e-5) {
    printf("x(t)=0.00\n");    
  } else {
    printf("x(t)=%.2f*cos(2*pi*%.2f*t%+.2f)\n", ph.a, ph.f, ph.phi);
  }
}

int* sample(int f_s, int n, Phasor ph) {
  int* samples = malloc(n * sizeof(int));
  ph.f = ph.f / f_s;
  for (int i = 0; i < n; i++) {
    samples[i] = ph.a * cos(2 * PI * ph.f * i + ph.phi);
  }
  return samples;
}

void printArr(int* arr, int size) {
  printf("[%d", arr[0]);
  for (int i = 1; i < size; i++) {
    printf(",%d", arr[i]);
  }
  printf("]\n");
}
