// Bart Lunenborg, s3410579

#ifndef __PHASOR_H__
#define __PHASOR_H__

/**
 * Phasor of the form a * cos(2 * pi * f * t + phi)
 * @field f    The frequency
 * @field a    The amplitude
 * @field phi  The phase
 */
typedef struct Phasor {
  double f;
  double a;
  double phi;
} Phasor;

/*
 * Vector of form $\vec{vec} = \begin{bmatrix}x\\y\end{bmatrix}$
 * @field x  The x coordinate
 * @field y  The y coordinate
 */
typedef struct Vector {
  double x;
  double y;
} Vector;

/*
 * Convert a Vector to a Phasor
 * @param vector  The Vector to convert
 * @param phasor  The pointer to the new Phasor
 */
void convertToPolar(Vector vector, Phasor* phasor);

/*
 * Add two Phasors of the form x(t) = a * cos(2 * pi * f * t + phi) with equal f
 * @param ph_0  The first Phasor to add
 * @param ph_1  The second Phasor to add
 * @param ph_2  Pointer to the new Phasor
 */
void phasorAdd(Phasor ph_0, Phasor ph_1, Phasor* ph_2);

/*
 * Formatted print a Phasor of the form x(t) = a * cos(2 * pi * f * t + phi)
 * @param phasor  The Phasor to print
 */
void phasorPrint(Phasor phasor);

/*
 * Given sampling rate f_s, num samples n; takes n samples from Phasor ph.
 * @param f_s     The sampling rate
 * @param n       The number of samples
 * @param phasor  The Phasor to take samples from
 * @return        A pointer to a calloc'd array of samples values (to be freed by caller)
 */
int* sample(int f_s, int n, Phasor phasor);

/*
 * Print an array of ints formatted: [a, b, c, .. n]\n
 * @param array  The array to print
 * @param n      The size of the array
 */
void printArr(int* array, int n);

#endif
