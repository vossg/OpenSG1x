#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

OSGMAINMAKE    = 1

SUBLIBS        = Action Action/DrawAction Base Field FieldContainer Log \
			     Loader Material Nodes State Window

#				 Image 


include $(OSGPOOL)/$(OSGCOMMON)/common.mk

SUB_TARGET =

OSG_DO_DOC     = 1
OSG_DO_INSTALL = 1

include $(OSGPOOL)/$(OSGCOMMON)/commonTopLevel.mk







