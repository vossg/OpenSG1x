
.SUFFIXES:	.src .prj

SUB_JOB := admin

INSTLINK := cp

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


SUB_MAKE      := $(MAKE) -r -k $($(PROJ)SUBMAKEPAR)

SUB_MAKEFILE  := Makefile

#########################################################################
# Normal lib Targets
#########################################################################

SUB_LIBTARGETS  := $(addsuffix .src, $(SUB_LIBS))

dbg:
	@$(MAKE) -k -r $($(PROJ)TOPMAKEPAR) -f Makefile dbg_internal

dbg_internal: SUB_TARGET := dbg
dbg_internal: SUB_JOB := build
dbg_internal: $(SUB_LIBTARGETS) 

dbgLnk:
	@$(MAKE) -k -r $($(PROJ)TOPMAKEPAR) -f Makefile dbg_internalLnk

dbg_internalLnk: SUB_TARGET := dbgLnk
dbg_internalLnk: SUB_JOB := build
dbg_internalLnk: $(SUB_LIBTARGETS) 

opt:
	@$(MAKE) -k -r $($(PROJ)TOPMAKEPAR) -f Makefile opt_internal


opt_internal: SUB_TARGET := opt
opt_internal: SUB_JOB := build
opt_internal: $(SUB_LIBTARGETS) 

optLnk:
	@$(MAKE) -k -r $($(PROJ)TOPMAKEPAR) -f Makefile opt_internalLnk


opt_internalLnk: SUB_TARGET := optLnk
opt_internalLnk: SUB_JOB := build
opt_internalLnk: $(SUB_LIBTARGETS) 

#########################################################################
# clean
#########################################################################

dbgclean: SUB_TARGET := dbgclean
dbgclean: $(SUB_LIBTARGETS)

optclean: SUB_TARGET := optclean
optclean: $(SUB_LIBTARGETS)

clean: SUB_TARGET := clean
clean: $(SUB_LIBTARGETS)

cleanLnk: SUB_TARGET := cleanLnk
cleanLnk: $(SUB_LIBTARGETS) $(SUB_APPTARGETS)

allclean: dbgclean optclean

dbgClean: SUB_TARGET := dbgClean
dbgClean: $(SUB_LIBTARGETS) 

optClean: SUB_TARGET := optClean
optClean: $(SUB_LIBTARGETS) 

Clean: SUB_TARGET := Clean
Clean: $(SUB_LIBTARGETS) 

CleanLnk: SUB_TARGET := CleanLnk
CleanLnk: $(SUB_LIBTARGETS) $(SUB_APPTARGETS)

LibClean: SUB_TARGET := LibClean
LibClean: $(SUB_LIBTARGETS) 

DepClean: SUB_TARGET := DepClean
DepClean: $(SUB_LIBTARGETS) 

distclean: SUB_TARGET := distclean
distclean: $(SUB_LIBTARGETS)

#########################################################################
# depend
#########################################################################

depend: SUB_TARGET := depend
depend: $(SUB_LIBTARGETS)

#########################################################################
# install
#########################################################################

install-includes:
	@if [ ! -w $(INSTALL_DIR)/include ]; then mkdir $(INSTALL_DIR)/include; fi
	@if [ ! -w $(INSTALL_DIR)/include/OpenSG ]; then 						 \
		mkdir $(INSTALL_DIR)/include/OpenSG; 								 \
	 fi
	CURRDIR=`pwd`;                                                     	 \
	find $(INSTALL_DIR)/include/OpenSG -follow  -name '*.h' 				 \
		-exec rm -f {} \;       ;											 \
	find $(INSTALL_DIR)/include/OpenSG -follow  -name '*.inl'				 \
		-exec rm -f {} \;       ;											 \
	find $($(PROJ)POOL)	-follow												 \
		\( -type d \( -name CVS -o -name Test -o -name include  -o 			 \
		   -name Tools -o -name '.*' -o -name examples -o					 \
		   -name Templates -o -name Builds -o -name VS \) -prune \) -o 		 \
		   -type f -name '*.h' 			 									 \
	-exec $($(PROJ)POOL)/Common/sedInc {} $(INSTALL_DIR)/include/OpenSG \; ; \
	find $($(PROJ)POOL)	-follow												 \
		\( -type d \( -name CVS -o -name Test -o -name include  -o 			 \
		   -name Tools -o -name '.*' -o -name examples -o					 \
		   -name Templates -o -name Builds -o -name VS \) -prune \) -o 		 \
		   -type f -name '*.inl'			 								 \
	-exec $($(PROJ)POOL)/Common/sedInl {} $(INSTALL_DIR)/include/OpenSG \; ; \
	find $$CURRDIR	-follow												\
		\( -type d \( -name CVS -o -name '*Test' -o -name include  -o	\
		   -name Tools -o -name Builds \) -prune \) 					\
		-o -type f -name '*\.h' 										\
	-exec $($(PROJ)POOL)/Common/sedIncBuild {} $(INSTALL_DIR)/include/OpenSG \; ; \
	find $$CURRDIR -follow           									\
		\( -type d \( -name CVS -o -name '*Test' -o -name include -o	\
		   -name Tools -o -name Builds \) -prune \)						\
		-o -type f -name '*\.inl'  										\
	-exec $($(PROJ)POOL)/Common/sedInl {} $(INSTALL_DIR)/include/OpenSG \; ; \

install-includes-gabe:
	@if [ ! -w $(INSTALL_DIR)/include ]; then mkdir $(INSTALL_DIR)/include; fi
	@if [ ! -w $(INSTALL_DIR)/include/OpenSG ]; then 						 \
		mkdir $(INSTALL_DIR)/include/OpenSG; 								 \
	 fi
	@CURRDIR=`pwd`;                                                     	 \
	find $(INSTALL_DIR)/include/OpenSG -follow  -name '*.h' 				 \
		-exec rm -f {} \;       ;											 \
	find $(INSTALL_DIR)/include/OpenSG -follow  -name '*.inl'				 \
		-exec rm -f {} \;       ;											 \
	find $($(PROJ)POOL)	-follow												 \
		\( -type d \( -name CVS -o -name Test -o -name include  -o 			 \
		   -name Tools -o -name '.*' -o -name examples -o					 \
		   -name Templates -o -name Builds -o -name VS \) -prune \) -o 		 \
		   -type f -name '*.h' 			 									 \
	-exec $(INSTLINK) {} $(INSTALL_DIR)/include/OpenSG \; -print;			 \
	find $($(PROJ)POOL)	-follow												 \
		\( -type d \( -name CVS -o -name Test -o -name include  -o 			 \
		   -name Tools -o -name '.*' -o -name examples -o					 \
		   -name Templates -o -name Builds -o -name VS \) -prune \) -o 		 \
		   -type f -name '*.inl'			 								 \
	-exec $(INSTLINK) {} $(INSTALL_DIR)/include/OpenSG \; -print;			 \
	find $$CURRDIR	-follow												\
		\( -type d \( -name CVS -o -name '*Test' -o -name include  -o	\
		   -name Tools -o -name Builds \) -prune \) 					\
		-o -type f -name '*\.h' 										\
	-exec $(INSTLINK) {} $(INSTALL_DIR)/include/OpenSG \; -print;		\
	find $$CURRDIR -follow           									\
		\( -type d \( -name CVS -o -name '*Test' -o -name include -o	\
		   -name Tools -o -name Builds \) -prune \)						\
		-o -type f -name '*\.inl'  										\
	-exec $(INSTLINK) {} $(INSTALL_DIR)/include/OpenSG \; -print; 		\

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
	@CURRDIR=`pwd`;                                                         \
	BUILDLIBS=`find $$CURRDIR -name 'lib-dbglnk'		        			\
					-exec find {} -name '*\$(LNK_LIB_SUFFIX)' -print \;` ;	\
	cd $(INSTALL_DIR)/lib/dbg;												\
	rm -f *$(LNK_LIB_SUFFIX);												\
	for t in $$BUILDLIBS; 													\
	do																		\
		echo $$t;															\
		$(INSTLINK) $$t .;													\
	done;                                                                   \
	cd $$CURRDIR;
	@CURRDIR=`pwd`;															\
	BUILDLIBS=`find $$CURRDIR -name 'lib-optlnk'		        			\
					-exec find {} -name '*\$(LNK_LIB_SUFFIX)' -print \;` ;	\
	cd $(INSTALL_DIR)/lib/opt;												\
	rm -f *$(LNK_LIB_SUFFIX);												\
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
	for t in $$BUILDLIBS; 													\
	do																		\
		echo  $$t;															\
		$(INSTLINK) $$t .;													\
	done;																	\
	cd $$CURRDIR;
endif


fcdToBase:
	@FCDEDIT=$($(PROJ)POOL)/Tools/fcdEdit/fcdEdit;							\
	CURRDIRBASE=`pwd` ;														\
	cd $($(PROJ)POOL) ;														\
	for i in `find .														\
		\( -type d \( -name CVS -o -name Test -o -name Builds -o			\
		   -name Tools -o -name examples -o -name '*/.*' \) -prune \) 		\
		-o -type f -name '*\.fcd' -print` ;									\
	do																		\
		echo $$i ;															\
		CURRDIR=`pwd` ;														\
		cd `dirname $$i` ;													\
		$$FCDEDIT -b `basename $$i`;										\
		cd $$CURRDIR ;														\
	done;																	\
	cd $$CURRDIRBASE

INSTALL_DIR_SED := $(shell echo $(INSTALL_DIR) | sed -e 's/\//\\\//g')
MOC_LD          := $(shell echo $(LD)          | sed -e 's/\//\\\//g')

install-bin:
	@if [ ! -w $(INSTALL_DIR)/bin ]; then mkdir $(INSTALL_DIR)/bin; fi
	VERSION=`cat $($(PROJ)POOL)/VERSION`; \
	ICOMP=`echo $(CC) | sed -e 's|^[ ]*||' -e 's|[ ]*$$||'`;\
	cat CommonPackages/osg-config |										\
	$(SED) -e 's/@am_gdz_system_flags@/\"$(CCFLAGS_EXT)\"/g'			\
	       -e 's/@am_gdz_system_flags_opt@/\"$(CCFLAGS_EXT_OPT)\"/g'	\
	       -e 's/@am_gdz_system_flags_dbg@/\"$(CCFLAGS_EXT_DBG)\"/g'	\
		   -e 's/@am_gdz_link_flags@/\"$(LD_FLAGS_EXT)\"/g'				\
		   -e 's/@am_gdz_link_flags_opt@/\"$(LD_FLAGS_EXT_OPT)\"/g'		\
		   -e 's/@am_gdz_link_flags_dbg@/\"$(LD_FLAGS_EXT_DBG)\"/g'		\
		   -e 's/@am_gdz_install_dir@/"$(INSTALL_DIR_SED)\"/g'			\
		   -e "s|@am_gdz_compiler@|\"$$ICOMP\"|g"						\
		   -e "s/@am_gdz_version@/$$VERSION/g"							\
		   -e 's/@am_gdz_qt_cflags@/\"$(QT_PLATTFORMDEF_EXT)\"/g'		\
		   -e 's/@am_gdz_exe_linker@/\"$(MOC_LD)\"/g'					\
		   -e "s/@am_gdz_compiler_id@/$(OS_CMPLR)/g"					\
		> $(INSTALL_DIR)/bin/osg-config
	chmod 755 $(INSTALL_DIR)/bin/osg-config

install-libs-ln: INSTLINK := $(LINK)
install-libs-ln: install-libs

install-libs-cp: INSTLINK := cp
install-libs-cp: install-libs

install-ln: install-includes install-libs-ln install-bin
install-cp: install-includes install-libs-cp install-bin
install: install-includes install-libs-cp install-bin

install-gabe: INSTLINK := cp
install-gabe: install-includes-gabe install-libs-cp

%.src:
	@if [ -d $* ]; then 													\
		cd $*; 																\
		$(SUB_MAKE) -f $(SUB_MAKEFILE) $(SUB_TARGET) SUB_JOB=$(SUB_JOB); 	\
		cd ..; 																\
	fi


#########################################################################
# Help Target
#########################################################################

help:
	@echo 
	@echo "Targets supported on this level (Top):"
	@echo "======================================"
	@echo 
	@echo "Creation targets"
	@echo 
	@echo "<default>  compile the same versions of the configured libraries as last time"
	@echo "dbg        compile the debug versions of the configured libraries"
	@echo "opt        compile the optimized versions of the configured libraries"
	@echo "depend     explicitly create the dependency information"
	@echo 
	@echo "Cleanup targets"
	@echo 
	@echo "remove temporary result files: object files, flex/bison/moc output etc.,"
	@echo "dbgclean    for the debugging libraries only"
	@echo "optclean    for the optimized libraries only"
	@echo "clean       for the same libraries as last time"
	@echo "allclean    dbgclean and optclean"
	@echo 
	@echo "remove dependency files"
	@echo "dbgDepClean    for the debugging libraries only"
	@echo "optDepClean    for the optimized libraries only"
	@echo "DepClean       for the same libraries as last time"
	@echo 
	@echo "same as clean + dependencies + results (libs/programs)"
	@echo "dbgClean    for the debugging libraries only"
	@echo "optClean    for the optimized libraries only"
	@echo "Clean       for the same libraries as last time"
	@echo "distclean   dbgClean and optClean"
	@echo 
	@echo "LibClean   remove libraries"
	@echo "ExeClean   remove executables"
	@echo 
	@echo "Installation targets"
	@echo 
	@echo "The installation base directory is the one given to configure as --prefix,"
	@echo "but it can be set on the make line with INSTALL_DIR=<dir>"
	@echo "install the libraries into INSTALL_DIR/lib/{dbg,opt}"
	@echo "install-libs-ln   using links"
	@echo "install-libs-cp   copying them"
	@echo "install-libs      linking or copying them, the same as last time"
	@echo "install-includes  install the include files into INSTALL_DIR/include"
	@echo "install-bin       install osg-config into INSTALL_DIR/bin"
	@echo "install-ln        install-includes + install-libs-ln + install-bin"
	@echo "install-cp        install-includes + install-libs-cp + install-bin"
	@echo "install           install-includes + install-libs-cp + install-bin"
	@echo 
	@echo "Other targets"
	@echo 
	@echo "fcdToBase    run through the tree and regenerate all the Base sources"
	@echo 
	@echo "Useful Environment Variables"
	@echo 
	@echo "OSGSUBPARJOBS     number of parallel compiler jobs to run"
