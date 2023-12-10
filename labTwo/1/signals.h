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
 * @param length  The length of the signal
 * @return        A pointer to the calloc'd array with the signal (to be freed by caller)
 */
Signal readSignal();


/**
 * Given a pointer to an array of integers and its length, prints it formatted [1,2,3..n].
 * @param length  The length of the signal
 * @param signal  The array of ints containing the signal
 */
void printSignal(Signal);


/**
 * Given a signal, frees it.
 * @Param signal  The signal to be freed
 */
void freeSignal(Signal);


/** 
 * Given a Fir filter and a signal, slides the filter across the signal (where there is overlap).
 * @Param x  The signal
 * @Param h  The filter
 * @return   The signal that is the result
 */
Signal filter(Signal x, Signal h);

#endif
