
INCL_DIR                  := $(OSGPOOL)/Window

PROJLIBS_FILE             := $(OSGPOOL)/Window/libWindow.$(OS).$(LIBEXT)

ifeq ($(OS_BASE), NT)
REQUIRED_SYSTEM_LIBS$(OS) := /LIBPATH:"$(LINK_GLUT)" $(LIBCIO)
else
REQUIRED_SYSTEM_LIBS$(OS) := -lglut -lGLU -lGL -lXmu -lXi -lXt -lX11	\
							 $(LIBCIO) -lm
endif

POST_LINK_LIBS$(OS)       := \
	$(filter-out $(REQUIRED_SYSTEM_LIBS$(OS)),$(POST_LINK_LIBS$(OS)))

POST_LINK_LIBS$(OS)      += $(REQUIRED_SYSTEM_LIBS$(OS))

ifeq ($(OS_BASE), NT)
INCL$(OS)    += /I"$(shell cygpath -w $(INCL_DIR))"
INCL$(OS)    += /I"$(INCLUDE_GLUT)"
PROJLIBS_WIN := "$(shell cygpath -w $(PROJLIBS_FILE))"
else
INCL$(OS)    += -I$(INCL_DIR)
PROJLIBS_WIN := $(PROJLIBS_FILE)
endif

PROJLIBS$(OS)  += $(PROJLIBS_WIN)


