
.SUFFIXES:	.src .prj

SUB_JOB := admin

#########################################################################
# Parallel Settings
#########################################################################

$(PROJ)TOPMAKEPAR :=

ifdef $(PROJ)TOPPARJOBS
ifneq ($($(PROJ)TOPPARJOBS), 0)
$(PROJ)TOPMAKEPAR = -j $($(PROJ)TOPPARJOBS)
endif
endif

$(PROJ)SUBMAKEPAR :=

ifneq ($($(PROJ)SUBPARJOBS),)
ifneq ($($(PROJ)SUBPARJOBS),0)
$(PROJ)SUBMAKEPAR = -j $($(PROJ)SUBPARJOBS)
endif
endif


SUB_MAKE      := gmake -r -k $($(PROJ)SUBMAKEPAR)

SUB_MAKEFILE  := Makefile

#########################################################################
# Normal lib Targets
#########################################################################

SUB_LIBTARGETS  := $(addsuffix .src, $(SUB_LIBS))

dbg:
	@gmake -k -r $($(PROJ)TOPMAKEPAR) -f Makefile dbg_internal

dbg_internal: SUB_TARGET := dbg
dbg_internal: SUB_JOB := build
dbg_internal: $(SUB_LIBTARGETS) 

opt:
	@gmake -k -r $($(PROJ)TOPMAKEPAR) -f Makefile opt_internal


opt_internal: SUB_TARGET := opt
opt_internal: SUB_JOB := build
opt_internal: $(SUB_LIBTARGETS) 

#########################################################################
# clean
#########################################################################

dbgclean: SUB_TARGET := dbgclean
dbgclean: $(SUB_LIBTARGETS)

optclean: SUB_TARGET := optclean
optclean: $(SUB_LIBTARGETS)

clean: SUB_TARGET := clean
clean: $(SUB_LIBTARGETS)

allclean: dbgclean optclean

dbgClean: SUB_TARGET := dbgClean
dbgClean: $(SUB_LIBTARGETS) 

optClean: SUB_TARGET := optClean
optClean: $(SUB_LIBTARGETS) 

Clean: SUB_TARGET := Clean
Clean: $(SUB_LIBTARGETS) 

LibClean: SUB_TARGET := LibClean
LibClean: $(SUB_LIBTARGETS) 

DepClean: SUB_TARGET := DepClean
DepClean: $(SUB_LIBTARGETS) 

#########################################################################
# install
#########################################################################

install-includes:
	@if [ ! -w include ]; then mkdir include; fi
	@cd include; 														\
	rm -f *.h *.inl *.h;												\
	find $($(PROJ)POOL)							\
		\( -type d \( -name CVS -o -name Test -o -name include -o 		\
		   -name Tools \) -prune \) 									\
		-o -type f -name '*\.hpp' -print -exec $(LINK) {} . \; ;		\
	find $($(PROJ)POOL)							\
		\( -type d \( -name CVS -o -name Test -o -name include  -o 		\
		   -name Tools \) -prune \) 									\
		-o -type f -name '*\.h' -print -exec $(LINK) {} . \; ;			\
	find $($(PROJ)POOL)            				\
		\( -type d \( -name CVS -o -name Test -o -name include \)		\
		   -prune \)													\
		-o -type f -name '*\.inl' -print -exec $(LINK) {} . \; ;		\
	cd ..;

install-libs:
	@if [ ! -w lib ]; then mkdir lib; fi
	@if [ ! -w lib/dbg ]; then mkdir lib/dbg; fi
	@if [ ! -w lib/opt ]; then mkdir lib/opt; fi
	@CURRDIR=`pwd`;                                                          \
	BUILDLIBS=`find $$CURRDIR -name 'lib-dbg' 			        			\
						-exec find {} -name '*\$(SO_SUFFIX)' -print \;` ;	\
	cd lib/dbg;																\
	rm -f *$(SO_SUFFIX);													\
	for t in $$BUILDLIBS; 													\
	do																		\
		echo $$t;															\
		$(LINK) $$t .;														\
	done;                                                                   \
	cd ..;
	@CURRDIR=`pwd`;															\
	BUILDLIBS=`find $$CURRDIR -name 'lib-opt' 			        			\
						-exec find {} -name '*\$(SO_SUFFIX)' -print \;` ;	\
	cd lib/opt;																\
	rm -f *$(SO_SUFFIX);													\
	for t in $$BUILDLIBS; 													\
	do																		\
		echo $$t;															\
		$(LINK) $$t .;														\
	done;																	\
	cd ..;
ifeq ($(OS_BASE),cygwin)
	@CURRDIR=`pwd`;															\
	BUILDLIBS=`find $$CURRDIR -name 'lib-dbg' 			        			\
						-exec find {} -name '*\$(LIB_SUFFIX)' -print \;` ;	\
	cd lib/dbg;																\
	rm -f *$(LIB_SUFFIX);													\
	for t in $$BUILDLIBS; 													\
	do																		\
		echo  $$t;															\
		$(LINK) $$t .;														\
	done;																	\
	cd ..;
	@CURRDIR=`pwd`;															\
	BUILDLIBS=`find $$CURRDIR -name 'lib-opt' 			        			\
						-exec find {} -name '*\$(LIB_SUFFIX)' -print \;` ;	\
	cd lib/opt;																\
	rm -f *$(LIB_SUFFIX);													\
	for t in $$BUILDLIBS; 													\
	do																		\
		echo  $$t;															\
		$(LINK) $$t .;														\
	done;																	\
	cd ..;
endif

install: install-includes install-libs

%.src:
	@if [ -d $* ]; then 													\
		cd $*; 																\
		$(SUB_MAKE) -f $(SUB_MAKEFILE) $(SUB_TARGET) SUB_JOB=$(SUB_JOB); 	\
		cd ..; 																\
	fi
