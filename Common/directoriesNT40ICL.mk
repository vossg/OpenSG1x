
SOFTDIR              = /D/Program\ Files/Intel/compiler
MEDSOFTDIR           = /D/Program\ Files/Intel/compiler

INCLUDE_SYSTEM		 = /D/Program\ Files/Microsoft\ Visual\ Studio/VC98/Include
INCLUDE_SYSTEM      := "$(shell cygpath -w $(INCLUDE_SYSTEM))"

ICL_VERSION          = 45

ICL_BASEDIR          = $(SOFTDIR)$(ICL_VERSION)

INCLUDE_SYSTEM_CC	 = #$(ICL_BASEDIR)/include

ICL_BIN              = $(ICL_BASEDIR)/bin

INCLUDE_COMPILER     = $(ICL_BASEDIR)/include
INCLUDE_COMPILER    := "$(shell cygpath -w $(INCLUDE_COMPILER))"

LIB_SYSTEM            = /D/Program\ Files/Microsoft\ Visual\ Studio/VC98/lib
LIB_SYSTEM           := "$(shell cygpath -w $(LIB_SYSTEM))"

LIB_COMPILER          = $(ICL_BASEDIR)/lib
LIB_COMPILER         := "$(shell cygpath -w $(LIB_COMPILER))"

INCLUDE_GLUT          = /F/Dev/glut
INCLUDE_GLUT         := "$(shell cygpath -w $(INCLUDE_GLUT))"

LINK_GLUT             = /F/Dev/glut
LINK_GLUT            := "$(shell cygpath -w $(LINK_GLUT))"
