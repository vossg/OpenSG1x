
POST_LINK_LIBS$(OS)       := \
	$(filter-out $(REQUIRED_SYSTEM_LIBS$(OS)),$(POST_LINK_LIBS$(OS)))

POST_LINK_LIBS$(OS)      += $(REQUIRED_SYSTEM_LIBS$(OS))

INCL$(OS)                += $(call buildIncPath,$(INCL_DIR)) 

ifndef PACKAGENAME
ifneq ($(PROJLIBS_FILE_$(SUB_DIR)),)
PROJLIBS_FILE_$(SUB_DIR) := $(call buildLibName,$(PROJLIBS_FILE_$(SUB_DIR)))
endif
else
ifneq ($(PROJLIBS_FILE_$(PACKAGENAME)),)
PROJLIBS_FILE_$(PACKAGENAME) := \
	$(call buildLibName,$(PROJLIBS_FILE_$(PACKAGENAME)))
endif
endif
