
ifeq ($(DEBUG_MAKE),1)
$(warning $(DBG))
endif

OBJDIR = $(OBJDIR_BASE)-$(DBG)
LIBDIR = $(LIBDIR_BASE)-$(DBG)
EXEDIR = $(EXEDIR_BASE)-$(DBG)

ifeq ($(DEBUG_MAKE),1)
$(warning $(OBJDIR))
endif

OBJ_SUFFIX := $(strip $(OBJ_SUFFIX))

#########################################################################
# Get Source Files
#########################################################################

getAllMDSourceFiles = $(wildcard $(1)/$(PROJ)MD*.s  ) \
					  $(wildcard $(1)/$(PROJ)MD*.cpp)
getSysMDSourceFiles = $(wildcard $(1)/$(PROJ)MD$(OS_BASE)*.s  ) \
					  $(wildcard $(1)/$(PROJ)MD$(OS_BASE)*.cpp)


getSourceFiles         = \
					     $(wildcard $(1)/$(PROJ)*.cpp) 	\
	 					 $(wildcard $(1)/*.c)   	   	\
			 			 $(wildcard $(1)/$(PROJ)*.s)

getTestSourceFiles     = \
					     $(wildcard $(1)/test*.cpp)

getQTSourceFiles       = $(wildcard $(1)/OSG*_qt.cpp)
getTestQTSourceFiles   = $(wildcard $(1)/test*_qt.cpp)

getProjSourceFiles     =$(foreach dir,$(1),$(call getSourceFiles,$(dir))) \
					    $(wildcard ./*.cpp)

getProjTestSourceFiles =$(foreach dir,$(1),$(call getTestSourceFiles,$(dir)))

getProjAllMDSourceFiles= $(foreach dir,$(1),$(call getAllMDSourceFiles,$(dir)))
getProjSysMDSourceFiles= $(foreach dir,$(1),$(call getSysMDSourceFiles,$(dir)))

getProjQTSourceFiles   = $(foreach dir,$(1),$(call getQTSourceFiles,$(dir)))

getPrTestQTSourceFiles = $(foreach dir,$(1),$(call getTestQTSourceFiles,$(dir)))

getLibDefHdrFiles      = $(wildcard $(1)/lib.def.hdr)
getProjLibDefHeader    = $(foreach dir,$(1),$(call getLibDefHdrFiles,$(dir)))

getLibDefFiles         = $(wildcard $(1)/lib.def.sym)
getProjLibDefFiles     = $(foreach dir,$(1),$(call getLibDefFiles,$(dir)))

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
ifeq ($(OS_CMPLR),g++)
buildIncPath      = $(INC_OPTION)$(1) 
else
buildIncPath      = $(INC_OPTION)"$(shell cygpath -w $(1))"
endif
else
buildIncPath      = $(INC_OPTION)$(1) 
endif

#########################################################################
# Build lib directive
#########################################################################

ifeq ($(OS_BASE), cygwin)
ifeq ($(OS_CMPLR),g++)
cnvSubDirUnix2Win  = $1
cnvSubDirsUnix2Win = $1
else
cnvSubDirUnix2Win = $(subst /,\,$(1))
cnvSubDirsUnix2Win = $(foreach dir,$(1),"$(call cnvSubDirUnix2Win,$(dir))")
endif
else
cnvSubDirUnix2Win  = $1
cnvSubDirsUnix2Win = $1
endif

ifeq ($(OS_BASE), cygwin)
buildLibPath      = $(LIBPATH_OPTION)"$(BUILD_BASE_WIN)\$(1)\$(LIBDIR)"
else
buildLibPath      = $(LIBPATH_OPTION)$(BUILD_BASE)/$(1)/$(LIBDIR)
endif

buildDepLibPath   = $(BUILD_BASE)/$(1)/$(LIBDIR)

ifeq ($(OS_BASE), cygwin)
buildLibName      = $(LIBLNK_OPTION)$(PROJ)$(1)$(LIB_SUFFIX)
else
buildLibName      = $(LIBLNK_OPTION)$(PROJ)$(1)
endif

buildLnkLibName   = $(LIBLNK_OPTION)$(PROJ)$(1)$(LNK_SUFFIX)$(LIB_SUFFIX)

ifeq ($(OS_BASE), cygwin)
buildDepLibName   = $(SO_PRAEFIX)$(PROJ)$(1)$(LIB_SUFFIX)
else
buildDepLibName   = $(SO_PRAEFIX)$(PROJ)$(1)$(SO_SUFFIX)
endif

buildDepLnkLibName   = $(SO_PRAEFIX)$(PROJ)$(1)$(LNK_SUFFIX)$(LIB_SUFFIX)

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

TEST_SOURCES       := $(call getProjTestSourceFiles,$(LIB_ABSSOURCEDIRS))
TEST_SOURCES        := $(notdir $(TEST_SOURCES))

#########################################################################
# Define Dep Objects
#########################################################################

ifeq ($($(PROJ)NODEPS),)
LIB_DEPS           := $(call cnvSourceToDep,$(LIB_SOURCES))
endif

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

LIB_FLEXTARGET_CPP      := $(addprefix $(OBJDIR)/,$(LIB_FLEXTARGET_CPP))

LIB_FLEXTARGET_DEPS     := $(patsubst %.cpp,%.d,$(LIB_FLEXTARGET_CPP))

flex_int = $(strip $(basename $(notdir $(1))))_
flex_ext =  $(strip $(basename $(notdir $(1))))
endif


ifneq ($(LIB_BISONSOURCES),)
LIB_BISONSOURCES_CPP := $(notdir $(patsubst %.y,%.cpp,$(LIB_BISONSOURCES)))
LIB_BISONTARGET_CPP  := $(notdir $(patsubst %.y,%.tab.cpp,$(LIB_BISONSOURCES)))
LIB_BISONTARGET_CPP  := $(addprefix $(OBJDIR)/,$(LIB_BISONTARGET_CPP))

LIB_BISONTARGET_DEPS := $(patsubst %.cpp,%.d,$(LIB_BISONTARGET_CPP))

bison_int = $(strip $(basename $(notdir $(1))))_
bison_ext = $(strip $(basename $(notdir $(1))))
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
# Define QT Objects
#########################################################################

ifeq ($(CONFIGURED_QT),1)
LIB_QT_SOURCES    := $(call getProjQTSourceFiles,$(LIB_ABSSOURCEDIRS))

ifneq ($(LIB_QT_SOURCES),)
LIB_QT_SOURCES    := $(notdir $(LIB_QT_SOURCES))

LIB_QTTARGET_CPP  := $(subst _qt,_qt_moc,$(LIB_QT_SOURCES))

LIB_QTTARGET_CPP  := $(addprefix $(OBJDIR)/,$(LIB_QTTARGET_CPP))

LIB_QTTARGET_DEPS := $(patsubst %.cpp,%.d,$(LIB_QTTARGET_CPP))

LIB_QT_TARGET     := $(LIB_QTTARGET_CPP) : $(LIB_QT_SOURCES)
endif
endif

#########################################################################
# Define Test Targets
#########################################################################

TEST_TARGETS_IN   := $(basename $(TEST_SOURCES))
TEST_TARGETS_LIST := $(basename $(TEST_SOURCES))

ifneq ($(FILTEREDTSTGOALS),)
FILTEREDTSTGOALS := $(basename $(FILTEREDTSTGOALS))
TEST_TARGETS_IN  := $(filter $(FILTEREDTSTGOALS),$(TEST_TARGETS_IN))
endif

TEST_TARGETS       := $(addprefix $(EXEDIR)$(DIR_SEP),$(TEST_TARGETS_IN))
TEST_TARGETS       := $(addsuffix $(EXE_SUFFIX),$(TEST_TARGETS))

TEST_TARGETS_CPP   := $(addsuffix .cpp,$(TEST_TARGETS_IN))

ifeq ($($(PROJ)NODEPS),)
TEST_DEPS          := $(call cnvSourceToDep,$(TEST_TARGETS_CPP))
endif

TEST_OBJS          := $(call cnvSourceToObject,$(TEST_TARGETS_CPP))

ifeq ($(CONFIGURED_QT),1)

LIB_TESTQT_SOURCES := $(call getPrTestQTSourceFiles,$(LIB_ABSSOURCEDIRS))

ifneq ($(LIB_TESTQT_SOURCES),)
LIB_TESTQT_SOURCES    := $(notdir $(LIB_TESTQT_SOURCES))

LIB_TESTQTTARGET_CPP  := $(subst _qt,_qt_moc,$(LIB_TESTQT_SOURCES))

LIB_TESTQTTARGET_CPP  := $(addprefix $(OBJDIR)/,$(LIB_TESTQTTARGET_CPP))

LIB_TESTQTTARGET_DEPS := $(patsubst %.cpp,%.d,$(LIB_TESTQTTARGET_CPP))

LIB_TESTQT_TARGET     := $(LIB_TESTQTTARGET_CPP) : $(LIB_TESTQT_SOURCES)
endif

endif

#########################################################################
# Define LibDef
#########################################################################

LIB_HEADER_SRC := $(strip $(call getProjLibDefHeader,$(LIB_ABSSOURCEDIRS)))
LIB_DEF_SRC    := $(strip $(call getProjLibDefFiles,$(LIB_ABSSOURCEDIRS)))

SUB_SO_DEF :=

ifneq ($(LIB_DEF_SRC),)

ifneq ($(LIB_HEADER_SRC),)

SUB_SO_DEF := lib.def

endif

endif

#########################################################################
# Define Packages
#########################################################################

REQUIRED_PACKAGES := $(LIB_ABSSOURCEDIRS)

REQUIRED_PACKAGES := \
	$(addsuffix /common$(MAK_SUFFIX),$(REQUIRED_PACKAGES))

REQUIRED_PACKAGES += $(LIB_REQUIRED_INCPACKAGES_FILES) \
					 $(LIB_REQUIRED_LNKPACKAGES_FILES)

ifeq ($(IN_TEST_DIR),1)
REQUIRED_PACKAGES += $(LIB_REQUIRED_TESTINCPACKAGES_FILES)
REQUIRED_PACKAGES += $(LIB_REQUIRED_TESTLNKPACKAGES_FILES)
endif

REQUIRED_PACKAGES := $(sort $(REQUIRED_PACKAGES))

include $(REQUIRED_PACKAGES)

#########################################################################
# Setup Compiler Environment
#########################################################################

INCL         := $(INCL_$(OS_BASE))
LIBPATHS     := $(LIBPATHS_$(OS_BASE))

RQ_LPACKS    := $(LIB_REQUIRED_LNKPACKAGES)

ifeq ($(IN_TEST_DIR),1)
ifeq ($(OS_BASE), cygwin)
RQ_LPACKS    := $(LIB_REQUIRED_TESTLNKPACKAGES) \
				$(filter-out $(LIB_REQUIRED_TESTLNKPACKAGES),$(RQ_LPACKS))
else
RQ_LPACKS    := $(LIB_REQUIRED_TESTLNKPACKAGES) \
				$(filter-out $(LIB_REQUIRED_TESTLNKPACKAGES), $(RQ_LPACKS))
#$(error $(LIBS) $(RQ_LPACKS))
endif
else
ifeq ($(OS_BASE), cygwin)
RQ_LPACKS    := $(LIB_REQUIRED_TESTLNKPACKAGES) $(RQ_LPACKS)
endif
endif

LIBPACKPATHS := $(foreach lp,$(RQ_LPACKS), $(LIBPATHS_$(lp)))

LIBPATHS     := $(LIBPATHS) $(LIBPACKPATHS)

ifeq ($(LNK),)
LIBS      := $(foreach lp,$(RQ_LPACKS), $(LIB_FILE_$(lp)))
else
LIBS      := $(foreach lp,$(RQ_LPACKS), $(LIB_FILE_$(lp)_LNK))
endif

LIBS      := $(LIBS) $(LIBS_$(OS_BASE))

ifeq ($(LNK),)
LIBS_DEP  := $(foreach lp,$(RQ_LPACKS), $(LIB_FILE_DEP_$(lp)))
else
LIBS_DEP  := $(foreach lp,$(RQ_LPACKS), $(LIB_FILE_DEP_$(lp)_LNK))
endif

include $($(PROJ)POOL)/$($(PROJ)COMMON)/DefaultRules.mk


#########################################################################
# Help Target
#########################################################################

ifeq ($(IN_TEST_DIR),1)

help:
	@echo 
	@echo "Targets supported on this level (Test):"
	@echo "======================================="
	@echo 
	@echo "list       list all available tests"
	@echo 
	@echo "Creation targets"
	@echo 
	@echo "<name>     compile the named test"
	@echo "Test       compile the same versions of the tests as last time"
	@echo "<default>  as as tests"
	@echo "dbg        compile the debug versions of the configured tests"
	@echo "opt        compile the optimized versions of the configured tests"
	@echo "depend     explicitly create the dependency information"
	@echo 
	@echo "Cleanup targets"
	@echo 
	@echo "remove temporary result files: object files, flex/bison/moc output etc.,"
	@echo "dbgclean    for the debugging libraries only"
	@echo "optclean    for the optimized libraries only"
	@echo "clean       for the same libraries as last time"
	@echo "allclean    dbgclean and optclean"
	@echo 
	@echo "remove dependency files"
	@echo "dbgDepClean    for the debugging libraries only"
	@echo "optDepClean    for the optimized libraries only"
	@echo "DepClean       for the same libraries as last time"
	@echo 
	@echo "same as clean + dependencies + results (libs/programs)"
	@echo "dbgClean    for the debugging libraries only"
	@echo "optClean    for the optimized libraries only"
	@echo "Clean       for the same libraries as last time"
	@echo "distclean   dbgClean and optClean"

else

help:
	@echo 
	@echo "Targets supported on this level (Library):"
	@echo "=========================================="
	@echo 
	@echo "Creation targets"
	@echo 
	@echo "<default>  compile the same versions of the library as last time"
	@echo "dbg        compile the debug versions of the library"
	@echo "opt        compile the optimized versions of the library"
	@echo "depend     explicitly create the dependency information"
	@echo 
	@echo "Cleanup targets"
	@echo 
	@echo "remove temporary result files: object files, flex/bison/moc output etc.,"
	@echo "dbgclean    for the debugging libraries only"
	@echo "optclean    for the optimized libraries only"
	@echo "clean       for the same libraries as last time"
	@echo "allclean    dbgclean and optclean"
	@echo 
	@echo "remove dependency files"
	@echo "dbgDepClean    for the debugging libraries only"
	@echo "optDepClean    for the optimized libraries only"
	@echo "DepClean       for the same libraries as last time"
	@echo 
	@echo "same as clean + dependencies + results (libs/programs)"
	@echo "dbgClean    for the debugging libraries only"
	@echo "optClean    for the optimized libraries only"
	@echo "Clean       for the same libraries as last time"
	@echo "distclean   dbgClean and optClean"
	@echo 
	@echo "LibClean   remove libraries"

endif
