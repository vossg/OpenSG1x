
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
					 optDepClean DepClean LibClean Tests dbkLnk cleanLnk

ifeq ($(MAKECMDGOALS),)
SUB_JOB := build
else
FILTEREDCMDGOALS := $(strip $(filter-out $(NONBUILDTARGETS),$(MAKECMDGOALS)))

ifeq ($(FILTEREDCMDGOALS),)
SUB_JOB := admin
else
SUB_JOB := build
endif
endif

ifneq ($(MAKECMDGOALS),)

DBGCMDGOAL := $(strip $(filter $(OPT_TARGETS),$(MAKECMDGOALS)))

ifneq ($(DBGCMDGOAL),)
DBG_BASE=opt
DEBUG_VERSION=0
$(warning Detected OPT)
else
$(warning Detected DBG)
DBG_BASE=dbg
DEBUG_VERSION=1
endif

DBGLNKCMDGOAL := $(strip $(filter $(LNK_TARGETS),$(MAKECMDGOALS)))

ifneq ($(DBGLNKCMDGOAL),)
LNK=lnk
$(warning Detected Link)
else
LNK=
endif

endif

DBG := $(DBG_BASE)$(LNK)

$(warning DBG=$(DBG))


