/* -------------------------- FILE PROLOGUE -------------------------------- */

/**
 *****************************************************************************
 * @copyright
 * 	(C) Copyright 2012
 * 	SYSGO AG.
 * 	Ulm, Germany
 * 	All rights reserved.
 *****************************************************************************
 */

/* ------------------------- FILE INCLUSION -------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "stub.h"
#include "coreload.h"


#define PERIOD_NSEC     100000000L // 100ms
#define PERIODS_PER_SEC  10

static int cpuLoad=0;
double maxStepBySecond=0;
static unsigned int verbose=0;

int64_t nSecTo(struct timespec start,struct timespec stop)
{
    int64_t diff = 0;
    diff = (stop.tv_nsec - start.tv_nsec);
    diff += (int64_t)NSECS_PER_SEC*((int64_t)(stop.tv_sec - start.tv_sec));
    return diff;
}

/**
 \brief Interface to initialize core load computing
 This function calibrates the measurement loop during \ref PERIOD_NSEC
 A loop is \ref BUSY_ITERATIONS iterations of dummy computing
 \param[in] verbose global variable to set for printing
 \param[out] maxStepBySecond global variable with max of loops computed
 */

void CoreLoad_init(unsigned int isV)
{

	struct timespec now,curr;
	int i;
	double step, duree;
	volatile double j;

	verbose = isV;

	if (verbose) {
		printf("Clock resolution: ");
		struct timespec res;
		clock_getres(CLOCK_REALTIME, &res);
		printf("%ld nsec\n", res.tv_nsec);
	}

	step = 0;
	duree = 0;

	clock_gettime(CLOCK_REALTIME, &now);
	do {
		for(i=0;i<BUSY_ITERATIONS;i++){
			j = (i + 3.0)/1.41;
		}
		step+=1.0;
		clock_gettime(CLOCK_REALTIME, &curr);
	} while(nSecTo(now, curr) < NSECS_TO_CALIBRATE);

	/** kind of cpuload normalization with maximum already measured */
	duree = (double)nSecTo(now, curr);
	maxStepBySecond = (((double)NSECS_TO_CALIBRATE)*step/duree) *PERIODS_PER_SEC;
	if (verbose) {
		printf("Steps resolution %d with normalized %ld max\n",
				(int)step, (long)maxStepBySecond);
	}
}

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
void CoreLoad_main()
{
	int i;
	double step;
	double j;
	double totalDuration, stepBySecond;
	struct timespec last,curr;
	int stop = 1;

	if (verbose) { printf("[Main Thread] Start CoreLoad infinite loop\n"); }
	clock_gettime(CLOCK_REALTIME, &last);

	while (!stop) {
		step = 0;
		do {
			for(i=0;i<BUSY_ITERATIONS;i++){
				j = (i + 3.0)/1.41;
			}
			step+=1.0;
			clock_gettime(CLOCK_REALTIME, &curr);
		} while(nSecTo(last, curr) < NSECS_PER_SEC);

		/** kind of cpuload normalization with maximum already measured */
		totalDuration = (double)nSecTo(last, curr);
		stepBySecond = (((double)NSECS_PER_SEC)*step) / totalDuration;
		if(maxStepBySecond < stepBySecond){
			maxStepBySecond = stepBySecond;
		}
		/** Compute the core busy percentage w.r.t. normalized max */
		cpuLoad = 100 - (100.0*stepBySecond)/maxStepBySecond;

		if (verbose) {
			printf(" %d %f %f\n", cpuLoad, stepBySecond, maxStepBySecond);
		}
		/** Set last with current time to start new measure cycle */
		usleep(1000);
		clock_gettime(CLOCK_REALTIME, &curr);
		last.tv_nsec = curr.tv_nsec;
		last.tv_sec = curr.tv_sec;
	}
}

/**
 \brief Interface to read back computing core load
 \param[out] cpuLoad global variable with core busy percent
 */
int CoreLoad_get(void)
{
	return cpuLoad;
}
