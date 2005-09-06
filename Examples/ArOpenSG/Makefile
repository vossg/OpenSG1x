# trivial makefile for OpenSG example

SRCS := V4LFrameGrabber.cpp MemoryManager.cpp

OBJS := $(SRCS:.cpp=.o)

ARTOOLKITPLUS := ARToolKitPlus

# set the path to the installed OpenSG root directory here
# if you installed in /usr/local:
# OSGROOT := /usr/local
# use this if you installed in Builds/*/
OSGROOT := $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)


CC := $(shell $(OSGROOT)/bin/osg-config --compiler)

CCFLAGS = -I. -I$(ARTOOLKITPLUS)/include $(shell $(OSGROOT)/bin/osg-config --cflags Base System GLUT)

LDFLAGS = $(shell $(OSGROOT)/bin/osg-config --libs Base System GLUT)


ArOpenSG: $(OBJS) main.o
	$(CC) -LANG:std  $(OBJS) main.o $(LDFLAGS) -o $@ 

clean:
	rm -f $(OBJS) main.o

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) -LANG:std $< $(OBJS) $(LDFLAGS) -o $@ 

