#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Loader Light  Misc Geometry IntersectAction DrawAction Action \
						FieldContainer Field Base Log
REQUIRED_LNKPACKAGES := Loader Action Misc Geometry Material FieldContainer \
						Field Log State Base IntersectAction DrawAction Action Light 
#Loader Loader
include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk

