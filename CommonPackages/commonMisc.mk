
SUB_DIR                  := Misc

INCL_DIR                 := $(OSGPOOL)/Nodes/$(SUB_DIR)

PROJLIBS_FILE_$(SUB_DIR) := \
	$(OSGPOOL)/Nodes/$(SUB_DIR)/lib$(SUB_DIR).$(OS).$(LIBEXT)


ifeq ($(OS_BASE), NT40)
REQUIRED_SYSTEM_LIBS$(OS) := glut32.lib opengl32.lib glu32.lib $(LIBCIO)
else
REQUIRED_SYSTEM_LIBS$(OS) := -lglut -lGLU -lGL -lXmu -lXi -lXt -lX11    \
                             -ltiff -ljpeg $(LIBCIO) -lm
endif

ifdef OSG_MK_DEBUG_RSL
$(warning commonLog : |$(REQUIRED_SYSTEM_LIBS$(OS))|)
endif

include $(OSGPOOL)/$(OSGCOMMON)/commonPackage.mk

ifdef OSG_MK_DEBUG_RSL
$(warning commonLog : |$(POST_LINK_LIBS$(OS))|)
endif