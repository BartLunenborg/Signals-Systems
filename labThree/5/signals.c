/** @file   signals.c
 *  @brief  Implementations of functions in signals.h
 *  @author Bart Lunenborg, s3410579
 */

#include "signals.h"
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
uint PRIME = 40961;
uint OMEGA = 243;

Signal readSignal() {
  int len;
  uint temp, *arr;
  char c;
  scanf("%d:", &len);
  arr = calloc(len, sizeof(uint));
  do c = getchar(); while (c != '[');
  if (len > 0) {
    scanf("%u", &temp);
    arr[0] = temp;
    for (int i=1; i < len; i++) {
      scanf(",%u", &temp);
      arr[i] = temp;
    }
  }
  do c = getchar(); while (c != ']');
  Signal s = {len, arr};
  return s;
}

void printSignal(const Signal s) {
  printf("%d: [", s.length);
  if (s.length > 0) {
    printf("%u", s.signal[0]);
    for (int i=1; i < s.length; i++) {
      printf(",%u", s.signal[i]);
    }
  }
  printf("]\n");
}

void freeSignals(Signal *ss, const int length) {
  for (int i = 0; i < length; i++) {
    free(ss[i].signal);
  }
  free(ss);
}

// computes (base^exponent) mod prime
uint powmod(uint base, uint exponent, uint prime) {
  uint pm = 1;
  base = base % prime;
  while (exponent > 0) {
    if (exponent % 2 == 1) {
      pm = (pm * base) % prime;
    }
    exponent /= 2;
    base = (base * base) % prime;
  } 
  return pm;
}

void splitEvenOdd(const Signal a, Signal *signals) {
  int n = a.length;
  Signal aEven = {n/2, calloc(n/2, sizeof(uint))};
  Signal aOdd  = {n/2, calloc(n/2, sizeof(uint))};
  for (int i = 0; i < n; i += 2) {
    aEven.signal[i/2] = a.signal[i];
    aOdd.signal[i/2] = a.signal[i+1];
  }
  signals[0] = aEven;
  signals[1] = aOdd;
}

Signal ntt(const Signal a) {
  int n = a.length;
  if (n == 1) {
    Signal y = {n, calloc(n, sizeof(uint))};
    y.signal[0] = a.signal[0];
    return y;
  }
  Signal *signals = calloc(4, sizeof(Signal));
  splitEvenOdd(a, signals); 
  signals[2] = ntt(signals[0]);
  signals[3] = ntt(signals[1]);
  Signal y = {n, calloc(n, sizeof(uint))};
  for (int i = 0; i < n/2; i++) {
    y.signal[i] = signals[2].signal[i] + powmod(OMEGA, i, PRIME) % PRIME;
    y.signal[i+n/2] = signals[3].signal[i] - powmod(OMEGA, i, PRIME) % PRIME;
  }
  freeSignals(signals, 4);
  return y; 
}
