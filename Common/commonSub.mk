
include $(SYSTEMDIRECTORIES)
include $(COMMONINCLUDE)

#########################################################################
# Make goal
#########################################################################

MAKECMDGOAL  := $(filter-out $(INTERNALTARGETS),$(MAKECMDGOALS))

#########################################################################
# Set Sources | Headers | Objects | Sublib
#########################################################################

getBisonSources  = $(wildcard *.y)
getFlexSources   = $(wildcard *.l)
getQTSources     = $(wildcard *_qt.cpp)

createMocSources = $(subst _qt,_qt_moc,$(1))

LIBSOURCES       := $(call getSourceFiles)

LIBFLEXSOURCES   := $(call getFlexSources)
LIBBISONSOURCES  := $(call getBisonSources)

LIBQTSOURCES     := $(call getQTSources)



ifneq ($(LIBFLEXSOURCES),)
LIBFLEXSOURCES_CPP     := $(patsubst %.l,%.cpp,$(LIBFLEXSOURCES)) 
LIBFLEXTARGET_CPP      := $(patsubst %.l,%.lex.cpp,$(LIBFLEXSOURCES)) 
LIBFLEXSOURCESTMP_CPP  := lex.$(LIBFLEXSOURCES_CPP)

FLEX_INTERNAL := $(strip $(basename $(LIBFLEXSOURCES_CPP)))_
FLEX_EXTERNAL := $(LIBFLEXTARGET_CPP)
endif

ifneq ($(LIBBISONSOURCES),)
LIBBISONSOURCES_CPP := $(patsubst %.y,%.cpp,$(LIBBISONSOURCES)) 
LIBBISONTARGET_CPP  := $(patsubst %.y,%.tab.cpp,$(LIBBISONSOURCES)) 

BISON_INTERNAL := $(strip $(basename $(LIBBISONSOURCES_CPP)))_
BISON_EXTERNAL := $(strip $(basename $(LIBBISONSOURCES_CPP)))

LIBHEADERS := $(call getSourceHeaderFiles)
endif

ifneq ($(LIBQTSOURCES),)
LIBQTSOURCES_CPP := $(LIBQTSOURCES)
LIBQTSOURCES_CPP := $(strip $(LIBQTSOURCES_CPP))

LIBQTMOCSOURCES_CPP := $(call createMocSources, $(LIBQTSOURCES))
LIBQTMOCSOURCES_CPP := $(strip $(LIBQTMOCSOURCES_CPP))
LIBQTMOCSOURCES_CPP := $(call addObjectDir, $(LIBQTMOCSOURCES_CPP))
endif

$(warning -$(LIBQTSOURCES)--$(LIBQTSOURCES_CPP)-)

LIBSOURCES := $(filter-out $(LIBBISONTARGET_CPP),$(LIBSOURCES))
LIBSOURCES := $(filter-out $(LIBFLEXTARGET_CPP),$(LIBSOURCES))
LIBSOURCES := $(filter-out $(LIBQTSOURCES_CPP),$(LIBSOURCES))

LIBOBJECTS  := $(call cnvSourceToObject,$(LIBSOURCES))

ifneq ($(LIBQTSOURCES),)
LIBOBJECTS := $(call cnvSourceToObject,$(LIBQTSOURCES_CPP)) $(LIBOBJECTS)
endif

ifneq ($(LIBFLEXSOURCES),)
LIBOBJECTS := $(call cnvSourceToObject,$(LIBFLEXTARGET_CPP)) $(LIBOBJECTS)
endif

ifneq ($(LIBBISONSOURCES),)
LIBOBJECTS := $(call cnvSourceToObject,$(LIBBISONTARGET_CPP)) $(LIBOBJECTS)
endif

ifeq ($(OS_BASE), NT)
ifdef OSG_BUILD_DLL
ifeq ($(MAKEPASS), DLLPASS)
SUB_SO      = $(call createSubSoName)
SUB_SO_LINK = $(call createSubSoLink)
endif
ifeq ($(MAKEPASS), LIBPASS)
SUB_LIB      = $(call createSublibName)
SUB_LIB_LINK = $(call createSublibLink)
SUB_LIB_UNIX      := $(call convWinUnix,$(SUB_LIB))
SUB_LIB_LINK_UNIX := $(call convWinUnix,$(SUB_LIB_LINK))
endif
SUB_LIB_TESTDEF = $(call createLibDefName)
SUB_LIB_DEF     = $(wildcard $(SUB_LIB_TESTDEF))
else
ifeq ($(OSGMAKESO),1)
SUB_SO      = $(call createSubSoName)
SUB_SO_LINK = $(call createSubSoLink)
else
SUB_LIB      = $(call createSublibName)
SUB_LIB_LINK = $(call createSublibLink)

SUB_LIB_UNIX      := $(SUB_LIB)
SUB_LIB_LINK_UNIX := $(SUB_LIB_LINK)

endif
endif

else
ifeq ($(OSGMAKESO),1)
SUB_SO      = $(call createSubSoName)
SUB_SO_LINK = $(call createSubSoLink)
else
SUB_LIB      = $(call createSublibName)
SUB_LIB_LINK = $(call createSublibLink)

SUB_LIB_UNIX      := $(SUB_LIB)
SUB_LIB_LINK_UNIX := $(SUB_LIB_LINK)

SUB_LIB_UNIX      := $(SUB_LIB)
SUB_LIB_LINK_UNIX := $(SUB_LIB_LINK)

endif
endif

# Used for depend call only
TESTSOURCES := $(call   getTestSourceFiles)
TESTSOURCES := $(strip $(TESTSOURCES))

ifneq ($(MAKECMDGOAL),)

NUMTESTPROGS := $(words $(MAKECMDGOAL))

ifneq ($(NUMTESTPROGS),1)
PROGSWARNING := More than one test given, ignoring all but last.
CMDGOALS     := $(word 1,$(MAKECMDGOAL))
else
PROGSWARNING := 
CMDGOALS     := $(MAKECMDGOAL)
endif

CMDGOALS    := $(filter-out %.cpp,$(CMDGOALS))

TESTSOURCES := $(filter $(CMDGOALS).cpp,$(TESTSOURCES))
TESTSOURCES := $(strip $(TESTSOURCES))

TESTOBJECTS := $(call   cnvSourceToObject,$(TESTSOURCES))

ifneq ($(TESTSOURCES),)
TESTPROGSTARG := $(CMDGOALS)
TESTPROGS     := $(CMDGOALS)$(EXEEXT)
TESTPROGRAMMS := $(CMDGOALS).$(OS)$(EXEEXT)

TESTPROGSTARG := $(strip $(TESTPROGSTARG))
TESTPROGS     := $(strip $(TESTPROGS))
else
TESTPROGSTARG := $(CMDGOALS)
TESTPROGS     := $(CMDGOALS)
TESTPROGRAMMS := 
PROGSWARNING  += "Error could not create rule for target $(CMDGOALS) !!"

TESTPROGRAMMS := $(call extractTestProgs,$(TESTSOURCES))
TESTPROGRAMMS := $(call addSysDep,$(TESTPROGRAMMS))
endif

endif # MAKECMDGOAL

ifeq ($(OSGIGNORECURRDIR),1)
REQUIRED_INCPACKAGES := $(REQUIRED_INCPACKAGES)
REQUIRED_LNKPACKAGES := $(REQUIRED_LNKPACKAGES)
else
REQUIRED_INCPACKAGES := $(CURRENTDIR) $(REQUIRED_INCPACKAGES)
REQUIRED_LNKPACKAGES := $(CURRENTDIR) $(REQUIRED_LNKPACKAGES)
endif

REQUIRED_PACKAGES := $(REQUIRED_INCPACKAGES) $(REQUIRED_LNKPACKAGES)
REQUIRED_PACKAGES := $(sort $(REQUIRED_PACKAGES))

ifneq ($(REQUIRED_PACKAGES),)

ifneq ($(OSGPOOL),$($(PROJECTPSD)POOL))
PACKAGE_INCLUDE := $(call includePackagesProj,$(REQUIRED_PACKAGES))
endif

PACKAGE_INCLUDE += $(call includePackages,$(REQUIRED_PACKAGES))

PACKAGE_INCLUDE := $(call verifyIncPackages,$(PACKAGE_INCLUDE))

include $(PACKAGE_INCLUDE) 

endif #REQUIRED_PACKAGES

TESTCLEANALL   := $(wildcard test*.cpp)

TESTCLEANBASE  := $(foreach file,$(TESTCLEANALL), $(basename $(file)))


TESTCLEANSYSTEM    := $(addsuffix .$(OS),$(TESTCLEANBASE))

TESTCLEANSYSTEMS   := \
	$(foreach sys,$(SYSTEMS), $(addsuffix .$(sys)*,$(TESTCLEANBASE)))

#########################################################################
# Include the rest
#########################################################################

#########################################################################
# Default Includes
#########################################################################


INCL                 := $(INCL$(OS))

PROJLIBSDEP          := $(call createProjLibsDep, $(REQUIRED_LNKPACKAGES))
PROJLIBS             := $(call createProjLibs,    $(REQUIRED_LNKPACKAGES))

REQUIRED_SYSTEM_LIBS := $(REQUIRED_SYSTEM_LIBS$(OS))

ifdef LINK_X11
POST_LINK_LIBS       := -L$(LINK_X11) 
else
POST_LINK_LIBS       :=
endif

POST_LINK_LIBS       := $(POST_LINK_LIBS) $(POST_LINK_LIBS$(OS))


ifneq ($(MAKECMDGOAL),)

ifeq ($(OS_BASE), NT)
PROJLIBSCHECKSYS := $(foreach file,$(PROJLIBS),$(shell cygpath -u $(file)))
else
PROJLIBSCHECKSYS := $(PROJLIBS)
endif

PROJLIBSCHECK := $(strip $(foreach lib,$(PROJLIBSCHECKSYS),$(wildcard $(lib))))
PROJLIBSSTRIP := $(strip $(PROJLIBSCHECKSYS))

PROJLIBSMISSING := $(filter-out $(PROJLIBSCHECK),$(PROJLIBSSTRIP))

ifneq ($(PROJLIBSCHECK),$(PROJLIBSSTRIP))

LIBERROR = $(PROJLIBSMISSING) {is|are} missing rebuild these libs first
$(error $(LIBERROR))

endif # ifneq ($(PROJLIBSCHECK),$(PROJLIBSSTRIP))

endif # ifneq ($(MAKECMDGOAL),)

include $(DEFAULTRULES)


-include $(DEP_MAKEFILE)




