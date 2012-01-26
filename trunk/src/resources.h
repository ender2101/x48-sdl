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

/* $Log: resources.h,v $
 * Revision 1.3  1995/01/11  18:20:01  ecd
 * major update to support HP48 G/GX
 *
 * Revision 1.2  1994/12/07  20:16:41  ecd
 * added more resource get functions
 *
 * Revision 1.2  1994/12/07  20:16:41  ecd
 * added more resource get functions
 *
 * Revision 1.1  1994/12/07  10:16:15  ecd
 * Initial revision
 *
 *
 * $Id: resources.h,v 1.3 1995/01/11 18:20:01 ecd Exp ecd $
 */
#ifndef _RESOURCES_H
#define _RESOURCES_H 1

#include "global.h"

extern int     verbose;
extern int     quiet;
extern int     useTerminal;
extern int     useSerial;
extern int     useXShm;
extern int     useDebugger;
extern int     netbook;
extern int     throttle;
extern char   serialLine[];
extern int     initialize;
extern int     resetOnStartup;
extern char   romFileName[];
extern char   homeDirectory[];

extern char   *progname;
extern char   *res_name;
extern char   *res_class;

void get_resources();

#endif /* !_RESOURCES_H */
