#!gmake -k -r

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Misc FieldContainer Field Log Base Action Window	\
						MultiThreading Misc Geometry
REQUIRED_LNKPACKAGES := Misc FieldContainer Field Log Base Action Window	\
						MultiThreading Misc Geometry

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk

REQUIRED_PACKAGES := 

