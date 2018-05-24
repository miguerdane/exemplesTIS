//#include "stub.h"
int verbose = 0;
int g_Time = 0;

int Pclock_gettime(long a, timespec* b)
{
  b->tv_sec=g_Time++;
  return 0;
}

