#
# This is a legacy Makefile. We will replace it with a more OpenSG-style 
# Did it ;-) (GV)
# Makefile later, but for now it has to suffice.
# 
# To compile the proxyBuilder you need your QTDIR to point to a QT-3.0
# installation. The OSGROOT settings below use an OpenSG installed in the
# Builds hierarchy, if yours is elsewhere call make with make OSGROOT=...
#
# If you have trouble making it, talk to us, we can help. See www.opensg.org
# for details.
#

# try to get configured information first, will not work if more
# than one system is configured from one dir. Just for the 1.0

PREFIXSUFFIX := $(shell ../../CommonConf/config.guess)

-include .prefix.$(PREFIXSUFFIX)

OSGROOT ?= $(OSGINSTALLPREFIX)

OSGROOT ?= $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)

# use debug or opt libs?
LIBTYPE ?= opt

ifeq ($(LIBTYPE),opt)
  LIBSUFFIX=
else
  LIBSUFFIX=D
endif

### PROJECT ##########################################################
TARGET = proxyBuilder
PROJINC = -I. -DQT_CLEAN_NAMESPACE # -DOSG_DEBUG
PROJLIB = 
PROBACK = *.ndf
######################################################################

### Common Makefile Declarations #####################################
######################################################################
### Common Makefile Declarations, Johannes Behr 1997,98,99  ##########
######################################################################

### System dependences ###############################################
######################################################################
### Common Makefile Declarations, Johannes Behr 1997,98,99  ##########
######################################################################

### System dependences ###############################################

OS      := $(shell echo `uname`)
OS_TYPE := $(shell echo `uname`_`uname -r`_`uname -p`)

# be very careful with these lines. There needs to be a space after the Unix
# lines and nothing after the win lines!!

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
CXXFLAGS   :=  -I. $(shell $(OSG_CONFIG) --cflags --$(LIBTYPE) Base System QT )
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

# all ui files that neads moc 
UI_IN   := $(wildcard *.ui)
UI_CPP  := $(addsuffix .cpp, $(basename $(addprefix uic_,$(UI_IN)))) 
UI_HPP  := $(addsuffix .h,   $(basename $(addprefix uic_,$(UI_IN)))) 
# all qt files that neads moc. This includes the header generate from .ui 
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
# required dependencies
DEPLIST  := $(addsuffix .$(SYSDEP).dep,$(basename $(SOURCES) ))
# existing dependencies
DEPFOUND := $(filter $(wildcard *.dep),$(DEPLIST))

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
	$(LDPREFIX) $(LD) $(LDFLAGS) $(BINOBJS) $(LIBS) $(LDOUT)$@
	@$(BINSET) $(SYSTARGET)

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

%.$(SYSDEP).dep: %.cpp
	@echo "Updating " $@ 
	@echo "THIS OPERATION IS DISABLED RIGHT NOW !!"
	@echo 
#	@$(MKDEP) $(INCS) -I. $< | sed 's/\.o/\.$(SYSDEP)\.o/' > $@

%.$(SYSDEP).o: %.cc
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.cxx
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.cpp %.$(SYSDEP).dep
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

Clean: clean
	-rm -rf *.o *.mk OOBR* *.dep TAGS tags *.bin


######################################################################

# DO NOT DELETE

OSGProxyBuilderBase.o: OSGProxyBuilderBase.h ./OSGProxyBuilderFields.h
OSGProxyBuilderBase.o: OSGProxyBuilder.h ./OSGProxyBuilderBase.inl
OSGProxyBuilderBase.o: ./OSGProxyBuilder.inl
OSGProxyBuilder.o: OSGProxyBuilder.h OSGProxyBuilderBase.h
OSGProxyBuilder.o: ./OSGProxyBuilderFields.h ./OSGProxyBuilderBase.inl
OSGProxyBuilder.o: ./OSGProxyBuilder.inl
ProxyBuilder.o: OSGProxyBuilder.h OSGProxyBuilderBase.h
ProxyBuilder.o: ./OSGProxyBuilderFields.h ./OSGProxyBuilderBase.inl
ProxyBuilder.o: ./OSGProxyBuilder.inl
