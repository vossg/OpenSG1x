#
#
# The OSGROOT settings below use an OpenSG installed in the
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

##OSGROOT ?= $(OSGINSTALLPREFIX)

OSGROOT ?= $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)

# use debug or opt libs?
LIBTYPE ?= dbg

### PROJECT ##########################################################
TARGET_TERM = actorEdit
TARGET_GUI  = actorEditGui
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

MOC           :=  $(shell $(OSG_CONFIG) --moc)
UIC           :=  $(shell $(OSG_CONFIG) --uic)
CXX           := "$(shell $(OSG_CONFIG) --compiler --$(LIBTYPE) )"
CXXFLAGS      :=  $(shell $(OSG_CONFIG) --cflags --$(LIBTYPE) Base QT)
ifeq ($(findstring WIN,$(OS)),WIN)
LD            := "$(shell $(OSG_CONFIG) --exe-linker --$(LIBTYPE) )"
else
LD            :=  $(shell $(OSG_CONFIG) --exe-linker --$(LIBTYPE) )
endif
LDFLAGS       :=
LIBS_TERM     :=  $(shell $(OSG_CONFIG) --libs --$(LIBTYPE) Base )
LIBS_GUI      :=  $(shell $(OSG_CONFIG) --libs --$(LIBTYPE) Base System QT )
CMPLR_ID      :=  $(shell $(OSG_CONFIG) --compiler-id)

SYSDEP        :=  $(OS)-$(CMPLR_ID)

# check these (GV)

LINK       := cp
BINSET     := touch
SYSTMP     := /tmp

######################################################################

ifeq ($(TMPBIN),YES)
    SYSTARGET_TERM := $(SYSTMP)$(TARGET_TERM).$(USER)_$(SYSDEP)$(BINSUF)
    SYSTARGET_GUI  := $(SYSTMP)$(TARGET_GUI).$(USER)_$(SYSDEP)$(BINSUF)
    TARGETLNK_TERM := $(SYSTMP)$(TARGET_TERM).$(USER)$(BINSUF)
    TARGETLNK_GUI  := $(SYSTMP)$(TARGET_GUI).$(USER)$(BINSUF)
    LIBTARGET_TERM := $(SYSTMP)/lib$(TARGET_TERM)$(LIBSUF)
    LIBTARGET_GUI  := $(SYSTMP)/lib$(TARGET_GUI)$(LIBSUF)
else
    SYSTARGET_TERM := $(TARGET_TERM).$(SYSDEP)$(BINSUF)
    SYSTARGET_GUI  := $(TARGET_GUI).$(SYSDEP)$(BINSUF)
    TARGETLNK_TERM := $(TARGET_TERM)$(BINSUF)
    TARGETLNK_GUI  := $(TARGET_GUI)$(BINSUF)
    LIBTARGET_TERM := lib$(TARGET_TERM)$(LIBSUF)
    LIBTARGET_GUI  := lib$(TARGET_GUI)$(LIBSUF)
endif

### Object and source files ##########################################

# files that need uic
UIC_IN  := $(wildcard *.ui)
UIC_CPP := $(addsuffix .cpp, $(addsuffix .uic, $(basename $(UIC_IN))))
UIC_HPP := $(addsuffix .h,   $(addsuffix .uic, $(basename $(UIC_IN))))

# files that need moc, i.e. *_qt.h and uic generated files
MOC_IN  := $(sort $(UIC_HPP) $(shell grep -l Q_OBJECT *.[hH]))
MOC_CPP := $(addsuffix .cpp, $(addsuffix _moc, $(basename $(MOC_IN))))

# sources, except the generated ones
SOURCE  := $(filter-out $(UIC_CPP) $(MOC_CPP), $(wildcard *.cpp))

# headers, except the generated ones
HEADERS := $(filter-out $(UIC_HPP), $(wildcard *.h))

# all object files
BINOBJS      := $(addsuffix .$(SYSDEP).o, $(basename $(UIC_CPP) $(MOC_CPP) $(SOURCE)))
BINOBJS_TERM := $(filter-out $(addsuffix .$(SYSDEP).o, $(basename $(MOC_CPP) $(UIC_CPP) $(wildcard *_qt.cpp) $(TARGET_GUI))), $(BINOBJS))
BINOBJS_GUI  := $(filter-out $(addsuffix .$(SYSDEP).o, $(TARGET_TERM)), $(BINOBJS))

# all object files, except the main files
LIBOBJS := $(filter-out $(addsuffix .o, $(TARGET_TERM)) $(addsuffix .o, $(TARGET_GUI)), $(BINOBJS))

######################################################################
### TARGET build rules ###############################################

allstuff : $(TARGET_TERM)$(BINSUF) $(TARGET_GUI)$(BINSUF)

$(TARGET_TERM)$(BINSUF): $(SYSTARGET_TERM)
	@echo "TARGET:   " $(TARGET_TERM)
	@echo "SYSTEM:   " $(SYSDEP)
	@rm -f $(TARGET_TERM)$(BINSUF)
	@rm -f $(TARGETLNK_TERM)
	@$(LINK) $(SYSTARGET_TERM) $(TARGETLNK_TERM)
ifneq ($(TARGETLNK_TERM),$(TARGET_TERM)$(BINSUF))
	@$(LINK) $(TARGETLNK_TERM) $(TARGET_TERM)$(BINSUF)
endif

$(TARGET_GUI)$(BINSUF): $(SYSTARGET_GUI)
	@echo "TARGET:   " $(TARGET_GUI)
	@echo "SYSTEM:   " $(SYSDEP)
	@rm -f $(TARGET_GUI)$(BINSUF)
	@rm -f $(TARGETLNK_GUI)
	@$(LINK) $(SYSTARGET_GUI) $(TARGETLNK_GUI)
ifneq ($(TARGETLNK_GUI),$(TARGET_GUI)$(BINSUF))
	@$(LINK) $(TARGETLNK_GUI) $(TARGET_GUI)$(BINSUF)
endif

$(SYSTARGET_TERM):  $(BINOBJS_TERM)
	@echo ""
	@echo "Linking $(SYSTARGET_TERM) (from $(BINOBJS_TERM))"
	$(LD) $(LDFLAGS) $(BINOBJS_TERM) $(LIBS_TERM) $(LDOUT)$@
	@$(BINSET) $(SYSTARGET_TERM)

$(SYSTARGET_GUI):  $(BINOBJS_GUI)
	@echo ""
	@echo "Linking $(SYSTARGET_GUI) (from $(BINOBJS_GUI))"
	$(LD) $(LDFLAGS) $(BINOBJS_GUI) $(LIBS_GUI) $(LDOUT)$@
	@$(BINSET) $(SYSTARGET_GUI)

dbg:
	$(MAKE) LIBTYPE=dbg

opt:
	$(MAKE) LIBTYPE=opt

######################################################################

.PRECIOUS: %_moc.cpp %.uic.cpp %.uic.h

### Implicit rules ###################################################
%.cpp: %.y
	$(YACC) -ld $< -o $@

%.cpp: %.l
	$(LEX) $< > $@

%.uic.h: %.ui
	@echo "Generating ui declaration: $@  from  $^"
	$(UIC) -o $@ $<

%.uic.cpp: %.ui %.uic.h
	@echo "Generating ui implementation: $@  from  $^"
	$(UIC) -i $*.uic.h -o $@ $<

%_moc.cpp: %.h
	@echo "Qt-precompiling: $@  from  $^"
	$(MOC) -f$< $< -o $@

%.$(SYSDEP).o: %.cc
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.cxx
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.cpp
	@echo "Compiling: $@  from  $^"
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
all: $(TARGET_TERM)$(BINSUF)

clean:
	-rm -f *.$(SYSDEP).o *.$(SYSDEP)*_pure_* *.bak *.swp *~ *% \#*\#
	-rm -f $(TARGET_TERM)$(BINSUF) $(SYSTARGET_TERM)
	-rm -f $(TARGET_GUI)$(BINSUF) $(SYSTARGET_GUI)
	-rm $(shell grep -l "generated from reading ui file" *.h *.cpp)
	-rm $(shell grep -l "This file was generated using the moc" *.h *.cpp)

Clean: clean
	-rm -rf *.o *.mk OOBR* *.dep TAGS tags *.bin

