
#-- WinNT | Intel Compiler ---------------------------------------------------

### General  #######################################################

OBJEXT       :=  obj
LIBEXT       :=  lib
OBJNAMEFLAG  := /Fo
COMPONLYFLAG := /c

### Binaries #######################################################

CC         = $(ICL_BIN)/icl /nologo
C          = $(ICL_BIN)/icl /nologo
AR         = $(ICL_BIN)/xilink /nologo -lib -qv
CPP        = #$(KCC_DIR)/cpp 
LD         = $(ICL_BIN)/xilink 
MOC        = #$(QT_DIR)/bin/moc
FLEX       = #/usr/bin/flex
BISON      = #/usr/bin/bison
STRIP      = #strip
LINK       = cp 
MAKEDEPEND = /QM

XDEBUGER	=	ddd
EDIT		= emacs
XTERM		= xterm
BINSET      = touch

LIBCIO = 


### Defines #######################################################

# For QT
DEP_PLATTFORMDEF = 

SOURCE_DEFINES   = 

SYSTEM_DEFINES   = /DWIN32 /D_DEBUG /D_WINDOWS

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
COMPILER    		= -Qvc6 /MTd /W3 /GX- /Gi- /Od /FD /GZ /GR

### Optimize / Debug ###############################################

ifeq ($(PRINT_INLINE), 1)
COMP_INLINE := 
endif

ifeq ($(DEBUG_VERSION), 0)
	COMP_OPTIMIZE    = 
	COMP_DEBUG       = 
else
	COMP_OPTIMIZE    =
	COMP_DEBUG       = /Z7 /DOSG_DEBUG
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

POST_LINK_LIBS$(OS) :=          \
	/LIBPATH:$(LIB_SYSTEM)		\
	/LIBPATH:$(LIB_COMPILER)

ifneq ($(LINK_STL),)
POST_LINK_LIBS$(OS) := 			\
	$(POST_LINK_LIBS$(OS))		\
	/LIBPATH:$(LINK_STL) 
endif

POST_LINK_LIBS$(OS) := 			\
	$(POST_LINK_LIBS$(OS))		\
	kernel32.lib 				\
	user32.lib      			\
	gdi32.lib 					\
	winspool.lib 				\
	comdlg32.lib 				\
	advapi32.lib				\
	shell32.lib 				\
	ole32.lib 					\
	oleaut32.lib 				\
	uuid.lib 					\
	odbc32.lib 					\
	odbccp32.lib

# Jo
#-D$(OS)_OS -DNATIVE_CC -DSTL_HSUFFIX
#LEX     = flex -dLst
#YACC    = /sgi/gnu2.7.2/bin/bison
#DFLAG		= -g 
#OPTFLAG =
#LDFLAGS = -o $(SYSTARGET) 
#SYSTMP	= /tmp/





