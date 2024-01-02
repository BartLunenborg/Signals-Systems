/** @file   signals.c
 *  @brief  Implementations of functions in signals.h
 *  @author Bart Lunenborg, s3410579
 */

#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <string.h>

typedef _Complex double cplx;
double PI = 3.14159265358979323846;

Signal readSignal() {
  int len, temp;
  cplx *arr;
  char c;
  scanf("%d:", &len);
  arr = calloc(len, sizeof(cplx));
  do c = getchar(); while (c != '[');
  if (len > 0) {
    scanf("%d", &temp);
    arr[0] = temp;
    for (int i=1; i < len; i++) {
      scanf(",%d", &temp);
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
    printf("%d", (int)round(creal(s.signal[0])));
    for (int i=1; i < s.length; i++) {
      printf(",%d", (int)round(creal(s.signal[i])));
    }
  }
  printf("]\n");
}

void printPearson(const Signal s) {
  printf("%d: [", s.length);
  if (s.length > 0) {
    printf("%.5lf", creal(s.signal[0]));
    for (int i=1; i < s.length; i++) {
      printf(",%.5lf", creal(s.signal[i]));
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

// finds the smallest number > n that is a power of two
int powerOfTwo(int n) {
  if (n & (n - 1)) {
    int p2 = 1;
    while (p2 < n) {
      p2 <<= 1;
    }
    return p2;
  }
  return n;
}

// splits the even and odd indices into two different arrays
void splitEvenOdd(const Signal a, Signal *signals) {
  int n = a.length;
  Signal aEven = {n/2, calloc(n/2, sizeof(cplx))};
  Signal aOdd  = {n/2, calloc(n/2, sizeof(cplx))};
  for (int i = 0; i < n; i += 2) {
    aEven.signal[i/2] = a.signal[i];
    aOdd.signal[i/2] = a.signal[i+1];
  }
  signals[0] = aEven;
  signals[1] = aOdd;
}

// Cooley and Tukey fft algorithm
Signal fft(const Signal a, const cplx omega) {
  int n = a.length;
  if (n == 1) {
    Signal y = {n, calloc(n, sizeof(cplx))};
    y.signal[0] = a.signal[0];
    return y;
  }
  cplx x = 1;
  Signal *signals = calloc(4, sizeof(Signal));
  splitEvenOdd(a, signals);  // signals[0] = a_even, signals[1] = a_odd
  signals[2] = fft(signals[0], omega * omega);  // y_even
  signals[3] = fft(signals[1], omega * omega);  // y_odd
  Signal y = {n, calloc(n, sizeof(cplx))};
  for (int i = 0; i < n/2; i++) {
    y.signal[i]     = signals[2].signal[i] + x * signals[3].signal[i];
    y.signal[i+n/2] = signals[2].signal[i] - x * signals[3].signal[i];
    x *= omega;
  }
  freeSignals(signals, 4);
  return y; 
}

Signal *padZeros(const Signal a, const Signal b, int n) {
  Signal *signals = calloc(2, sizeof(Signal));
  Signal xMod = {n, calloc(n, sizeof(cplx))};
  Signal hMod = {n, calloc(n, sizeof(cplx))};
  memcpy(xMod.signal, a.signal, a.length * sizeof(cplx));
  memcpy(hMod.signal, b.signal, b.length * sizeof(cplx));
  signals[0] = xMod;
  signals[1] = hMod;
  return signals;
}

Signal *ffts(Signal *signals, cplx omega) {
  Signal *ffts = calloc(2, sizeof(Signal));
  ffts[0] = fft(signals[0], omega);
  ffts[1] = fft(signals[1], omega);
  freeSignals(signals, 2);
  return ffts;
}

Signal convolve(const Signal x, const Signal h) {
  int length = x.length + h.length - 1;
  int n = powerOfTwo(length);

  // fft of each (after padding x and h with zeros)
  cplx omega = cexp(2 * I * PI / n);
  Signal *fftxh = ffts(padZeros(x, h, n), omega);

  // component multiply
  for (int i = 0; i < n; i++) {
    fftxh[0].signal[i] *= fftxh[1].signal[i];
  }

  // inverse fft
  omega = conj(omega);
  Signal y = fft(fftxh[0], omega);
  freeSignals(fftxh, 2);
  // adjust y
  y.length = length;
  for (int i = 0; i < length; i++) {
    y.signal[i] /= n;
  }
  return y;
}

Signal reverse(const Signal s) {
  Signal reverse = {s.length, calloc(s.length, sizeof(Signal))};
  for (int i = 0; i < s.length; i++) {
    reverse.signal[i] = s.signal[s.length - 1 - i];
  }
  return reverse;
}

Signal correlate(const Signal x, const Signal h) {
  Signal *signals = calloc(2, sizeof(Signal));
  signals[0] = reverse(h);
  signals[1] = convolve(x, signals[0]);
  int length = x.length - h.length + 1;
  Signal y = {length, calloc(length, sizeof(cplx))};
  memcpy(y.signal, signals[1].signal + h.length - 1, length * sizeof(cplx));
  freeSignals(signals, 2);
  return y;
}

// values that we need to do the adjusting efficiently
void helperValues(double *hMean, double *hS, double *xMean, double *xS, const Signal x, const Signal h) {
  int n = h.length;
  double hSumVals=0, xSumVals=0, hSumSquares=0, xSumSquares=0;
  for (int i = 0; i < n; i++) {
    hSumVals += h.signal[i];
    xSumVals += x.signal[i];
    hSumSquares += h.signal[i] * h.signal[i];
    xSumSquares += x.signal[i] * x.signal[i];
  }
  *hMean = hSumVals / n;
  *hS = sqrt((hSumSquares - hSumVals * hSumVals / n) / (n - 1));
  xMean[0] = xSumVals / n;
  xS[0] = sqrt((xSumSquares - xSumVals * xSumVals / n) / (n - 1));
  for (int i = 1; i < x.length - n + 1; i++) {
    double out = x.signal[i - 1];
    double in = x.signal[i + n - 1];
    xSumVals = xSumVals - out + in;
    xSumSquares = xSumSquares - out * out + in * in;
    xS[i] = sqrt((xSumSquares - xSumVals * xSumVals / n) / (n - 1));
    xMean[i] = xSumVals / n;
  }
}

Signal pearsonCorrelate(const Signal x, const Signal h) {
    Signal p = correlate(x, h);
    // now we do some adjusting
    double hMean, hS;
    double *xMean = calloc(x.length, sizeof(double));
    double *xS = calloc(x.length, sizeof(double));
    helperValues(&hMean, &hS, xMean, xS, x, h);
    for (int i = 0; i < p.length; i++) {
        p.signal[i] = (p.signal[i] - h.length * xMean[i] * hMean) / ((h.length - 1) * xS[i] * hS);
    }
    free(xMean);
    free(xS);
    return p;
}
