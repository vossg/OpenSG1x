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

### PROJECT ##########################################################
TARGET = fcdEdit
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
UIC        :=  $(shell $(OSG_CONFIG) --uic)
CXX        := "$(shell $(OSG_CONFIG) --compiler --$(LIBTYPE) )"
CXXFLAGS   :=  $(shell $(OSG_CONFIG) --cflags --$(LIBTYPE) Base System QT )
ifeq ($(findstring WIN,$(OS)),WIN)
LD         := "$(shell $(OSG_CONFIG) --exe-linker --$(LIBTYPE) )"
else
LD         := $(shell $(OSG_CONFIG) --exe-linker --$(LIBTYPE) )
endif
LDFLAGS    :=
LIBS       :=  $(shell $(OSG_CONFIG) --libs --$(LIBTYPE) Base System QT )
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
	-rm $(shell grep -l "generated from reading ui file" *.h *.cpp)
	-rm $(shell grep -l "This file was generated using the moc" *.h *.cpp)

Clean: clean
	-rm -rf *.o *.mk OOBR* *.dep TAGS tags *.bin

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
