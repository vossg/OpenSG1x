#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Window Material Image State Misc IntersectAction 			\
						DrawAction Action MultiThreading FieldContainer 	\
						Field Base Log
REQUIRED_LNKPACKAGES := Window Material Image State Misc IntersectAction 			\
						DrawAction Action MultiThreading Field Base 		\
						FieldContainer Log

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk

