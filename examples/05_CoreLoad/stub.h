/*****************************************************************/
struct timespec_s{
double tv_nsec;
double tv_sec;
}timespec_t;
                  
extern clock_gettime(long, timespec*);
