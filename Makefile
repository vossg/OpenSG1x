#!gmake -k -r 

OSGCOMMON      ?= Common

#ifndef OSGPOOL
OSGPOOL         = $(shell pwd)
#endif

OSGMAINMAKE    = 1

SUBLIBS        = Base Field FieldContainer Action Action/DrawAction 	\
				 Nodes/Misc Nodes/Geometry Nodes/Light Image Log Loader \
				 Window State 

include $(OSGPOOL)/$(OSGCOMMON)/common.mk

SUB_TARGET =

#########################################################################
# Normal lib Targets
#########################################################################

dbg: SUB_TARGET += dbg
dbg: $(SUBLIBTARGETS) 

opt: SUB_TARGET += opt
opt: $(SUBLIBTARGETS) 

all: libs

libs: SUB_TARGET += SubLib
libs: $(SUBLIBTARGETS) 
	@echo $(SUBLIBTARGETS);

#########################################################################
# depend
#########################################################################

depend: SUB_TARGET += dbgdepend
depend: $(SUBLIBTARGETS) $(SUBTESTTARGETS) 

dbgdepend: SUB_TARGET += dbgdepend
dbgdepend: $(SUBLIBTARGETS) $(SUBTESTTARGETS) 

optdepend: SUB_TARGET += optdepend
optdepend: $(SUBLIBTARGETS) $(SUBTESTTARGETS) 

#########################################################################
# clean
#########################################################################


dbgclean: SUB_TARGET += dbgclean
dbgclean: $(SUBLIBTARGETS)

optclean: SUB_TARGET += optclean
optclean: $(SUBLIBTARGETS)

clean: SUB_TARGET += clean
clean: $(SUBLIBTARGETS)

allclean: dbgclean optclean

Clean: SUB_TARGET += Clean
Clean: $(SUBLIBTARGETS) $(SUBTESTTARGETS)

#########################################################################
# distclean
#########################################################################

distclean: SUB_TARGET += distclean
distclean: $(SUBLIBTARGETS) $(SUBTESTTARGETS) initclean

initclean: $(SUBLIBTARGETS) $(SUBTESTTARGETS)
	@echo "initclear"
	@-rm -rf bin
	@-rm -rf lib
	@if [ -w $(DOCBASEDIR) ]; 	\
	 then 						\
		rm -rf $(DOCDIR);		\
	fi

#########################################################################
# cvs
#########################################################################

commit:
	cvs commit

update:
	cvs update

#########################################################################
# install
#########################################################################

install-includes:
	@if [ -w include ]; 													\
	 then																	\
		cd include; 														\
		rm -f *.hpp *.inl;													\
		find $(OSGPOOL) \( -type d \( -name CVS -o -name Test \) -prune \)	\
			-o -type f -name '*\.h' -print -exec ln -s {} . \; ;			\
		find $(OSGPOOL) \( -type d \( -name CVS -o -name Test \) -prune \)	\
			-o -type f -name '*\.inl' -print -exec ln -s {} . \; ;			\
	fi;																		\
	cd $(VSCPOOL);

install-libs:
	@BUILDLIBS=`find $(OSGPOOL) -name '$(OBJDIR)' 	 						\
						-exec find {} -name '*\.a' -print \;` ;				\
	if [ -w lib/$(OS)$(DBG) ];												\
	 then																	\
		cd lib/$(OS)$(DBG);													\
		rm -f *.a;															\
		for t in $$BUILDLIBS; 												\
		do																	\
			ln -s $$t .;													\
			echo  $$t;														\
		done																\
	fi;																		\
	cd $(OSGPOOL);

install: install-includes install-libs

#########################################################################
# init
#########################################################################

init: SUB_TARGET += init
init: $(SUBLIBTARGETS) $(SUBTESTTARGETS)
	@echo "init"
	@if [ ! -w bin ]; then mkdir bin; fi
	@if [ ! -w bin/$(OS) ]; then mkdir bin/$(OS); fi
	@if [ ! -w lib ]; then mkdir lib; fi
	@if [ ! -w lib/$(OS)DBG ]; then mkdir lib/$(OS)DBG; fi
	@if [ ! -w lib/$(OS)OPT ]; then mkdir lib/$(OS)OPT; fi
	@if [ ! -w include ]; then mkdir include; fi
	@if [ -w $(DOCBASEDIR) ]; 	\
	 then 						\
	 	if [ ! -w $(DOCDIR) ]; 	\
	 	 then 					\
			mkdir $(DOCDIR); 	\
	 	fi 						\
	fi

DOC_HEADER := $(foreach dir,$(SUBLIBS),$(wildcard $(dir)/*.h))

html: 
	@if [ -w $(DOCDIR) ];	 				\
	 then									\
		if [ ! -w $(DOCDIR)/html ];		 	\
		then								\
			mkdir $(DOCDIR)/html;			\
		fi									\
	 fi

doc: 
	$(DOC_ENV) doxygen $(OSGPOOL)/$(OSGCOMMON)/Doxygen$(OS_BASE).cfg

docg:
	$(DOC_ENV) doxygen $(OSGPOOL)/Doxygeng.cfg

docall: html latex 

include $(COMMONINCLUDE)

.SUFFIXES:	.src .o .cpp .c _m.cpp .hpp .l .y .tab.cpp .tab.h .s %.$(SYSDEP).o

%.src:
	@cd $*; \
		$(SUB_MAKE) -f $(SUB_MAKEFILE) $(SUB_TARGET); cd ..;

%.prj:
	@cd $*; \
		$(SUB_MAKE) -f $(SUB_MAKEFILE) $(SUB_TARGET); cd ..;




