/*
struct timespec_s{
double tv_nsec;
double tv_sec;
}timespec;
                  

extern void clock_getres(int a, struct timespec* b);
*/
#ifndef STUB_CORELOAD_H_
#define STUB_CORELOAD_H_

extern int Pclock_gettime(long a, struct timespec* b);
#endif STUB_CORELOAD_H_
