/** @file   sinusoid.h
 *  @brief  Structs and functions for sinusoid operations
 *  @author Bart Lunenborg, s3410579
 */

#ifndef __SINUSOID_H__
#define __SINUSOID_H__


/**
 * Sinusoid of the form a * cos(2 * pi * f * t + phi)
 */
typedef struct Sinusoid {
  double f;    /**< The frequency */ 
  double a;    /**< The amplitude */
  double phi;  /**< The phase */
} Sinusoid;


/**
 * A 2d Vector in Cartesian space
 */
typedef struct Vector {
  double x;  /**< The x coordinate */
  double y;  /**< The y coordinate */
} Vector;


/**
 * Convert a Vector to a Sinusoid
 * @param vector    The Vector to convert
 * @param sinusoid  The pointer to the new Sinusoid
 */
void convertToPolar(Vector vector, Sinusoid* sinusoid);


/**
 * Add two Sinusoids with equal frequency
 * @param s_0  The first Sinusoid to add
 * @param s_1  The second Sinusoid to add
 * @param s_2  Pointer to the new Sinusoid
 */
void sinusoidAdd(Sinusoid s_0, Sinusoid s_1, Sinusoid* s_2);


/**
 * Formatted print a Sinusoid in the form x(t)=a*cos(2*pi*f*t+phi)
 * @param sinusoid  The Sinusoid to print
 */
void sinusoidPrint(Sinusoid sinusoid);


/**
 * Given sampling rate f_s, num samples n; takes n samples from a Sinusoid.
 * @param f_s       The sampling rate (in hertz)
 * @param n         The number of samples to take
 * @param sinusoid  The Sinusoid to take samples from
 * @return          A pointer to a calloc'd array of samples values (to be freed by caller)
 */
int* sampleSinusoid(int f_s, int n, Sinusoid sinusoid);


/**
 * Given sampling rate f_s, num samples n; takes n samples from m Sinusoids.
 * @param f_s        The sampling rate (in hertz)
 * @param n          The number of samples to take
 * @param sinusoids  The array of Sinusoids to take samples from
 * @param m          The number of Sinusoids in the sinusoids array
 * @return           A pointer to a calloc'd array of samples values (to be freed by caller)
 */
int* sampleSinusoids(int f_s, int n, Sinusoid* sinusoids, int m);


/**
 * Print a non-empty array of ints formatted: [a, b, c, .. n]\n
 * @param array  The array to print
 * @param n      The size of the array
 */
void printArr(int* array, int n);


/**
 * Determines whether 2 sinusoids are aliases
 * @param a    The first Sinusoid
 * @param b    The second Sinusoid
 * @param f_s  The sampling rate
 * @return     1 if aliases, else 0
 */
int areAliases(Sinusoid a, Sinusoid b, int f_s);


/**
 * Finds the Sinusoid that is observed at x_2
 * @param x_0  The x of the first source
 * @param x_1  The x of the second source
 * @param x_2  The x of the observer
 * @param s    The signal produced at x_0 and x_1
 * @return     The Sinusoid observed at x_2
 */
Sinusoid observedSignal(int x_0, int x_1, int x_2, Sinusoid s);

#endif
