#
# This is a legacy Makefile. We will replace it with a more OpenSG-style 
# Did it ;-) (GV)
# Makefile later, but for now it has to suffice.
# 
# To compile the SceneViewer you need your QTDIR to point to a QT-3.0
# installation. The OSGROOT settings below use an OpenSG installed in the
# Builds hierarchy, if yours is elsewhere call make with make OSGROOT=...
#
# If you have trouble making it, talk to us, we can help. See www.opensg.org
# for details.
#

# try to get configured information first, will not work if more
# than one system is configured from one dir. Just for the 1.0

.SUFFIXES := cpp h

PREFIXSUFFIX := $(shell ../../CommonConf/config.guess)

-include .prefix.$(PREFIXSUFFIX)

OSGROOT ?= $(OSGINSTALLPREFIX)

OSGROOT ?= $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)

# use debug or opt libs?
LIBTYPE ?= dbg

# compile fcdCompile
NOGUI ?= false

### PROJECT ##########################################################
ifeq ($(NOGUI),true)
TARGET = fcdCompile
else
TARGET = fcdEdit
endif

######################################################################

### System dependences ###############################################

OS      := $(shell echo `uname`)
OS_TYPE := $(shell echo `uname`_`uname -r`)

# be very careful with these lines. There needs to be a space after the Unix
# lines and nothing after the win lines!!

ifeq ($(OS),IRIX)
    
    	CCOUT := -o 
	LDOUT := -o 
	BINSUF:=

endif
ifeq ($(OS),IRIX64)
    
    	CCOUT := -o 
    	LDOUT := -o 
	BINSUF:=

endif
ifeq ($(OS),Linux)
    
    	CCOUT := -o 
    	LDOUT := -o 
	BINSUF:=

endif
ifeq ($(findstring WIN,$(OS)),WIN)
    
    	OS := WIN32
    	CCOUT := -Fo
    	LDOUT := /out:
	BINSUF := .exe

endif
ifeq ($(OS),HP-UX)
    
    	CCOUT := -o 
    	LDOUT := -o 
	BINSUF:=

endif

### Retrieve osg-info ##########################################

OSG_CONFIG := $(OSGROOT)/bin/osg-config 

MOC        :=  $(shell $(OSG_CONFIG) --moc)

# when OpenSG is not configured with QT compile fcdCompile.
ifeq ($(TARGET), fcdEdit)
	ifeq ($(MOC), moc)
		TARGET = fcdCompile
		NOGUI = true
	endif
endif

UIC        :=  $(shell $(OSG_CONFIG) --uic)
CXX        := "$(shell $(OSG_CONFIG) --compiler --$(LIBTYPE) )"
ifeq ($(NOGUI),true)
CXXFLAGS   :=  $(shell $(OSG_CONFIG) --cflags --$(LIBTYPE) Base System ) -DFCD_TERM
else
CXXFLAGS   :=  $(shell $(OSG_CONFIG) --cflags --$(LIBTYPE) Base QT )
endif

ifeq ($(findstring WIN,$(OS)),WIN)
LD         := "$(shell $(OSG_CONFIG) --exe-linker --$(LIBTYPE) )"
else
LD         := $(shell $(OSG_CONFIG) --exe-linker --$(LIBTYPE) )
endif
LDFLAGS    :=
ifeq ($(NOGUI),true)
LIBS       :=  $(shell $(OSG_CONFIG) --libs --$(LIBTYPE) Base )
else
LIBS       :=  $(shell $(OSG_CONFIG) --libs --$(LIBTYPE) Base QT )
endif
CMPLR_ID   :=  $(shell $(OSG_CONFIG) --compiler-id)

SYSDEP     := $(OS)-$(CMPLR_ID)

# check these (GV)

LINK       := cp
BINSET     := touch
SYSTMP     := /tmp

######################################################################

ifeq ($(TMPBIN),YES)
	SYSTARGET := $(SYSTMP)$(TARGET).$(USER)_$(SYSDEP)$(BINSUF)
	TARGETLNK := $(SYSTMP)$(TARGET).$(USER)$(BINSUF)
	LIBTARGET := $(SYSTMP)/lib$(TARGET)$(LIBSUF)
else
	SYSTARGET := $(TARGET).$(SYSDEP)$(BINSUF)
	TARGETLNK := $(TARGET)$(BINSUF)
	LIBTARGET := lib$(TARGET)$(LIBSUF)
endif

### Object and source files ##########################################

# all ui files that need moc
ifeq ($(NOGUI),false)
UI_IN   := $(wildcard *.ui)
UI_CPP  := $(addsuffix .cpp, $(basename $(addprefix uic_,$(UI_IN)))) 
UI_HPP  := $(addsuffix .h,   $(basename $(addprefix uic_,$(UI_IN)))) 
# all qt files that need moc. This includes the header generate from .ui 
MOC_IN   := $(sort $(UI_HPP) $(shell grep -l Q_OBJECT *.[hH]))
MOC_CPP  := $(addsuffix .cpp, $(basename $(addprefix moc_,$(MOC_IN)))) 
# all source files without generated sources
SOURCES  := $(filter-out $(UI_CPP) $(MOC_CPP), $(wildcard *.[ylcC] *.cc *.cxx *.cpp))
# all headers without generated headers
HEADERS  := $(filter-out $(UI_HPP),$(wildcard *.h *.H *.hh *.hxx *.ui))
# all object files
BINOBJS  := $(addsuffix .$(SYSDEP).o,$(basename $(UI_CPP) $(MOC_CPP) $(SOURCES)))
# all object files without main object
LIBOBJS  := $(filter-out main.$(SYSDEP).o ,$(BINOBJS))
else
SOURCES := main.cpp FieldContainer.cpp Field.cpp
HEADERS := ActionType.h FieldContainer.h Field.h
BINOBJS := main.$(SYSDEP).o FieldContainer.$(SYSDEP).o Field.$(SYSDEP).o
LIBOBJS := FieldContainer.$(SYSDEP).o Field.$(SYSDEP).o
endif
######################################################################
### TARGET build rules ###############################################

allstuff : $(TARGET)$(BINSUF)

$(TARGET)$(BINSUF): $(SYSTARGET) 
	@echo "TARGET:   " $(TARGET)
	@echo "SYSTEM:   " $(SYSDEP)
	@rm -f $(TARGET)$(BINSUF)
	@rm -f $(TARGETLNK)
	@$(LINK) $(SYSTARGET) $(TARGETLNK)
ifneq ($(TARGETLNK),$(TARGET)$(BINSUF))
	@$(LINK) $(TARGETLNK) $(TARGET)$(BINSUF)
endif

$(SYSTARGET):  $(BINOBJS)
	@echo "Linking $(SYSTARGET) (from $(BINOBJS))"
	$(LD) $(LDFLAGS) $(BINOBJS) $(LIBS) $(LDOUT)$@
	@$(BINSET) $(SYSTARGET)


dbg:
	$(MAKE) LIBTYPE=dbg
    
opt:
	$(MAKE) LIBTYPE=opt

######################################################################

.PRECIOUS: moc_%.cpp uic_%.cpp uic_%.h

### Implicit rules ###################################################
%.cpp: %.y
	$(YACC) -ld $< -o $@

%.cpp: %.l
	$(LEX) $< > $@

uic_%.h: %.ui
	$(UIC) -o $@ $<

uic_%.cpp: %.ui uic_%.h
	$(UIC) -i uic_$*.h -o $@ $<

moc_%.cpp: %.h
	$(MOC) -f$< $< -o $@

%.$(SYSDEP).o: %.cc
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.cxx
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< $(CCOUT)$@

%.$(SYSDEP).o: %.C
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.c
	$(CC) $(CXXFLAGS) $<

%.pp: %.cpp
	$(CXX) -E $(CXXFLAGS) $<

######################################################################

######################################################################

### Commands #########################################################
all: $(TARGET)$(BINSUF)
	
clean:
	-rm -f *.$(SYSDEP).o *.$(SYSDEP)*_pure_* *.bak *.swp *~ *% \#*\# 
	-rm -f $(TARGET)$(BINSUF) $(SYSTARGET)
	-rm -f $(shell grep -l "generated from reading ui file" *.h *.cpp)
	-rm -f $(shell grep -l "This file was generated using the moc" *.h *.cpp)

Clean: clean
	-rm -rf *.o OOBR* *.dep TAGS tags *.bin

help:
	@echo "fcdEdit make options"
	@echo "===================="
	@echo ""
	@echo "OSGROOT=[osg root dir] - e.g. .../OpenSG/Builds/i686-pc-cygwin-icl60"
	@echo "LIBTYPE=[opt|dbg]"
	@echo "NOGUI=[true|false]     - compiles fcdCompile with no dependencies to the QT GUI library."

# this doesn't work. Not sure why. :-?
FieldContainer.o: $(wildcard FC*Template*.h)

######################################################################

# DO NOT DELETE

FieldContainer.o: FieldContainer.cpp FieldContainer.h
FieldContainerViewCtl.o: FieldContainerViewCtl.cpp FieldContainerViewCtl.h
Field.o: Field.cpp Field.h
main.o: main.cpp 
ParseComandLine.o: ParseComandLine.cpp ParseComandLine.h
xmlparser.o: xmlparser.cpp xmlparser.hpp
xmlpp.o: xmlpp.cpp xmlpp.hpp
xmltokenizer.o: xmltokenizer.cpp xmltokenizer.hpp
