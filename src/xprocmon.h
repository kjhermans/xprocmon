#ifndef _XPROCMON_H_
#define _XPROCMON_H_

#include <unistd.h>

#include "XNextEventTimed.h"

typedef struct
{
  unsigned                      numthreads;
  struct {
    unsigned                      stack;
    unsigned                      heap;
  }                             mem;
}
xprocmon_t;

extern
int xprocmon_window
  (pid_t pid);

#endif
