#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Light Loader Misc Geometry DrawAction Action \
						FieldContainer Field Base Log
REQUIRED_LNKPACKAGES := Action Misc Loader Geometry FieldContainer Field Log	\
						Base DrawAction Action Light    						 

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk

