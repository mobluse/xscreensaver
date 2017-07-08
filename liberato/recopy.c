#include <unistd.h>
#include<stdlib.h>
#include<X11/Xlib.h>

#include "vroot.h"


#define NCOLORS 3

int main ()
{
  Display *dpy;
  Window root;
  XWindowAttributes wa;
  GC g;

  char *colors[NCOLORS]={"red", "green", "blue"};
  XColor xcolors[NCOLORS];
  XColor xc, sc;
  int c;

  int x, y;

  Pixmap double_buffer;

  XEvent e;


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


  /* allocate colors */
  for(c=0; c<NCOLORS; c++) {
    XAllocNamedColor(dpy,
                     DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy)),
                     colors[c],
                     &sc, &xc);
    xcolors[c]=sc;
  }


  /* we want expose events */
  XSelectInput(dpy, root, ExposureMask);


  /* draw something */
  while (1)
    {
      /* set color and position */
      x=random()%(wa.width-50);
      y=random()%(wa.height-40);
      c=xcolors[random()%NCOLORS].pixel;
      

      /* draw in the window and in the double buffer */
      XSetForeground(dpy, g, xcolors[random()%NCOLORS].pixel);
      XFillRectangle (dpy, root, g, x, y, 50, 40);
      XFillRectangle (dpy, double_buffer, g, x, y, 50, 40);


      /* once in a while, clear all */
      if( random()%500<1 ) {
        XClearWindow(dpy, root);
        XSetForeground(dpy, g, BlackPixelOfScreen(DefaultScreenOfDisplay(dpy)));
        XFillRectangle(dpy, double_buffer, g, 0, 0, wa.width, wa.height);
      }


      /* check events */
      if( XCheckWindowEvent(dpy, root, ExposureMask, &e) ) {
        while( XCheckWindowEvent(dpy, root, ExposureMask, &e) );
        XCopyArea(dpy, double_buffer, root, g,
                   0, 0, wa.width, wa.height, 0, 0);
      }


      /* sleep */
      usleep (10);
    }


  XCloseDisplay (dpy);
}
