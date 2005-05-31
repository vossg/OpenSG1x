# trivial makefile for OpenSG example

SRCS := Nodes.cpp TestWindow.cpp Test.cpp Image.cpp python_wrapper.cpp

OBJS := $(SRCS:.cpp=.o)

OPT :=  --dbg
# set the path to the installed OpenSG root directory here
# if you installed in /usr/local:
# OSGROOT := /usr/local
# use this if you installed in Builds/*/
#OSGROOT := $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)


BOOST_ROOT=/usr
OSGROOT := ../../Builds/i686-pc-linux-gnu-g++

CC := $(shell $(OSGROOT)/bin/osg-config --compiler)

CCFLAGS = -I. -I$(BOOST_ROOT) -I/usr/include/python2.3 \
          -DBOOST_PYTHON_DYNAMIC_LIB \
        $(shell $(OSGROOT)/bin/osg-config --cflags $(OPT) Base System GLUT)

LDFLAGS = $(shell $(OSGROOT)/bin/osg-config --libs $(OPT) Base System GLUT) \
        -L$(BOOST_ROOT)/lib -L. -lboost_python

default: osgbench.so

clean:
	rm -f *.o osgbench.so

osgbench.so: $(OBJS) $(SRCS)

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) $< $(OBJS) $(LDFLAGS) -o $@ 


%.so:
	$(CC) -shared $(OBJS) $(LDFLAGS) -o $@ 


Nodes.o: Nodes.h Nodes.cpp
TestWindow.o: TestWindow.h TestWindow.cpp
Test.o: Test.h Test.cpp
python_wrapper.o: python_wrapper.cpp Nodes.h TestWindow.h Test.h Image.h
