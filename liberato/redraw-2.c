#include <unistd.h>
#include<stdlib.h>
#include<X11/Xlib.h>

#include "vroot.h"


#define NCOLORS 3
#define NRECTS 100

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

  int x[NRECTS], y[NRECTS];		/* the positions */
  int col[NRECTS];			/* the colors */
  int lp=0;				/* last point */

  XEvent e;				/* the event */
  int i;
  int ee;				/* is there any Expose event? */


  /* open the display (connect to the X server) */
  dpy = XOpenDisplay (getenv ("DISPLAY"));


  /* get the root window */
  root = DefaultRootWindow (dpy);


  /* get attributes of the root window */
  XGetWindowAttributes(dpy, root, &wa);


  /* create a GC for drawing in the window */
  g = XCreateGC (dpy, root, 0, NULL);


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
      /* random position and color for the next point */
      col[lp]=xcolors[random()%NCOLORS].pixel;
      x[lp]=random()%(wa.width-50);
      y[lp]=random()%(wa.height-40);

    
      /* set color and draw */
      XSetForeground(dpy, g, col[lp]);
      XFillRectangle (dpy, root, g, x[lp], y[lp], 50, 40);


      /* increase point number */
      lp++;
      if( lp==NRECTS ) {
        lp=0;
        XClearWindow(dpy, root);
      }


      /* check events */
      ee=False;

      if( XCheckWindowEvent(dpy, root, ExposureMask, &e) ) {
        if( e.type==Expose )
          ee=True;

        while( XCheckWindowEvent(dpy, root, ExposureMask, &e) )
          if( e.type==Expose )
            ee=True;

        if( ee ) 
          for(i=0; i<lp; i++) {
            XSetForeground(dpy, g, col[i]);
            XFillRectangle (dpy, root, g, x[i], y[i], 50, 40);
          }
      }


      /* sleep */
      usleep (10);
    }


  XCloseDisplay (dpy);
}
