# trivial makefile for OpenSG tutorials

SYSTEM := $(shell uname)

# set the path to the installed OpenSG root directory here
# if you installed in /usr/local:
# OSGROOT := /usr/local
# use this if you installed in Builds/*/

# try to get configured information first, will not work if more
# than one system is configured from one dir. Just for the 1.0

-include .prefix

OSGROOT ?= $(OSGINSTALLPREFIX)

OSGROOT ?= $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)

# the path where GLUT is found
# you can ignore this on Linux, it's in the system libs
GLUTPATH := /igd/a4/software/$(SYSTEM)

### System dependences ###############################################

# be very careful with these lines. There needs to be a space after the Unix
# lines and nothing after the win lines!!

ifeq ($(SYSTEM),IRIX)
        CCOUT := -o 
        LDOUT := -o 
		LINK  := 
endif
ifeq ($(SYTEM),IRIX64)
        CCOUT := -o 
        LDOUT := -o 
		LINK  := 
endif
ifeq ($(SYSTEM),Linux)
        CCOUT := -o 
        LDOUT := -o 
		LINK  := 
endif
ifeq ($(findstring WIN,$(SYSTEM)),WIN)
        OS := WIN32
        CCOUT := -Fo
        LDOUT := /out:
		LINK  := -link
endif

# use debug or opt libs?
LIBTYPE := dbg

# Var settings

CC = "$(shell $(OSGROOT)/bin/osg-config --compiler)"

CCFLAGS = \
  $(shell $(OSGROOT)/bin/osg-config --$(LIBTYPE) --cflags Base System GLUT)

LDFLAGS = $(LINK) \
  $(shell $(OSGROOT)/bin/osg-config --$(LIBTYPE) --libs Base System GLUT)


# all tutorials in this directory

TUTS :=  $(wildcard [0-9][0-9]*.cpp) 
PROGS := $(TUTS:.cpp=) 

# program dependencies

default:	$(PROGS)

# make rules

.PHONY: clean Clean

clean:
	rm -f  *.o 
	rm -rf ii_files

Clean: clean
	rm -f $(PROGS) 

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) (LDOUT)$@ $< $(LDFLAGS)

%: %.cpp
	$(CC) $(CCFLAGS) $< $(LDFLAGS) $(LDOUT)$@ 
