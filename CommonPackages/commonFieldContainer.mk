
SUB_DIR                  := FieldContainer
PACKAGENAME              := FieldContainer

INCL_DIR                 := $(OSGPOOL)/$(SUB_DIR)

PROJLIBS_FILE_$(SUB_DIR) := \
	$(OSGPOOL)/$(SUB_DIR)/lib$(PACKAGENAME).$(OS).$(LIBEXT)

REQUIRED_SYSTEM_LIBS$(OS) :=

ifeq ($(OS_BASE), Linux)
REQUIRED_SYSTEM_LIBS$(OS) += -lpthread 
endif

ifeq ($(OS_BASE), IRIX64)
endif

ifeq ($(OS_BASE), SunOS)
REQUIRED_SYSTEM_LIBS$(OS) += -lpthread
endif

ifeq ($(OS_BASE), NT)
REQUIRED_SYSTEM_LIBS$(OS) := $(LIB_CIO)
else
REQUIRED_SYSTEM_LIBS$(OS) += -lCio -lm
endif

ifdef OSG_MK_DEBUG_RSL
$(warning commonDataStorage : |$(REQUIRED_SYSTEM_LIBS$(OS))|)
endif

include $(OSGPOOL)/$(OSGCOMMON)/commonPackage.mk

ifdef OSG_MK_DEBUG_RSL
$(warning commonDataStorage : |$(POST_LINK_LIBS$(OS))|)
endif







