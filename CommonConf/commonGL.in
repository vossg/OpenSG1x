
INCLUDE_GL :=
LINK_GL    :=

ifeq ($(OS_BASE), cygwin)
LIB_GL   := opengl32.lib glu32.lib gdi32.lib
else
LIB_GL   := -lGLU -lGL -lXmu -lXi -lXt -lX11
endif

ifneq ($(INCLUDE_GL),)
INCL_$(OS_BASE) += $(INC_OPTION)$(INCLUDE_GL)
endif

ifneq ($(LINK_GL),)
LIBPATHS_GL     := $(LIBPATH_OPTION)$(LINK_GL)
endif

ifneq ($(LIB_GL),)
LIB_FILE_GL     := $(LIB_GL)
endif

