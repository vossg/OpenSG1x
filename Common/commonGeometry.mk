
INCL_DIR                  := $(OSGPOOL)/Nodes/Geometry

PROJLIBS_FILE             := \
	$(OSGPOOL)/Nodes/Geometry/libGeometry.$(OS).$(LIBEXT)

REQUIRED_SYSTEM_LIBS$(OS) := 

ifeq ($(OS_BASE), NT40)
REQUIRED_SYSTEM_LIBS$(OS) += /LIBPATH:$(LINK_GLUT)
REQUIRED_SYSTEM_LIBS$(OS) += glut32.lib opengl32.lib glu32.lib $(LIBCIO)
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

ifeq ($(OS_BASE), NT40)
INCL$(OS)    += /I"$(shell cygpath -w $(INCL_DIR))"
INCL$(OS)    += /I$(INCLUDE_GLUT)
PROJLIBS_GEO := "$(shell cygpath -w $(PROJLIBS_FILE))"
else

INCL$(OS)    += -I$(INCL_DIR) 

ifdef INCLUDE_GLUT
INCL$(OS)    += -I$(INCLUDE_GLUT)
endif

PROJLIBS_GEO := $(PROJLIBS_FILE)
endif

PROJLIBS$(OS) += $(PROJLIBS_GEO)
