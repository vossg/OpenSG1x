#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Window State DrawAction Action Geometry Misc FieldContainer \
						Field Log Base 
REQUIRED_LNKPACKAGES := Window State DrawAction Action Geometry Misc FieldContainer \
						Field Log Base 

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk


