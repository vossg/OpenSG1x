
ifeq ($(OS), Linux)

PINCL$(OS)                := -I$(OSGPOOL)/Action/RenderAction

INCL$(OS)                :=	\
	$(filter-out $(PINCL$(OS)),$(INCL$(OS)))

INCL$(OS)                 += $(PINCL$(OS))

PROJLIBS$(OS)            += $(OSGPOOL)/Action/RenderAction/libRenderAction.$(OS).a

REQUIRED_SYSTEM_LIBS$(OS) =  -lpthread -lm

POST_LINK_LIBS$(OS)       := \
	$(filter-out $(REQUIRED_SYSTEM_LIBS$(OS)),$(POST_LINK_LIBS$(OS)))

POST_LINK_LIBS$(OS)      += $(REQUIRED_SYSTEM_LIBS$(OS))
endif

ifeq ($(OS), IRIX64)

PINCL$(OS)                := -I$(OSGPOOL)/Action/RenderAction

INCL$(OS)                :=	\
	$(filter-out $(PINCL$(OS)),$(INCL$(OS)))

INCL$(OS)                 += $(PINCL$(OS))

PROJLIBS$(OS)            += $(OSGPOOL)/Action/RenderAction/libRenderAction.$(OS).a

ifeq ($(COMPILERVERSION),731)
REQUIRED_SYSTEM_LIBS$(OS) = $(LIBCIO) -lm 
else
REQUIRED_SYSTEM_LIBS$(OS) = -lm 
endif

#REQUIRED_SYSTEM_LIBS$(OS) = $(LIBCIO) -lm

POST_LINK_LIBS$(OS)       := \
	$(filter-out $(REQUIRED_SYSTEM_LIBS$(OS)),$(POST_LINK_LIBS$(OS)))

POST_LINK_LIBS$(OS)      += $(REQUIRED_SYSTEM_LIBS$(OS))
endif

ifeq ($(OS), SunOS)

PINCL$(OS)                := -I$(OSGPOOL)/Action/RenderAction

INCL$(OS)                :=	\
	$(filter-out $(PINCL$(OS)),$(INCL$(OS)))

INCL$(OS)                 += $(PINCL$(OS))

PROJLIBS$(OS)            += $(OSGPOOL)/Action/RenderAction/libRenderAction.$(OS).a

REQUIRED_SYSTEM_LIBS$(OS) =  -lpthread -lm

POST_LINK_LIBS$(OS)       := \
	$(filter-out $(REQUIRED_SYSTEM_LIBS$(OS)),$(POST_LINK_LIBS$(OS)))

POST_LINK_LIBS$(OS)      += $(REQUIRED_SYSTEM_LIBS$(OS))
endif
