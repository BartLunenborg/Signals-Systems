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

void printSignal(Signal s) {
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

Signal filter(Signal x, Signal h) {
  Signal y = {x.length + h.length - 1, calloc(x.length + h.length - 1, sizeof(int))};
  for (int i = 0; i < x.length; i++) {
    for (int j = 0; j < h.length; j++) {
      y.signal[i+j] += x.signal[i] * h.signal[j];
    }
  }
  return y;
}
