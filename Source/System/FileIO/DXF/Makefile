# trivial makefile for OpenSG tutorials

# use debug or opt libs?
LIBTYPE := dbg

# where to find GLUT?
# You can ignore this on Linux, it's in the system pathes.
SYSTEM := $(shell uname)
GLUTROOT := /igd/a4/software/$(SYSTEM)/

# set the path to the installed OpenSG root directory here
# if you installed in /usr/local:
# OSGROOT := /usr/local
# use this if you just unpacked the binary distribution
#OSGROOT := /igd/a4/projects/OpenSG/OpenSG-1.1.0/Linux
#OSGROOT := /igd/a4/temp/vd3/OpenSG-ehnes/Builds/i686-pc-linux-gnu-g++
OSGROOT := /igd/a4/projects4/VirtualHuman/OpenSG/Builds/i686-pc-linux-gnu-g++
#QTDIR :=	/igd/a4/software/Linux/packages/qt-3
OBJDIR = obj


# Var settings
MOC = $(shell $(OSGROOT)/bin/osg-config --moc)
CC = $(shell $(OSGROOT)/bin/osg-config --compiler)

#CCFLAGS = -I$(OSGROOT)/include \
#  $(shell $(OSGROOT)/bin/osg-config --$(LIBTYPE) --cflags Base System GLUT QT)

#LDFLAGS = -L$(OSGROOT)/lib/$(LIBTYPE) \
#  $(shell $(OSGROOT)/bin/osg-config --$(LIBTYPE) --libs Base System GLUT QT)

CCFLAGS = -I. -I$(GLUTROOT)/include -I$(OSGROOT)/include/OpenSG \
		  $(shell $(OSGROOT)/bin/osg-config --$(LIBTYPE) --cflags Base System GLUT)

LDFLAGS = -L$(GLUTROOT)/lib -L$(OSGROOT)/lib/$(LIBTYPE) \
		  $(shell $(OSGROOT)/bin/osg-config --$(LIBTYPE) --libs Base System GLUT)


# all tutorials in this directory

TUTS := $(wildcard *.cpp)
#TARGET := $(TUTS:.cpp=)
TARGET := testDXFLoader

MOCINPUTS  := $(shell grep -s -l Q_OBJECT *.h)
MOCSOURCES := $(MOCINPUTS:%.h=moc_%.cpp)

SOURCES := $(wildcard OSG*.cpp) $(MOCSOURCES)
OBJECTS := $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# program dependencies

default:	$(TARGET)

-include $(OBJDIR)/$(TARGET).d

# hview: $(OBJECTS)
# 	$(CC) -o $@ $^ $(LDFLAGS)

# service dependencies

.PHONY: clean Clean depend

clean:
	rm -fr $(OBJECTS) ii_files

Clean: clean
	rm -fr $(TARGET) $(OBJDIR)/$(TARGET).d
	rm -rf html latex

depend:
	$(CC) $(CCFLAGS) -MM $(SOURCES) $(TARGET).cpp > $(OBJDIR)/$(TARGET).d

# build rules

moc_%.cpp: %.h
	$(MOC) -o $@ $<

$(OBJDIR)/%.o: %.cpp
	$(CC) -c $(CCFLAGS) $< -o $@

%: $(OBJDIR)/%.o


%: %.cpp
	$(CC) $(CCFLAGS) $< $(LDFLAGS) -o $@

$(TARGET):  $(OBJECTS) $(TARGET).cpp
	$(CC) $(CCFLAGS) $^ $(LDFLAGS) -o $@
