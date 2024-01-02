/** @file   signals.h
 *  @brief  Functions for signal operations
 *  @author Bart Lunenborg, s3410579
 */

#ifndef __SIGNALS_H__
#define __SIGNALS_H__

/**
 * A discrete Signal contain length unsigned ints.
 */
typedef struct Signal {
  int  length;           /**< The length of the Signal  */
  unsigned int *signal;  /**< The array with the Signal */
} Signal;


/**
 * Given the length of a discrete Signal, reads it from the input.
 * @return  The read Signal (to be freed by caller)
 */
Signal readSignal();


/**
 * Given a Signal, prints it's values formatted n:[1,2,3..n].
 * @param s  The Signal to print
 */
void printSignal(const Signal s);


/**
 * Given an array of Signals, frees them.
 * @param signals  The Signals array to be freed
 * @param length   The length of the array
 */
void freeSignals(Signal *signals, const int length);

Signal ntt(const Signal a);

#endif
