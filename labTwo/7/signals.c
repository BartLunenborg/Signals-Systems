/** @file   signals.c
 *  @brief  Implementations of functions in signals.h
 *  @author Bart Lunenborg, s3410579
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "signals.h"

Signal readSignal() {
  int len, *arr;
  char c;
  scanf("%d:", &len);
  arr = calloc(len, sizeof(int));
  do c = getchar(); while (c != '[');
  if (len > 0) {
    scanf("%d", &arr[0]);
    for (int i=1; i < len; i++) scanf(",%d", &arr[i]);
  }
  do c = getchar(); while (c != ']');
  Signal s = {len, arr};
  return s;
}

void printSignal(const Signal s) {
  printf("%d: [", s.length);
  if (s.length > 0) {
    printf("%d", s.signal[0]);
    for (int i=1; i < s.length; i++) printf(",%d", s.signal[i]);
  }
  printf("]\n");
}

void printPearson(const Pearson p) {
  printf("%d: [", p.length);
  if (p.length > 0) {
    printf("%.5lf", p.corrs[0]);
    for (int i=1; i < p.length; i++) printf(",%.5lf", p.corrs[i] < 0 && p.corrs[i] > -0.00001 ? 0.00000 : p.corrs[i]);
  }
  printf("]\n");
}

void freeSignal(Signal s) {
  free(s.signal);
}

void freeSignals(Signal *ss, const int length) {
  for (int i = 0; i < length; i++) {
    freeSignal(ss[i]);
  }
  free(ss);
}

Signal convolve(const Signal x, const Signal h) {
  int length = x.length + h.length - 1;
  Signal y = {length, calloc(length, sizeof(int))};
  for (int i = 0; i < x.length; i++) {
    for (int j = 0; j < h.length; j++) {
      y.signal[i+j] += x.signal[i] * h.signal[j];
    }
  }
  return y;
}

Signal firFilterH(const Signal x, const Signal y) {
  int length = y.length - x.length + 1;
  int *arr = calloc(length, sizeof(int));
  int *sums = calloc(y.length, sizeof(int));
  for (int i = 0; i < length; i++) {
    arr[i] = (y.signal[i] - sums[i]) / x.signal[0];
    for (int j = 0; j < x.length; j++) {
      sums[i+j] += arr[i] * x.signal[j];
    }
  }
  Signal h = {length, arr};

  for (int i = length; i < y.length; i++) {
    if (sums[i] != y.signal[i]) {
      free(sums);
      h.length = -1;
      return h;
    }
  }

  free(sums);
  return h;
}

Signal correlate(const Signal x, const Signal h) {
  int length = x.length - h.length + 1;
  int *arr = calloc(length, sizeof(int));
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < h.length; j++) {
      arr[i] += h.signal[j] * x.signal[j + i];
    }
  }
  Signal y = {length, arr};
  return y;
}

Pearson pearsonCorrelate(const Signal x, const Signal h) {
  double mean_h = 0;
  for (int i = 0; i < h.length; i++) mean_h += h.signal[i];
  mean_h /= h.length;
  
  int length = x.length - h.length + 1;
  double *arr = malloc(length * sizeof(double));
  for (int i = 0; i < length; i++) {
    double mean_x = 0;
    for (int j = 0; j < h.length; j++) mean_x += x.signal[j + i];
    mean_x /= h.length;
    double cov = 0;
    double sd_x = 0;
    double sd_h = 0;
    for (int j = 0; j < h.length; j++) {
      cov  += (h.signal[j] - mean_h) * (x.signal[j+i] - mean_x);
      sd_x += (x.signal[j+i] - mean_x) * (x.signal[j+i] - mean_x);
      sd_h += (h.signal[j] - mean_h) * (h.signal[j] - mean_h);
    }
    arr[i] = cov / (sqrt(sd_x) * sqrt(sd_h));
  }

  Pearson p = {length, arr};
  return p;
}
