#include <unistd.h>
#include<stdlib.h>
#include<X11/Xlib.h>

#include "vroot.h"


int main ()
{
  Display *dpy;
  Window root;
  XWindowAttributes wa;
  GC g;

  XColor redx, reds;


  /* open the display (connect to the X server) */
  dpy = XOpenDisplay (getenv ("DISPLAY"));


  /* get the root window */
  root = DefaultRootWindow (dpy);


  /* get attributes of the root window */
  XGetWindowAttributes(dpy, root, &wa);


  /* create a GC for drawing in the window */
  g = XCreateGC (dpy, root, 0, NULL);


  /* allocate the red color */
  XAllocNamedColor(dpy,
                     DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy)),
                     "red",
                     &reds, &redx);


  /* set foreground color */
  XSetForeground(dpy, g, reds.pixel);


  /* draw something */
  while (1)
    {
      /* draw a square */
      XFillRectangle (dpy, root, g, random()%(wa.width-50),
                      random()%(wa.height-40), 50, 40);


      /* once in a while, clear all */
      if( random()%500<1 )
        XClearWindow(dpy, root);


      /* flush changes and sleep */
      XFlush(dpy);
      usleep (10);
    }


  XCloseDisplay (dpy);
}
