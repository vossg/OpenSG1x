
#########################################################################
# Build Rules
#########################################################################

.SUFFIXES:	.src $(OBJ_SUFFIX) .cpp .c .hpp .l .y .tab.cpp .tab.h .s 	\
			$(SO_SUFFIX) _moc.o _moc.cpp _qt.hpp 


cnvUnix2Win = "$(shell cygpath -w $(1))"

ifeq ($(OS_BASE), cygwin)
$(OBJDIR)/%$(OBJ_SUFFIX): %.cpp
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)"$(OBJDIR)" $(INC_OPTION)"."					\
	$(OBJ_OPTION)"$(OBJDIR)\\" $(call cnvUnix2Win,$<)
$(OBJDIR)/%$(OBJ_SUFFIX): %.c
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)"$(OBJDIR)" $(INC_OPTION)"."					\
	 $(OBJ_OPTION)"$(OBJDIR)\\" $(call cnvUnix2Win,$<)
else
$(OBJDIR)/%$(OBJ_SUFFIX): %.cpp
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)$(OBJDIR) $(INC_OPTION).						\
	 $(OBJ_OPTION) $@ $< $($(PROJ)SODEF)
$(OBJDIR)/%$(OBJ_SUFFIX): %.c
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)$(OBJDIR) $(INC_OPTION).						\
	$(OBJ_OPTION) $@ $< $($(PROJ)SODEF)
endif

ifeq ($(OS_BASE), cygwin)
$(OBJDIR)/%$(OBJ_SUFFIX): $(OBJDIR)/%.cpp
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)"$(OBJDIR)" $(INC_OPTION)"."					\
	$(OBJ_OPTION)"$(OBJDIR)\\" $<

else
$(OBJDIR)/%$(OBJ_SUFFIX): $(OBJDIR)/%.cpp
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)$(OBJDIR) $(INC_OPTION).						\
	$(OBJ_OPTION) $@ $< $($(PROJ)SODEF)
endif

ifeq ($(OS_BASE), cygwin)
$(EXEDIR)/%.exe: $(OBJDIR)/%.obj
	$(LD) $< $(LD_FLAGS) $(LDLOCALFLAGS) \
		     $(LIBPATHS) $(LIBS) /out:$@ 
else
$(EXEDIR)/%: $(OBJDIR)/%.o 
	$(CC) $(LD_OUTOPT)$(LD_OUTSPACE)$@ $(LD_FLAGS) $(LDLOCALFLAGS) \
		$(call cnvSubDirsUnix2Win,$<) $(LIBPATHS) $(LIBS)
endif


define win_make_depend 	
	@echo "# Building dependency $(@F) from $(<F)" 				
	@-rm -f $@;													
	@echo '# Module dependencies' > $@							
	@$(CC) $(DEPEND_OPTION) $(call cnvUnix2Win,$<) $(CCFLAGS) $(INC_OPTION)"."\
	 $(CCLOCALFLAGS) $(COMPONLYFLAG) $(INCL) $(INC_OPTION)"$(OBJDIR)" |	\
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
	@$(CC) $(DEPEND_OPTION) $< $(CCFLAGS) $(CCLOCALFLAGS) $(INCL) \
	 $(INC_OPTION)$(OBJDIR) $(INC_OPTION). | \
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

ifeq ($(OS_BASE), cygwin)
$(OBJDIR)/%_qt_moc.cpp: %_qt.h
	$(MOC) $(call cnvUnix2Win,$<) -i -o $@

$(OBJDIR)/%_qt_moc.cpp: %_qt.cpp
	$(MOC) $(call cnvUnix2Win,$<) -i -o $@
else
$(OBJDIR)/%_qt_moc.cpp: %_qt.h
	$(MOC) $< -i -o $@

$(OBJDIR)/%_qt_moc.cpp: %_qt.cpp
	$(MOC) $< -i -o $@
endif

#########################################################################
# Automatic Targets Lib Toplevel
#########################################################################

ifeq ($(OS_BASE), cygwin)
SO_INIT_FLAGS =
else
ifeq ($(SO_NEEDS_INIT),1)
SO_INIT_FLAGS = -Wl,-init -Wl,vscInitSharedObject$(PACKAGE_NAME)
else
SO_INIT_FLAGS =
endif
endif

ifneq ($(SUB_SO),)
SubLib: $(LIB_DEPS) $(SUB_SO) 
	@echo "LASTDBG=$(DBG)" > .lastdbg

$(SUB_SO): $(LIBS_DEP) $(LIB_QTTARGET_CPP) $(LIB_OBJECTS) 
	@echo $(LIB_OBJECTS) $(AR_FLAGS) $(SUB_SO)
	$(LD_SHARED) $(LD_OUTOPT)$(LD_OUTSPACE)$(SUB_SO) \
		$(call cnvSubDirsUnix2Win,$(LIB_OBJECTS)) $(LIBPATHS) $(LIBS) \
		$(SO_INIT_FLAGS) $(LD_FLAGS)

$(LIB_QT_TARGET)
endif

#########################################################################
# Automatic Targets Test Toplevel
#########################################################################

$(TEST_TARGETS): $(TEST_OBJS) $(LIBS_DEP) $(TEST_DEPS)  

$(TEST_TARGETS_IN):  $(LIB_TESTQTTARGET_CPP) $(TEST_TARGETS) 
	@for file in $@; do                \
		echo $$file;                   \
		rm -f $$file;                  \
		ln -s $(EXEDIR)/$$file $$file; \
	done

Test: $(TEST_TARGETS_IN)
	@echo Test

$(LIB_TESTQT_TARGET)

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
	mv $(BISON_INTERNAL).tab.h            $(BISON_EXTERNAL).tab.h
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
# depend
#########################################################################

depend_i: $(LIB_DEPS)

depend: DepClean depend_i

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
	@-rm -f $(LIBDIR)/*$(LIB_SUFFIX) 	2>/dev/null
endif
	@-rm -f $(LIBDIR)/*$(SO_SUFFIX)	 	2>/dev/null

ExeClean:
	@-rm -f $(EXEDIR)/*                 2>/dev/null

ifeq ($(IN_TEST_DIR),0)
ifeq ($(SUB_JOB), build)
-include $(LIB_DEPS)
endif
else
ifeq ($(SUB_JOB), build)
-include $(TEST_DEPS)
endif
endif
