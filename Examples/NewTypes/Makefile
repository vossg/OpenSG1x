# trivial makefile for OpenSG example

### System dependences ###############################################

OS      := $(shell echo `uname`)
OS_TYPE := $(shell echo `uname`_`uname -r`_`uname -p`)

# be very careful with these lines. There needs to be a space after the Unix
# lines and nothing after the win lines!!

ifeq ($(OS),IRIX)  
        OBJEXT := .o
        CCOUT  := -o 
        LDOUT  := -o 
	BINSUF :=
endif
ifeq ($(OS),IRIX64)  
        OBJEXT := .o
        CCOUT  := -o 
        LDOUT  := -o 
	BINSUF :=
endif
ifeq ($(OS),Linux)    
        OBJEXT := .o
        CCOUT  := -o 
        LDOUT  := -o 
	BINSUF :=
endif
ifeq ($(findstring WIN,$(OS)),WIN)    
        OBJEXT := .obj
        CCOUT  := -Fo
        LDOUT  := /out:
	BINSUF := .exe
endif

SRCS := $(wildcard OSG*.cpp)

OBJS := $(SRCS:.cpp=$(OBJEXT))

# set the path to the installed OpenSG root directory here
# if you installed in /usr/local:
# OSGROOT := /usr/local
# use this if you installed in Builds/*/
OSGROOT := $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)


CC := "$(shell $(OSGROOT)/bin/osg-config --compiler)"

CCFLAGS = -I. $(shell $(OSGROOT)/bin/osg-config --cflags Base System GLUT) -DOSG_BUILD_DLL -DOSG_COMPILEMYLIBRARY

LD := "$(shell $(OSGROOT)/bin/osg-config --exe-linker)"

LDFLAGS = $(shell $(OSGROOT)/bin/osg-config --libs Base System GLUT)


testTypes$(BINSUF): $(OBJS) testTypes$(OBJEXT) 

%$(OBJEXT): %.cpp
	$(CC) -c $(CCFLAGS) $< $(CCOUT)$@

%$(BINSUF): %$(OBJEXT)
	$(LD) $< $(OBJS) $(LDFLAGS) $(LDOUT)$@
