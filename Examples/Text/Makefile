# trivial makefile for OpenSG example

SRCS := $(wildcard OSG*.cpp)

OBJS := $(SRCS:.cpp=.o)

# set the path to the installed OpenSG root directory here
# if you installed in /usr/local:
# OSGROOT := /usr/local
# use this if you installed in Builds/*/
OSGROOT := $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)


CC := $(shell $(OSGROOT)/bin/osg-config --compiler)

CCFLAGS = -I/home/reiners/include/FTGL -I/usr/include/freetype2 -I. $(shell $(OSGROOT)/bin/osg-config --cflags Base System GLUT) 

LDFLAGS = -L/home/reiners/lib -lftgl -lfreetype -lOpenMesh_Core $(shell $(OSGROOT)/bin/osg-config --libs Base System GLUT)


testText: $(OBJS) testText.o 

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) -LANG:std $< $(OBJS) $(LDFLAGS) -o $@ 

