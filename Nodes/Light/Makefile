#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Action DrawAction Geometry Misc FieldContainer 	\
						Field Log Base 
REQUIRED_LNKPACKAGES := Action DrawAction Geometry Misc FieldContainer 	\
						Field Log Base 

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk



