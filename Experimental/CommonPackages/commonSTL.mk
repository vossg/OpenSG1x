
INCLUDE_STL := 
LINK_STL    := 
LIB_STL     := -lCio

ifneq ($(INCLUDE_STL),)
INCL_$(OS_BASE) := $(INC_OPTION)$(INCLUDE_STL) $(INCL_$(OS_BASE))
endif

ifneq ($(LINK_STL),)
LIBPATHS_$(OS_BASE) := $(LIBPATH_OPTION)$(LINK_STL) $(LIBPATHS_$(OS_BASE))
endif

