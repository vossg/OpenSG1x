
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

Clean: SUB_TARGET := Clean
Clean: $(SUB_LIBTARGETS) 

LibClean: SUB_TARGET := LibClean
LibClean: $(SUB_LIBTARGETS) 

DepClean: SUB_TARGET := DepClean
DepClean: $(SUB_LIBTARGETS) 


%.src:
	@if [ -d $* ]; then 													\
		cd $*; 																\
		$(SUB_MAKE) -f $(SUB_MAKEFILE) $(SUB_TARGET) SUB_JOB=$(SUB_JOB); 	\
		cd ..; 																\
	fi
