#include <unistd.h>

#include "XNextEventTimed.h"

int XNextEventTimed(Display* dsp, XEvent* event_return, struct timeval* tv) {

  // optimization

  if (tv == NULL) {
    XNextEvent(dsp, event_return);
    return 1;
  }

  // the real deal

  if (XPending(dsp) == 0) {
    int fd = ConnectionNumber(dsp);
    fd_set readset;
    FD_ZERO(&readset);
    FD_SET(fd, &readset);
    switch (select(fd+1, &readset, NULL, NULL, tv)) {
    case -1:
      return -1;
    case 0:
      return 0;
    default:
      XNextEvent(dsp, event_return);
      return 1;
    }
  } else {
    XNextEvent(dsp, event_return);
    return 1;
  }
}
