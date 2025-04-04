#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/utsname.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "xprocmon.h"

int xprocmon_window
  (pid_t pid)
{
  Display* dpy = XOpenDisplay(NULL);
  if (dpy == NULL) 
  {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }
 
  int s = DefaultScreen(dpy);
  Window win = XCreateSimpleWindow(dpy, RootWindow(dpy, s), 10, 10, 660, 200, 1,
                                   BlackPixel(dpy, s), WhitePixel(dpy, s));
  XSelectInput(dpy, win, ExposureMask | KeyPressMask);
  XMapWindow(dpy, win);

  XStoreName(dpy, win, "XProcMon");
  
  Atom WM_DELETE_WINDOW = XInternAtom(dpy, "WM_DELETE_WINDOW", False); 
  XSetWMProtocols(dpy, win, &WM_DELETE_WINDOW, 1);  

  struct utsname sname;
  uname(&sname);

  XEvent e;
  while (1) 
  {
    struct timeval tv = { .tv_sec = 0, .tv_usec = 100000 };
    int r = XNextEventTimed(dpy, &e, &tv);
    xprocmon_t pm = { 0 };

    xprocmon_stat(pid, &pm);
    if (r == False || e.type == Expose) 
    {
      int y_offset = 20;
 
      const char* s1 = "X11 test app under Linux";
      
      const char* s2 = "(C)2012 Geeks3D.com"; 
      XDrawString(dpy, win, DefaultGC(dpy, s), 10, y_offset, s1, strlen(s1));
      y_offset += 20;
      XDrawString(dpy, win, DefaultGC(dpy, s), 10, y_offset, s2, strlen(s2));
      y_offset += 20;

      {
        char buf[256] = {0};
        
        sprintf(buf, "System information:");
        XDrawString(dpy, win, DefaultGC(dpy, s), 10, y_offset, buf, strlen(buf));
        y_offset += 15;

        sprintf(buf, "- System: %s", sname.sysname);
        XDrawString(dpy, win, DefaultGC(dpy, s), 10, y_offset, buf, strlen(buf));
        y_offset += 15;

        sprintf(buf, "- Release: %s", sname.release);
        XDrawString(dpy, win, DefaultGC(dpy, s), 10, y_offset, buf, strlen(buf));
        y_offset += 15;

        sprintf(buf, "- Version: %s", sname.version);
        XDrawString(dpy, win, DefaultGC(dpy, s), 10, y_offset, buf, strlen(buf));
        y_offset += 15;
        
        sprintf(buf, "- Machine: %s", sname.machine);
        XDrawString(dpy, win, DefaultGC(dpy, s), 10, y_offset, buf, strlen(buf));
        y_offset += 20;
      }


      XWindowAttributes  wa;
      XGetWindowAttributes(dpy, win, &wa);
      int width = wa.width;
      int height = wa.height;
      char buf[128]={0};
      sprintf(buf, "Current window size: %dx%d", width, height);
      XDrawString(dpy, win, DefaultGC(dpy, s), 10, y_offset, buf, strlen(buf));
      y_offset += 20;
    }
    
    if (e.type == KeyPress)
    {
      char buf[128] = {0};
      KeySym keysym;
      int len = XLookupString(&e.xkey, buf, sizeof buf, &keysym, NULL);
      if (keysym == XK_Escape)
        break;
    }

    if ((e.type == ClientMessage) && (e.xclient.data.l[0] == WM_DELETE_WINDOW))
    {
      break;
    }
  }
  
  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  return 0;
}
