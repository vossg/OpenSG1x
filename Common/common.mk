
#########################################################################
# Get Ostype
#########################################################################

OS      := $(shell echo `uname`)
OS_TYPE := $(shell echo `uname`_`uname -r`_`uname -p`)

ifeq ($(OS), CYGWIN_NT-4.0)
OS      := NT40
OS_TYPE := NT40
endif

OS_BASE := $(OS)

PROC    := $(shell uname -m)

#########################################################################
# Set Filenames
#########################################################################

COMMONPATH         = $(OSGPOOL)/$(OSGCOMMON)

COMMONINCLUDE      = common
DEFAULTRULES       = DefaultRules

SYSTEMS            = IRIX64 Linux SunOS

OSGCOMPEXT        ?=

OS                := $(OS)$(OSGCOMPEXT)

INTERNALTARGETS    = SubLib dbg opt dbgclean optclean clean 		\
					 dbgClean optClean Clean distclean initclean	\
					 init depend dbgdepend optdepend html doc

COMMONINCLUDE     := $(COMMONPATH)/$(COMMONINCLUDE)$(OS).mk

DEFAULTRULES      := $(COMMONPATH)/$(DEFAULTRULES)

SYSTEMDIRECTORIES  = directories

SYSTEMDIRECTORIES := $(COMMONPATH)/$(SYSTEMDIRECTORIES)$(OS).mk

DBG           ?= DBG

SUB_MAKE      := gmake -r -k 
SUB_MAKEFILE  := Makefile

DEP_MAKEFILE   = Makefile$(OS)$(DBG).dep

SUBLIBTARGETS  := $(addsuffix .src, $(SUBLIBS))

SUBTESTTARGETS := $(addsuffix .prj, $(TESTS))

SYSDEP     = $(OS)
OBJDIRBASE = obj.$(OS)
OBJDIR     = $(OBJDIRBASE)$(DBG)

CURRENTDIR := $(notdir $(shell pwd))

OBJEXT       :=  o
LIBEXT       :=  a
OBJNAMEFLAG  := -o
COMPONLYFLAG := -c

#########################################################################
# Extract object|source|header filenames from directories
#########################################################################


getAllMachineDependendSource = $(wildcard OSGMD*.s) $(wildcard OSGMD*.cpp)
getMachineDependendSource    = $(filter-out OSGMD$(OS)%, \
	$(call getAllMachineDependendSource))

getAllSourceFiles    = $(wildcard *.cpp) $(wildcard *.s)
filterMDSourceFiles  = $(filter-out $(call getMachineDependendSource),	\
	$(call getAllSourceFiles))

getSourceFiles       = $(filter-out test%.cpp,$(call filterMDSourceFiles))

getTestSourceFiles   = $(wildcard test*.cpp)

getSourceHeaderFiles = $(wildcard *.h) 

addObjectDir      = $(if $(OBJDIR),$(addprefix $(OBJDIR)/, $(1)),$(1))

ifneq ($(OBJDIR),)
cppSourceToObject = $(patsubst %.cpp,%.$(OBJEXT), $(call addObjectDir, $(1)))
asSourceToObject  = $(patsubst %.s,%.$(OBJEXT), $(1))
else
cppSourceToObject = $(patsubst %.cpp,%.$(SYSDEP).$(OBJEXT), \
					  $(call addObjectDir, $(1)))
asSourceToObject  = $(patsubst %.s,%.$(SYSDEP).$(OBJEXT), $(1))
endif

cnvSourceToObject = $(call asSourceToObject, $(call cppSourceToObject,$(1)))

addSysDep         = $(addsuffix .$(SYSDEP), $(1))


#########################################################################
# Create Libname
#########################################################################

LIBPRAEFIX = $(if $(OBJDIR),$(OBJDIR)/lib,lib)

createSublibName = $(addprefix $(LIBPRAEFIX), \
	               $(addsuffix .$(SYSDEP).$(LIBEXT), $(CURRENTDIR)))

createSublibLink = $(addprefix lib, \
	               $(addsuffix .$(SYSDEP).$(LIBEXT), $(CURRENTDIR)))

#########################################################################
# Create Package Include
#########################################################################

includePackages = $(addprefix $(OSGPOOL)/$(OSGCOMMON)/common,\
				  $(addsuffix .mk,$(1)))

extractTestProgs = $(basename $(1))

#########################################################################
# Documenation Settings
#########################################################################

DOCBASEDIR := Doc
DOCCODEDIR := Code
DOCDIR     := $(DOCBASEDIR)/$(DOCCODEDIR)

DOC_PROJECT_NAME   = OpenSG
DOC_PROJECT_NUMBER = 0.0.1

DOC_HTML  = NO
DOC_LATEX = NO
DOC_MAN   = NO

DOC_LIBS   = Base Field FieldContainer Action Log Nodes/Geometry
DOC_PATTERN = OSG*.cpp OSG*.h OSG*.inl 

DOC_ENV := DOC_PROJECT_NAME=$(DOC_PROJECT_NAME) DOCDIR=$(DOCDIR) 
DOC_ENV += DOC_PROJECT_NUMBER=$(DOC_PROJECT_NUMBER) DOC_LIBS="$(DOC_LIBS)"
DOC_ENV += DOC_PATTERN="$(DOC_PATTERN)"

-include .lastdbg




