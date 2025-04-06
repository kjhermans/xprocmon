#ifndef _XPROCMON_H_
#define _XPROCMON_H_

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

#include "XNextEventTimed.h"

typedef struct
{
  struct timeval                tv;
  long                          stime;
  long                          cstime;
  unsigned                      numthreads;
  struct {
    unsigned                      stack;
    unsigned                      heap;
    unsigned                      total;
  }                             mem;
}
xprocmon_t;

typedef struct
{
#define XPROCMON_GRAPHSIZE      2048
  xprocmon_t                    points[ XPROCMON_GRAPHSIZE ];
  unsigned                      offset;
  unsigned                      size;
  unsigned                      graph_height;
}
xprocmon_data_t;

#ifdef _DEBUG
#define DBGMSG(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__);
#else
#define DBGMSG(fmt, ...)
#endif

#define CHECK(fnc) { \
  int __r = (fnc); \
  if (__r) { \
    DBGMSG("Error at %s:%d\n", __FILE__, __LINE__); \
    return __r; \
  } \
}

#include "xprocmon_functions.h"

#endif
