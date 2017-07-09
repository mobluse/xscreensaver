#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#include "liberato/vroot.h"

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

  char *colors[NCOLORS] = {"red", "green", "blue"};
  XColor xcolors[NCOLORS];
  XColor xc, sc;
  int c;

  int x, y;
  int txtwidth;

  // https://www.raspberrypi.org/forums/viewtopic.php?f=33&t=170112
  float systemp, millideg;
  FILE *thermal;
  int n;
  static char s[50];

  /* open the display (connect to the X server) */
  dpy = XOpenDisplay (getenv ("DISPLAY"));


  /* get the root window */
  root = DefaultRootWindow (dpy);


  /* get attributes of the root window */
  XGetWindowAttributes(dpy, root, &wa);


  /* create a GC for drawing in the window */
  g = XCreateGC (dpy, root, 0, NULL);


  /* load a font */
  // f = XLoadFont(dpy, "-*-fixed-*-r-*-*-13-*-*-*-*-*-iso8859-*"); // Only font that works in VcXsrv 1.19.2.0
  f = XLoadFont(dpy, "-*-helvetica-bold-r-*-*-*-240-*-*-*-*-iso8859-*");
  XSetFont(dpy, g, f);


  /* get font metrics */
  XGetGCValues (dpy, g, GCFont, &v);
  fs = XQueryFont (dpy, v.font);


  /* allocate colors */
  for(c = 0; c < NCOLORS; ++c) {
    XAllocNamedColor(dpy,
                     DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy)),
                     colors[c],
                     &sc, &xc);
    xcolors[c] = sc;
  }


  float systemp_save = 60.00f;
  /* draw something */
  for(;;) {
    thermal = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    n = fscanf(thermal, "%f", &millideg);
    fclose(thermal);
    systemp = (int)(millideg/10.0f)/100.0f;
    sprintf(s, "CPU: %.2f\260C", systemp);

    XClearWindow(dpy, root);

    /* set a random foreground color */
    XSetForeground(dpy, g, xcolors[systemp > systemp_save ? 0 :
                                     (systemp == systemp_save ? 1 : 2)].pixel);
    systemp_save = systemp;

    /* get text width and height */
    txtwidth = XTextWidth (fs, s, strlen(s));

    /* random x and y position */
    x = random()%(wa.width - txtwidth);
    y = random()%(wa.height - (fs->ascent + fs->descent)) + fs->ascent;

    /* draw the frames (boxes) */
    XDrawRectangle(dpy, root, g, x, y-fs->ascent, txtwidth,
       fs->ascent + fs->descent);

    /* draw a string */
    XDrawString(dpy, root, g, x, y,
                s, strlen(s));

    /* flush changes and sleep */
    XFlush(dpy);
    sleep (1);
  }


  XCloseDisplay(dpy);
}
