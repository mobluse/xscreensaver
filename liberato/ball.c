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

  int x=10, y=10; 	/* position of the ball */
  int dx=1, dy=1;	/* direction of the ball */


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
      /* remove the ball from the screen */
      XClearArea(dpy, root, x, y, 40, 40, False);

      /* change position */
      x+=dx;
      y+=dy;

      /* draw in the new position */
      XFillArc(dpy, root, g, x, y, 40, 40, 0, 360*64);

      /* bounce (if the ball is at the edge of the screen) */
      if( x<=0 || x>=wa.width-40 )
        dx= -dx;
      if( y<=0 || y>=wa.height-40 )
        dy= -dy;


      /* flush changes and sleep */
      XFlush(dpy);
      usleep (10);
    }


  XCloseDisplay (dpy);
}
