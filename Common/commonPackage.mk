
ifneq ($(HAS_INCL),)
INCL_$(OS_BASE) += $(call buildIncPath,$(INCL_DIR)) 
endif

ifneq ($(HAS_LIB),)
LIBPATHS_$(SUB_DIR)     := \
	$(call buildLibPath,$(call cnvSubDirUnix2Win,$(SUB_DIR)))

LIB_FILE_$(SUB_DIR)     := $(call buildLibName,$(PACKAGENAME))

LIB_FILE_$(SUB_DIR)_LNK := $(call buildLnkLibName,$(PACKAGENAME))

ifeq ($(OS_BASE), darwin)
LIB_FILE_$(SUB_DIR)_LNK := -all_load $(LIB_FILE_$(SUB_DIR)_LNK) 
LIB_FILE_$(SUB_DIR)     := -all_load $(LIB_FILE_$(SUB_DIR)) 
endif


LIB_FILE_DEP_$(SUB_DIR) := \
	$(call buildDepLibPath,$(SUB_DIR))/$(call buildDepLibName,$(PACKAGENAME))

LIB_FILE_DEP_$(SUB_DIR)_LNK := \
	$(call buildDepLibPath,$(SUB_DIR))/$(call buildDepLnkLibName,$(PACKAGENAME))
endif
