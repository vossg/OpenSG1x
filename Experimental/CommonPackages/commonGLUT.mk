
INCLUDE_GLUT := //q/Win/NT/glut/include
LINK_GLUT    := //q/Win/NT/glut/lib
LIB_GLUT     := -lglut

ifneq ($(INCLUDE_GLUT),)
INCL_$(OS_BASE) += $(INC_OPTION)$(INCLUDE_GLUT)
endif

ifneq ($(LINK_GLUT),)
LIBPATHS_GLUT     := $(LIBPATH_OPTION)$(LINK_GLUT)

LIB_FILE_GLUT     := $(LIB_GLUT)
endif

