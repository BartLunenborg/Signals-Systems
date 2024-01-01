/** @file   signals.h
 *  @brief  Functions for signal operations
 *  @author Bart Lunenborg, s3410579
 */

#ifndef __SIGNALS_H__
#define __SIGNALS_H__

/**
 * A discrete Signal contain length complex doubles.
 */
typedef struct Signal {
  int  length;              /**< The length of the Signal  */
  _Complex double *signal;  /**< The array with the Signal */
} Signal;


/**
 * Given the length of a discrete Signal, reads it from the input.
 * @return  The read Signal (to be freed by caller)
 */
Signal readSignal();


/**
 * Given a pointer to an array of integers and its length, prints it formatted [1,2,3..n].
 * @param signal  The Signal to print
 */
void printSignal(const Signal signal);


/**
 * Given an array of Signals, frees them.
 * @param signals  The Signals array to be freed
 * @param length   The length of the array
 */
void freeSignals(Signal *signals, const int length);


/** 
 * Returns the convolution of Signal x and h using the fft.
 * @param x  The input Signal
 * @param h  The filter
 * @return   The resulting Signal after convolution (to be freed by caller )
 */
Signal convolve(const Signal x, const Signal h);

#endif
