#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

  Colormap colormap = DefaultColormap(dpy, 0);

  XColor red, blue;

  char red_bits[] = "#FF0000";
  XParseColor(dpy, colormap, red_bits, &red);
  XAllocColor(dpy, colormap, &red);

  char blue_bits[] = "#0000FF";
  XParseColor(dpy, colormap, blue_bits, &blue);
  XAllocColor(dpy, colormap, &blue);

  XEvent e;
  xprocmon_data_t pmd = { 0 };

  while (1) 
  {
    struct timeval tv = { .tv_sec = 0, .tv_usec = 100000 };
    int r = XNextEventTimed(dpy, &e, &tv);
    xprocmon_t* pm = &(pmd.points[ pmd.offset ]);
    int d = xprocmon_data(pid, pm); (void)d;

    xprocmon_data_examine(&pmd);
    ++(pmd.offset);
    pmd.offset %= XPROCMON_GRAPHSIZE;

    if (r == False || e.type == Expose) 
    {
      XWindowAttributes  wa;
      XGetWindowAttributes(dpy, win, &wa);
      int width = wa.width;
      int height = wa.height;

      XSetForeground(dpy, DefaultGC(dpy, s), WhitePixel(dpy, s));
      XFillRectangle(dpy, win, DefaultGC(dpy, s), 0, 0, width, height);

      if (height <= 20) {
        const char* s1 = "Window is too small";
        XDrawString(dpy, win, DefaultGC(dpy, s), 10, 15, s1, strlen(s1));
        continue;
      }

      double factor_h = (double)(height - 20) / (double)(pmd.graph_height);
      double factor_w = (double)(width - 20) / (double)XPROCMON_GRAPHSIZE;

      for (unsigned i = 0; i < XPROCMON_GRAPHSIZE; i++) {
        unsigned pi = (XPROCMON_GRAPHSIZE + pmd.offset - i) % XPROCMON_GRAPHSIZE;
        pm = &(pmd.points[ pi ]);
        unsigned x = width - ((10 + i) * factor_w);
        if (pm->mem.stack) {
          unsigned y = height - (10 + (pm->mem.stack * factor_h));
          XSetForeground(dpy, DefaultGC(dpy, s), red.pixel);
          XFillRectangle(dpy, win, DefaultGC(dpy, s), x, y, 2, 2);
        }
        if (pm->mem.heap) {
          unsigned y = height - (10 + (pm->mem.heap * factor_h));
          XSetForeground(dpy, DefaultGC(dpy, s), blue.pixel);
          XFillRectangle(dpy, win, DefaultGC(dpy, s), x, y, 2, 2);
        }
      }

    }
    
    if (e.type == KeyPress)
    {
      char buf[128] = {0};
      KeySym keysym;
      int len = XLookupString(&e.xkey, buf, sizeof buf, &keysym, NULL);
      if (keysym == XK_Escape) {
        break;
      }
      (void)len;
    }

    if ((e.type == ClientMessage) &&
        ((Atom)(e.xclient.data.l[0]) == WM_DELETE_WINDOW))
    {
      break;
    }
  }
  
  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  return 0;
}
