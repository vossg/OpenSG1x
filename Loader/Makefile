#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Window IntersectAction DrawAction Action Geometry Material State Misc \
						MultiThreading FieldContainer Field Base Log
REQUIRED_LNKPACKAGES := Window IntersectAction Geometry DrawAction Action Material State Misc \
						MultiThreading FieldContainer Field Base Log

#FieldContainer Field

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk


