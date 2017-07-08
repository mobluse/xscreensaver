#include <unistd.h>
#include<stdlib.h>
#include<X11/Xlib.h>

#include "vroot.h"


#define NCOLORS 3

int main () {
  Display *dpy;
  Window root;
  XWindowAttributes wa;
  GC g;
  Pixmap pix;

  int i;
  char *colors[NCOLORS]={"red", "green", "blue"};
  XColor xcolors[NCOLORS];
  XColor xc, sc;
  int c;


  /* open the display (connect to the X server) */
  dpy = XOpenDisplay (getenv ("DISPLAY"));


  /* get the root window */
  root = DefaultRootWindow (dpy);


  /* get attributes of the root window */
  XGetWindowAttributes(dpy, root, &wa);


  /* create a GC for drawing */
  g = XCreateGC (dpy, root, 0, NULL);


  /* create a pixmap as large as the root window */
  pix = XCreatePixmap (dpy, root, wa.width, wa.height, wa.depth);


  /* clear the pixmap (not done by default) */
  XSetForeground(dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)) );
  XFillRectangle (dpy, pix, g, 0, 0, wa.width, wa.height);


  /* allocate colors */
  for(c=0; c<NCOLORS; c++) {
    XAllocNamedColor(dpy,
                     DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy)),
                     colors[c],
                     &sc, &xc);
    xcolors[c]=sc;
  }


  /* draw in the pixmap */
  for(i=0; i<500; i++) {
      /* set a random foreground color */
      XSetForeground(dpy, g, xcolors[random()%NCOLORS].pixel);


      /* draw a square */
      XFillRectangle (dpy, pix, g, random()%(wa.width-50),
                      random()%(wa.height-40), 50, 40);
  }


  /* set the pixmap as the background of the root window */
  XSetWindowBackgroundPixmap (dpy, root, pix);


  /* clear the root window to make the pixmap visible */
  XClearWindow (dpy, root);


  XCloseDisplay (dpy);
}
