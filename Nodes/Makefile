#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

OSGMAINMAKE    = 1

SUBLIBS        = Geometry Light Misc

include $(OSGPOOL)/$(OSGCOMMON)/common.mk

SUB_TARGET =

OSG_DO_DOC     = 0
OSG_DO_INSTALL = 0

include $(OSGPOOL)/$(OSGCOMMON)/commonTopLevel.mk
