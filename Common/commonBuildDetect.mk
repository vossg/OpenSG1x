
ifeq ($(DBG),)
DBG_BASE := dbg
endif

#########################################################################
# Get Job Type
#########################################################################

OPT_TARGETS=opt optLnk optClean optclean optCleanLnk optcleanLnk

LNK_TARGETS=dbgLnk optLnk dbgCleanLnk dbgCleanLnk optCleanLnk optcleanLnk \
			cleanLnk CleanLnk

NONBUILDTARGETS    = depend commonclean dbgclean optclean clean commonClean	\
					 dbgClean optClean Clean commonDepClean dbgDepClean		\
					 optDepClean DepClean LibClean dbkLnk cleanLnk

TESTBUILDTARGETS   = Test Tests dbg opt

ifeq ($(MAKECMDGOALS),)
SUB_JOB := build
else
FILTEREDCMDGOALS := $(strip $(filter-out $(NONBUILDTARGETS), $(MAKECMDGOALS)))
FILTEREDTSTGOALS := $(strip $(filter-out $(TESTBUILDTARGETS),$(MAKECMDGOALS)))

ifeq ($(FILTEREDCMDGOALS),)
SUB_JOB := admin
else
SUB_JOB := build
endif
endif

#ifneq ($(MAKECMDGOALS),)

DBGCMDGOAL := $(strip $(filter $(OPT_TARGETS),$(MAKECMDGOALS)))

ifneq ($(DBGCMDGOAL),)
$(warning Detected OPT)
DBG_BASE=opt
DEBUG_VERSION=0
DEBUG_CHAR:=
else
$(warning Detected DBG)
DBG_BASE=dbg
DEBUG_VERSION=1
DEBUG_CHAR:=D
endif

DBGLNKCMDGOAL := $(strip $(filter $(LNK_TARGETS),$(MAKECMDGOALS)))

ifneq ($(DBGLNKCMDGOAL),)
LNK=lnk
LNK_SUFFIX=Lnk
$(warning Detected Link Lib)
else
LNK=
LNK_SUFFIX=
$(warning Detected Shared Lib)
endif

#endif

DBG := $(DBG_BASE)$(LNK)

ifeq ($(MAKECMDGOALS),depend)
OSGNODEPSREBUILD=0
endif

ifeq ($(DEBUG_MAKE),1)
$(warning DBG=$(DBG))
endif
