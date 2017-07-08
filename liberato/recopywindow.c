#include <unistd.h>
#include<stdlib.h>
#include<X11/Xlib.h>

#include "vroot.h"


#define NCOLORS 3

int main (int argc, char *argv[])
{
  Display *dpy;
  Window w;
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


  /* get the window to draw into */
  if( argc<=1 )
    w = DefaultRootWindow (dpy);
  else { 
    /* create, name, and map window */
    w = XCreateSimpleWindow (dpy, DefaultRootWindow (dpy),
                             200, 200, 400, 400, 1,
                             BlackPixel (dpy, DefaultScreen (dpy)),
                             WhitePixel (dpy, DefaultScreen (dpy)));
    XStoreName (dpy, w, "This is a name");
    XSelectInput (dpy, w, StructureNotifyMask);
    XMapRaised (dpy, w);
    do {
      XWindowEvent (dpy, w, StructureNotifyMask, &e);
    } while( e.type != MapNotify );
  }


  /* get attributes of the window */
  XGetWindowAttributes(dpy, w, &wa);


  /* create a GC for drawing in the window */
  g = XCreateGC (dpy, w, 0, NULL);


  /* create the double buffer */
  double_buffer = XCreatePixmap(dpy, w,
                  wa.width, wa.height, wa.depth);
  XSetForeground(dpy, g, BlackPixelOfScreen(DefaultScreenOfDisplay(dpy)));
  XFillRectangle(dpy, double_buffer, g, 0, 0, wa.width, wa.height);
  XCopyArea(dpy, double_buffer, w, g, 0, 0, wa.width, wa.height, 0, 0);


  /* allocate colors */
  for(c=0; c<NCOLORS; c++) {
    XAllocNamedColor(dpy,
                     DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy)),
                     colors[c],
                     &sc, &xc);
    xcolors[c]=sc;
  }


  /* we want expose events */
  XSelectInput(dpy, w, ExposureMask);


  /* draw something */
  while (1)
    {
      /* set color and position */
      x=random()%(wa.width-50);
      y=random()%(wa.height-40);
      c=xcolors[random()%NCOLORS].pixel;
      

      /* draw in the window and in the double buffer */
      XSetForeground(dpy, g, xcolors[random()%NCOLORS].pixel);
      XFillRectangle (dpy, w, g, x, y, 50, 40);
      XFillRectangle (dpy, double_buffer, g, x, y, 50, 40);


      /* once in a while, clear all */
      if( random()%500<1 ) {
        XClearWindow(dpy, w);
        XSetForeground(dpy, g, BlackPixelOfScreen(DefaultScreenOfDisplay(dpy)));
        XFillRectangle(dpy, double_buffer, g, 0, 0, wa.width, wa.height);
      }


      /* check events */
      if( XCheckWindowEvent(dpy, w, ExposureMask, &e) ) {
        while( XCheckWindowEvent(dpy, w, ExposureMask, &e) );
        XCopyArea(dpy, double_buffer, w, g,
                   0, 0, wa.width, wa.height, 0, 0);
      }


      /* sleep */
      usleep (10);
    }


  XCloseDisplay (dpy);
}
