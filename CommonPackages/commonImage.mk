
SUB_DIR                  := Image

INCL_DIR                 := $(OSGPOOL)/$(SUB_DIR)

PROJLIBS_FILE_$(SUB_DIR) := $(OSGPOOL)/$(SUB_DIR)/lib$(SUB_DIR).$(OS).$(LIBEXT)

ifeq ($(OS_BASE), NT40)
REQUIRED_SYSTEM_LIBS$(OS) := $(LIBCIO)
else
REQUIRED_SYSTEM_LIBS$(OS) := -ltiff -ljpeg $(LIBCIO) -lm
endif

ifdef OSG_MK_DEBUG_RSL
$(warning commonLog : |$(REQUIRED_SYSTEM_LIBS$(OS))|)
endif

include $(OSGPOOL)/$(OSGCOMMON)/commonPackage.mk

ifdef OSG_MK_DEBUG_RSL
$(warning commonLog : |$(POST_LINK_LIBS$(OS))|)
endif