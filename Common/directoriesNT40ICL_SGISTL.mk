
include $(OSGPOOL)/$(OSGCOMMON)/directoriesNT40ICL.mk

INCLUDE_STL          = /F/Dev/stdlib_0608
INCLUDE_STL         := "$(shell cygpath -w $(INCLUDE_STL))"

#INCLUDE_STLDUMMIES   = /E/Projects/Dummies
#INCLUDE_STLDUMMIES  := "$(shell cygpath -w $(INCLUDE_STLDUMMIES))"

LINK_STL             = /F/Dev/stdlib_0608/Debug
LINK_STL            := "$(shell cygpath -w $(LINK_STL))"
