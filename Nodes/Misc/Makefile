#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Geometry Action IntersectAction DrawAction State FieldContainer 	\
						Field Base Log 
REQUIRED_LNKPACKAGES := Geometry Action IntersectAction DrawAction State FieldContainer 	\
						Field Base Log 

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk



