#!gmake -k -r

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Window Material State DrawAction Action Misc 	\
						MultiThreading Geometry FieldContainer Field 	\
						Log Base
REQUIRED_LNKPACKAGES := Window Material State DrawAction Action Misc 	\
						MultiThreading Geometry FieldContainer Field 	\
						Log Base

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk

REQUIRED_PACKAGES := 

