#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := FieldContainer Field Base Log
REQUIRED_LNKPACKAGES := FieldContainer Field Base Log

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk

# include the TIFF and JPEG
#SOURCE_DEFINES += -DTIFF_LIB -DJPEG_LIB
