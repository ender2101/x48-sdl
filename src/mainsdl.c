/*
	SDL port of x48
	Copyright (C) 2011-2012 Daniel Roggen
	Revision 1.0
*/

/*
 *  This file is part of x48, an emulator of the HP-48sx Calculator.
 *  Copyright (C) 1994  Eddie C. Dost  (ecd@dressler.de)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* $Log: main.c,v $
 * Revision 1.11  1995/01/11  18:20:01  ecd
 * major update to support HP48 G/GX
 *	
 * Revision 1.10  1994/12/07  20:20:50  ecd
 * changed initialization
 *
 * Revision 1.10  1994/12/07  20:20:50  ecd
 * changed initialization
 *
 * Revision 1.9  1994/11/28  02:00:51  ecd
 * reordered initialization. serial_init() is called after x11 init.
 *
 * Revision 1.8  1994/11/04  03:42:34  ecd
 * added call to parse_options()
 *
 * Revision 1.7  1994/11/02  14:44:28  ecd
 * call to emulate_debug() added
 *
 * Revision 1.6  1994/10/05  08:36:44  ecd
 * new function call to init_nibble_maps()
 *
 * Revision 1.5  1994/09/30  12:37:09  ecd
 * deleted saturn.intenable = 1; statement
 *
 * Revision 1.4  1994/09/18  22:47:20  ecd
 * fixed typo
 *
 * Revision 1.3  1994/09/18  15:29:22  ecd
 * turned off unused rcsid message
 *
 * Revision 1.2  1994/09/13  16:57:00  ecd
 * changed to plain X11
 *
 * Revision 1.1  1994/09/13  15:05:05  ecd
 * Initial revision
 *
 * $Id: main.c,v 1.11 1995/01/11 18:20:01 ecd Exp ecd $
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <fcntl.h>

#include "x48_sdl.h"
#include "hp48.h"
#include "debugger.h"
#include "resources.h"

#include <langinfo.h>
#include <locale.h>



#ifdef PLATFORMWEBOS
#include <PDL.h>
#endif

char  *progname;
char  *res_name;
char  *res_class;

int    saved_argc;
char **saved_argv;

saturn_t saturn;

void
#ifdef __FunctionProto__
signal_handler(int sig)
#else
signal_handler(sig)
int sig;
#endif
{
  switch (sig) {
    case SIGINT:
      enter_debugger |= USER_INTERRUPT;
      break;
    case SIGALRM:
      got_alarm = 1;
      break;
    case SIGPIPE:
      exit_x48(0);
      exit (0);
    default:
      break;
  }
}


// Some error or information messages
const char *errinit_title="Emulator initialization failed";
const char *errinit_text[]={
		"",
		"In order to work the emulator needs",
		"the following files:",
		"  rom:   an HP48 rom dump",
		"  ram:   ram file",
		"  hp48:  HP state file",
		"",
		"These files must be in ~/.hp48",
		"",
		"Install these files and try again.",
		0
	};


void testexit()
{
	printf("In test exit\n");
}
#ifdef PLATFORMWEBOS
void pdlexit()
{
	printf("pdl quit\n");
	PDL_Quit();
}
#endif

int
#ifdef __FunctionProto__
main(int argc, char **argv)
#else
main(argc, argv)
int argc;
char **argv;
#endif
{
	int rv,i;
	char *name;	
	sigset_t set;
	struct sigaction sa;
	long flags;
	struct itimerval it;
	unsigned t1,t2;

#ifdef PLATFORMWEBOS
#include <PDL.h>
#endif

	
	atexit(testexit);

	printf("x48-sdl\n");
	
#ifdef PLATFORMWEBOS
	// start the PDL library
	PDL_ScreenMetrics ScreenMetrics;
	PDL_Init(0);
	PDL_GetScreenMetrics(&ScreenMetrics);
	printf("Screen size: %d %d\n",ScreenMetrics.horizontalPixels,ScreenMetrics.verticalPixels);
	atexit(pdlexit);
#endif
	
	// SDL Initialization
	SDLInit();
	
	
	
	// Global parameter initialization
	get_resources();
	
	
	setlocale(LC_ALL, "C");
	
	name = (char *)0;
	/*
	*  Get the name we are called.
	*/
	progname = strrchr(argv[0], '/');
	if (progname == NULL)
	progname = argv[0];
	else
	progname++;
	
	


	
	// initialize emulator stuff
	rv = init_emulator();
	if(rv!=0)
	{
		printf("%s\n",errinit_title);
		for(i=0;errinit_text[i];i++)
			printf("%s\n",errinit_text[i]);
		SDLMessageBox(300,200,errinit_title,errinit_text,0xf0e0c0c0,0xff000000,0);
	
		return 0;
	}
	

	// Create the HP-48 window
	SDLCreateHP();
	

	
	// Some more initialization
	printf("init active stuff\n");
	init_active_stuff();
	
	/*
	*  install a handler for SIGALRM
	*/
	printf("SIGALRM\n");
	sigemptyset(&set);
	sigaddset(&set, SIGALRM);
	sa.sa_handler = signal_handler;
	sa.sa_mask = set;
	#ifdef SA_RESTART
	sa.sa_flags = SA_RESTART;
	#endif
	sigaction(SIGALRM, &sa, (struct sigaction *)0);
	
	/*
	*  install a handler for SIGINT
	*/
	printf("SIGINT\n");
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sa.sa_handler = signal_handler;
	sa.sa_mask = set;
	#ifdef SA_RESTART
	sa.sa_flags = SA_RESTART;
	#endif
	sigaction(SIGINT, &sa, (struct sigaction *)0);
	
	/*
	*  install a handler for SIGPIPE
	*/
	printf("SIGPIPE\n");
	sigemptyset(&set);
	sigaddset(&set, SIGPIPE);
	sa.sa_handler = signal_handler;
	sa.sa_mask = set;
	#ifdef SA_RESTART
		sa.sa_flags = SA_RESTART;
	#endif
	sigaction(SIGPIPE, &sa, (struct sigaction *)0);
	
	/*
	* set the real time interval timer
	*/
	printf("int timer\n");
	int interval = 20000;
	it.it_interval.tv_sec = 0;
	it.it_interval.tv_usec = interval;
	it.it_value.tv_sec = 0;
	it.it_value.tv_usec = interval;
	setitimer(ITIMER_REAL, &it, (struct itimerval *)0);
	
	/*
	* Set stdin flags to not include O_NDELAY and O_NONBLOCK
	*/
	printf("stdin flags\n");
	flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	flags &= ~O_NDELAY;
	flags &= ~O_NONBLOCK;
	fcntl(STDIN_FILENO, F_SETFL, flags);
	
	
	printf("start emulate\n");	
	
	do
	{
		if (!exec_flags)
			emulate ();
		else
			emulate_debug ();
	
		debug();
	} while (1);
	
	return 0;
}

