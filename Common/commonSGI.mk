#-- SGI --------------------------------------------------------------

### Compiler Version ###############################################

COMPILER := $(shell CC -version 2>&1  | cat)

CV := $(word $(words $(COMPILER)),$(COMPILER))
CV := $(subst ., ,$(CV))
CV := $(wordlist 1,1,$(CV))$(wordlist 2,2,$(CV))$(wordlist 3,3,$(CV))

COMPILERVERSION := $(strip $(CV))


### Binaries #######################################################

CC         = CC
C          = cc
AR         = CC -ar -o
CPP        = $(CC) -E
LD_SHARED  = CC -shared
LD         = CC -all -demangle
MOC        = $(QTDIR)/bin/moc
FLEX       = /igd/a4/software/bin/flex
BISON      = /igd/a4/software/bin/bison
STRIP      = strip
LINK       = ln -s
CTAGS      = /igd/a4/software/vim/bin/ctags 

MAKEDEPEND = -M
INCPRE     = -I

XDEBUGER	=	ddd
EDIT		= xemacs
XTERM		= xterm
BINSET      = touch

ISA     = mips3
ABI     = n32
DEFLIBS = 32

LIBCIO = -lCio

### Defines #######################################################

# For QT
DEP_PLATTFORMDEF = -D__sgi -D__EDG__ -D_STANDARD_C_PLUS_PLUS

SOURCE_DEFINES   = 

SYSTEM_DEFINES   =

### Warnings #######################################################

WARNINGS	   		= -fullwarn 

WARNINGS_C_OFF		= # -woff 835

# 1110 : statement is unreachable
# 1174 : Variable declared but never referenced
# 1375 : Base class Destructor not virtual
# 1376 : class has no accessible constructors
# 1424 : The template parameter is not used in declaring the argument types
# 1682 : overloaded virtual function is only partially overridden
# rubens
# warning(3322): omission of explicit type is nonstandard ("int" assumed)

WARNINGS_CPP_OFF 	= #-woff 1110,1174,1375,1682,1424,3322

WARN_ERR_CPP        = -diag_error 1548,1116,1681,1552,3303,1682,1551,1197	\
					  -diag_error 1174,1375


### Language #######################################################

TAGS_OPTIONS        = -R --langmap=c++:+.inl --c-types=+C --totals

LANG_FLAGS          = -LANG:ansi-for-init-scope=off -LANG:restrict			\
					  -LANG:exceptions=off


ifeq ($(COMPILERVERSION),730)
LANG_FLAGS         += -LANG:std
endif

ifeq ($(COMPILERVERSION),731)
LANG_FLAGS         += -LANG:std
endif

COMPILER    		= -$(ABI) -$(ISA) -xansi  -use_readonly_const 			\
					  -no_auto_include $(LANG_FLAGS)

### Optimize / Debug ###############################################

COMP_INLINE := -INLINE:=on

ifeq ($(PRINT_INLINE), 1)
COMP_INLINE := $(COMP_INLINE) -INLINE:list=ON
endif

ifeq ($(DBG), OPT)
	COMP_OPTIMIZE    = -OPT:Olimit=8192 -O3 $(COMP_INLINE)
	COMP_DEBUG       = 
else
	COMP_OPTIMIZE    =
	COMP_DEBUG       = -g -INLINE:none 
endif

### Compiler Flags ################################################


DEFINES     = $(SOURCE_DEFINES) $(SYSTEM_DEFINES) 

# C Compiler Flags

NO_STD_INC     = -I
NO_STD_INC_DEP = -Y

CFLAGS   = $(WARNINGS) $(WARNINGS_C_OFF) -D__STDC__ 						\
		   $(DEFINES) $(COMPILER) $(COMP_OPTIMIZE) $(COMP_DEBUG) 			\
		   $(NO_STD_INC)

# CPP Compiler Flags

CCFLAGS   = $(WARNINGS) $(WARNINGS_CPP_OFF) $(WARN_ERR_CPP) $(DEFINES) \
		    $(COMPILER) $(COMP_OPTIMIZE) $(COMP_DEBUG) $(NO_STD_INC)

# Assembler Flags

ASFLAGS   = $(WARNINGS) $(WARNINGS_C_OFF) $(DEFINES) 	\
	 	    $(COMPILER) $(COMP_OPTIMIZE) $(COMP_DEBUG) $(NO_STD_INC)


# Linker Flags

ifeq ($(PRINT_INLINE), 1)
LINK_INLINE := $(LINK_INLINE) -INLINE:list=ON
endif

ifeq ($(DBG), OPT)
	LINK_OPTIMIZE    = -O3 -OPT:Olimit=8192 $(LINK_INLINE)
	AR_FLAGS         = -O3 -OPT:Olimit=8192 $(LINK_INLINE) 
	LINK_DEBUG       = 
else
	LINK_OPTIMIZE    =
	LINK_DEBUG       = -g 
endif

LD_FLAGS = -L

ifdef LINK_STL
LD_FLAGS += -L$(LINK_STL)
endif

ifdef LINK_GLUT
LD_FLAGS += -L$(LINK_GLUT)
endif

ifdef LINK_QT
LD_FLAGS += -L$(LINK_QT)
endif

LD_FLAGS += -L$(LINK_ISA) -L$(LINK_INTERNAL) 						\
		    -L$(LINK_CPLUSPLUS) 									\
			-$(ABI) -$(ISA) $(LINK_OPTIMIZE) $(LINK_DEBUG)


### ii files ######################################################

II_FILESDIR = $(if $(OBJDIR),$(addprefix $(OBJDIR)/, ii_files),ii_files) \
			  ii_files

II_FILESDIRDBG = $(if $(OBJDIRBASE),\
	$(addprefix $(OBJDIRBASE)DBG/, ii_files),ii_files) \
	ii_files
II_FILESDIROPT = $(if $(OBJDIRBASE),\
	$(addprefix $(OBJDIRBASE)OPT/, ii_files),ii_files) \
	ii_files

INCL$(OS) := -I$(INCLUDE_COMPILER)		\
			 -I$(INCLUDE_SYSTEM)

ifdef INCLUDE_STL
INCL$(OS) := $(INCL$(OS)) -I$(INCLUDE_STL)
endif

INCL$(OS) := $(INCL$(OS)) -I$(INCLUDE_SYSTEM_CC)

ifdef INCLUDE_QT
INCL$(OS) := $(INCL$(OS)) -I$(INCLUDE_QT)
endif

ifdef INCLUDE_GLUT
INCL$(OS) := $(INCL$(OS)) -I$(INCLUDE_GLUT)
endif

# Jo
#-D$(OS)_OS -DNATIVE_CC -DSTL_HSUFFIX
#LEX     = flex -dLst
#YACC    = /sgi/gnu2.7.2/bin/bison
#DFLAG		= -g 
#OPTFLAG =
#LDFLAGS = -o $(SYSTARGET) 
#SYSTMP	= /tmp/
