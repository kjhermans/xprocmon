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

extern
int xprocmon_stat
  (pid_t pid, xprocmon_t* pm);

extern
int xprocmon_maps
  (pid_t pid, xprocmon_t* pm);

extern
int absorb_file
  (char* path, unsigned char** buf, unsigned* buflen);

extern
char* dup_file_string
  (char* path);

#endif
