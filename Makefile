#!gmake

OS_BASE= $(shell 'CommonConf/config.guess')

#########################################################################
# Documenation Settings
#########################################################################

DOCBASEDIR := Doc
DOCCODEDIR := Code
DOCDIR     := $(DOCBASEDIR)/$(DOCCODEDIR)

DOC_PROJECT_NAME = OpenSG
DOC_PROJECT_NUMBER = "0.2 beta"

DOC_LIBS   ?= Base Field FieldContainer Image Loader Log Material 	\
              MultiThreading Nodes/OSGNodes.doxygen Nodes/Geometry 	\
			  Nodes/Light 											\
              Nodes/Misc State Window mainpage.doxygen


#DOC_LIBS   = Window

DOC_PATTERN = OSG*.cpp OSG*.hpp OSG*.inl OSG*.doxygen

DOC_ENV := DOC_PROJECT_NAME="$(DOC_PROJECT_NAME)" DOCDIR=$(DOCDIR) 
DOC_ENV += DOC_PROJECT_NUMBER=$(DOC_PROJECT_NUMBER) DOC_LIBS="$(DOC_LIBS)"
DOC_ENV += DOC_PATTERN="$(DOC_PATTERN)"
DOC_ENV += OSGPOOL="$(OSGPOOL)"

all:
	@echo "We finally switched to configure, please have a look at INSTALL"
	@echo "and using_configure how to use it"
	@echo 
	@echo "Use make help to see all available targets at every level"

help: 
	@echo "Targets supported on this level:"
	@echo "================================"
	@echo 
	@echo "doc          run doxygen to create the documentation"
	@echo "fcdToBase    run through the tree and regenerate all the Base sources"


.PHONY: doc
doc: 
	$(DOC_ENV) doxygen Common/Doxygen_$(OS_BASE).cfg -d


fcdToBase:
	@CURRDIR=`pwd`;															\
	FCDEDIT=$${CURRDIR}/Tools/fcdEdit/fcdEdit;								\
	for i in `find .														\
		\( -type d \( -name CVS -o -name Test -o -name Builds -o			\
		   -name Tools -o -name examples -o -name '*/.*' \) -prune \) 		\
		-o -type f -name '*\.fcd' -print` ;									\
	do																		\
		echo $$i ;															\
		cd `dirname $$i` ;													\
		$$FCDEDIT -b `basename $$i`;										\
		cd $$CURRDIR ;														\
	done;																	\
