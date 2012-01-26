HP 48GX emulator - Running on SDL (Simple DirectMedia Layer)

by Daniel Roggen, 2011-2012
   droggen@gmail.com


NOTES

- This is a port of the x48 HP48 emulator, which is an X11-based HP48 emulator, to use the Simple DirectMedia Layer.
- It will work on any Linux or Linux-derived system: straight Linux, Cygwin, WebOS (Pre-, Pre3), ...
- x48 compiles on many unices but x48-sdl won't: lots of stuff has been 'statically configured'.
- x48-sdl is based on x48 version 0.6.4 plus a patch from an older x48 version that disables arrow and delete key repeat (throttling-related issue)
- It might happen that the HP48 doesn't turn on: in this case press repeatedly the ON key, or close and relaunch the program. This is an issue of x48.
- Currently there is no way to load a program from the emulator. However the data of the emulator is stored in a directory '~/hp48'. You can also place there your own 'ram', 'port1' or 'port2' files to load some programs. For instance set-up your emulator on your PC then transfer the 'port1'. If needed you can also erase these files to clear the HP48 memory. 
- Credit where credit's due: The original author of x48 is Eddie C. Dost, the maintainer is G. Allen Morris III

HOW TO COMPILE
- cd src
- make

DEPENDENCIES
- SDL (on cygwin may need to be compiled manually)

PLATFORMS
- Cygwin
- Linux
- WebOS (Pre-, Pre+, Pre2, Pre3, Pixi, Veer, Touchpad): need the Palm PDK; compile with make -fwebosMakefile; package with webospackage.cmd


HOW WAS THE PORT DONE?
One need to very manually sync to upstream... if a new x48 version is released one may need to repeat this process.
This is what was done:
0) SVN checkout from http://developer.berlios.de/projects/x48/
1) Compile under cygwin by:
- ./autogen.sh
- ./configure (and comment out 2 lines that break in configure, and rerun, until the configure is complete)
- make
2) At this stage config.h is created. Move it to src
3) Start the port from what is in src:
- removing all the X11, Pixmap, etc.... replacing by SDL




HISTORY 

v0.9.0 26.01.2012: 
	- Add sdl_compact to minimize the screen space needed for small devices (currently for WebOS)
	
v0.8.0 09.01.2012: First release










