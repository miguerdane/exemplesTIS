/*****************************************************************/
struct timespec_s{
double tv_nsec;
double tv_sec;
}timespec;
                  
extern void clock_gettime(long a, timespec* b);
