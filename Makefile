#!gmake

OS_BASE= $(shell 'CommonConf/config.guess')

include Common/common.mk

#########################################################################
# Documenation Settings
#########################################################################

DOCBASEDIR := Doc
DOCCODEDIR := Code
DOCDIR     := $(DOCBASEDIR)/$(DOCCODEDIR)

DOC_PROJECT_NAME = OpenSG
DOC_PROJECT_NUMBER = $(shell cat VERSION)

DOC_LIBS   ?= Base Field FieldContainer Image Loader Log Material 	\
              MultiThreading Nodes/OSGNodes.doxygen Nodes/Geometry 	\
			  Nodes/Light 											\
              Nodes/Misc State Window 

DOC_LIBS   := $(DOC_LIBS) mainpage.doxygen Common/dummyClasses.doxygen

#DOC_LIBS   = Base

DOC_PATTERN = OSG*.cpp OSG*.hpp OSG*.inl OSG*.doxygen

DOC_ENV := DOC_PROJECT_NAME="$(DOC_PROJECT_NAME)" DOCDIR=$(DOCDIR) 
DOC_ENV += DOC_PROJECT_NUMBER=$(DOC_PROJECT_NUMBER) DOC_LIBS="$(DOC_LIBS)"
DOC_ENV += DOC_PATTERN="$(DOC_PATTERN)"
DOC_ENV += OSGPOOL="$(OSGPOOL)"

# map some common targets into the Builds/ directory for the current system
# NOTE: this will fail if there are multiple directories for one system (i.e.
# if multiple compilers have been used)

default:
	$(MAKE) -C Builds/${OS_BASE}* 
        
opt:
	$(MAKE) -C Builds/${OS_BASE}* opt

install:
	cd Builds/${OS_BASE}* && $(MAKE) install

clean:
	cd Builds/${OS_BASE}* && $(MAKE) clean

ctags:
	ctags -R --c-types=+c --totals -h +.inl --langmap=c++:.h.hpp.cpp.cxx.inl .

etags:
	etags -R --c-types=+c --totals -h +.inl --langmap=c++:.h.hpp.cpp.cxx.inl .

help: 
	@echo "Most targets are only supported inside the Builds/* directories!"
	@echo "Go there and type 'make help' to get a list of possible targets."
	@echo
	@echo "Targets supported on this level:"
	@echo "================================"
	@echo 
	@echo "doc          run doxygen to create the documentation"
	@echo "fcdToBase    run through the tree and regenerate all the Base sources"
	@echo "<default>    go into the Builds directory and call $(MAKE)"
	@echo "install      go into the Builds directory and call $(MAKE) install"
	@echo "clean        go into the Builds directory and call $(MAKE) clean"
	@echo "ctags        create tags file using ctags"
	@echo "etags        create tags file using etags"


.PHONY: doc
doc: 
	# find all headers and create dummy classes
	@rm -f Common/dummyClasses.doxygen Common/dummyClasses.list
	@touch Common/dummyClasses.doxygen Common/dummyClasses.list

	@for i in $(DOC_LIBS) ; do 							  			\
		find $$i -name '*.h' -print  >> Common/dummyClasses.list; 	\
	done

	@perl Common/makeDummyClasses 			  					\
		`cat Common/dummyClasses.list` 		  					\
                 > Common/dummyClasses.doxygen

	@rm -f Common/dummyClasses.list       						

	# do doxygen
	$(DOC_ENV) doxygen Common/Doxygen_$(OS_BASE).cfg -d


#	@rm -f Common/dummyClasses.doxygen  


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
