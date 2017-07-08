#include <unistd.h>
#include <string.h>
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

  Font f;
  XFontStruct *fs;
  XGCValues v;


  char *colors[NCOLORS]={"red", "green", "blue"};
  XColor xcolors[NCOLORS];
  XColor xc, sc;
  int x, y;
  int c;


  /* open the display (connect to the X server) */
  dpy = XOpenDisplay (getenv ("DISPLAY"));


  /* get the root window */
  root = DefaultRootWindow (dpy);


  /* get attributes of the root window */
  XGetWindowAttributes(dpy, root, &wa);


  /* create a GC for drawing in the window */
  g = XCreateGC (dpy, root, 0, NULL);


  /* load a font */
  f=XLoadFont(dpy, "-*-helvetica-bold-r-*-*-20-*-*-*-*-*-*-*");
  XSetFont(dpy, g, f);


  /* get font metrics */
  XGetGCValues (dpy, g, GCFont, &v);
  fs = XQueryFont (dpy, v.font);


  /* allocate colors */
  for(c=0; c<NCOLORS; c++) {
    XAllocNamedColor(dpy,
                     DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy)),
                     colors[c],
                     &sc, &xc);
    xcolors[c]=sc;
  }


  /* draw something */
  x=0;
  y=fs->ascent;
  
  while (1)
    {
      /* set a random foreground color */
      XSetForeground(dpy, g, xcolors[random()%NCOLORS].pixel);

      
      /* draw a string */
      XDrawString(dpy, root, g, x, y,
                  "Ooops!", strlen("Ooops!") );


      /* increase x and y */
      x=x+XTextWidth (fs, "Ooops!", strlen("Ooops!") );

      if( x>wa.width ) {
        x=0;
        y=y+fs->ascent+fs->descent;
      }

      if( y-fs->ascent>wa.height ) {
        XClearWindow(dpy, root);
        x=0;
        y=fs->ascent;
      }


      /* flush changes and sleep */
      XFlush(dpy);
      usleep (10);
    }


  XCloseDisplay (dpy);
}
