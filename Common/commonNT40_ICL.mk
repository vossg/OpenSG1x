
#-- WinNT | Intel Compiler ---------------------------------------------------

### General  #######################################################

OBJEXT       :=  obj
LIBEXT       :=  lib
SOEXT        :=  dll
EXEEXT       := .exe
OBJNAMEFLAG  := /Fo
COMPONLYFLAG := /c
#LIBCIO       := libCio.lib
LIBCIO       := 

### Binaries #######################################################

ifdef OSG_BUILD_DLL
CC         = $(ICL_BIN)/icl /nologo /I. 
C          = $(ICL_BIN)/icl /nologo
AR         = $(ICL_BIN)/xilink /nologo /lib /NODEFAULTLIB 
else
CC         = $(ICL_BIN)/icl /nologo  
C          = $(ICL_BIN)/icl /nologo
AR         = $(ICL_BIN)/xilink /nologo /lib /NODEFAULTLIB 
endif

CPP        =  
LD_SHARED  = $(ICL_BIN)/xilink /nologo /dll  /NODEFAULTLIB 
LD         = $(ICL_BIN)/xilink /nologo /NODEFAULTLIB
MOC        = $(QTDIR)/bin/moc
FLEX       = $(CYNWINCONTRIBBIN)/flex
BISON      = $(CYNWINCONTRIBBIN)/bison
STRIP      = strip
LINK       = cp
MAKEDEPEND = /QM

XDEBUGER	=	ddd
EDIT		= emacs
XTERM		= xterm
BINSET      = touch

INCPRE      = /I

### Defines #######################################################

# For QT
DEP_PLATTFORMDEF = 

SOURCE_DEFINES   = 

SYSTEM_DEFINES   = /DWIN32 /D_DEBUG /D_WINDOWS \
				   -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410
ifdef OSG_BUILD_DLL
SYSTEM_DEFINES  += /DOSG_BUILD_DLL
endif

### Warnings #######################################################

WARNINGS	   		= 

WARNINGS_C_OFF		= # -woff 835

# 1110 : statement is unreachable
# 1174 : Variable declared but never referenced
# 1375 : Base class Destructor not virtual
# 1376 : class has no accessible constructors
# 1424 : The template parameter is not used in declaring the argument types
# 1682 : overloaded virtual function is only partially overridden
# rubens
# warning(3322): omission of explicit type is nonstandard ("int" assumed)

WARNINGS_CPP_OFF 	= 

### Language #######################################################

LANG_FLAGS          = 

ifdef OSG_BUILD_DLL
COMPILER    		= -Qvc6 /MDd /W3 /GX- /Gi- /ZI /Od /FD /GZ /GR
else
COMPILER    		= -Qvc6 /MTd /W3 /GX- /Gi- /ZI /Od /FD /GZ /GR
endif

### Optimize / Debug ###############################################

ifeq ($(PRINT_INLINE), 1)
COMP_INLINE := 
endif

ifeq ($(DEBUG_VERSION), 0)
	COMP_OPTIMIZE    = 
	COMP_DEBUG       = 
else
	COMP_OPTIMIZE    =
	COMP_DEBUG       = 
endif

### Compiler Flags ################################################


DEFINES     = $(SOURCE_DEFINES) $(SYSTEM_DEFINES) 

# C Compiler Flags

NO_STD_INC     = /X
NO_STD_INC_DEP = 

CFLAGS   = $(WARNINGS) $(WARNINGS_C_OFF) /D __STDC__ $(DEFINES) 	\
		   $(COMPILER) $(COMP_OPTIMIZE) $(COMP_DEBUG) $(NO_STD_INC)

# CPP Compiler Flags

CCFLAGS   = $(WARNINGS) $(WARNINGS_CPP_OFF) $(DEFINES) \
		    $(COMPILER) $(COMP_OPTIMIZE) $(COMP_DEBUG) $(NO_STD_INC)

# Assembler Flags

ASFLAGS   = $(WARNINGS) $(WARNINGS_C_OFF) $(DEFINES) 	\
	 	    $(COMPILER) $(COMP_OPTIMIZE) $(COMP_DEBUG) $(NO_STD_INC)


# Linker Flags

ifeq ($(PRINT_INLINE), 1)
LINK_INLINE := 
endif

ifeq ($(DEBUG_VERSION), 0)
	LINK_OPTIMIZE    = 
	AR_FLAGS         = 
	LINK_DEBUG       = 
else
	LINK_OPTIMIZE    =
	LINK_DEBUG       = /Debug
endif

LD_FLAGS = /subsystem:console /incremental:no /machine:I386			\
		   $(LINK_OPTIMIZE) $(LINK_DEBUG)

ifneq ($(LINK_STL),)
LD_FLAGS += /LIBPATH:$(LINK_STL)
endif

LD_SHARED_FLAGS = /incremental:no /machine:I386 /subsystem:windows			\
		  	      $(LINK_OPTIMIZE) $(LINK_DEBUG)

ifneq ($(LINK_STL),)
LD_SHARED_FLAGS += /LIBPATH:$(LINK_STL)
endif

### ii files ######################################################

II_FILESDIR = 

II_FILESDIRDBG = 
II_FILESDIROPT = 

INCL$(OS) := 

ifneq ($(INCLUDE_STL),)
INCL$(OS) += /I$(INCLUDE_STL)
endif

ifneq ($(INCLUDE_STLDUMMIES),)
INCL$(OS) += /I$(INCLUDE_STLDUMMIES)
endif

ifneq ($(INCLUDE_COMPILER),)
INCL$(OS) += /I$(INCLUDE_COMPILER)
endif

ifneq ($(INCLUDE_SYSTEM),)
INCL$(OS) += /I$(INCLUDE_SYSTEM)
endif

ifneq ($(INCLUDE_SYSTEM_CC),)
INCL$(OS) += /I$(INCLUDE_SYSTEM_CC)
endif

ifneq ($(INCLUDE_GLUT),)
INCL$(OS) += /I$(INCLUDE_GLUT)
endif

ifneq ($(INCLUDE_QT),)
INCL$(OS) += /I$(INCLUDE_QT)
endif

ifdef OSG_BUILD_DLL
POST_LINK_LIBS$(OS) := \
	/LIBPATH:$(LIB_SYSTEM)		\
	/LIBPATH:$(LIB_COMPILER)	\
	kernel32.lib 				\
	MSVCPRTD.lib				\
	MSVCRTD.lib					\
	libmmd.lib					\
	winmm.lib					
else
POST_LINK_LIBS$(OS) := \
	/LIBPATH:$(LIB_SYSTEM)		\
	/LIBPATH:$(LIB_COMPILER)	\
	kernel32.lib 				\
	libCPMT.lib					\
	libCMT.lib					
endif


#	..\\Log\\libOSGLog.lib		\
#	..\\Field\\libOSGField.lib		\
#	..\\Base\\libOSGBase.lib		\
#
#	..\\FieldContainer\\libOSGFieldContainer.lib		\
#
#	libmmt.lib					\
#	user32.lib      			\
#	gdi32.lib 					\
#	winspool.lib 				\
#	comdlg32.lib 				\
#	advapi32.lib				\
#	shell32.lib 				\
#	ole32.lib 					\
#	oleaut32.lib 				\
#	uuid.lib 					\
#	odbc32.lib 					\
#	odbccp32.lib				\
#	wsock32.lib					\


ifneq ($(LINK_GLUT),)
POST_LINK_LIBS$(OS) := $(POST_LINK_LIBS$(OS)) /LIBPATH:$(LINK_GLUT)
endif

# Jo
#-D$(OS)_OS -DNATIVE_CC -DSTL_HSUFFIX
#LEX     = flex -dLst
#YACC    = /sgi/gnu2.7.2/bin/bison
#DFLAG		= -g 
#OPTFLAG =
#LDFLAGS = -o $(SYSTARGET) 
#SYSTMP	= /tmp/





