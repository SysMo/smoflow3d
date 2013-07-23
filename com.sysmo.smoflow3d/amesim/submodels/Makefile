# Example build
# Linux build:
# make OSNAME=Linux32 AME=.... (AME folder)
# Linux clean:
# make clean OSNAME=Linux32
# Windows build
# make
# Windows clean
# make clean

# Set-up the OS related variables
#gcc -g -DWIN32 -D_DEBUG -D_WINDOWS -D_MBCS -I"D:\AMESim\v1200"\lib -c TWOPORTVALVE_00.c -o win32-gcc\TWOPORTVALVE_00.o 
export CC=${AME}/sys/mingw32/bin/gcc
COMPILER_COMMON_FLAGS= -D_MBCS -ffloat-store -fno-builtin -Wall -Wno-unused-variable -m32 -std=c99 -c -fms-extensions

ifndef OSNAME
	OSNAME=Win32
endif
ifeq ($(OSNAME),Win32)
	export OBJDIR=win32-gcc
	export CLEAN_CMD=del /f *.o && del /f *.a && del /f *.exe && del /f *.dll
	OS_COMPILER_FLAG=-DWIN32 -D_WINDOWS
else ifeq ($(OSNAME),Linux32)
	export OBJDIR=lnx
	export CLEAN_CMD=rm -f *.o && rm -f *.a
	OS_COMPILER_FLAG=-DLINUX
else
$(error Unsupported operating system $(OSNAME). Possibilities are Win32 and Linux32)
endif

COMPILER_RELEASE_FLAGS= -O3 $(COMPILER_COMMON_FLAGS) $(OS_COMPILER_FLAG)
COMPILER_DEBUG_FLAGS= -g -D_DEBUG $(COMPILER_COMMON_FLAGS) $(OS_COMPILER_FLAG)
#Set up if it is debug compilation
ifdef DEBUG
	export COMPILER_FLAGS= $(COMPILER_DEBUG_FLAGS)
else
	export COMPILER_FLAGS= $(COMPILER_RELEASE_FLAGS)	
endif

INCLUDE_FLAGS = -I"$(AME)/lib" -I"../../src"

# Add a list of .c files to be compiled release/debug
SOURCE_FILES = \
	SMO_MEDIUM_DEFINITION.c \
	SMO_FLUID_SOURCE.c \
	SMO_MEDIUM_PROPERTY_SENSOR.c \
	SMO_ZERO_FLOW.c \
	
OBJECT_FILES = $(SOURCE_FILES:%.c=$(OBJDIR)/%.o)


build: $(OBJECT_FILES)

clean:
	cd $(OBJDIR) && $(CLEAN_CMD)
	
	
$(OBJDIR)/%.o: %.c
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_FLAGS) -o $(@) $(@:$(OBJDIR)/%.o=%.c)
	
