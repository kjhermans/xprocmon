#ifndef _XPROCMON_H_
#define _XPROCMON_H_

#include <unistd.h>

typedef struct
{
  int foo;
}
xprocmon_t;

extern
int xprocmon_window
  (pid_t pid);

#endif
