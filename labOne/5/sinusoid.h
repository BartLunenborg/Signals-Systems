// Bart Lunenborg, s3410579

#ifndef __SINUSOID_H__
#define __SINUSOID_H__

/**
 * Sinusoid of the form a * cos(2 * pi * f * t + phi)
 * @field f    The frequency
 * @field a    The amplitude
 * @field phi  The phase
 */
typedef struct Sinusoid {
  double f;
  double a;
  double phi;
} Sinusoid;

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
 * Convert a Vector to a Sinusoid
 * @param vector    The Vector to convert
 * @param sinusoid  The pointer to the new Sinusoid
 */
void convertToPolar(Vector vector, Sinusoid* sinusoid);

/*
 * Add two Sinusoids
 * @param s_0  The first Sinusoid to add
 * @param s_1  The second Sinusoid to add
 * @param s_2  Pointer to the new Sinusoid
 */
void sinusoidAdd(Sinusoid s_0, Sinusoid s_1, Sinusoid* s_2);

/*
 * Add an array of Sinusoids (non-empty)
 * @param sinusoids  The array of sinusoids 
 * @param size       The size of the array
 * @return           The sum of all Sinusoids
 */
Sinusoid sinusoidsAdd(Sinusoid* sinusoids, int size);

/*
 * Formatted print a Sinusoid in the form x(t)=a*cos(2*pi*f*t+phi)
 * @param sinusoid  The Sinusoid to print
 */
void sinusoidPrint(Sinusoid sinusoid);

/*
 * Given sampling rate f_s, num samples n; takes n samples from Sinusoid s.
 * @param f_s       The sampling rate
 * @param n         The number of samples
 * @param sinusoid  The Sinusoid to take samples from
 * @return          A pointer to a calloc'd array of samples values (to be freed by caller)
 */
int* sample(int f_s, int n, Sinusoid sinusoid);

/*
 * Print a non-empty array of ints formatted: [a, b, c, .. n]\n
 * @param array  The array to print
 * @param n      The size of the array
 */
void printArr(int* array, int n);

#endif
