
SUB_DIR                  := Action
PACKAGENAME              := Action

INCL_DIR                 := $(OSGPOOL)/$(SUB_DIR)

PROJLIBS_FILE_$(SUB_DIR) := \
	$(OSGPOOL)/$(SUB_DIR)/lib$(PACKAGENAME).$(OS).$(LIBEXT)

ifeq ($(OS_BASE), NT)
REQUIRED_SYSTEM_LIBS$(OS) := $(LIBCIO)
else
REQUIRED_SYSTEM_LIBS$(OS) := $(LIBCIO) -lm
endif

ifdef OSG_MK_DEBUG_RSL
$(warning commonLog : |$(REQUIRED_SYSTEM_LIBS$(OS))|)
endif

include $(OSGPOOL)/$(OSGCOMMON)/commonPackage.mk

ifdef OSG_MK_DEBUG_RSL
$(warning commonLog : |$(POST_LINK_LIBS$(OS))|)
endif