#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Light Loader Misc Geometry DrawAction Action \
						FieldContainer Field Base Log
REQUIRED_LNKPACKAGES := Light Loader Misc Geometry DrawAction Action \
						FieldContainer Field Base Log

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk

