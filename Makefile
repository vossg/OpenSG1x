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
              Nodes/Misc State Window mainpage.doxygen 				\
              Common/dummyClasses.doxygen


#DOC_LIBS   = Window

DOC_PATTERN = OSG*.cpp OSG*.hpp OSG*.inl OSG*.doxygen

DOC_ENV := DOC_PROJECT_NAME="$(DOC_PROJECT_NAME)" DOCDIR=$(DOCDIR) 
DOC_ENV += DOC_PROJECT_NUMBER=$(DOC_PROJECT_NUMBER) DOC_LIBS="$(DOC_LIBS)"
DOC_ENV += DOC_PATTERN="$(DOC_PATTERN)"
DOC_ENV += OSGPOOL="$(OSGPOOL)"

all:
	@echo "We finally switched to configure, please have a look at INSTALL"
	@echo "and using_configure how to use it"
	@echo "################################################"
	@echo "Only 'make doc' is still supportet at this level"
	@echo "################################################"

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
	@rm -f Common/dummyClasses.doxygen  

