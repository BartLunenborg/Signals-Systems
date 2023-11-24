/** @file   sinusoid.c
 *  @brief  implementations of functions for sinusoid operations
 *  @author Bart Lunenborg, s3410579
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sinusoid.h"


/** 
 * pi up to 20 digits precision
 */
const double PI = 3.14159265358979323846;


/**
 * Margin of error for floating point operations
 */
const double ERROR = 1e-5;


/**
 * The speed of sound in m/s
 */
const int SOS = 343;

void convertToPolar(Vector vec, Sinusoid* s) {
  s->a = sqrt(vec.x * vec.x + vec.y * vec.y);
  s->phi = atan2(vec.y, vec.x);
  s->phi = vec.y == 0 && vec.x < 0 ? -s->phi : s->phi;
}


void sinusoidAdd(Sinusoid s_0, Sinusoid s_1, Sinusoid* s_2) {
  Vector vec_0 = {s_0.a * cos(s_0.phi), s_0.a * sin(s_0.phi)};
  Vector vec_1 = {s_1.a * cos(s_1.phi), s_1.a * sin(s_1.phi)};
  Vector vec_2 = {vec_0.x + vec_1.x, vec_0.y + vec_1.y};
  convertToPolar(vec_2, s_2);
}


void sinusoidPrint(Sinusoid s) {
  if (fabs(s.a) <= ERROR) {
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


int* sampleSinusoids(int f_s, int n, Sinusoid* ss, int m) {
  int* samples = malloc(n * sizeof(int));
  for (int i = 0; i < m; i++) {
    ss[i].f /= f_s;
  }
  for (int i = 0; i < n; i++) {
    double val = 0;
    for (int j = 0; j < m; j++) {
      val += ss[j].a * cos(2 * PI * ss[j].f * i + ss[j].phi);
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


int areAliases(Sinusoid a, Sinusoid b, int f_s) {
  return fabs(a.a * cos(2 * PI * a.f / f_s + a.phi) - b.a * cos(2 * PI * b.f /f_s + b.phi)) < ERROR;
}


Sinusoid observedSignal(int x_0, int x_1, int x_2, Sinusoid s) {
  Sinusoid v, w;
  v = s;
  int distance_0 = abs(x_2 - x_0);
  int distance_1 = abs(x_2 - x_1);
  s.phi += 2 * PI * s.f * distance_0 / SOS;
  v.phi += 2 * PI * v.f * distance_1 / SOS;

  sinusoidAdd(s, v, &w);
  return w; 
}
