
INCL_DIR                  := $(OSGPOOL)/Fhs

PROJLIBS_FILE             := $(OSGPOOL)/Fhs/libFhs.$(OS).$(LIBEXT)

REQUIRED_SYSTEM_LIBS$(OS) := 

ifeq ($(OS_BASE), NT)
REQUIRED_SYSTEM_LIBS$(OS) += $(LIBCIO)
else
REQUIRED_SYSTEM_LIBS$(OS) += $(LIBCIO) -lm
endif

POST_LINK_LIBS$(OS)       := \
	$(filter-out $(REQUIRED_SYSTEM_LIBS$(OS)),$(POST_LINK_LIBS$(OS)))

POST_LINK_LIBS$(OS)      += $(REQUIRED_SYSTEM_LIBS$(OS))

ifeq ($(OS_BASE), NT)
INCL$(OS)      += /I "$(shell cygpath -w $(INCL_DIR))"
PROJLIBS_FHS   := "$(shell cygpath -w $(PROJLIBS_FILE))"
else
INCL$(OS)      += -I$(INCL_DIR)
PROJLIBS_FHS   := $(PROJLIBS_FILE)
endif

PROJLIBS$(OS)  += $(PROJLIBS_FHS)

