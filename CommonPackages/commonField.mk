
SUB_DIR                  := Field
PACKAGENAME              := Field

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
REQUIRED_SYSTEM_LIBS$(OS) := $(LIBCIO)
else
REQUIRED_SYSTEM_LIBS$(OS) += $(LIBCIO) -lm
endif

include $(OSGPOOL)/$(OSGCOMMON)/commonPackage.mk









