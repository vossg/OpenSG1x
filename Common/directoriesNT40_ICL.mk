
SOFTDIR             ?= /D/Program\ Files/Intel/compiler
MSDIR               ?= /D/Program\ Files/Microsoft\ Visual\ Studio

CYNWINCONTRIB        = /V/Win/NT/cygwin
CYNWINCONTRIBBIN     = $(CYNWINCONTRIB)/bin

INCLUDE_SYSTEM		 = $(MSDIR)/VC98/Include
INCLUDE_SYSTEM      := "$(shell cygpath -w $(INCLUDE_SYSTEM))"

ICL_VERSION          = 45

ICL_BASEDIR          = $(SOFTDIR)$(ICL_VERSION)

INCLUDE_SYSTEM_CC	 = #$(ICL_BASEDIR)/include

ICL_BIN              = $(ICL_BASEDIR)/bin

INCLUDE_COMPILER     = $(ICL_BASEDIR)/include
INCLUDE_COMPILER    := "$(shell cygpath -w $(INCLUDE_COMPILER))"

INCLUDE_STL          = /V/Win/NT/ICL/stdlib_0608
INCLUDE_STL         := "$(shell cygpath -w $(INCLUDE_STL))"

INCLUDE_STLDUMMIES   = /T/Projects/Dummies
INCLUDE_STLDUMMIES  := "$(shell cygpath -w $(INCLUDE_STLDUMMIES))"

LINK_STL             = /V/Win/NT/ICL/stdlib_0608/Debug
LINK_STL            := "$(shell cygpath -w $(LINK_STL))"

LIB_SYSTEM            = $(MSDIR)/lib
LIB_SYSTEM           := "$(shell cygpath -w $(LIB_SYSTEM))"

LIB_COMPILER          = $(ICL_BASEDIR)/lib
LIB_COMPILER         := "$(shell cygpath -w $(LIB_COMPILER))"

QTDIR                   = /V/Win/NT/VC6/qt-2.11
INCLUDE_QT              = $(QTDIR)/include
LINK_QT                 = $(QTDIR)/lib
