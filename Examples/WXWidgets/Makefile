# trivial makefile for OpenSG example

# set the path to the installed OpenSG root directory here
# if you installed in /usr/local:
# OSGROOT := /usr/local
# use this if you installed in Builds/*/
OSGROOT := $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)

# wxWidgets options

WXROOT := /home/reiners

# Program rules

wxOpenSGtest: wxOpenSGtest.o 


# Rules

CC := $(shell $(OSGROOT)/bin/osg-config --compiler)

CCFLAGS = -I. $(shell $(WXROOT)/bin/wx-config --cppflags) $(shell $(OSGROOT)/bin/osg-config --cflags Base System) 

LDFLAGS =  $(shell $(WXROOT)/bin/wx-config --ldflags --libs=std,gl) $(shell $(OSGROOT)/bin/osg-config --libs Base System)


clean:
	rm -f $(OBJS) wxOpenSGtest.o wxOpenSGtest

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) -LANG:std $< $(OBJS) $(LDFLAGS) -o $@ 

