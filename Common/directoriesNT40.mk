
SOFTDIR              = /D/Program\ Files/Microsoft\ Visual\ Studio/VC98
MEDSOFTDIR           = /D/Program\ Files/Microsoft\ Visual\ Studio/VC98/

INCLUDE_SYSTEM		 = /D/Program\ Files/Microsoft\ Visual\ Studio/VC98/Include
INCLUDE_SYSTEM      := "$(shell cygpath -w $(INCLUDE_SYSTEM))"

ICL_VERSION          = 

ICL_BASEDIR          = $(SOFTDIR)$(ICL_VERSION)

INCLUDE_SYSTEM_CC	 = #$(ICL_BASEDIR)/include

ICL_BIN              = $(ICL_BASEDIR)/bin

INCLUDE_COMPILER     = $(ICL_BASEDIR)/include
INCLUDE_COMPILER    := "$(shell cygpath -w $(INCLUDE_COMPILER))"

INCLUDE_STL          = /F/Dev/stdlib_0608_ms
INCLUDE_STL         := "$(shell cygpath -w $(INCLUDE_STL))"

INCLUDE_STLDUMMIES   = /E/Projects/Dummies
INCLUDE_STLDUMMIES  := "$(shell cygpath -w $(INCLUDE_STLDUMMIES))"

LINK_STL             = /F/Dev/stdlib_0608_ms/Debug
LINK_STL            := "$(shell cygpath -w $(LINK_STL))"

LIB_SYSTEM            = /D/Program\ Files/Microsoft\ Visual\ Studio/VC98/lib
LIB_SYSTEM           := "$(shell cygpath -w $(LIB_SYSTEM))"

LIB_COMPILER          = /D/Program\ Files/Intel/compiler45/lib
LIB_COMPILER         := "$(shell cygpath -w $(LIB_COMPILER))"

INCLUDE_GLUT          = /F/Dev/glut
INCLUDE_GLUT         := "$(shell cygpath -w $(INCLUDE_GLUT))"

LINK_GLUT             = /F/Dev/glut
LINK_GLUT            := "$(shell cygpath -w $(LINK_GLUT))"
