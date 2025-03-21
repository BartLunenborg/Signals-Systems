/** @file   signals.h
 *  @brief  Functions for signal operations
 *  @author Bart Lunenborg, s3410579
 */

#ifndef __SIGNALS_H__
#define __SIGNALS_H__


/**
 * A discrete signal contain length integers.
 */
typedef struct Signal {
  int  length;  /**< The length of the Signal  */
  int* signal;  /**< The array with the Signal */
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
 * Given a signal, frees it.
 * @Param signal  The Signal to be freed
 */
void freeSignal(Signal signal);


/**
 * Given an array of Signals, frees it.
 * @Param signals  The Signals array to be freed
 * @Param length   The length of the array
 */
void freeSignals(Signal* signals, const int length);


/** 
 * Returns the convolution of Signal x and h.
 * @Param x  The input Signal
 * @Param h  The filter
 * @return   The resulting Signal after convolution (to be freed by caller )
 */
Signal convolve(const Signal x, const Signal h);


/**
 * Given Signal x and y, finds Signal h.
 * If h did not produce y from x, return h with length = -1.
 * Length = -1 indicate that the Signal y was not produced by x through a FIR filter.
 * @Param x  The input Signal
 * @Param y  The output Signal
 * @return   The Signal h that made y from x (to be freed by caller)
 */
Signal firFilterH(const Signal, const Signal);


/**
 * Given Signal x and h finds the steady state of y.
 * Obtained by correlating x with h.
 * @Param x  The input Signal
 * @Param h  The template Signal (h.length should be < x.length)
 * @return   The Signal obtained by correlating x with h (to be freed by caller)
 */
Signal correlate(const Signal, Signal h);

#endif
