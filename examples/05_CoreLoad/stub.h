/*****************************************************************/
struct timespec{
tv_nsec;
tv_sec;
};
                  
extern clock_gettime(long, timspec*);
