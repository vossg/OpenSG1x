
ifneq ($(HAS_INCL),)
INCL_$(OS_BASE) += $(call buildIncPath,$(INCL_DIR)) 
endif

ifneq ($(HAS_LIB),)
LIBPATHS_$(PACKAGENAME)     := \
	$(call buildLibPath,$(call cnvSubDirUnix2Win,$(SUB_DIR)))

LIB_FILE_$(PACKAGENAME)     := $(call buildLibName,$(LIBNAME))

LIB_FILE_DEP_$(PACKAGENAME) := \
	$(call buildDepLibPath,$(SUB_DIR))/$(call buildDepLibName,$(LIBNAME))
endif
