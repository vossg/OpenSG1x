
INCL$(OS)                 += -I$(OSGPOOL)/Stuff

PROJLIBS$(OS)             += \
	$(OSGPOOL)/Stuff/libStuff.$(OS).a

REQUIRED_SYSTEM_LIBS$(OS) := $(LIBCIO) -lm

POST_LINK_LIBS$(OS)       := \
	$(filter-out $(REQUIRED_SYSTEM_LIBS$(OS)),$(POST_LINK_LIBS$(OS)))

POST_LINK_LIBS$(OS)      += $(REQUIRED_SYSTEM_LIBS$(OS))

