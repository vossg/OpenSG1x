#!gmake

include ../Common/common.mk

#########################################################################
# Documenation Settings
#########################################################################

DOCBASEDIR := .
DOCCODEDIR := Code
DOCDIR     := $(DOCBASEDIR)/$(DOCCODEDIR)/$(DOC_LEVEL_NAME)

DOC_PROJECT_NAME = OpenSG
DOC_PROJECT_NUMBER = $(shell cat ../VERSION)

DOCS_BASE  := ../Source/Base/Base ../Source/Base/Field ../Source/Base/Functors		\
			  ../Source/Base/Network/Base ../Source/Base/Network/Socket			\
			  ../Source/Base/StringConversion  

DOCS_SYS   := ../Source/System/Action  										\
			  ../Source/System/Action/DrawAction  					    		\
			  ../Source/System/Action/IntersectAction  						\
			  ../Source/System/Action/RenderAction  							\
			  ../Source/System/Cluster/Base                                    \
              ../Source/System/Cluster/Server		                            \
			  ../Source/System/Cluster/Window  								\
			  ../Source/System/Cluster/Window/Base								\
			  ../Source/System/Cluster/Window/MultiDisplay						\
			  ../Source/System/Cluster/Window/SortFirst						\
			  ../Source/System/FieldContainer  								\
			  ../Source/System/FieldContainer/Impl								\
			  ../Source/System/FileIO  										\
			  ../Source/System/FileIO/Base										\
			  ../Source/System/FileIO/BIN										\
			  ../Source/System/FileIO/OBJ										\
			  ../Source/System/FileIO/OFF										\
			  ../Source/System/FileIO/OSG										\
			  ../Source/System/FileIO/RAW										\
			  ../Source/System/FileIO/WRL										\
			  ../Source/System/FileIO/ScanParseSkel							\
			  ../Source/System/Image											\
			  ../Source/System/Material										\
			  ../Source/System/NodeCores/Drawables/Base						\
			  ../Source/System/NodeCores/Drawables/Geometry					\
			  ../Source/System/NodeCores/Drawables/Misc						\
			  ../Source/System/NodeCores/Drawables/Particles					\
			  ../Source/System/NodeCores/Groups/Base							\
			  ../Source/System/NodeCores/Groups/Light							\
			  ../Source/System/NodeCores/Groups/Misc							\
			  ../Source/System/RenderingBackend								\
			  ../Source/System/State											\
			  ../Source/System/Statistics										\
			  ../Source/System/Window

DOCS_X     := ../Source/WindowSystem/X
DOCS_W32   := ../Source/WindowSystem/WIN32
DOCS_GLUT  := ../Source/WindowSystem/GLUT
DOCS_QT    := ../Source/WindowSystem/QT

DOC_LIBS   ?= $(DOCS_BASE) $(DOCS_SYS) 										\
			  $(DOCS_X) $(DOCS_W32) $(DOCS_GLUT) $(DOCS_QT) $(DOCS_PAGES)

# DOC_LIBS   := $(DOC_LIBS) mainpage.dox ../Common/dummyClasses.dox

# test setup: only do what's necessary
#DOC_LIBS   = $(DOCS_BASE) \
    	     ../Source/System/State\
    	     ../Source/System/NodeCores/Drawables/Particles\
             ../Source/System/FieldContainer\
             ../Source/System/FieldContainer/Impl

# defines for starter guide generation
DOC_LATEX ?= "NO"
DOC_INTRO ?= "Code/intro.dox"

# The separate documentation pages
DOC_PAGES  := 	../Common/dummyClasses.dox \
				Code/mainpage.dox \
				$(DOC_INTRO) \
				../Source/Base/Base/Base.dox \
				../Source/System/System.dox \
				../Source/Base/Field/Field.dox \
				../Source/Base/Functors/Functors.dox \
				../Source/Base/Network/Socket.dox \
				../Source/Base/StringConversion/StringConversion.dox \
				../Source/System/FieldContainer/FieldContainer.dox \
				../Source/System/NodeCores/NodeCores.dox \
				../Source/System/NodeCores/Groups/Groups.dox \
				../Source/System/NodeCores/Groups/Base/GroupsBase.dox \
				../Source/System/NodeCores/Groups/Light/GroupsLight.dox \
				../Source/System/NodeCores/Groups/Misc/GroupsMisc.dox \
				../Source/System/NodeCores/Drawables/Drawables.dox \
				../Source/System/NodeCores/Drawables/Base/DrawablesBase.dox \
				../Source/System/NodeCores/Drawables/Geometry/DrawablesGeometry.dox \
				../Source/System/NodeCores/Drawables/Misc/DrawablesMisc.dox \
				../Source/System/NodeCores/Drawables/Particles/DrawablesParticles.dox \
				../Source/System/State/State.dox \
				../Source/System/Material/Material.dox \
				../Source/System/Action/Action.dox \
				../Source/System/Window/Window.dox \
				../Source/System/Window/OGLExt.dox \
				../Source/WindowSystem/GLUT/WindowGlut.dox \
				../Source/WindowSystem/QT/WindowQt.dox \
				../Source/WindowSystem/X/WindowX.dox \
				../Source/WindowSystem/WIN32/WindowWin32.dox \
				../Source/System/FileIO/FileIO.dox \
				../Source/System/System.dox  \
				../Source/System/Cluster/Cluster.dox  \
				../Source/System/Image/Image.dox \
				../Source/System/RenderingBackend/RenderingBackend.dox \
				../Source/System/Statistics/Statistics.dox

DOC_IMAGE_PATHES := Images

DOC_FILES := $(DOC_LIBS) $(DOC_PAGES)

# DOC_FILES := $(DOC_PAGES) ../Source/System/NodeCores/Groups/Misc \
            ../Source/System/NodeCores/Groups/Base

# level-dependent defines
DOC_LEVEL ?= 1
DOC_LEVEL_PREDEF ?= ""
DOC_LEVEL_ENABLED ?= ""


DOC_ENV := DOC_PROJECT_NAME="$(DOC_PROJECT_NAME)" DOCDIR=$(DOCDIR) 
DOC_ENV += DOC_PROJECT_NUMBER=$(DOC_PROJECT_NUMBER) DOC_FILES="$(DOC_FILES)"
DOC_ENV += OSGPOOL="$(OSGPOOL)"  DOC_LATEX="$(DOC_LATEX)"
DOC_ENV += OSG_DOC_LEVEL="$(DOC_LEVEL)" DOC_LEVEL_PREDEF="$(DOC_LEVEL_PREDEF)"
DOC_ENV += DOC_LEVEL_ENABLED="$(DOC_LEVEL_ENABLED)" 
DOC_ENV += DOC_IMAGE_PATHES="$(DOC_IMAGE_PATHES)"


default: help

doc: userdoc

qdoc:
	make userdoc | egrep -v '^Preprocessing' | egrep -v '^Parsing' | \
			egrep -v '^Generating'

alldocs: userstarter extdoc devdoc

# Doc targets

.PHONY: dodoc dostarter
dodoc: 
	# find all headers and create dummy classes
	@rm -f ../Common/dummyClasses.list
	@touch ../Common/dummyClasses.list

	@for i in $(DOC_LIBS) ; do \
		find $$i -name '*.h' -print  >> ../Common/dummyClasses.list; \
	done

	@cat ../Common/dummyClasses.list | xargs perl ../Common/makeDummyClasses  \
				> ../Common/dummyClasses.dox

	#@rm -f ../Common/dummyClasses.list       						
	
	# find all images and convert them (if necessary)
	make DOC_IMAGE_TYPE=html images
	 
	# do doxygen
	$(DOC_ENV) /data/dirk/software/doxygen-1.2.18/bin/doxygen ../Common/Doxygen_$(BUILD_ENV).cfg -d

#	@rm -f ../Common/dummyClasses.dox 

userdoc:
	make DOC_LEVEL=1 DOC_LEVEL_NAME=user \
	    DOC_LEVEL_PREDEF= \
		DOC_LEVEL_ENABLED= dodoc

extdoc:
	make DOC_LEVEL=2 DOC_LEVEL_NAME=ext \
	    DOC_LEVEL_PREDEF="OSG_DOC_EXT" \
		DOC_LEVEL_ENABLED="ext" dodoc

devdoc:
	make DOC_LEVEL=3 DOC_LEVEL_NAME=dev \
	    DOC_LEVEL_PREDEF="OSG_DOC_EXT OSG_DOC_DEV" \
	    DOC_LEVEL_ENABLED="ext dev"  dodoc

# Starter targets

dostarter:
	make DOC_LATEX="YES" DOC_INTRO="starter.dox" $(DOC_STARTER)doc
	# link the images
	cd $(DOCDIR)/$(DOC_STARTER)/latex/ ; \
	../../../../Common/refmanToStarter refman.tex StarterGuide.tex ;  \
	latex StarterGuide && latex StarterGuide && dvips StarterGuide && \
		ps2pdf StarterGuide.ps

userstarter:
	make DOC_IMAGE_TYPE=latex images
	make DOC_STARTER="user" dostarter

extstarter:
	make DOC_IMAGE_TYPE=latex images
	make DOC_STARTER="ext" dostarter

devstarter:
	make DOC_IMAGE_TYPE=latex images
	make DOC_STARTER="dev" dostarter


# Image conversion rules

images:
	# find all used images and convert them (if necessary)
	
	rm -f imagelist
	-for i in $(DOC_PAGES) ; do \
		fgrep "\image $(DOC_IMAGE_TYPE)" $$i  | cut -d' ' -f3-3 | \
		sed -e 's|^|Images/|' >> imagelist; 	\
	done
	
	make `cat imagelist`


Images/%.eps: Images/%.gif
	convert -compress none $< PS:$@ 

Images/%.eps: Images/%.tif
	convert -compress none $< PS:$@ 

Images/%.eps: Images/%.jpg
	convert -compress none $< PS:$@ 
	# jpeg2ps gives better results, but is not usually available
	# jpeg2ps -q $< > $@ 

Images/%.eps: Images/%.fig
	fig2dev -L eps $< $@ 
	
Images/%.eps: Images/%.gpl
	gnuplot $<

Images/%.eps: Images/%.ps
	cp $< $@ 
	touch $@

Images/%.eps: Images/%.eps.gz
	gzip -dc $< > $@ 
	touch $@

Images/%.png: Images/%.fig
	fig2dev -L png $< $@ 

Images/%.png: Images/%.jpg
	convert  $< $@ 

Images/%.png: Images/%.tif
	convert  $< $@ 

Images/%.png: Images/%.eps.gz
	gzip -dc $< | convert - $@ 



help:
	@echo "Targets supported on this level:"
	@echo "================================"
	@echo 
	@echo "userdoc      create the HMTL version of the user-level docs"
	@echo "userstarter  create the PS/PDF version of the user-level docs"
	@echo "extdoc       create the HMTL version of the extender-level docs"
	@echo "extstarter   create the PS/PDF version of the extender-level docs"
	@echo "devdoc       create the HMTL version of the developer-level docs"
	@echo "devstarter   create the PS/PDF version of the developer-level docs"
	@echo "alldocs      all of the above"
	
