
#-- SUNOS --------------------------------------------------------------

### Binaries #######################################################

CC         = $(GCC_BIN)/gcc 
C          = $(GCC_BIN)/gcc 
AR         = ar ruv
CPP        = $(GCC_DIR)/cpp 
LD         = $(GCC_BIN)/g++
MOC        = $(QT_DIR)/bin/moc
FLEX       = flex
BISON      = bison
STRIP      = strip
LINK       = ln -s
MAKEDEPEND = -M

XDEBUGER	=	ddd
EDIT		= emacs
XTERM		= xterm
BINSET      = touch

### Defines #######################################################

# For QT
DEP_PLATTFORMDEF =

SOURCE_DEFINES   = -D_GNU_SOURCE

SYSTEM_DEFINES   =

### Warnings #######################################################

WARNINGS	   		= -Wall -pedantic 

WARNINGS_C_OFF		= # -woff 835

# 1110 : statement is unreachable
# 1174 : Variable declared but never referenced
# 1375 : Base class Destructor not virtual
# 1376 : class has no accessible constructors
# 1424 : The template parameter is not used in declaring the argument types
# 1682 : overloaded virtual function is only partially overridden
# rubens
# warning(3322): omission of explicit type is nonstandard ("int" assumed)

WARNINGS_CPP_OFF 	= -Wno-unused -Wno-long-long -Wno-unknown-pragmas  

### Language #######################################################

LANG_FLAGS          = 
COMPILER    		= -ansi  -use_readonly_const -D__EXTENSIONS__=1

### Optimize / Debug ###############################################

ifeq ($(PRINT_INLINE), 1)
COMP_INLINE := 
endif

ifeq ($(DEBUG_VERSION), 0)
	COMP_OPTIMIZE    = -O2
	COMP_DEBUG       = 
else
	COMP_OPTIMIZE    =
	COMP_DEBUG       = -g -DOSG_DEBUG
endif

### Compiler Flags ################################################


DEFINES     = $(SOURCE_DEFINES) $(SYSTEM_DEFINES) 

# C Compiler Flags

NO_STD_INC     = -nostdinc
NO_STD_INC_DEP = -Y

CFLAGS   = $(WARNINGS) $(WARNINGS_C_OFF) -D__STDC__ $(DEFINES) 	\
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
	LINK_OPTIMIZE    = -O2
	AR_FLAGS         = 
	LINK_DEBUG       = 
else
	LINK_OPTIMIZE    =
	LINK_DEBUG       = -g 
endif

LD_FLAGS = -v -Wl,"-zallextract" -Wl,"-zmuldefs" -L -L$(LINK_ISA) $(LINK_OPTIMIZE) $(LINK_DEBUG)


### ii files ######################################################

II_FILESDIR = 

II_FILESDIRDBG = 
II_FILESDIROPT = 

INCL$(OS) := -I$(INCLUDE_COMPILER)		\
			 -I$(INCLUDE_PLATTFORM)		\
		 	 -I$(INCLUDE_SYSTEM)		\
			 -I$(INCLUDE_STL)        	\
			 -I$(INCLUDE_SYSTEM_CC)

# Jo
#-D$(OS)_OS -DNATIVE_CC -DSTL_HSUFFIX
#LEX     = flex -dLst
#YACC    = /sgi/gnu2.7.2/bin/bison
#DFLAG		= -g 
#OPTFLAG =
#LDFLAGS = -o $(SYSTARGET) 
#SYSTMP	= /tmp/
