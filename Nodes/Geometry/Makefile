#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Window Material State Misc IntersectAction DrawAction Action FieldContainer Field Base Log
REQUIRED_LNKPACKAGES := Window Material State Misc IntersectAction DrawAction Action Field Base FieldContainer Log

# 	\
						Field FieldContainer Base Log

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk

