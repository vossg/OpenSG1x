# trivial makefile for OpenSG example

SRCS := OSGCubes.cpp OSGCubesBase.cpp

OBJS := $(SRCS:.cpp=.o)

# set the path to the installed OpenSG root directory here
# if you installed in /usr/local:
# OSGROOT := /usr/local
# use this if you installed in Builds/*/
OSGROOT := $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)


CC := $(shell $(OSGROOT)/bin/osg-config --compiler)

CCFLAGS = -I. $(shell $(OSGROOT)/bin/osg-config --cflags Base System GLUT) 

LDFLAGS = $(shell $(OSGROOT)/bin/osg-config --libs Base System GLUT)


testCubes: $(OBJS) testCubes.o 

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) -LANG:std $< $(OBJS) $(LDFLAGS) -o $@ 

