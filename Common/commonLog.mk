
INCL_DIR                  := $(OSGPOOL)/Log

PROJLIBS_FILE             := $(OSGPOOL)/Log/libLog.$(OS).$(LIBEXT)

ifeq ($(OS_BASE), NT40)
REQUIRED_SYSTEM_LIBS$(OS) := $(LIBCIO)
else
REQUIRED_SYSTEM_LIBS$(OS) := $(LIBCIO) -lm
endif

POST_LINK_LIBS$(OS)       := \
	$(filter-out $(REQUIRED_SYSTEM_LIBS$(OS)),$(POST_LINK_LIBS$(OS)))

POST_LINK_LIBS$(OS)      += $(REQUIRED_SYSTEM_LIBS$(OS))

ifeq ($(OS_BASE), NT40)
INCL$(OS)    += /I "$(shell cygpath -w $(INCL_DIR))"
PROJLIBS_LOG := "$(shell cygpath -w $(PROJLIBS_FILE))"
else
INCL$(OS)    += -I$(INCL_DIR)
PROJLIBS_LOG := $(PROJLIBS_FILE)
endif

PROJLIBS$(OS)  += $(PROJLIBS_LOG)
