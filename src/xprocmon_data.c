#include "xprocmon.h"

/**
 *
 */
int xprocmon_data
  (pid_t pid, xprocmon_t* pm)
{
  gettimeofday(&(pm->tv), 0);
  CHECK(xprocmon_maps(pid, pm));
  CHECK(xprocmon_stat(pid, pm));
  return 0;
}
