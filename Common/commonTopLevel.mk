
.SUFFIXES:	.src .prj

SUB_JOB := admin

INSTLINK := ln -s

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
	@if [ ! -w $(INSTALL_DIR)/include ]; then mkdir $(INSTALL_DIR)/include; fi
	@CURRDIR=`pwd`;                                                     \
	cd $(INSTALL_DIR)/include;											\
	rm -f *.h *.inl *.h;												\
	find $($(PROJ)POOL) -follow							\
		\( -type d \( -name CVS -o -name Test -o -name include -o 		\
		   -name Tools \) -prune \) 									\
		-o -type f -name '*\.hpp' -print -exec $(INSTLINK) {} . \; ;	\
	find $($(PROJ)POOL)	-follow						\
		\( -type d \( -name CVS -o -name Test -o -name include  -o 		\
		   -name Tools \) -prune \) 									\
		-o -type f -name '*\.h' -print -exec $(INSTLINK) {} . \; ;		\
	find $($(PROJ)POOL) -follow           				\
		\( -type d \( -name CVS -o -name Test -o -name include \)		\
		   -prune \)													\
		-o -type f -name '*\.inl' -print -exec $(INSTLINK) {} . \; ;	\
	cd $$CURRDIR;

install-libs:
	@if [ ! -w $(INSTALL_DIR)/lib ]; then mkdir $(INSTALL_DIR)/lib; fi
	@if [ ! -w $(INSTALL_DIR)/lib/dbg ]; then mkdir $(INSTALL_DIR)/lib/dbg; fi
	@if [ ! -w $(INSTALL_DIR)/lib/opt ]; then mkdir $(INSTALL_DIR)/lib/opt; fi
	@CURRDIR=`pwd`;                                                         \
	BUILDLIBS=`find $$CURRDIR -name 'lib-dbg' 			        			\
						-exec find {} -name '*\$(SO_SUFFIX)' -print \;` ;	\
	cd $(INSTALL_DIR)/lib/dbg;												\
	rm -f *$(SO_SUFFIX);													\
	for t in $$BUILDLIBS; 													\
	do																		\
		echo $$t;															\
		$(INSTLINK) $$t .;													\
	done;                                                                   \
	cd $$CURRDIR;
	@CURRDIR=`pwd`;															\
	BUILDLIBS=`find $$CURRDIR -name 'lib-opt' 			        			\
						-exec find {} -name '*\$(SO_SUFFIX)' -print \;` ;	\
	cd $(INSTALL_DIR)/lib/opt;												\
	rm -f *$(SO_SUFFIX);													\
	for t in $$BUILDLIBS; 													\
	do																		\
		echo $$t;															\
		$(INSTLINK) $$t .;													\
	done;																	\
	cd $$CURRDIR;
ifeq ($(OS_BASE),cygwin)
	@CURRDIR=`pwd`;															\
	BUILDLIBS=`find $$CURRDIR -name 'lib-dbg' 			        			\
						-exec find {} -name '*\$(LIB_SUFFIX)' -print \;` ;	\
	cd $(INSTALL_DIR)/lib/dbg;												\
	rm -f *$(LIB_SUFFIX);													\
	for t in $$BUILDLIBS; 													\
	do																		\
		echo  $$t;															\
		$(INSTLINK) $$t .;													\
	done;																	\
	cd $$CURRDIR;
	@CURRDIR=`pwd`;															\
	BUILDLIBS=`find $$CURRDIR -name 'lib-opt' 			        			\
						-exec find {} -name '*\$(LIB_SUFFIX)' -print \;` ;	\
	cd $(INSTALL_DIR)/lib/opt;												\
	rm -f *$(LIB_SUFFIX);													\
	for t in $$BUILDLIBS; 													\
	do																		\
		echo  $$t;															\
		$(INSTLINK) $$t .;													\
	done;																	\
	cd $$CURRDIR;
endif

install-includes-ln: INSTLINK := $(LINK)
install-includes-ln: install-includes

install-includes-cp: INSTLINK := cp
install-includes-cp: install-includes

install-libs-ln: INSTLINK := $(LINK)
install-libs-ln: install-libs

install-libs-cp: INSTLINK := cp
install-libs-cp: install-libs

install-ln: install-includes-ln install-libs-ln
install-cp: install-includes-cp install-libs-cp
install: install-includes-ln install-libs-ln

%.src:
	@if [ -d $* ]; then 													\
		cd $*; 																\
		$(SUB_MAKE) -f $(SUB_MAKEFILE) $(SUB_TARGET) SUB_JOB=$(SUB_JOB); 	\
		cd ..; 																\
	fi
