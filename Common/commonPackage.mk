
ifneq ($(HAS_INCL),)
INCL_$(OS_BASE) += $(call buildIncPath,$(INCL_DIR)) 
endif

ifneq ($(HAS_LIB),)
LIBPATHS_$(SUB_DIR)     := \
	$(call buildLibPath,$(call cnvSubDirUnix2Win,$(SUB_DIR)))

LIB_FILE_$(SUB_DIR)     := $(call buildLibName,$(PACKAGENAME))

LIB_FILE_DEP_$(SUB_DIR) := \
	$(call buildDepLibPath,$(SUB_DIR))/$(call buildDepLibName,$(PACKAGENAME))
endif
