#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := DrawAction Action Geometry Material State Misc \
						FieldContainer Field Base Log
REQUIRED_LNKPACKAGES := Geometry DrawAction Action Material State Misc \
						FieldContainer Field Base Log

#FieldContainer Field

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk


