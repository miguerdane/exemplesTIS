/*
 * CoreLoad.h
 *
 *  Created on: Oct 3, 2013
 *      Author: t0106851
 */

#ifndef CORELOAD_H_
#define CORELOAD_H_

#include <stdint.h>
//#include <time.h>

#define MAXSZ		128		/** Maximum message size. */
#define MAXLINELEN	64		/** Maximum amount of data we're going to write. */

#ifndef NSECS_PER_SEC
#define NSECS_PER_SEC 	1000000000L /** Number of nano seconds per second */
#endif
#define NSECS_TO_CALIBRATE 100000000L /** Duration in nsecs to calibrate */
#define BUSY_ITERATIONS	1000 /** Number of for loop computation iterations */

extern int64_t nSecTo(struct timespec start,struct timespec stop);

/**
 \brief Interface to initialize core load computing
 This function calibrates the measurement loop during \ref PERIOD_NSEC
 A loop is \ref BUSY_ITERATIONS iterations of dummy computing
 \param[in] verbose global variable to set for printing
 \param[out] maxStepBySecond global variable with max of loops computed
 */
extern void CoreLoad_init(unsigned int isV);

/**
 \brief Interface to main core load computing infinite loop
 This function measures and calculates the core busy percentage
 Percentage is adjusted every \ref NSECS_PER_SEC with respect to the maximum
 calibrated with \ref CoreLoad_init
 \param[in] stop provides a mean to exit from infinite loop
 \param[in] verbose global variable to set for printing
 \param[in] maxStepBySecond global variable with max of loops computed
 \param[out] cpuLoad global variable with core busy percent
 */
extern void CoreLoad_main();

/**
 \brief Interface to read back computing core load
 \param[out] cpuLoad global variable with core busy percent
 */
extern int CoreLoad_get(void);

#endif /* CORELOAD_H_ */
