#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

OSGMAINMAKE    = 1

SUBLIBS        = Action Action/DrawAction Action/IntersectAction Base Field FieldContainer Log \
				 Image Material Nodes State Window Loader

TAGS_EXCLUDEDIRS := Action/DrawAction


include $(OSGPOOL)/$(OSGCOMMON)/common.mk

SUB_TARGET =

OSG_DO_DOC     = 1
OSG_DO_INSTALL = 1

include $(OSGPOOL)/$(OSGCOMMON)/commonTopLevel.mk







