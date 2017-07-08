# XScreensaver for Raspberry Pi and updates to a screensaver tutorial
A screensaver for Raspberry Pi that shows temperature with updates to a tutorial from *liberato*.
The tutorial from *liberato* also seems to work in WSL/BashOnWindows, if you install an X-server.

How to measure temperature with a Raspberry Pi from C:  
https://www.raspberrypi.org/forums/viewtopic.php?f=33&t=170112

Tutorial on how to write screensavers for Linux (and maybe Mac OS X):  
http://www.dis.uniroma1.it/~liberato/screensaver/

Problems with the tutorial, but I have figured out how to compile and run, see shell scripts:  
https://stackoverflow.com/questions/11686699/hints-and-tips-for-writing-a-screensaver-using-xscreensaver

Install:  
**$ sudo apt-get install xscreensaver**

Run in the folder whose screensavers you want to use:  
**$ ./rebuild.sh**  
**$ ./install.sh**

Run:  
**$ xscreensaver-demo**  
or run it from start menu: Preferences/Screensaver  
Look up your screensavers and preview. It doesn't work to just run the screensaver program because it then uses an invisible screen.
