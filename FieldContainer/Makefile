#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Base Field Log
REQUIRED_LNKPACKAGES := Base Field Log

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk
