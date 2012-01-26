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

/* $Log: resources.c,v $
 * Revision 1.3  1995/01/11  18:20:01  ecd
 * major update to support HP48 G/GX
 *
 * Revision 1.2  1994/12/07  20:20:50  ecd
 * more resource get functions
 *
 * Revision 1.2  1994/12/07  20:20:50  ecd
 * more resource get functions
 *
 * Revision 1.1  1994/12/07  10:15:47  ecd
 * Initial revision
 *
 *
 * $Id: resources.c,v 1.3 1995/01/11 18:20:01 ecd Exp ecd $
 */

/* xscreensaver, Copyright (c) 1992 Jamie Zawinski <jwz@lucid.com>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation.  No representations are made about the suitability of this
 * software for any purpose.  It is provided "as is" without express or
 * implied warranty.
 */

#include "global.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <unistd.h>	


#include "resources.h"
#include "disasm.h"
#include "errors.h"


int	verbose;
int	quiet;
int     useTerminal;
int     useSerial;
char   serialLine[1024];
int     useXShm;
int     useDebugger;
int	netbook;
int	throttle;
int     initialize;
int     resetOnStartup;
char   romFileName[1024];
char   homeDirectory[1024];

void
#ifdef __FunctionProto__
get_resources(void)
#else
get_resources()
#endif
{/*
  if (get_boolean_resource("printVersion", "PrintVersion"))
    show_version();
  if (get_boolean_resource("printCopyright", "PrintCopyright"))
    show_copyright();
  if (get_boolean_resource("printWarranty", "PrintWarranty"))
    show_warranty();*/

  
  verbose = 0;
  quiet = 0;
  useTerminal = 1;
  useSerial = 0;
  strcpy(serialLine,"/dev/ttyS0");
  //initialize=0;
  initialize=0;
  resetOnStartup=0;
  
	// There are two directories that can contain files:
	// homeDirectory:		Directory in which the live files (hp state, ram, but also a copy of the rom) are stored
	//							homeDirectory is the first directory in which x48 attempts to load the emulator data
	//							It is also in homeDirectory that state files are saved
	// romFileName:		if loading files from homeDirectory fails, the emulator instead initializes the state and ram from scratch, and attempts
	//							to load the ROM romFileName. This is just for bootstrapping: afterwards then the emulator will save the state to homeDirectory
	
	// Have homeDirectory in the user's home
#ifdef PLATFORMWEBOS
	strcpy(homeDirectory,"/media/internal/hp48");
#else
	strcpy(homeDirectory,".hp48");				// live files are stored in ~/.hp48
#endif
	
	

	// As a fallback, assume that a ROM will be available at the same location as the executable
	// We assume that the rom file is in the same 
	int rv;
	rv = readlink("/proc/self/exe", romFileName, sizeof(romFileName));	// Find the full path name of the executable (this is linux/cygwin only)
	if(rv>0 && rv<sizeof(romFileName))
	{
		// If found...
		romFileName[rv]=0;
		// find the last slash and terminate
		char *slash = strrchr(romFileName,'/');
		*slash=0;
		// append the name of the rom file
		strcat(romFileName,"/rom");
		
	}
	else
	{
		// Couldn't find path to executable... just use some default
		strcpy(romFileName,"rom.dump");
	}
	
	printf("homeDirectory: %s\n",homeDirectory);
	printf("romFileName: %s\n",romFileName);

	useDebugger=1;
	disassembler_mode=CLASS_MNEMONICS; // HP_MNEMONICS
	netbook=0;
	throttle=0;
  
  
}

