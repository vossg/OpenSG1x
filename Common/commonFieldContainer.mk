
INCL_DIR                  := $(OSGPOOL)/FieldContainer

PROJLIBS_FILE             := \
	$(OSGPOOL)/FieldContainer/libFieldContainer.$(OS).$(LIBEXT)

REQUIRED_SYSTEM_LIBS$(OS) := 

ifeq ($(OS_BASE), NT40)
REQUIRED_SYSTEM_LIBS$(OS) += $(LIBCIO)
else
REQUIRED_SYSTEM_LIBS$(OS) += $(LIBCIO) -lm
endif

POST_LINK_LIBS$(OS)       := \
	$(filter-out $(REQUIRED_SYSTEM_LIBS$(OS)),$(POST_LINK_LIBS$(OS)))

POST_LINK_LIBS$(OS)      += $(REQUIRED_SYSTEM_LIBS$(OS))

ifeq ($(OS_BASE), NT40)
INCL$(OS)     += /I "$(shell cygpath -w $(INCL_DIR))"
PROJLIBS_FC   := "$(shell cygpath -w $(PROJLIBS_FILE))"
else
INCL$(OS)     += -I$(INCL_DIR)
PROJLIBS_FC := $(PROJLIBS_FILE)
endif

PROJLIBS$(OS)  += $(PROJLIBS_FC)

