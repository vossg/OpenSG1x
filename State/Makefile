#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Window IntersectAction DrawAction Action Misc Image FieldContainer \
						Field Log Base 
REQUIRED_LNKPACKAGES := Window IntersectAction DrawAction Action Misc Image FieldContainer \
						Field Log Base 

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk


