# Very general use makefile for openSG Programs 

# use debug or opt libs?
LIBTYPE ?= dbg

# set the path to the installed osg-config executable here
# e.g. if you installed in /usr/local
OSGCONFIG := /usr/local/bin/osg-config

CC = "$(shell $(OSGCONFIG) --compiler)"

CCFLAGS = $(shell $(OSGCONFIG) --cflags --$(LIBTYPE) Base System GLUT)

LDFLAGS = $(shell $(OSGCONFIG) --libs --$(LIBTYPE) Base System GLUT)


# all tutorials in this directory

TUTS :=  $(wildcard [0-9][0-9]*.cpp) 
PROGS := $(TUTS:.cpp=) 

# program dependencies

default:	$(PROGS)

# make rules

.PHONY: clean Clean

clean:
	rm -f  *.o 

Clean: clean
	rm -f $(PROGS) 

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) -o $@ $< $(LDFLAGS)

%: %.cpp
	$(CC) $(CCFLAGS) $< $(LDFLAGS) -o $@ 
