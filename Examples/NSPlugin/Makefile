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

PREFIXSUFFIX := $(shell ../../CommonConf/config.guess)

-include .prefix.$(PREFIXSUFFIX)

OSGROOT ?= $(OSGINSTALLPREFIX)

OSGROOT ?= $(wildcard ../../Builds/$(PREFIXSUFFIX)-*)

# use debug or opt libs?
LIBTYPE ?= dbg

### PROJECT ##########################################################
TARGET = npOpenSG
PROJINC = -I. -DQT_CLEAN_NAMESPACE # -DOSG_DEBUG
PROJLIB = # -lefence
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
OS_TYPE := $(shell echo `uname`_`uname -r`)

# be very careful with these lines. There needs to be a space after the Unix
# lines and nothing after the win lines!!

LIBSUF := so

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
	LIBSUF := dll

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
ifeq ($(findstring WIN,$(OS)),WIN)
# we need OSGNSPlugin.res for the mime type and OSGNSPlugin.def to export some functions.
LDFLAGS    :=  /dll OSGNSPlugin.res /def:OSGNSPlugin.def
else
LDFLAGS    :=  -shared
endif
LIBS       :=  $(shell $(OSG_CONFIG) --libs --$(LIBTYPE) Base System QT GLUT )
CMPLR_ID   :=  $(shell $(OSG_CONFIG) --compiler-id)

SYSDEP     := $(OS)-$(CMPLR_ID)

# check these (GV)

LINK       := cp
BINSET     := touch
SYSTMP     := /tmp

######################################################################

ifeq ($(TMPBIN),YES)
	#SYSTARGET := $(SYSTMP)$(TARGET).$(USER)_$(SYSDEP)$(BINSUF)
	SYSTARGET := $(SYSTMP)$(TARGET).$(LIBSUF)
	TARGETLNK := $(SYSTMP)$(TARGET).$(USER)$(BINSUF)
	LIBTARGET := $(SYSTMP)/lib$(TARGET)$(LIBSUF)
else
	SYSTARGET := $(TARGET).$(LIBSUF)
	TARGETLNK := $(TARGET)$(BINSUF)
	LIBTARGET := lib$(TARGET)$(LIBSUF)
endif

### Object and source files ##########################################

HEADERS := $(shell cat declist.mk 2> /dev/null)
SOURCES := $(shell cat implist.mk 2> /dev/null)
BINOBJS := $(shell cat objlist.$(SYSDEP).mk 2> /dev/null ) 
LIBOBJS := $(shell sed -e 2> /dev/null < objlist.$(SYSDEP).mk 's/main\.[a-zA-Z_0-9]*\.o//g' )

#ifeq ($(strip $(HEADERS)),)
#$(warning HEADERS empty, be sure your lists are up to date use $(MAKE) lists to rebuild them) 
#endif

#ifeq ($(strip $(SOURCES)),)
#$(warning SOURCES empty, be sure your lists are up to date use $(MAKE) lists to rebuild them) 
#endif

#ifeq ($(strip $(BINOBJS)),)
#$(warning BINOBJS empty, be sure your lists are up to date use $(MAKE) lists to rebuild them) 
#endif

#ifeq ($(strip $(LIBOBJS)),)
#$(warning LIBOBJS empty, be sure your lists are up to date use $(MAKE) lists to rebuild them) 
#endif


######################################################################

### TARGET build rules ###############################################

allstuff : lists 
	# need to call recursive, as the lists need to be done when make starts
	$(MAKE) $(TARGET)$(LIBSUF)

$(TARGET)$(LIBSUF): $(SYSTARGET) 
	@echo "TARGET:   " $(TARGET)
	@echo "SYSTEM:   " $(SYSDEP)
	@rm -f $(TARGET)$(LIBSUF)
	@rm -f $(TARGETLNK)
#	@$(LINK) $(SYSTARGET) $(TARGETLNK)
#ifneq ($(TARGETLNK),$(TARGET)$(LIBSUF))
#	@$(LINK) $(TARGETLNK) $(TARGET)$(LIBSUF)
#endif

$(SYSTARGET):  $(BINOBJS)
	@echo "Linking $(SYSTARGET) (from $(BINOBJS))"
	$(LDPREFIX) $(LD) $(LDFLAGS) $(BINOBJS) $(LIBS) $(PROJLIB) $(LDOUT)$@
	@$(BINSET) $(SYSTARGET)

######################################################################

.PRECIOUS: moc_%.cpp

### Implicit rules ###################################################
%.cpp: %.y
	$(YACC) -ld $< -o $@

%.cpp: %.l
	$(LEX) $< > $@

%.h: %.ui
	$(UIC) -o $@ $<

%.cpp: %.ui
	$(UIC) -i $*.h -o $@ $<

moc_%.cpp: %.h
	$(MOC) -f$< $< -o $@

%.$(SYSDEP).dep: %.cpp
	@echo "Updating " $@ 
	@echo "THIS OPERATION IS DISABLED RIGHT NOW !!"
	@echo 
#	@$(MKDEP) $(INCS) -I. $< | sed -e 's/\.o/\.$(SYSDEP)\.o/' > $@

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

# Watch out for HP-UX. echo doesn't understand -n, sed ignores incomplete lines...

### File lists #######################################################
lists: declist implist objlist depend 

declist:
	@echo "make declist.mk"
	@rm -f declist.mk
	@echo *.[hH] *.hh *.hxx *.ui " " | \
	sed -e 's/\*\.[a-zA-Z]* //g' | \
	cat >declist.mk

implist: $(PROSRCS)
	@echo "make implist.mk"
	@rm -f implist.mk
	@rm -f moc_*.cpp
	@echo *.y *.l *.c *.C *.cc *.cxx *.cpp " " | \
	sed -e 's/\*\.[a-zA-Z]* //g' | \
	cat >implist.mk

objlist: implist.mk
	@echo "make objlist.$(SYSDEP).mk"
	@rm -f objlist.$(SYSDEP).mk
	@grep -l Q_OBJECT *.[hH] | sed -e 's/^/moc_/g' > objlist.mk
	@cat implist.mk >> objlist.mk
	@cat < objlist.mk | \
	tr '\n' ' ' | tr '\r' ' ' > qtmoc
ifneq ($(findstring HP,$(OS)),HP)
	@echo >> qtmoc
endif
	@cat qtmoc | sed -e 's/\.cc/\.$(SYSDEP)\.o/g' | \
	sed -e 's/\.cxx/\.$(SYSDEP)\.o/g' | \
	sed -e 's/\.cpp/\.$(SYSDEP)\.o/g' | \
	sed -e 's/\.[cC]/\.$(SYSDEP)\.o/g' | \
	sed -e 's/\.[ly]/\.$(SYSDEP)\.o/g' | \
	sed -e 's/\.h/\.$(SYSDEP)\.o/g' | \
	cat > objlist.$(SYSDEP).mk
	@echo >> objlist.$(SYSDEP).mk

deplist.$(SYSDEP).mk:
	@echo "init deplist.$(SYSDEP).mk"
	@echo >deplist.$(SYSDEP).mk ""
	@$(MAKE) lists

depend: implist.mk
	@echo "make deplist.$(SYSDEP).mk"
	@echo "include " | tr '\n' ' ' | tr '\r' ' ' > deplist.$(SYSDEP).mk 
	@cat objlist.$(SYSDEP).mk | \
	sed -e 's/\.o/.dep/g' | \
	cat >> deplist.$(SYSDEP).mk

######################################################################

### Commands #########################################################
all: $(TARGET)$(BINSUF)

uinstall: $(SYSTARGET)
	$(STRIP) $(SYSTARGET)
	cp $(SYSTARGET) $(HOME)/bin/$(OS)/$(TARGET)$(BINSUF)

install: $(SYSTARGET)
	$(STRIP) $(SYSTARGET)
	cp $(SYSTARGET) $(PPOOL)/bin/$(OS)/$(TARGET)$(BINSUF)

lib: $(LIBOBJS)
	rm -f $(LIBTARGET).a
	$(AR) $(LIBTARGET).a $(LIBOBJS)

so: $(LIBOBJS)
	rm -f $(LIBTARGET).so
	$(SOLD) -o $(LIBTARGET).so $(LIBOBJS)

ulibinstall: lib
	mv $(LIBTARGET).a $(HOME)/lib/$(OS)/$(LIBDIR)

libinstall: lib
	mv $(LIBTARGET).a $(PPOOL)/lib/$(OS)/$(LIBDIR)

soinstall: so
	mv $(LIBTARGET).so $(PPOOL)/lib/$(OS)/$(LIBDIR)

usoinstall: so
	mv $(LIBTARGET).so $(HOME)/lib/$(OS)/$(LIBDIR)

incinstall: 
	cp *.h $(PPOOL)/include/$(NAMESPACE)

uincinstall: 
	cp *.h $(HOME)/include/$(NAMESPACE)

soinc: so
	cp *.h $(PPOOL)/include/$(NAMESPACE)
	mv $(LIBTARGET).so $(PPOOL)/lib/$(OS)/$(LIBDIR)

usoinc: so
	cp *.h $(HOME)/include/$(NAMESPACE)
	mv $(LIBTARGET).so $(HOME)/lib/$(OS)/$(LIBDIR)

includelink:
	ln -s $(PWD) $(PPOOL)/include/$(TARGET)

clean:
	-rm -f qtmoc moc_* *.mk *.$(SYSDEP).o *.$(SYSDEP)*_pure_* *.bak *.swp *~ *% \#*\# 
	-rm -f $(TARGET).*

Clean: clean
	-rm -rf *.o *.mk OOBR* *.dep TAGS tags *.bin

run: $(RUN)

xrun: $(SYSTARGET) 
	@echo "RUN: $(SYSTARGET)"
	@$(XTERM) -geometry 80x60+0+0 -bg black -fg green \
	-title '$(SYSTARGET) console' \
	-e $(SYSTARGET) -geometry +200+200

run: $(SYSTARGET)
	@echo "RUN: $(SYSTARGET)"
	$(SYSTARGET) 

strip: $(SYSTARGET)
	@echo "STRIP: $(SYSTARGET)"
	@$(STRIP) $(SYSTARGET)

edit:
	$(EDIT) &

docify:
	mdocify $(HEADERS)

$(DOCDIR):
	mkdir -p $(DOCDIR)

doc: $(DOCDIR)

$(DOCDIR)/tex: doc
	mkdir -p $(DOCDIR)/tex

tex:	$(HEADERS) $(DOCDIR)/tex
	doc++ -t -o $(DOCDIR)/tex/$(TARGET).tex $(HEADERS)

ps: tex
	cd $(DOCDIR)/tex; latex $(TARGET).tex; latex $(TARGET).tex; \
	dvips -o $(TARGET).ps $(TARGET).dvi

$(DOCDIR)/html: doc
	mkdir -p $(DOCDIR)/html

html: $(HEADERS) $(DOCDIR)/html
	doc++ -p -u -H -d $(DOCDIR)/html -b $(HEADERS)

docu: ps html

debug: $(SYSTARGET)
	@echo "DEBUG: $(SYSTARGET)"
	@$(XDEBUGER) --$(DEBUGER) $(SYSTARGET)

count: 
	wc $(HEADERS) $(SOURCES)

tar:
	tar cvf $(TARGET).tar $(HEADERS) $(SOURCES) [Mm]akefile $(PROBACK)

star:
	tar cvf $(TARGET)-src.tar $(HEADERS) $(SOURCES) [Mm]akefile 

tgz: tar
	gzip $(TARGET).tar
	mv $(TARGET).tar $(TARGET).tgz

backup: tar
	mv $(TARGET).tar $(PPOOL)/src/backup

sbackup: star
	mv $(TARGET)-src.tar $(PPOOL)/src/backup

tags: declist.mk implist.mk
	@echo "make tag file"
	@etags -C $(shell cat implist.mk) $(shell cat implist.mk)

######################################################################

