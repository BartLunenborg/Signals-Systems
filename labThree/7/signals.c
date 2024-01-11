/** @file   signals.c
 *  @brief  Implementations of functions in signals.h
 *  @author Bart Lunenborg, s3410579
 */

#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;
uint PRIME = 40961;
uint LEN   = 8192;
uint OMEGA = 243;

Signal readSignal() {
  uint len, temp, *arr;
  char c;
  scanf("%u:", &len);
  arr = calloc(len, sizeof(uint));
  do c = getchar(); while (c != '[');
  if (len > 0) {
    scanf("%u", &temp);
    arr[0] = temp;
    for (uint i=1; i < len; i++) {
      scanf(",%u", &temp);
      arr[i] = temp;
    }
  }
  do c = getchar(); while (c != ']');
  Signal s = {len, arr};
  return s;
}

void printSignal(const Signal s) {
  printf("%u: [", s.length);
  if (s.length > 0) {
    printf("%u", s.signal[0]);
    for (int i=1; i < s.length; i++) {
      printf(",%u", s.signal[i]);
    }
  }
  printf("]\n");
}

void freeSignals(Signal *ss, const uint length) {
  for (uint i = 0; i < length; i++) {
    free(ss[i].signal);
  }
  free(ss);
}

// helper for _ntt, split a Signal into two Signals, based on even and odd indices
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

// ntt algorithm, based on the Cooley and Tukey fft
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

// finds the omega needed to use for the ntt based on the input length
uint _omega(const int length) {
  uint len = LEN;
  uint omega = OMEGA;
  while (len != length) {
    len /= 2;
    omega = (omega * omega) % PRIME;
  }
  return omega;
}

// slow but simple modular inverse of n mod PRIME
uint _modInverse(const uint n) {
  uint inverse = n;
  while (inverse * n % PRIME != 1) {
    inverse++;
  }
  return inverse;
}

Signal fntt(const Signal s) {
  return _ntt(s, _omega(s.length));
}

Signal intt(const Signal s) {
  Signal y = _ntt(s, _modInverse(_omega(s.length)));
  uint x = _modInverse(s.length);
  for (int i = 0; i < s.length; i++) {
    y.signal[i] = y.signal[i] * x % PRIME;
  }
  return y;
}

// finds the smallest number > n that is a power of two
uint _powerOfTwo(const uint n) {
  if (n & (n - 1)) {
    uint p2 = 1;
    while (p2 < n) {
      p2 <<= 1;
    }
    return p2;
  }
  return n;
}

// pads two Signals with 0 to length n
Signal *_padZeros(const Signal a, const Signal b, uint n) {
  Signal *signals = calloc(2, sizeof(Signal));
  Signal xPadded = {n, calloc(n, sizeof(uint))};
  Signal hPadded = {n, calloc(n, sizeof(uint))};
  memcpy(xPadded.signal, a.signal, a.length * sizeof(uint));
  memcpy(hPadded.signal, b.signal, b.length * sizeof(uint));
  signals[0] = xPadded;
  signals[1] = hPadded;
  return signals;
}

// computes the fntt of an array of 2 Signals (frees input)
Signal *_fntts(Signal *signals) {
  Signal *fntts = calloc(2, sizeof(Signal));
  uint omega = _omega(signals[0].length);
  fntts[0] = _ntt(signals[0], omega);
  fntts[1] = _ntt(signals[1], omega);
  freeSignals(signals, 2);
  return fntts;
}

Signal convolve(const Signal v, const Signal w) {
  uint len = v.length + w.length - 1;
  uint n = _powerOfTwo(len);

  // fntt of each
  Signal *fnttvw = _fntts(_padZeros(v, w, n)); 
  
  // component multiply
  for (int i = 0; i < n; i++) {
    fnttvw[0].signal[i] *= fnttvw[1].signal[i];
  }

  // intt
  Signal y = intt(fnttvw[0]);
  freeSignals(fnttvw, 2);

  // adjust y
  y.length = len;
  y.signal = realloc(y.signal, y.length * sizeof(uint));
  return y;
}
