#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Action DrawAction Geometry Misc FieldContainer 	\
						MultiThreading Field Log Base Material
REQUIRED_LNKPACKAGES := Action DrawAction Misc FieldContainer 	\
						MultiThreading Field Log Base Geometry 

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk



