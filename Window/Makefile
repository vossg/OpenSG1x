#!gmake -r -k

OSGCOMMON     ?= Common
OSGCOMMONPACK ?= CommonPackages

ifndef OSGPOOL
OSGPOOL         = $(shell expr `pwd` : '\(.*/OpenSG\).*' )
endif

REQUIRED_INCPACKAGES := Loader Light  Misc Geometry IntersectAction 	\
						DrawAction Action MultiThreading 				\
						Image FieldContainer Field Base Log
REQUIRED_LNKPACKAGES := Loader Action Misc Geometry Material			\
						MultiThreading  FieldContainer 					\
						Image Field Log State Base IntersectAction 		\
						DrawAction Action Light 

include $(OSGPOOL)/$(OSGCOMMON)/common.mk
include $(OSGPOOL)/$(OSGCOMMON)/commonSub.mk

DEFINES += -DQT_CLEAN_NAMESPACE

$(OBJDIRBASE)$(DBG)/testWindowMTQT_qt.o: $(OBJDIRBASE)$(DBG)/testWindowMTQT_qt_moc.cpp
$(OBJDIRBASE)$(DBG)/testWindowQT_qt.o: $(OBJDIRBASE)$(DBG)/testWindowQT_qt_moc.cpp


