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
  int *signal;  /**< The array with the Signal */
} Signal;


/**
 * Pearson correlation values of a Signal.
 */
typedef struct Pearson {
  int    length;  /**< The length of the array */ 
  double *corrs;  /**< The correlation values  */
} Pearson;


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
 * Given an array of Pearson correlations, prints is (5 digits precision).
 * @param p  The Pearson array
 */
void printPearson(const Pearson p);


/**
 * Given a signal, frees it.
 * @param signal  The Signal to be freed
 */
void freeSignal(Signal signal);


/**
 * Given an array of Signals, frees it.
 * @param signals  The Signals array to be freed
 * @param length   The length of the array
 */
void freeSignals(Signal *signals, const int length);


/** 
 * Returns the convolution of Signal x and h.
 * @param x  The input Signal
 * @param h  The filter
 * @return   The resulting Signal after convolution (to be freed by caller )
 */
Signal convolve(const Signal x, const Signal h);


/**
 * Given Signal x and y, finds Signal h.
 * If h did not produce y from x, return h with length = -1.
 * Length = -1 indicate that the Signal y was not produced by x through a FIR filter.
 * @param x  The input Signal
 * @param y  The output Signal
 * @return   The Signal h that made y from x (to be freed by caller)
 */
Signal firFilterH(const Signal x, const Signal y);


/**
 * Given Signal x and h finds the steady state of y.
 * Obtained by correlating x with h.
 * @param x  The input Signal
 * @param h  The template Signal (h.length should be < x.length)
 * @return   The Signal obtained by correlating x with h (to be freed by caller)
 */
Signal correlate(const Signal x, Signal h);


/** 
 * Given Signal x and h, returns the Pearson correlation values
 * @param x  The input Signal
 * @param h  The template Signal (h.length should be < x.length)
 * @return   The Pearson correlation values (to be freed by caller)
 */
Pearson pearsonCorrelate(const Signal x, const Signal h);

#endif
