
SUB_DIR                  := Field

INCL_DIR                 := $(OSGPOOL)/$(SUB_DIR)

PROJLIBS_FILE_$(SUB_DIR) := $(OSGPOOL)/$(SUB_DIR)/lib$(SUB_DIR).$(OS).$(LIBEXT)

REQUIRED_SYSTEM_LIBS$(OS) :=

ifeq ($(OS_BASE), Linux)
REQUIRED_SYSTEM_LIBS$(OS) += -lpthread 
endif

ifeq ($(OS_BASE), IRIX64)
endif

ifeq ($(OS_BASE), SunOS)
REQUIRED_SYSTEM_LIBS$(OS) += -lpthread
endif

ifeq ($(OS_BASE), NT40)
REQUIRED_SYSTEM_LIBS$(OS) := libCio.lib
else
REQUIRED_SYSTEM_LIBS$(OS) += -lCio -lm
endif

include $(OSGPOOL)/$(OSGCOMMON)/commonPackage.mk









