
INCL_DIR                  := $(OSGPOOL)/Nodes/Light

PROJLIBS_FILE             := \
	$(OSGPOOL)/Nodes/Light/libLight.$(OS).$(LIBEXT)

REQUIRED_SYSTEM_LIBS$(OS) := 

ifeq ($(OS_BASE), NT)
REQUIRED_SYSTEM_LIBS$(OS) += $(LIBCIO)
else

ifdef LINK_GLUT
REQUIRED_SYSTEM_LIBS$(OS) += -L$(LINK_GLUT)
endif

REQUIRED_SYSTEM_LIBS$(OS) += -lglut -lGLU -lGL -lXmu -lXi -lXt -lX11	\
							$(LIBCIO) -lm
endif

POST_LINK_LIBS$(OS)       := \
	$(filter-out $(REQUIRED_SYSTEM_LIBS$(OS)),$(POST_LINK_LIBS$(OS)))

POST_LINK_LIBS$(OS)      += $(REQUIRED_SYSTEM_LIBS$(OS))

ifeq ($(OS_BASE), NT)
INCL$(OS)      += /I "$(shell cygpath -w $(INCL_DIR))"
PROJLIBS_LIGHT := "$(shell cygpath -w $(PROJLIBS_FILE))"
else

INCL$(OS)      += -I$(INCL_DIR) 

ifdef INCLUDE_GLUT
INCL$(OS)    += -I$(INCLUDE_GLUT)
endif

PROJLIBS_LIGHT := $(PROJLIBS_FILE)
endif

PROJLIBS$(OS)  += $(PROJLIBS_LIGHT)
