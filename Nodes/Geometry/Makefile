#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Material State Misc IntersectAction DrawAction Action FieldContainer Field Base Log
REQUIRED_LNKPACKAGES := Material State Misc IntersectAction DrawAction Action Field Base FieldContainer Log

# 	\
						Field FieldContainer Base Log

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk

