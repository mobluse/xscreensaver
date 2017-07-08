#!/bin/sh
# http://www.dis.uniroma1.it/~liberato/screensaver/
# Raspberry Pi: /usr/lib/arm-linux-gnueabihf
gcc -std=gnu99 -o simplesquares simplesquares.c -L/usr/lib -lX11
gcc -std=gnu99 -o sizeofscreen sizeofscreen.c -L/usr/lib -lX11
gcc -std=gnu99 -o redsquares redsquares.c -L/usr/lib -lX11
gcc -std=gnu99 -o coloredsquares coloredsquares.c -L/usr/lib -lX11
gcc -std=gnu99 -o chars chars.c -L/usr/lib -lX11
gcc -std=gnu99 -o fonts fonts.c -L/usr/lib -lX11
gcc -std=gnu99 -o framechars framechars.c -L/usr/lib -lX11
gcc -std=gnu99 -o metrics metrics.c -L/usr/lib -lX11
gcc -std=gnu99 -o image image.c -L/usr/lib -lX11 -lXpm
gcc -std=gnu99 -o embed embed.c -L/usr/lib -lX11 -lXpm
gcc -std=gnu99 -o trans trans.c  -L/usr/lib -lX11 -lXpm
gcc -std=gnu99 -o ball ball.c -L/usr/lib -lX11
gcc -std=gnu99 -o double double.c -L/usr/lib -lX11
gcc -std=gnu99 -o clip clip.c -L/usr/lib -lX11
gcc -std=gnu99 -o clipbit clipbit.c -L/usr/lib -lX11
gcc -std=gnu99 -o cliporigin cliporigin.c -L/usr/lib -lX11
gcc -std=gnu99 -o redraw redraw.c -L/usr/lib -lX11
gcc -std=gnu99 -o redraw-2 redraw-2.c -L/usr/lib -lX11
gcc -std=gnu99 -o recopy recopy.c -L/usr/lib -lX11
gcc -std=gnu99 -o coloredwindow coloredwindow.c -L/usr/lib -lX11
gcc -std=gnu99 -o resizewindow resizewindow.c -L/usr/lib -lX11
gcc -std=gnu99 -o recopywindow recopywindow.c -L/usr/lib -lX11
gcc -std=gnu99 -o background background.c -L/usr/lib -lX11
