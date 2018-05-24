/*****************************************************************/
struct timespec{
double tv_nsec;
double tv_sec;
};
                  
extern clock_gettime(long, timspec*);
