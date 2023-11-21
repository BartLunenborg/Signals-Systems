// Bart Lunenborg, s3410579
// Functions for Sinusoid operations

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sinusoid.h"

double PI = 3.14159265358979;

void convertToPolar(Vector vec, Sinusoid* s) {
  s->a = sqrt(vec.x * vec.x + vec.y * vec.y);
  s->phi = atan2(vec.y, vec.x);
  s->phi = vec.y == 0 && vec.x < 0 ? -s->phi : s->phi;
}

void sinusoidAdd(Sinusoid s_0, Sinusoid s_1, Sinusoid* s_2) {
  if (s_0.f == s_1.f) {
    Vector vec_0 = {s_0.a * cos(s_0.phi), s_0.a * sin(s_0.phi)};
    Vector vec_1 = {s_1.a * cos(s_1.phi), s_1.a * sin(s_1.phi)};
    Vector vec_2 = {vec_0.x + vec_1.x, vec_0.y + vec_1.y};
    convertToPolar(vec_2, s_2);
    s_2->f = s_0.f;
  } 
}

void sinusoidPrint(Sinusoid s) {
  if (fabs(s.a) <= 1e-5) {
    printf("x(t)=0.00\n");    
  } else {
    printf("x(t)=%.2f*cos(2*pi*%.2f*t%+.2f)\n", s.a, s.f, s.phi);
  }
}

int* sampleSinusoid(int f_s, int n, Sinusoid s) {
  int* samples = malloc(n * sizeof(int));
  s.f /= f_s;
  for (int i = 0; i < n; i++) {
    samples[i] = s.a * cos(2 * PI * s.f * i + s.phi);
  }
  return samples;
}

int* sampleSinusoids(int f_s, int n, Sinusoid* sss, int m) {
  int* samples = malloc(n * sizeof(int));
  for (int i = 0; i < m; i++) {
    sss[i].f /= f_s;
  }
  for (int i = 0; i < n; i++) {
    double val = 0;
    for (int j = 0; j < m; j++) {
      val += sss[j].a * cos(2 * PI * sss[j].f * i + sss[j].phi);
    }
    samples[i] = (int)val;
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
