
include $(SYSTEMDIRECTORIES)
include $(COMMONINCLUDE)

#########################################################################
# Make goal
#########################################################################

MAKECMDGOAL  := $(filter-out $(INTERNALTARGETS),$(MAKECMDGOALS))

#########################################################################
# Set Sources | Headers | Objects | Sublib
#########################################################################

getBisonSources := $(wildcard *.y)
getFlexSources  := $(wildcard *.l)

LIBSOURCES := $(call getSourceFiles)

LIBFLEXSOURCES  := $(call getFlexSources)
LIBBISONSOURCES := $(call getBisonSources)




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

LIBSOURCES := $(filter-out $(LIBBISONTARGET_CPP),$(LIBSOURCES))
LIBSOURCES := $(filter-out $(LIBFLEXTARGET_CPP),$(LIBSOURCES))

LIBOBJECTS  := $(call cnvSourceToObject,$(LIBSOURCES))

ifneq ($(LIBBISONSOURCES),)
LIBOBJECTS += $(call cnvSourceToObject,$(LIBBISONTARGET_CPP))
endif

ifneq ($(LIBFLEXSOURCES),)
LIBOBJECTS += $(call cnvSourceToObject,$(LIBFLEXTARGET_CPP))
endif

SUB_LIB      = $(call createSublibName)
SUB_LIB_LINK = $(call createSublibLink)

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
TESTPROGS     := $(CMDGOALS)
TESTPROGRAMMS := $(CMDGOALS).$(OS)
else
TESTPROGS     := $(CMDGOALS)
TESTPROGRAMMS := 
PROGSWARNING  += "Error could not create rule for target $(CMDGOALS) !!"

TESTPROGRAMMS := $(call extractTestProgs,$(TESTSOURCES))
TESTPROGRAMMS := $(call addSysDep,$(TESTPROGRAMMS))
endif

endif # MAKECMDGOAL

REQUIRED_PACKAGES := $(CURRENTDIR) $(REQUIRED_PACKAGES)

ifneq ($(REQUIRED_PACKAGES),)

PACKAGE_INCLUDE := $(call includePackages,$(REQUIRED_PACKAGES))

include $(PACKAGE_INCLUDE) 

endif #REQUIRED_PACKAGES

TESTCLEANALL   := $(wildcard test*.cpp)

TESTCLEANBASE  := $(foreach file,$(TESTCLEANALL), $(basename $(file)))


TESTCLEANSYSTEM    := $(addsuffix .$(OS),$(TESTCLEANBASE))

TESTCLEANSYSTEMS   := \
	$(foreach sys,$(SYSTEMS), $(addsuffix .$(sys),$(TESTCLEANBASE)))

#########################################################################
# Include the rest
#########################################################################

#########################################################################
# Default Includes
#########################################################################


INCL                 := $(INCL$(OS))
PROJLIBS             := $(PROJLIBS$(OS))
REQUIRED_SYSTEM_LIBS := $(REQUIRED_SYSTEM_LIBS$(OS))

ifdef LINK_X11
POST_LINK_LIBS       := -L$(LINK_X11) 
else
POST_LINK_LIBS       :=
endif

POST_LINK_LIBS       := $(POST_LINK_LIBS) $(POST_LINK_LIBS$(OS))


ifneq ($(MAKECMDGOAL),)

ifeq ($(OS_BASE), NT40)
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
