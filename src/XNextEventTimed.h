#ifndef _XNEXTEVENTTIMED_H_
#define _XNEXTEVENTTIMED_H_

#include <sys/time.h>
#include <X11/Xlib.h>

/*
* XNextEventTimed returns True when the XEvent structure returned in
* EVENT_RETURN was filled in properly with the next XEvent in the queue,
* and False when the timeval structure pointed to by TV timed out.
* if TV is NULL, this function will wait indefinetely and will always
* return True.
*/

int XNextEventTimed(Display* dsp, XEvent* event_return, struct timeval* tv);

#endif // _XNEXTEVENT_H_
