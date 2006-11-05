# trivial makefile for OpenSG example

# Config: where to find ANN and METIS
ANN_INC := ann_1.1/include
ANN_LIB := ann_1.1/lib
METIS_INC := metis-4.0/Lib
METIS_LIB := metis-4.0

# set the path to the installed OpenSG root directory here
# if you installed in /usr/local:
# OSGROOT := /usr/local
# use this if you installed in Builds/*/
OSGROOT := $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)

LIB_TYPE := --opt
#LIB_TYPE := --dbg


SRCS := VGrid.cpp BBoxGeoRec.cpp SplitGeoRec.cpp RAFile.cpp \
        OOCPLYFeeder.cpp OOCFeeder.cpp OOCOSGFeeder.cpp OOCSMBFeeder.cpp \
        smreader_smb.cpp MaterialPool.cpp

OBJS := $(SRCS:.cpp=.o)
HDRS := $(wildcard *.h *.inl)


CC := $(shell $(OSGROOT)/bin/osg-config --compiler)

CCFLAGS = -Di386 -I. $(shell $(OSGROOT)/bin/osg-config $(LIB_TYPE) --cflags Base System) -I${ANN_INC} -I${METIS_INC}

LDFLAGS = -L${ANN_LIB} -lANN -L${METIS_LIB} -lmetis $(shell $(OSGROOT)/bin/osg-config $(LIB_TYPE) --libs Base System)


oocproxybuilder: ann_1.1 metis-4.0 $(OBJS) oocproxybuilder.o

clean:
	rm -f $(OBJS) oocproxybuilder.o

# Libs rules

ann_1.1: ann_1.1_patch_01.tar.gz
	tar xfz ann_1.1_patch_01.tar.gz
	make -C ann_1.1 linux-g++

metis-4.0: metis-4.0.tar.gz
	tar xfz metis-4.0.tar.gz
	make -C metis-4.0
	
# Basic rules

%.o: %.cpp $(HDRS)
	$(CC) -c $(CCFLAGS) $<

%.o: %.c $(HDRS)
	gcc -c $(CCFLAGS) $<

%: %.o
	$(CC) $(OBJS) $< $(LDFLAGS) -o $@ 

