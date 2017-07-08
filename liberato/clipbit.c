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
  GC gc;

  XColor redx, reds;

  int x=10, y=10; 	/* position of the ball */
  int dx=1, dy=1;	/* direction of the ball */

  Pixmap double_buffer;
  Pixmap clip_mask;


  /* open the display (connect to the X server) */
  dpy = XOpenDisplay (getenv ("DISPLAY"));


  /* get the root window */
  root = DefaultRootWindow (dpy);


  /* get attributes of the root window */
  XGetWindowAttributes(dpy, root, &wa);


  /* create a GC for drawing in the window */
  g = XCreateGC (dpy, root, 0, NULL);


  /* create the double buffer */
  double_buffer = XCreatePixmap(dpy, root,
                  wa.width, wa.height, wa.depth);
  XSetForeground(dpy, g, BlackPixelOfScreen(DefaultScreenOfDisplay(dpy)));
  XFillRectangle(dpy, double_buffer, g, 0, 0, wa.width, wa.height);
  XCopyArea(dpy, double_buffer, root, g, 0, 0, wa.width, wa.height, 0, 0);


  /* create the clipping mask */
  clip_mask = XCreatePixmap(dpy, double_buffer, wa.width, wa.height, 1);
  gc=XCreateGC (dpy, clip_mask, 0, NULL);


  /* allocate the red color */
  XAllocNamedColor(dpy,
                     DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy)),
                     "red",
                     &reds, &redx);


  /* draw something */
  while (1)
    {
      /* clear clipping mask */
      XSetBackground(dpy, gc, 0);
      XFillRectangle(dpy, clip_mask, gc, 0, 0, wa.width, wa.height);


      /* remove the ball from the screen */
      XSetForeground(dpy, g, BlackPixelOfScreen(DefaultScreenOfDisplay(dpy)));
      XFillArc(dpy, double_buffer, g, x, y, 40, 40, 0, 360*64);


      /* region changed, set mask */
      XSetForeground(dpy, gc, 1);
      XFillArc(dpy, clip_mask, gc, x, y, 40, 40, 0, 360*64);


      /* change position */
      x+=dx;
      y+=dy;


      /* draw in the new position */
      XSetForeground(dpy, g, reds.pixel);
      XFillArc(dpy, double_buffer, g, x, y, 40, 40, 0, 360*64);


      /* region changed, set mask */
      XSetForeground(dpy, gc, 1);
      XFillArc(dpy, clip_mask, gc, x, y, 40, 40, 0, 360*64);


      /* bounce (if the ball is at the edge of the screen) */
      if( x<=0 || x>=wa.width-40 )
        dx= -dx;
      if( y<=0 || y>=wa.height-40 )
        dy= -dy;


      /* set clipping mask */
      XSetClipMask(dpy, g, clip_mask);


      /* copy the buffer to the window */
      XCopyArea(dpy, double_buffer, root, g, 0, 0, wa.width, wa.height, 0, 0);


      /* flush changes and sleep */
      XFlush(dpy);
      usleep (10);
    }


  XCloseDisplay (dpy);
}
