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
  int  length;  /**< The length of the signal  */
  int* signal;  /**< The array with the signal */
} Signal;


/**
 * Given the length of a discrete signal, reads it from the input.
 * @return  The read Signal (to be freed by caller)
 */
Signal readSignal();


/**
 * Given a pointer to an array of integers and its length, prints it formatted [1,2,3..n].
 * @param signal  The signal to print
 */
void printSignal(Signal signal);


/**
 * Given a signal, frees it.
 * @Param signal  The signal to be freed
 */
void freeSignal(Signal signal);


/**
 * Given an array of signals, frees it.
 * @Param signals  The signals array to be freed
 * @Param length   The length of the array
 */
void freeSignals(Signal* signals, int length);


/** 
 * Given a Fir filter and a signal, slides the filter across the signal (where there is overlap).
 * @Param x  The signal
 * @Param h  The filter
 * @return   The signal that is the result
 */
Signal filter(Signal x, Signal h);

#endif
