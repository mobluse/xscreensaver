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

  Pixmap double_buffer;

  XRectangle clip_rect[1];


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


  /* allocate the red color */
  XAllocNamedColor(dpy,
                     DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy)),
                     "red",
                     &reds, &redx);


  /* draw something */
  while (1)
    {
      /* remove the ball from the screen */
      XSetForeground(dpy, g, BlackPixelOfScreen(DefaultScreenOfDisplay(dpy)));
      XFillRectangle(dpy, double_buffer, g, x, y, 40, 40);

      /* change position */
      x+=dx;
      y+=dy;

      /* draw in the new position */
      XSetForeground(dpy, g, reds.pixel);
      XFillArc(dpy, double_buffer, g, x, y, 40, 40, 0, 360*64);

      /* bounce (if the ball is at the edge of the screen) */
      if( x<=0 || x>=wa.width-40 )
        dx= -dx;
      if( y<=0 || y>=wa.height-40 )
        dy= -dy;


      /* create the clipping rectangle */
      clip_rect[0].x=x-1;
      clip_rect[0].y=y-1;
      clip_rect[0].width=42;
      clip_rect[0].height=42;
      XSetClipRectangles(dpy, g, 0, 0, clip_rect, 1, Unsorted);


      /* copy the buffer to the window */
      XCopyArea(dpy, double_buffer, root, g, 0, 0, wa.width, wa.height, 0, 0);


      /* flush changes and sleep */
      XFlush(dpy);
      usleep (10);
    }


  XCloseDisplay (dpy);
}
