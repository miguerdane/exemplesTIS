/*****************************************************************/
struct timespec_s{
double tv_nsec;
double tv_sec;
}timespec;
                  
extern void clock_gettime(long a, struct timespec* b);
extern void clock_getres(int a, struct timespec* b);
