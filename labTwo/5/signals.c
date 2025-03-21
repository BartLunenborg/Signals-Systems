#include <stdio.h>
#include <stdlib.h>
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
  Signal y = {x.length + h.length - 1, calloc(x.length + h.length - 1, sizeof(int))};
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
