
#########################################################################
# Build Rules
#########################################################################

.SUFFIXES:	.src $(OBJ_SUFFIX) .cpp .c .hpp .l .y .tab.cpp .tab.h .s 	\
			$(SO_SUFFIX) _moc.o _moc.cpp _qt.hpp

cnvUnix2Win = "$(shell cygpath -w $(1))"

ifeq ($(OS_BASE), cygwin)
$(OBJDIR)/%$(OBJ_SUFFIX): %.cpp
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)"$(OBJDIR)" $(OBJ_OPTION)"$(OBJDIR)\\" $(call cnvUnix2Win,$<)
$(OBJDIR)/%$(OBJ_SUFFIX): %.c
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)"$(OBJDIR)" $(OBJ_OPTION)"$(OBJDIR)\\" $(call cnvUnix2Win,$<)
else
$(OBJDIR)/%$(OBJ_SUFFIX): %.cpp
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)$(OBJDIR) $(OBJ_OPTION) $@ $< $($(PROJ)SODEF)
$(OBJDIR)/%$(OBJ_SUFFIX): %.c
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)$(OBJDIR) $(OBJ_OPTION) $@ $< $($(PROJ)SODEF)
endif

ifeq ($(OS_BASE), cygwin)
$(OBJDIR)/%$(OBJ_SUFFIX): $(OBJDIR)/%.cpp
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)"$(OBJDIR)" $(OBJ_OPTION)"$(OBJDIR)\\" $<

else
$(OBJDIR)/%$(OBJ_SUFFIX): $(OBJDIR)/%.cpp
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)$(OBJDIR) $(OBJ_OPTION) $@ $< $($(PROJ)SODEF)
endif


define win_make_depend 	
	@echo "# Building dependency $(@F) from $(<F)" 				
	@-rm -f $@;													
	@echo '# Module dependencies' > $@							
	@$(CC) $(DEPEND_OPTION) $(call cnvUnix2Win,$<) $(CCFLAGS)   \
	 $(CCLOCALFLAGS) $(COMPONLYFLAG) $(INCL) | 		\
	 $(SED) -e '/:.*\\Microsoft /d' 				\
		 	-e '/:.*\\Intel\\/d' 					\
		 	-e '/:.*\\stdlib/d' 					\
		 	-e 's/\([A-Z]\):/\\\1/' 				\
		 	-e 's/\\/\//g' 							\
		 	-e 's/ /\\ /g' 							\
		 	-e 's/:\\ /: /1' 						\
		 	-e 's///' 								\
		 	-e 's/^\([^\.]*\)$(OBJ_SUFFIX):/$(OBJDIR)\/\1$(DEP_SUFFIX) $(OBJDIR)\/\1$(OBJ_SUFFIX):/1'		\
	 		>> $@
endef

define unix_make_depend
	@echo "# Building dependency $(@F) from $(<F)"
	@-rm -f $@
	@echo '# Module dependencies' > $@
	@$(CC) $(DEPEND_OPTION) $< $(CCFLAGS) $(CCLOCALFLAGS) $(INCL) |\
	 $(SED) -e 's/^\([^:]*:\)/$(OBJDIR)\/\1/1' 	\
			-e '/:.*\/stdlib\//d' 				\
			-e '/:[     ]*\/usr\/include\//d'	\
			-e 's/^\([^\.]*\)$(OBJ_SUFFIX):/\1$(DEP_SUFFIX) \1$(OBJ_SUFFIX):/1' \
			>> $@
endef

ifeq ($(OS_BASE), cygwin)
$(OBJDIR)/%$(DEP_SUFFIX): %.cpp 
	$(win_make_depend)

$(OBJDIR)/%$(DEP_SUFFIX): %.c 
	$(win_make_depend)
else
$(OBJDIR)/%$(DEP_SUFFIX): %.cpp
	$(unix_make_depend)

$(OBJDIR)/%$(DEP_SUFFIX): %.c
	$(unix_make_depend)
endif

#########################################################################
# Automatic Targets Lib Toplevel
#########################################################################

ifneq ($(SUB_SO),)
SubLib: $(LIB_DEPS) $(SUB_SO) 
	@echo "LASTDBG=$(DBG)" > .lastdbg

$(SUB_SO): $(LIBQTMOCSOURCES_CPP) $(LIB_OBJECTS) $(LIBS_DEP)
	@echo $(LIB_OBJECTS) $(AR_FLAGS) $(SUB_SO)
	$(LD_SHARED) $(LD_OUTOPT)$(LD_OUTSPACE)$(SUB_SO) \
		$(call cnvSubDirsUnix2Win,$(LIB_OBJECTS)) $(LIBPATHS) $(LIBS)

#		-Wl,-init -Wl,vscInitSharedObject
endif


#########################################################################
# Automatic Targets Flex
#########################################################################

ifneq ($(LIB_FLEXTARGET_CPP),)
$(LIB_FLEXTARGET_CPP) : $(LIB_FLEXSOURCES)
	$(FLEX) -l -P$(FLEX_INTERNAL) $<
	mv lex.$(FLEX_INTERNAL).c $(FLEX_EXTERNAL)
endif

#########################################################################
# Automatic Targets Bison
#########################################################################

ifneq ($(LIB_BISONTARGET_CPP),)
$(LIB_BISONTARGET_CPP): $(LIB_BISONSOURCES)
	$(BISON) -d -v -p$(BISON_INTERNAL) -b$(BISON_INTERNAL) $<
	mv $(BISON_INTERNAL).tab.c  $(OBJDIR)/$(BISON_EXTERNAL).tab.cpp
	mv $(BISON_INTERNAL).tab.h  $(OBJDIR)/$(BISON_EXTERNAL).tab.h
	mv $(BISON_INTERNAL).output $(OBJDIR)/$(BISON_EXTERNAL).output
endif

#########################################################################
# Normal lib Targets
#########################################################################

dbg: DBG := dbg
dbg: SubLib
	@echo "LASTDBG=dbg" > .lastdbg

opt: DBG := opt
opt: SubLib
	@echo "LASTDBG=dbg" > .lastdbg

#########################################################################
# clean
#########################################################################

commonclean:
	@-rm -f core                       2>/dev/null
	@-rm -f *.pure                     2>/dev/null
	@-rm -f *.idb			           2>/dev/null
	@-rm -f *.pdb				       2>/dev/null
	@-rm -f *.core                     2>/dev/null
	@-rm -f $(OBJDIR)/*$(OBJ_SUFFIX)   2>/dev/null
	@-rm -f $(OBJDIR)/*_moc.cpp        2>/dev/null
	@-rm -f $(OBJDIR)/*.lex.cpp        2>/dev/null
	@-rm -f $(OBJDIR)/*.tab.cpp        2>/dev/null
	@-rm -f $(OBJDIR)/*.tab.h          2>/dev/null
	@-rm -f $(OBJDIR)/*.output         2>/dev/null
ifneq ($(II_FILESDIR),)
	@-rm -rf  $(OBJDIR)/$(II_FILESDIR)  2>/dev/null
endif

dbgclean: DBG := dbg
dbgclean: commonclean

optclean: DBG := opt
optclean: commonclean

clean: commonclean


#########################################################################
# Clean
#########################################################################

commonClean : commonclean DepClean
	@-rm -f $(LIBDIR)/*$(SO_SUFFIX) 2>/dev/null
	@-rm -f so_locations            2>/dev/null

dbgClean: DBG := dbg
dbgClean: commonClean

optClean: DBG := opt
optClean: commonClean

Clean: commonClean

#########################################################################
# DepClean
#########################################################################

commonDepClean:
	@-rm -f $(OBJDIR)/*.d 2>/dev/null

dbgDepClean: DBG := dbg
dbgDepClean: commonDepClean

optDepClean: DBG := opt
optDepClean: commonDepClean

DepClean: commonDepClean

#########################################################################
# LibClean
#########################################################################

LibClean:
ifeq ($(OS_BASE), cygwin)
	@-rm -f $(LIBDIR)/*.exp 			2>/dev/null
	@-rm -f $(LIBDIR)/*.pdb 			2>/dev/null
	-rm -f $(LIBDIR)/*$(LIB_SUFFIX) 	2>/dev/null
	-rm -f $(LIBDIR)/*$(SO_SUFFIX)	 	2>/dev/null
endif

ifeq ($(SUB_JOB), build)
-include $(LIB_DEPS)
endif
