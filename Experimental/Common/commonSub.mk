
-include .lastdbg

DBG ?= $(LASTDBG)

DBG := $(strip $(DBG))

ifeq ($(DBG),)
DBG := dbg
endif


OBJDIR = $(OBJDIR_BASE)-$(DBG)
LIBDIR = $(LIBDIR_BASE)-$(DBG)

OBJ_SUFFIX := $(strip $(OBJ_SUFFIX))

#########################################################################
# Get Source Files
#########################################################################

getAllMDSourceFiles = $(wildcard $(1)/$(PROJ)MD*.s  ) \
					  $(wildcard $(1)/$(PROJ)MD*.cpp)
getSysMDSourceFiles = $(wildcard $(1)/$(PROJ)MD$(OS_BASE)*.s  ) \
					  $(wildcard $(1)/$(PROJ)MD$(OS_BASE)*.cpp)


getSourceFiles         = \
					     $(wildcard $(1)/$(PROJ)*.cpp) \
	 					 $(wildcard $(1)/*.c)   	   \
			 			 $(wildcard $(1)/$(PROJ)*.s)

getProjSourceFiles     =$(foreach dir,$(1),$(call getSourceFiles,$(dir)))

getProjAllMDSourceFiles= $(foreach dir,$(1),$(call getAllMDSourceFiles,$(dir)))
getProjSysMDSourceFiles= $(foreach dir,$(1),$(call getSysMDSourceFiles,$(dir)))

#########################################################################
# Get Flex/Bison Source Files
#########################################################################

getBisonSources  = $(wildcard $(1)/*.y)
getFlexSources   = $(wildcard $(1)/*.l)

getProjFlexSourceFiles  = $(foreach dir,$(1),$(call getFlexSources,$(dir)))
getProjBisonSourceFiles = $(foreach dir,$(1),$(call getBisonSources,$(dir)))

#########################################################################
# Create Objectfilenames
#########################################################################

addObjectDir      = $(if $(OBJDIR),$(addprefix $(OBJDIR)$(DIR_SEP), $(1)),$(1))

cppSourceToObject  = \
	$(patsubst %.cpp,%$(2), $(call addObjectDir,$(1)))
cSourceToObject   = $(patsubst %.c,%$(2),$(1))
asSourceToObject  = $(patsubst %.s,%$(2),$(1))


cnvCandCPPSourceToObject = \
	$(call cSourceToObject, $(call cppSourceToObject,$(1),$(2)),$(2))

cnvSourceToObject        = \
	$(call asSourceToObject, \
		$(call cnvCandCPPSourceToObject,$(1),$(OBJ_SUFFIX)),$(OBJ_SUFFIX))

cnvSourceToDep        = \
	$(call asSourceToObject, \
		$(call cnvCandCPPSourceToObject,$(1),$(DEP_SUFFIX)),$(DEP_SUFFIX))

#########################################################################
# Build include directive
#########################################################################

ifeq ($(OS_BASE), cygwin)
buildIncPath      = $(INC_OPTION)"$(shell cygpath -w $(1))"
else
buildIncPath      = $(INC_OPTION)$(1) 
endif
$
#########################################################################
# Build lib directive
#########################################################################


ifeq ($(OS_BASE), cygwin)
buildLibPath      = $(LIBPATH_OPTION)"$(BUILD_BASE_WIN)\$(1)\$(LIBDIR)"
else
buildLibPath      = $(LIBPATH_OPTION)$(BUILD_BASE)/$(1)/$(LIBDIR)
endif

buildDepLibPath   = $(BUILD_BASE)/$(1)/$(LIBDIR)

buildLibName      = $(LIBLNK_OPTION)$(PROJ)$(PACKAGENAME)$(LIB_SUFFIX)

buildDepLibName   = $(SO_PRAEFIX)$(PROJ)$(PACKAGENAME)$(SO_SUFFIX)


#########################################################################
# Define Objects
#########################################################################

#ifeq ($(OS_BASE), cygwin)
#LIB_SOURCEPACKAGES := $(strip $(subst :, ,$(subst $($(PROJ)POOL)/,,\
#	$(subst .:,,$(VPATH)))))
#else
LIB_SOURCEPACKAGES := $(strip $(subst :, ,$(subst /,,$(subst $($(PROJ)POOL)/,,\
	$(subst .:,,$(VPATH))))))
#endif

LIB_ABSSOURCEDIRS  := $(strip $(subst :, ,$(subst .:,,$(VPATH))))

LIB_SYSMDSOURCES   := $(call getSysMDSourceFiles,$(LIB_ABSSOURCEDIRS))

LIB_ALLMDSOURCES   := $(call getProjAllMDSourceFiles,$(LIB_ABSSOURCEDIRS))

LIB_RMMDSOURCES    := $(filter-out $(LIB_SYSMDSOURCES),$(LIB_ALLMDSOURCES))
LIB_RMMDSOURCES    := $(notdir $(LIB_RMMDSOURCES))

LIB_SOURCES        := $(call getProjSourceFiles,$(LIB_ABSSOURCEDIRS))

LIB_SOURCES        := $(notdir $(LIB_SOURCES))
LIB_SOURCES        := $(filter-out $(LIB_RMMDSOURCES),$(LIB_SOURCES))

LIB_OBJECTS        := $(call cnvSourceToObject,$(LIB_SOURCES))

#########################################################################
# Define Objects
#########################################################################

LIB_DEPS           := $(call cnvSourceToDep,$(LIB_SOURCES))

#########################################################################
# Define FLex/Bison Objects
#########################################################################

LIB_FLEXSOURCES   := $(call getProjFlexSourceFiles,$(LIB_ABSSOURCEDIRS))
LIB_FLEXSOURCES   := $(strip $(LIB_FLEXSOURCES))

LIB_BISONSOURCES  := $(call getProjBisonSourceFiles,$(LIB_ABSSOURCEDIRS))
LIB_BISONSOURCES  := $(strip $(LIB_BISONSOURCES))

ifneq ($(LIB_FLEXSOURCES),)
LIB_FLEXSOURCES_CPP     := $(notdir $(patsubst %.l,%.cpp,$(LIB_FLEXSOURCES)))
LIB_FLEXTARGET_CPP      := $(patsubst %.l,%.lex.cpp,$(LIB_FLEXSOURCES)) 
LIB_FLEXTARGET_CPP      := $(notdir $(LIB_FLEXTARGET_CPP))

LIB_FLEXTARGET_CPP      := $(OBJDIR)/$(LIB_FLEXTARGET_CPP) 

FLEX_INTERNAL := $(strip $(basename $(LIB_FLEXSOURCES_CPP)))_
FLEX_EXTERNAL := $(LIB_FLEXTARGET_CPP)
endif


ifneq ($(LIB_BISONSOURCES),)
LIB_BISONSOURCES_CPP := $(notdir $(patsubst %.y,%.cpp,$(LIB_BISONSOURCES)))
LIB_BISONTARGET_CPP  := $(notdir $(patsubst %.y,%.tab.cpp,$(LIB_BISONSOURCES)))
LIB_BISONTARGET_CPP  := $(OBJDIR)/$(LIB_BISONTARGET_CPP)

BISON_INTERNAL := $(strip $(basename $(LIB_BISONSOURCES_CPP)))_
BISON_EXTERNAL := $(strip $(basename $(LIB_BISONSOURCES_CPP)))
endif

ifneq ($(LIB_FLEXSOURCES),)
LIB_OBJECTS := $(call cnvSourceToObject, $(notdir $(LIB_FLEXTARGET_CPP))) \
			   $(LIB_OBJECTS)
endif

ifneq ($(LIB_BISONSOURCES),)
LIB_OBJECTS := $(call cnvSourceToObject, $(notdir $(LIB_BISONTARGET_CPP))) \
			   $(LIB_OBJECTS)
endif

#########################################################################
# Define Packages
#########################################################################

REQUIRED_PACKAGES := $(LIB_SOURCEPACKAGES)
REQUIRED_PACKAGES += $(LIB_REQUIRED_INCPACKAGES) $(LIB_REQUIRED_LNKPACKAGES)

REQUIRED_PACKAGES := $(sort $(REQUIRED_PACKAGES))


REQUIRED_PACKAGES := \
   $(addprefix $($(PROJ)POOL)/$($(PROJ)COMMONPACK)/common,$(REQUIRED_PACKAGES))

REQUIRED_PACKAGES := \
	$(addsuffix $(MAK_SUFFIX)/,$(REQUIRED_PACKAGES))

include $(REQUIRED_PACKAGES)

#########################################################################
# Setup Compiler Environment
#########################################################################

INCL         := $(INCL_$(OS_BASE))
LIBPATHS     := $(LIBPATHS_$(OS_BASE))

LIBPACKPATHS := $(foreach lp,$(LIB_REQUIRED_LNKPACKAGES), $(LIBPATHS_$(lp)))

LIBPATHS     := $(LIBPATHS) $(LIBPACKPATHS)

LIBS      := $(foreach lp,$(LIB_REQUIRED_LNKPACKAGES), $(LIB_FILE_$(lp)))
LIBS      := $(LIBS) $(LIBS_$(OS_BASE))

LIBS_DEP  := $(foreach lp,$(LIB_REQUIRED_LNKPACKAGES), $(LIB_FILE_DEP_$(lp)))

include $($(PROJ)POOL)/$($(PROJ)COMMON)/DefaultRules.mk
