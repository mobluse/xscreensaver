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
  GC g;
  XImage *img;


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
  if (XpmReadFileToImage (dpy, "/usr/local/games/monalisa.xpm", &img, NULL, NULL)) {
      printf ("Error reading file\n");
      exit (1);
  }


  /* draw something */
  while (1)
    {
      /* copy the image (which is ir->weight large and ir->height high,
         to a random position of the screen */
      XPutImage(dpy, root, g, img, 0, 0,
                random()%(wa.width-img->width),
                random()%(wa.height-img->height),
                img->width, img->height );


      /* once in a while, clear all */
      if( random()%500<1 )
        XClearWindow(dpy, root);


      /* flush changes and sleep */
      XFlush(dpy);
      usleep (10);
    }


  XCloseDisplay (dpy);
}
