
ifneq ($(HAS_INCL),)

ifeq ($(BUILD_INC),1)

INCL_$(OS_BASE) += $(call buildIncPath,$(INCL_DIR)) 

else

INCL_DIR := $$

ifeq ($(OS_BASE), cygwin)
ifeq ($(OS_CMPLR),g++)
INCL_DIR := $(INCL_DIR)$(INCL_DIR)BD/$(SUB_DIR)
else
INCL_DIR := "$(INCL_DIR)$(INCL_DIR)BD\$(shell cygpath -w $(SUB_DIR))"
endif
else
INCL_DIR := $(INCL_DIR)$(INCL_DIR)BD/$(SUB_DIR)
endif

INCL_$(OS_BASE) += $(call buildIncPathPlain,$(INCL_DIR)) 

endif

ifndef NO_INCL_EXP
INCL_EXP_$(OS_BASE) += $(call buildIncPathPlain,../../$(SUB_DIR))
endif

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
