
INCL$(OS)                 += -I$(OSGPOOL)/Fhs

PROJLIBS$(OS)             += \
	$(OSGPOOL)/Fhs/libFhs.$(OS).a

REQUIRED_SYSTEM_LIBS$(OS) := $(LIBCIO) -lm

POST_LINK_LIBS$(OS)       := \
	$(filter-out $(REQUIRED_SYSTEM_LIBS$(OS)),$(POST_LINK_LIBS$(OS)))

POST_LINK_LIBS$(OS)      += $(REQUIRED_SYSTEM_LIBS$(OS))

