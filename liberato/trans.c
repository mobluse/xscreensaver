#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<X11/xpm.h>

#include "vroot.h"

int main ()
{
  Display *dpy;
  Window root;
  XWindowAttributes wa;
  GC g, gc;
  XImage *img, *clp;
  Pixmap pix;
  int x, y;


  /* open the display (connect to the X server) */
  dpy = XOpenDisplay (getenv ("DISPLAY"));


  /* get the root window */
  root = DefaultRootWindow (dpy);


  /* get attributes of the root window */
  XGetWindowAttributes(dpy, root, &wa);


  /* create a GC for drawing in the window */
  g = XCreateGC (dpy, root, 0, NULL);


  /* set foreground color */
  XSetForeground(dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)) );


  /* read the image */
  if (XpmReadFileToImage (dpy, "/usr/local/games/star5.xpm", &img, &clp, NULL)) {
      printf ("Error reading file\n");
      exit (1);
  }


  /* copy the transparent image into the pixmap */
  pix = XCreatePixmap(dpy, root, clp->width, clp->height, clp->depth);
  gc = XCreateGC (dpy, pix, 0, NULL);
  XPutImage(dpy, pix, gc, clp, 0, 0, 0, 0, clp->width, clp->height);


  /* draw something */
  while (1)
    {
      /* set random coordinates */
      x=random()%(wa.width-img->width);
      y=random()%(wa.height-img->height);


      /* set clip origin and copy */
      XSetClipMask(dpy, g, pix);
      XSetClipOrigin(dpy, g, x, y);
      XPutImage(dpy, root, g, img, 0, 0, x, y, img->width, img->height );


      /* once in a while, clear all */
      if( random()%500<1 )
        XClearWindow(dpy, root);


      /* flush changes and sleep */
      XFlush(dpy);
      usleep (10);
    }


  XCloseDisplay (dpy);
}
