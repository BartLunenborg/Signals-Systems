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
  unsigned int  length;  /**< The length of the Signal  */
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
void freeSignals(Signal *signals, const unsigned int length);


/**
 * Given a signal performs the forward number theoretic transform (fntt).
 * Assuming the signal.length is a power of 2.
 * @param signal  The signal to perform the fntt on.
 * @return        The Signal that is the result of the fntt (to be freed by caller).
 */
Signal ntt(const Signal s);


/**
 * Given a signal performs the inverse number theoretic transform (intt).
 * Assuming the signal.length is a power of 2.
 * @param signal  The signal to perform the intt on.
 * @return        The Signal that is the result of the intt (to be freed by caller).
 */
Signal intt(const Signal s);

#endif
