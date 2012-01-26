/*
	SDL port of x48
	Copyright (C) 2011-2012 Daniel Roggen
	Revision 1.0
*/
/*
	Main changes in SDL port:
	- struct button_t: changed char * to const char * 
	- struct color_t: changed char * to const char * 
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

/* $Log: x48_x11.h,v $
 * Revision 1.11  1995/01/11  18:20:01  ecd
 * major update to support HP48 G/GX
 *
 * Revision 1.10  1994/12/07  20:16:41  ecd
 * added "refresh_icon"
 *
 * Revision 1.10  1994/12/07  20:16:41  ecd
 * added "refresh_icon"
 *
 * Revision 1.9  1994/11/28  02:19:22  ecd
 * added support for contrast adjustment
 *
 * Revision 1.8  1994/11/04  03:44:47  ecd
 * added support for mono and gray displays
 *
 * Revision 1.7  1994/11/02  14:51:27  ecd
 * minor fix
 *
 * Revision 1.6  1994/10/09  20:26:35  ecd
 * changed disp_t
 *
 * Revision 1.5  1994/10/06  16:29:28  ecd
 * added XShm - Extension stuff
 *
 * Revision 1.4  1994/10/05  08:33:22  ecd
 * changed disp_t: removed Pixmap
 *
 * Revision 1.3  1994/09/30  12:32:49  ecd
 * changed display stuff, added detection of interrupts in GetEvent
 *
 * Revision 1.2  1994/09/18  15:31:58  ecd
 * started Real Time support
 *
 * Revision 1.1  1994/09/13  15:05:11  ecd
 * Initial revision
 *
 *
 * $Id: x48_x11.h,v 1.11 1995/01/11 18:20:01 ecd Exp ecd $
 */

#ifndef _X48_SDL_H
#define _X48_SDL_H 1

#include "global.h"


#include "SDL.h"

// Colors
#define WHITE		0
#define LEFT		1
#define RIGHT		2
#define BUT_TOP 	3
#define BUTTON  	4
#define BUT_BOT 	5
#define LCD		6
#define PIXEL		7
#define PAD_TOP 	8
#define PAD		9
#define PAD_BOT		10
#define DISP_PAD_TOP	11
#define DISP_PAD	12
#define DISP_PAD_BOT	13
#define LOGO		14
#define LOGO_BACK	15
#define LABEL		16
#define FRAME		17
#define UNDERLAY	18
#define BLACK		19

// ?
#define UPDATE_MENU	1
#define UPDATE_DISP	2

// Buttons
#define BUTTON_A	0
#define BUTTON_B	1
#define BUTTON_C	2
#define BUTTON_D	3
#define BUTTON_E	4
#define BUTTON_F	5

#define BUTTON_MTH	6
#define BUTTON_PRG	7
#define BUTTON_CST	8
#define BUTTON_VAR	9
#define BUTTON_UP	10
#define BUTTON_NXT	11

#define BUTTON_COLON	12
#define BUTTON_STO	13
#define BUTTON_EVAL	14
#define BUTTON_LEFT	15
#define BUTTON_DOWN	16
#define BUTTON_RIGHT	17

#define BUTTON_SIN	18
#define BUTTON_COS	19
#define BUTTON_TAN	20
#define BUTTON_SQRT	21
#define BUTTON_POWER	22
#define BUTTON_INV	23

#define BUTTON_ENTER	24
#define BUTTON_NEG	25
#define BUTTON_EEX	26
#define BUTTON_DEL	27
#define BUTTON_BS	28

#define BUTTON_ALPHA	29
#define BUTTON_7	30
#define BUTTON_8	31
#define BUTTON_9	32
#define BUTTON_DIV	33

#define BUTTON_SHL	34
#define BUTTON_4	35
#define BUTTON_5	36
#define BUTTON_6	37
#define BUTTON_MUL	38

#define BUTTON_SHR	39
#define BUTTON_1	40
#define BUTTON_2	41
#define BUTTON_3	42
#define BUTTON_MINUS	43

#define BUTTON_ON	44
#define BUTTON_0	45
#define BUTTON_PERIOD	46
#define BUTTON_SPC	47
#define BUTTON_PLUS	48

#define LAST_BUTTON	48

// Screen size

#define _KEYBOARD_HEIGHT	(buttons_gx[LAST_BUTTON].y + buttons_gx[LAST_BUTTON].h)
#define _KEYBOARD_WIDTH  (buttons_gx[LAST_BUTTON].x + buttons_gx[LAST_BUTTON].w)

#define _TOP_SKIP		65
#define _SIDE_SKIP		20
#define _BOTTOM_SKIP		25
#define _DISP_KBD_SKIP		65
#define _KBD_UPLINE			25

#define _DISPLAY_WIDTH		(264 + 8)
#define _DISPLAY_HEIGHT		(128 + 16 + 8)
#define _DISPLAY_OFFSET_X	(SIDE_SKIP+(286-DISPLAY_WIDTH)/2)
#define _DISPLAY_OFFSET_Y	TOP_SKIP

#define _DISP_FRAME		8

#define _KEYBOARD_OFFSET_X	SIDE_SKIP
#define _KEYBOARD_OFFSET_Y	(TOP_SKIP + DISPLAY_HEIGHT + DISP_KBD_SKIP)




// Typedefs
typedef struct color_t {
  const char *name;
  int r, g, b;
} color_t;

typedef struct keypad_t {
  unsigned int	width;
  unsigned int	height;
} keypad_t;

typedef struct disp_t {
  unsigned int     w, h;
  short            mapped;
  int		   offset;
  int		   lines;
} disp_t;

typedef struct button_t {

  const char		*name;
  short		pressed;
  short		extra;

  int		code;
  int		x, y;
  unsigned int	w, h;

  int		lc;
  const char		*label;
  short		font_size;
  unsigned int	lw, lh;
  unsigned char *lb;

  const char		*letter;

  const char		*left;
  short		is_menu;
  const char		*right;
  const char		*sub;

  	///////////////////////////////////////////////
	// SDL PORT
	///////////////////////////////////////////////
	SDL_Surface *surfaceup,*surfacedown;  

} button_t;

// This mimicks the structure formerly lcd.c, except with SDL surfaces instead of Pixmaps. 
typedef struct ann_struct {
	int            bit;
	int            x;
	int            y;
	unsigned int   width;
	unsigned int   height;
	unsigned char *bits;
	///////////////////////////////////////////////
	// SDL PORT
	///////////////////////////////////////////////
	
	SDL_Surface *surfaceon;
	SDL_Surface *surfaceoff;
} ann_struct_t;

typedef struct SDLWINDOW {
	SDL_Surface *oldsurf,*surf;
	int x,y;
} SDLWINDOW_t;



extern color_t *colors;
extern ann_struct_t ann_tbl[];
extern disp_t   disp;
extern button_t *buttons;
extern button_t buttons_sx[];
extern button_t buttons_gx[];



extern int	InitDisplay	 __ProtoType__((int argc, char **argv));
extern void SDLCreateHP();
extern int	GetEvent	 __ProtoType__((void));

extern void	adjust_contrast  __ProtoType__((int contrast));

extern void	ShowConnections	 __ProtoType__((char *w, char *i));

extern void	exit_x48	 __ProtoType__((int tell_x11));


///////////////////////////////////////////////
// SDL PORT
///////////////////////////////////////////////
extern unsigned int ARGBColors[BLACK];
extern int SDLGetEvent();
extern SDL_Surface *sdlscreen;
extern SDL_Surface *sdlsurface;


void SDLInit();
void SDLDrawAnnunc(char *annunc);
#define DISP_ROWS	       64
#define NIBS_PER_BUFFER_ROW    (NIBBLES_PER_ROW + 2)


void SDLCreateAnnunc();
//void SDLDrawLcd(unsigned char lcd_buffer[DISP_ROWS][NIBS_PER_BUFFER_ROW]);
//void SDLDrawLcd();
void SDLDrawNibble(int nx,int ny,int val);
void SDLDrawKeypad(void);
void SDLDrawButtons();
SDL_Surface *SDLCreateSurfFromData(unsigned int w,unsigned int h,unsigned char *data,unsigned int coloron,unsigned int coloroff);
SDL_Surface *SDLCreateARGBSurfFromData(unsigned int w,unsigned int h,unsigned char *data,unsigned int xpcolor);
//void SDLDrawSmallString(int x, int y, const char *string, unsigned int length);
void SDLDrawSmallString(int x, int y, const char *string, unsigned int length,unsigned int coloron,unsigned int coloroff);
void SDLCreateColors();
void SDLDrawKeyLetter();
unsigned SDLBGRA2ARGB(unsigned color);
void SDLDrawBezel(unsigned int width, unsigned int height, unsigned int offset_y, unsigned int offset_x);
void SDLDrawMore(unsigned int w, unsigned int h, unsigned int cut,unsigned int offset_y, unsigned int offset_x,int keypad_width,int keypad_height);
void SDLDrawLogo(unsigned int w, unsigned int h, unsigned int cut,unsigned int offset_y, unsigned int offset_x,int keypad_width,int keypad_height);
void SDLDrawBackground(int width, int height, int w_top, int h_top);
void SDLUIShowKey(int hpkey);
void SDLUIHideKey();
void SDLUIFeedback();
SDLWINDOW_t SDLCreateWindow(int x,int y,int w,int h,unsigned color,int framewidth,int inverted);
void SDLShowWindow(SDLWINDOW_t *win);
void SDLSHideWindow(SDLWINDOW_t *win);
void SDLARGBTo(unsigned color,unsigned *a,unsigned *r,unsigned *g,unsigned *b);
unsigned SDLToARGB(unsigned a,unsigned r,unsigned g,unsigned b);
void SDLMessageBox(int w,int h,const char *title,const char *text[],unsigned color,unsigned colortext,int center);
void SDLEventWaitClickOrKey();
void SDLShowInformation();
#endif /* !_X48_SDL_H */


