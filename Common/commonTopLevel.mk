
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
depend: $(SUBLIBTARGETS) 

dbgdepend: SUB_TARGET += dbgdepend
dbgdepend: $(SUBLIBTARGETS)

optdepend: SUB_TARGET += optdepend
optdepend: $(SUBLIBTARGETS)

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
Clean: $(SUBLIBTARGETS) 

#########################################################################
# distclean
#########################################################################

distclean: SUB_TARGET += distclean
distclean: $(SUBLIBTARGETS) initclean

initclean: $(SUBLIBTARGETS) $(SUBTESTTARGETS)
	@echo "initclear"
	@-rm -rf bin
	@-rm -rf lib
	@-rm -rf include
	@if [ -w $(DOCBASEDIR) ]; 	\
	 then 						\
		rm -rf $(DOCDIR);		\
	 fi

#########################################################################
# install
#########################################################################

ifeq ($(OSG_DO_INSTALL),1)
install-includes:
	@if [ -w include ]; 													\
	 then																	\
		cd include; 														\
		rm -f *.h *.inl *.h;												\
		find $($(PROJECTPSD)POOL)											\
			\( -type d \( -name CVS -o -name Test -o -name include \) 		\
			   -prune \) 													\
			-o -type f -name '*\.hpp' -print -exec $(LINK) {} . \; ;		\
		find $($(PROJECTPSD)POOL)											\
			\( -type d \( -name CVS -o -name Test -o -name include \) 		\
			   -prune \) 													\
			-o -type f -name '*\.h' -print -exec $(LINK) {} . \; ;			\
		find $($(PROJECTPSD)POOL)											\
			\( -type d \( -name CVS -o -name Test -o -name include \)		\
			   -prune \)													\
			-o -type f -name '*\.inl' -print -exec $(LINK) {} . \; ;		\
	fi;																		\
	cd $($(PROJECTPSD)POOL);

install-libs:
	@BUILDLIBS=`find $($(PROJECTPSD)POOL) -name '$(OBJDIR)'					\
						-exec find {} -name '*\.$(LIBEXT)' -print \;` ;		\
	if [ -w lib/$(OS)$(DBG) ];												\
	 then																	\
		cd lib/$(OS)$(DBG);													\
		rm -f *.$(LIBEXT);													\
		for t in $$BUILDLIBS; 												\
		do																	\
			$(LINK) $$t .;													\
			echo  $$t;														\
		done																\
	fi;																		\
	cd $($(PROJECTPSD)POOL);

install: install-includes install-libs
endif

#########################################################################
# init
#########################################################################

init: SUB_TARGET += init
init: $(SUBLIBTARGETS)
	@echo "init"
ifeq ($(OSG_DO_INSTALL),1)
	@if [ ! -w bin ]; then mkdir bin; fi
	@if [ ! -w bin/$(OS) ]; then mkdir bin/$(OS); fi
	@if [ ! -w lib ]; then mkdir lib; fi
	@if [ ! -w lib/$(OS)DBG ]; then mkdir lib/$(OS)DBG; fi
	@if [ ! -w lib/$(OS)OPT ]; then mkdir lib/$(OS)OPT; fi
	@if [ ! -w include ]; then mkdir include; fi
endif
ifeq ($(OSG_DO_DOC),1)
	@if [ ! -w $(DOCBASEDIR) ]; then mkdir $(DOCBASEDIR); fi
	@if [ ! -w $(DOCDIR) ]; then mkdir $(DOCDIR); fi
endif

doc: 
	$(DOC_ENV) doxygen $(OSGPOOL)/$(OSGCOMMON)/Doxygen$(OS_BASE).cfg

include $(COMMONINCLUDE)

.SUFFIXES:	.src .prj

%.src:
	@cd $*; \
		$(SUB_MAKE) -f $(SUB_MAKEFILE) $(SUB_TARGET); cd ..;

%.prj:
	@cd $*; \
		$(SUB_MAKE) -f $(SUB_MAKEFILE) $(SUB_TARGET); cd ..;

