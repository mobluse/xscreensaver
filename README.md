# XScreensaver for Raspberry Pi & Updates to a Screensaver Tutorial
A [screensaver](https://en.wikipedia.org/wiki/Screensaver) for [Raspberry Pi](https://en.wikipedia.org/wiki/Raspberry_Pi)
that shows temperature with updates to a tutorial from *liberato*. The tutorial from *liberato* also seems to work in
[WSL/BashOnWindows](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux), if you install an
[X-server](https://sourceforge.net/projects/vcxsrv/).

Open Bash and install packages:  
**$ sudo apt-get install xscreensaver libxpm-dev xfonts-100dpi**  
I you use WSL you might skip **xfonts-100dpi** because it doesn't help **xfontsel** since the X-server is external.

Clone this repository:
**$ git clone https://github.com/mobluse/xscreensaver**

Run in the folder whose screensavers you want to use:  
**$ ./rebuild.sh**  
**$ ./install.sh**

Run:  
**$ xscreensaver-demo**  
or run it from start menu: Preferences/Screensaver  
Look up your screensavers and preview. It doesn't work to just run the screensaver program because then it uses an 
invisible screen.

## Screensaver Temperature
This screensaver shows the CPU-temperature and it is red when increasing, green when unchanged, and blue when sinking, compared to 
the previous second. The temperature shifts position each second. This screensaver doesn't work in WSL since it doesn't have the 
device at the same place. 
![Temperature Red](https://github.com/mobluse/xscreensaver/blob/master/temperature_red.png?raw=true) ![Temperature Green](https://github.com/mobluse/xscreensaver/blob/master/temperature_green.png?raw=true) ![Temperature Blue](https://github.com/mobluse/xscreensaver/blob/master/temperature_blue.png?raw=true)

How to measure CPU-temperature with a Raspberry Pi from the C programming language:  
https://www.raspberrypi.org/forums/viewtopic.php?f=33&t=170112

## Screensavers from the Tutorial by *liberato*
The other screensavers does work in WSL except for those using text, since VcXsrv doesn't have all the fonts,
but one can change font to an existing, manually in the source code.
(VcXsrv has only two fonts. Check which by running **xfontsel**.
There is a yet unanswered question about how to add fonts to VcXsrv,
see https://superuser.com/questions/1192339/how-to-add-fonts-to-vcxsrv-x-server.)

## Tutorial on How to Write Screensavers for Linux:  
http://www.dis.uniroma1.it/~liberato/screensaver/  
[XScreensaver](https://www.jwz.org/xscreensaver/) exists for X11 (e.g. Linux), Mac OS X, iOS, Android.

There are some problems with the tutorial, but I have figured out how to compile and run, see shell scripts:  
https://stackoverflow.com/questions/11686699/hints-and-tips-for-writing-a-screensaver-using-xscreensaver
