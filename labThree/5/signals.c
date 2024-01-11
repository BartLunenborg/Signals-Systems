/** @file   signals.c
 *  @brief  Implementations of functions in signals.h
 *  @author Bart Lunenborg, s3410579
 */

#include "signals.h"
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
uint PRIME = 40961;
uint N = 8192;
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

Signal *_splitEvenOdd(const Signal s) {
  Signal *signals = malloc(4 * sizeof(Signal));
  int n = s.length;
  Signal aEven = {n/2, calloc(n/2, sizeof(uint))};
  Signal aOdd  = {n/2, calloc(n/2, sizeof(uint))};
  for (int i = 0; i < n; i += 2) {
    aEven.signal[i/2] = s.signal[i];
    aOdd.signal[i/2] = s.signal[i+1];
  }
  signals[0] = aEven;
  signals[1] = aOdd;
  return signals;
}

Signal _ntt(const Signal s, const uint omega) {
  uint n = s.length;
  if (n == 1) {
    Signal y = {n, calloc(n, sizeof(uint))};
    y.signal[0] = s.signal[0];
    return y;
  }
  uint x = 1;
  Signal *ss = _splitEvenOdd(s);  // ss[0] = a_even, ss[1] = a_odd
  ss[2] = _ntt(ss[0], (omega * omega) % PRIME);   // ss[2] = y_even
  ss[3] = _ntt(ss[1], (omega * omega) % PRIME);   // ss[3] = y_odd
  Signal y = {n, calloc(n, sizeof(uint))};
  for (int i = 0; i < n/2; i++) {
    y.signal[i]     = (ss[2].signal[i] + x * ss[3].signal[i]) % PRIME;
    y.signal[i+n/2] = (ss[2].signal[i] + PRIME - x * ss[3].signal[i] % PRIME) % PRIME;
    x = (x * omega) % PRIME;
  }
  freeSignals(ss, 4);
  return y; 
}

uint _findOmega(const int length) {
  uint n = N;
  uint omega = OMEGA;
  while (n != length) {
    n /= 2;
    omega = (omega * omega) % PRIME;
  }
  return omega;
}

Signal ntt(const Signal s) {
  return _ntt(s, _findOmega(s.length));
}
