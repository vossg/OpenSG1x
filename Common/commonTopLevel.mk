
.PHONY: tags

#########################################################################
# Normal lib Targets
#########################################################################

MMAKEPASS:=

ifeq ($(MULTIPASS), 1)
ifdef OSG_BUILD_DLL
dbg: SUB_TARGET += dbg
dbg: 
	@echo ================== LIBPASS ==========================
	$(SUB_MAKE) dbg_lib
	@echo ================== LIBPASS FINISHED =================
	@echo ================== DLLPASS ==========================
	$(SUB_MAKE) dbg_dll 
	@echo ================== LIBPASS FINISHED =================

dbg_lib: MMAKEPASS:=LIBPASS
dbg_lib: $(SUBLIBTARGETS)
	@echo done libs

dbg_dll: MMAKEPASS:=DLLPASS
dbg_dll: $(SUBLIBTARGETS)
	@echo done dlls
else
dbg: SUB_TARGET += dbg
dbg: $(SUBLIBTARGETS) 
endif
else
dbg: SUB_TARGET += dbg
dbg: $(SUBLIBTARGETS) 
endif

ifeq ($(MULTIPASS), 1)
opt: SUB_TARGET += opt
opt: 
	@echo ================== LIBPASS ==========================
	$(SUB_MAKE) opt_lib
	@echo ================== LIBPASS FINISHED =================
	@echo ================== DLLPASS ==========================
	$(SUB_MAKE) opt_dll 
	@echo ================== LIBPASS FINISHED =================

opt_lib: MMAKEPASS:=LIBPASS
opt_lib: $(SUBLIBTARGETS)
	@echo done libs

opt_dll: MMAKEPASS:=DLLPASS
opt_dll: $(SUBLIBTARGETS)
	@echo done dlls
else
opt: SUB_TARGET += opt
opt: $(SUBLIBTARGETS) 
endif

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
ifeq ($(OS_BASE),NT)
	@BUILDLIBS=`find $($(PROJECTPSD)POOL) -name '$(OBJDIR)'					\
						-exec find {} -name '*\.$(SOEXT)' -print \;` ;		\
	if [ -w lib/$(OS)$(DBG) ];												\
	 then																	\
		cd lib/$(OS)$(DBG);													\
		rm -f *.$(SOEXT);													\
		for t in $$BUILDLIBS; 												\
		do																	\
			$(LINK) $$t .;													\
			echo  $$t;														\
		done																\
	fi;																		\
	cd $($(PROJECTPSD)POOL);
endif

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

ifeq ($(MULTIPASS), 1)
%.src:
	@cd $*; \
		$(SUB_MAKE) -f $(SUB_MAKEFILE) MAKEPASS=$(MMAKEPASS) RECURSE=1	\
		$(SUB_TARGET); \
		cd ..;
else
%.src:
	@cd $*; \
		$(SUB_MAKE) -f $(SUB_MAKEFILE) $(SUB_TARGET); cd ..;
endif

%.prj:
	@cd $*; \
		$(SUB_MAKE) -f $(SUB_MAKEFILE) $(SUB_TARGET); cd ..;

TAGS_SUBDIRS := $(filter-out $(TAGS_EXCLUDEDIRS), $(SUBLIBS) )

tags:
	@echo Creating common tags file for directories
	@echo " $(TAGS_SUBDIRS) .."
	@$(TAGS) $(TAGS_OPTIONS) $(TAGS_SUBDIRS)
