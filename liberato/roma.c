#include<stdlib.h>
#include<X11/Xlib.h>
#include<X11/xpm.h>

#include "vroot.h"

#define IMGDIR "/home/liberato/roma"

main ()
{
  Display *dpy;
  Window root;
  XWindowAttributes wa;
  GC g;
  XImage *img;
  char imgfile[100];


  /* open the display (connect to the X server) */
  dpy = XOpenDisplay (getenv ("DISPLAY"));


  /* get the root window */
  root = DefaultRootWindow (dpy);


  /* get attributes of the root window */
  XGetWindowAttributes (dpy, root, &wa);


  /* create a GC for drawing in the window */
  g = XCreateGC (dpy, root, 0, NULL);


  /* set foreground color */
  XSetForeground (dpy, g, WhitePixelOfScreen (DefaultScreenOfDisplay (dpy)));


  /* cycle of drawing */
  while (1) {

      /* determine the image file name */
      sprintf(imgfile, "%s/%02d.xpm", IMGDIR, random()%20+1);

      /* read the image */
      if (XpmReadFileToImage (dpy, imgfile, &img, NULL, NULL)) {
	  /* printf ("Error reading file\n");
	  exit (1); */
          continue;
      }

      /* copy the image (which is ir->weight large and ir->height high,
         to a random position of the screen */
      XPutImage (dpy, root, g, img, 0, 0,
		 random () % (wa.width - img->width),
		 random () % (wa.height - img->height),
		 img->width, img->height);


      /* deallocate the image */
      XDestroyImage(img);

      /* flush changes and sleep */
      XFlush (dpy);
      usleep (500000);
    }


  XCloseDisplay (dpy);
}
