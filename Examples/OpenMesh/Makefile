# trivial makefile for OpenSG example

# set the path to the installed OpenSG root directory here
# if you installed in /usr/local:
# OSGROOT := /usr/local
# use this if you installed in Builds/*/
OSGROOT := $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)

# OpenMesh options

# This is the directory in which OpenMesh has been compiled. Note that the includes use
# OpenMesh/..., so make sure this the directory above the actual OpenMesh source
OPENMESHROOT := .

# these are hardcoded for Suse Linux 8.0. You will have to change them for
# other systems. Check "acgmake -debug" for the options that are used on your system.

OPENMESHCCFLAGS := -I$(OPENMESHROOT) -pipe -Wall -fPIC -DOM_USE_OSG=1 -g -DARCH_LINUX \
                   -DINCLUDE_TEMPLATES -ftemplate-depth-100 -DDEBUG
                   
OPENMESHLDFLAGS := -pipe -Wall -fPIC -DOM_USE_OSG=1 -g -DARCH_LINUX -DINCLUDE_TEMPLATES \
                   -ftemplate-depth-100 -DDEBUG \
                   -L$(OPENMESHROOT)/OpenMesh/Core/SuSE8.0_gcc_dbg -lOpenMesh_Core 

# Program rules

openmeshviewer: openmeshviewer.o 


# Rules

CC := $(shell $(OSGROOT)/bin/osg-config --compiler)

CCFLAGS = -I. $(OPENMESHCCFLAGS) $(shell $(OSGROOT)/bin/osg-config --cflags Base System GLUT) 

LDFLAGS = $(OPENMESHLDFLAGS) $(shell $(OSGROOT)/bin/osg-config --libs Base System GLUT)


clean:
	rm -f $(OBJS) openmeshviewer.o openmeshviewer

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) -LANG:std $< $(OBJS) $(LDFLAGS) -o $@ 

