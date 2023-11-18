// Bart Lunenborg, s3410579

#ifndef __PHASOR_H__
#define __PHASOR_H__

// Phasor of form a*cos(2*\pi*f*t+\phi)
typedef struct Phasor {
  double f;
  double a;
  double phi;
} Phasor;

// Vector of form $\vec{vec} = \begin{bmatrix}x\\y\end{bmatrix}$
typedef struct Vector {
  double x;
  double y;
} Vector;

// Convert a Vector to a Phasor
void convertToPolar(Vector, Phasor *);
// Add two Phasors
void phasorAdd(Phasor, Phasor, Phasor *);
// Print a Phasor
void phasorPrint(Phasor);

#endif
