#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

uint powmod(uint base, uint exponent, uint prime) {
  /* This function computes: base raised to the power exponent modulus prime
   * in maths notation: (base^exponent) mod prime
   */
  uint pm = 1;
  base = base%prime;
  while (exponent > 0) {
    if (exponent%2 == 1) { /* exponent is odd */
      pm = (pm*base)%prime;
    }
    exponent /= 2;
    base = (base*base)%prime;
  } 
  return pm;
}

int main(int argc, char *argv[]) {
  uint N=8192, prime=40961, omega=243;
  while (N != 1) {
    printf("N=%4u: (%u^%u) mod %d=%u\n", N, omega, N, prime, powmod(omega, N, prime));
    N /= 2;
    omega = (omega*omega)%prime;
  };
  
  return EXIT_SUCCESS;
}
