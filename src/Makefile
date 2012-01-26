# Makefile to build x48-sdl

srcdir  = .

CC      = g++
#CC      = gcc
EXE	= .exe
OBJ  = .o

# Setting for Cygwin:
CFLAGS  = -O2 -I/usr/local/include/SDL -I/usr/include/mingw -DPLATFORM_MINGW -DWITH_SDL -DPLATFORM_LINUX -DPLATFORM_CYGWIN
LIBS	=  -L/usr/local/lib -lSDLmain -lSDL 


# Tryouts
#CFLAGS  = -g -O2 -I/usr/local/include/SDL -I/usr/include/mingw -mno-cygwin -Dmain=SDL_main -DHAVE_OPENGL -DPLATFORM_MINGW -DWITH_SDL 
#LIBS	=  -L/usr/local/lib -lmingw32 -lSDLmain -lSDL -mno-cygwin -mwindows
#CFLAGS  = -g -O2 -I/usr/local/include/SDL -I/usr/include/mingw -mno-cygwin -DPLATFORM_MINGW -DWITH_SDL -I../serialio -I../da
#CFLAGS  = -g -O2 -I/usr/local/include/SDL -I/usr/include/mingw -DPLATFORM_MINGW -DWITH_SDL
#LIBS	=  -L/usr/local/lib -lSDLmain -lSDL -lX11 -lXext -lSM -lICE -lhistory  -lreadline
#LIBS	=  -L/usr/local/lib -lSDLmain -lSDL -lSM -lICE -lhistory  -lreadline
#CFLAGS  = -O2 -I/usr/local/include/SDL -I/usr/include/mingw -DPLATFORM_MINGW -DWITH_SDL -DPLATFORM_WIN32
#LIBS	=  -L/usr/local/lib -L/usr/i686-pc-mingw32/sys-root/mingw/lib -lSDLmain -lSDL -lhistory  -lreadline -lmingw32 -lkernel32 -mwindows
#LIBS	=  -L/usr/local/lib -lmingw32 -lSDLmain -lSDL -mno-cygwin 
#LIBS	=  -L/usr/local/lib -lmingw32  -mno-cygwin -mwindows

SRC+=mainsdl.c

SRC+=actions.c
SRC+=debugger.c
SRC+=device.c
SRC+=disasm.c
SRC+=emulate.c
SRC+=errors.c
SRC+=init.c
SRC+=lcd.c
SRC+=memory.c
SRC+=register.c 
SRC+=resources.c
SRC+=romio.c
SRC+=rpl.c
SRC+=serial.c
SRC+=timer.c
SRC+=x48_sdl.c
SRC+=SDL_gfxPrimitives.c
SRC+=SDL_rotozoom.c

# Source without the directory
SRCnod = $(notdir $(SRC))

TARGET = main.exe

# Convert source files with .cpp extension to list of object with .o extension
#OBJS = $(SRC:.cpp=.o) $(SRC:c=.o)
OBJS = $(SRC:.c=.o)
#OBJS = $(SRCnod:.cpp=.o) 

#@echo $(SRC)
#@echo $(OBJS)

all: $(OBJS)
	@echo 
	@echo $(MSG_LINKING) $@
	$(CC) -o $(TARGET) $(OBJS)  $(CFLAGS) $(LIBS) 


REMOVE = rm -f

clean: 
	@echo
	@echo Cleaning
	$(REMOVE) *.o
	$(REMOVE) *.exe
	$(REMOVE) *.d
	

################################################################################################
################################################################################################
# Quick help
# $<	name of the first prerequisite
# $?	name of all prerequisites newer than target
# $@	file name of target
################################################################################################
################################################################################################

################################################################################################
################################################################################################
# Generic rules
################################################################################################
################################################################################################

#
# Automatically generate C source code dependencies.
#
# To output file in source directory: 
# 		"set -e; $(CC) -MM $(CFLAGS) $< | sed 's,\(.*\)\.o[ :]*,\1.o \1.d : ,g' > $@; [ -s $@ ] || rm -f $@" 
# To output file in current directory:
#		"set -e; $(CC) -MM $(CFLAGS) $< | sed 's,\(.*\)\.o[ :]*,\1.o \1.d : ,g' > $(@F); [ -s $(@F) ] || rm -f $(@F)"
# Beware that if the dependency is output in the current directory, the include of the .d file should be adapted
# Note: did not manage to have the .d in the local directory.... use the source directory (implicit rule does not find the source.cpp)

%.d: %.cpp
	set -e; $(CC) -MM $(CFLAGS) $< | sed 's,\(.*\)\.o[ :]*,\1.o \1.d : ,g' > $@; [ -s $@ ] || rm -f $@

%.d: %.c
	set -e; $(CC) -MM $(CFLAGS) $< | sed 's,\(.*\)\.o[ :]*,\1.o \1.d : ,g' > $@; [ -s $@ ] || rm -f $@



# Compile: create object files from CPP source files
# Target file is stored in the local directory 
%.o : %.cpp
	@echo 
	@echo Compiling: $<
	$(CC) -c $(CFLAGS) $< -o $@

%.o : %.c
	@echo 
	@echo Compiling: $<
	$(CC) -c $(CFLAGS) $< -o $@


# If .d files are in the directories of the source files
#include $(SRC:.cpp=.d)
#all dependencies
DEPENDENCIESCPP = $(SRC:.cpp=.d)
DEPENDENCIES = $(DEPENDENCIESCPP:.c=.d)
include $(DEPENDENCIES)
#include $(SRC:.cpp=.d)
#include $(SRC:.c=.d)
# If the .d files are in the current directory
#SRCnod = $(notdir $(SRC))
#include $(SRCnod:.cpp=.d)


################################################################################################
################################################################################################
# msg
################################################################################################
################################################################################################

MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_SIZE_BEFORE = Size before:
MSG_SIZE_AFTER = Size after:
MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
