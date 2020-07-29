# budwm

budwm is an extremely fast, small, and dynamic window manager for X.


Requirements
------------
In order to build budwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (budwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install budwm (if
necessary as root):

    make clean install


Running budwm
-----------
Add the following line to your .xinitrc to start budwm using startx:

    exec budwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.


TODO
-------------
 - re document config
