
#########################################################################
# Get Ostype
#########################################################################

OS      := $(shell echo `uname`)
OS_TYPE := $(shell echo `uname`_`uname -r`_`uname -p`)

OS_BASE := $(OS)

ifeq ($(OS), IRIX64)
OS_BASE := IRIX
endif

ifeq ($(OS), CYGWIN_NT-4.0)
OS      := NT40
OS_TYPE := NT40
OS_BASE := NT
endif

ifeq ($(OS), CYGWIN_NT-5.0)
OS      := NT50
OS_TYPE := NT50
OS_BASE := NT
endif

ifndef RECURSE
ifeq ($(OS_BASE), NT)
MULTIPASS = 1
endif
endif

PROC    := $(shell uname -m)

#########################################################################
# Set Filenames
#########################################################################

COMMONPATH         = $(OSGPOOL)/$(OSGCOMMON)

COMMONINCLUDE      = common
DEFAULTRULES       = DefaultRules

SYSTEMS            = IRIX Linux SunOS

COMPEXT           ?=

OS                := $(OS)$(OSGCOMPEXT)

INTERNALTARGETS    = SubLib dbg opt dbgclean optclean clean 			\
					 dbgClean optClean Clean distclean initclean		\
					 init depend dbgdepend optdepend html doc printinfo	\
					 %.$(OBJEXT) %.$(LIBEXT) %.cpp %.h %.inl %.y %.l

COMMONINCLUDE     := $(COMMONPATH)/$(COMMONINCLUDE)$(OS).mk

DEFAULTRULES      := $(COMMONPATH)/$(DEFAULTRULES)

SYSTEMDIRECTORIES  = directories

SYSTEMDIRECTORIES := $(COMMONPATH)/$(SYSTEMDIRECTORIES)$(OS).mk

MAKEOPTCMDGOAL    := $(findstring opt,$(MAKECMDGOALS))
MAKEDBGCMDGOAL    := $(findstring dbg,$(MAKECMDGOALS))

ifeq ($(MAKEOPTCMDGOAL),opt)
DBG := OPT
endif

ifeq ($(MAKEDBGCMDGOAL),dbg)
DBG := DBG
endif

DBG           ?= DBG

SUB_MAKE      := gmake -r -k
SUB_MAKEFILE  := Makefile

DEP_MAKEFILE   = Makefile$(OS)$(DBG).dep

SUBLIBTARGETS  := $(addsuffix .src, $(SUBLIBS))

ifneq ($(SUBLIBS_$(OS_BASE)),)
SUBLIBTARGETS  += $(addsuffix .src, $(SUBLIBS_$(OS_BASE)))
endif


SUBTESTTARGETS := $(addsuffix .prj, $(TESTS))

SYSDEP     = $(OS)
OBJDIRBASE = obj.$(OS)
OBJDIR     = $(OBJDIRBASE)$(DBG)

PROJECTPSD ?= OSG

ifndef PACKAGENAME
CURRENTDIR := $(notdir $(shell pwd))
else
CURRENTDIR := $(PACKAGENAME)
endif

OBJEXT       :=  o
LIBEXT       :=  a
SOEXT        := so
EXEEXT       := 
OBJNAMEFLAG  := -o
COMPONLYFLAG := -c 

.SUFFIXES:

#########################################################################
# Extract object|source|header filenames from directories
#########################################################################

getAllMachineDependendSource = $(wildcard OSGMD*.s) $(wildcard OSGMD*.cpp)
getMachineDependendSource    = $(filter-out OSGMD$(OS)%, \
	$(call getAllMachineDependendSource))

getAllSourceFiles    = $(wildcard *.cpp) $(wildcard *.c) $(wildcard *.s)
filterMDSourceFiles  = $(filter-out $(call getMachineDependendSource),	\
	$(call getAllSourceFiles))

getSourceFiles       = $(filter-out test%.cpp,$(call filterMDSourceFiles))

getTestSourceFiles   = $(wildcard test*.cpp)

getSourceHeaderFiles = $(wildcard *.h) 

addObjectDir      = $(if $(OBJDIR),$(addprefix $(OBJDIR)/, $(1)),$(1))

ifneq ($(OBJDIR),)
cppSourceToObject = $(patsubst %.cpp,%.$(OBJEXT), $(call addObjectDir, $(1)))
cSourceToObject   = $(patsubst %.c,%.$(OBJEXT), $(1))
asSourceToObject  = $(patsubst %.s,%.$(OBJEXT), $(1))
else
cppSourceToObject = $(patsubst %.cpp,%.$(SYSDEP).$(OBJEXT), \
					  $(call addObjectDir, $(1)))
asSourceToObject  = $(patsubst %.s,%.$(SYSDEP).$(OBJEXT), $(1))
endif

cnvCCPPSToObj     = $(call cSourceToObject, $(call cppSourceToObject,$(1)))
cnvSourceToObject = $(call asSourceToObject, $(call cnvCCPPSToObj,$(1)))

addSysDep         = $(addsuffix .$(SYSDEP), $(1))

CPL1 := PROJLIBS_PREFLAGS_
CPL2 := PROJLIBS_FILE_
CPL3 := PROJLIBS_POSTFLAGS_

createProjLibs    = $(foreach package,\
	$(1), $($(CPL1)$(package)) $($(CPL2)$(package)) $($(CPL3)$(package)))

convWinUnix       = $(if $(strip $(1)),$(shell cygpath -u $(1)),)

ifeq ($(OS_BASE), NT)
createProjLibsDep = $(foreach package, $(1), \
					$(call convWinUnix, $($(CPL2)$(package))))
else
createProjLibsDep = $(foreach package, $(1), $($(CPL2)$(package)))
endif

ifeq ($(OS_BASE), NT)

buildIncPath      = $(INCPRE)"$(shell cygpath -w $(1))"
buildLibName      = "$(shell cygpath -w $(1))"

else

buildIncPath      = $(INCPRE)$(1) 
buildLibName      = $(1)

endif

#########################################################################
# Create Libname
#########################################################################

ifeq ($(OS_BASE), NT)

LIBPRAEFIX = $(if $(OBJDIR),$(OBJDIR)\\lib$(PROJECTPSD),lib$(PROJECTPSD))

else

LIBPRAEFIX = $(if $(OBJDIR),$(OBJDIR)/lib$(PROJECTPSD),lib$(PROJECTPSD))

endif

createSublibName = $(addprefix $(LIBPRAEFIX), \
	               $(addsuffix .$(LIBEXT), $(CURRENTDIR)))

createSublibLink = $(addprefix lib, \
	               $(addsuffix .$(SYSDEP).$(LIBEXT), $(CURRENTDIR)))

createSubSoName  = $(addprefix $(LIBPRAEFIX), \
	               $(addsuffix .$(SOEXT), $(CURRENTDIR)))

createSubSoLink  = $(addprefix lib, \
	               $(addsuffix .$(SYSDEP).$(SOEXT), $(CURRENTDIR)))

#########################################################################
# Create Package Include
#########################################################################

includePackages = $(addprefix $(OSGPOOL)/$(OSGCOMMONPACK)/common,\
				  $(addsuffix .mk,$(1)))

includePackagesProj = \
	$(addprefix $($(PROJECTPSD)POOL)/$(OSGCOMMONPACK)/common,\
	      		$(addsuffix .mk,$(1)))

verifyIncPackages = $(foreach file,$(1),$(wildcard $(file)))

extractTestProgs = $(basename $(1))

#########################################################################
# Documenation Settings
#########################################################################

DOCBASEDIR := Doc
DOCCODEDIR := Code
DOCDIR     := $(DOCBASEDIR)/$(DOCCODEDIR)

DOC_PROJECT_NAME = OpenSG
DOC_PROJECT_NUMBER = 0.1

DOC_HTML  = NO
DOC_LATEX = NO
DOC_MAN   = NO

DOC_LIBS   ?= Base Communication DataStorage Field Log Math \
			  PluginsInternal PluginsExternal

DOC_PATTERN = OSG*.cpp OSG*.hpp OSG*.inl 

DOC_ENV := DOC_PROJECT_NAME="$(DOC_PROJECT_NAME)" DOCDIR=$(DOCDIR) 
DOC_ENV += DOC_PROJECT_NUMBER=$(DOC_PROJECT_NUMBER) DOC_LIBS="$(DOC_LIBS)"
DOC_ENV += DOC_PATTERN="$(DOC_PATTERN)"

-include .lastdbg




