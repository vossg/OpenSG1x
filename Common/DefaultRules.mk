
#########################################################################
# Build Rules
#########################################################################

.SUFFIXES:	.src $(OBJ_SUFFIX) .cpp .c .hpp .l .y .tab.cpp .tab.h .s 	\
			$(SO_SUFFIX) _moc.o _moc.cpp _qt.hpp .inl


cnvUnix2Win = "$(shell cygpath -w $(1))"

ifeq ($(OS_BASE), cygwin)
ifeq ($(OS_CMPLR),bcc)
$(OBJDIR)/%$(OBJ_SUFFIX): %.cpp
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)"$(OBJDIR)" $(INC_OPTION)"."					\
	$(OBJ_OPTION)$(call cnvUnix2Win,$@) $(call cnvUnix2Win,$<)
$(OBJDIR)/%$(OBJ_SUFFIX): %.c
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)"$(OBJDIR)" $(INC_OPTION)"."					\
	 $(OBJ_OPTION) $(call cnvUnix2Win,$@) $(call cnvUnix2Win,$<)
else
ifeq ($(OS_CMPLR),g++)
$(OBJDIR)/%$(OBJ_SUFFIX): %.cpp
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)$(OBJDIR) $(INC_OPTION).						\
	 $(OBJ_OPTION) $@ $< $($(PROJ)SODEF)
$(OBJDIR)/%$(OBJ_SUFFIX): %.c
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)$(OBJDIR) $(INC_OPTION).						\
	$(OBJ_OPTION) $@ $< $($(PROJ)SODEF)
else
$(OBJDIR)/%$(OBJ_SUFFIX): %.cpp
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)"$(OBJDIR)" $(INC_OPTION)"."					\
	$(OBJ_OPTION)"$(OBJDIR)\\" $(call cnvUnix2Win,$<)
$(OBJDIR)/%$(OBJ_SUFFIX): %.c
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)"$(OBJDIR)" $(INC_OPTION)"."					\
	 $(OBJ_OPTION)"$(OBJDIR)\\" $(call cnvUnix2Win,$<)
endif
endif
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
ifeq ($(OS_CMPLR),g++)
$(OBJDIR)/%$(OBJ_SUFFIX): $(OBJDIR)/%.cpp
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)$(OBJDIR) $(INC_OPTION).						\
	$(OBJ_OPTION) $@ $< $($(PROJ)SODEF)
else
$(OBJDIR)/%$(OBJ_SUFFIX): $(OBJDIR)/%.cpp
	$(CC) $(CCFLAGS) $(CCLOCALFLAGS) $(COMPONLY_OPTION) $(INCL) \
	$(INC_OPTION)"$(OBJDIR)" $(INC_OPTION)"."					\
	$(OBJ_OPTION)"$(OBJDIR)\\" $<
endif
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

define linux_make_depend
	@echo "# Building dependency $(@F) from $(<F)"
	@-rm -f $@
	@echo '# Module dependencies' > $@
	@$(CC) $(DEPEND_OPTION) $< $(CCFLAGS) $(CCLOCALFLAGS) $(INCL) 	\
	 $(INC_OPTION)$(OBJDIR) $(INC_OPTION). 							\
	 | $(SED) -e 's/^\([^:]*:\)/$(OBJDIR)\/\1/1' 					\
	 		  -e 's/\/usr\/include\/[^ ]*//g'						\
	 		  -e 's/\/usr\/Software\/[^ ]*//g'						\
	 		  -e 's/\/igd\/[^ ]*//g'								\
			  -e 's/.*\.\.\/Base\/[^ ]*//g'							\
			  -e 's/^\([^\.]*\)$(OBJ_SUFFIX):/\1$(DEP_SUFFIX) \1$(OBJ_SUFFIX):/1' \
			>> $@ 
endef

define irix_make_depend
	@echo "# Building dependency $(@F) from $(<F) "
	@-rm -f $@
	@echo '# Module dependencies' > $@
	@$(CC) $(DEPEND_OPTION) $< $(CCFLAGS) $(CCLOCALFLAGS) $(INCL) 	\
	 $(INC_OPTION)$(OBJDIR) $(INC_OPTION).							\
	 | $(SED)	-e 's/^\([^:]*:\)/$(OBJDIR)\/\1/1' 					\
	 		 	-e '/:[     ]*\/usr\/include\//d'					\
				-e '/:.*\/stdlib\//d' 								\
				-e '/:.*\.\.\/Base\//d'								\
				-e 's/^\([^\.]*\)$(OBJ_SUFFIX):/\1$(DEP_SUFFIX) \1$(OBJ_SUFFIX):/1' \
			>> $@
endef

ifeq ($(OS_BASE), cygwin)
$(OBJDIR)/%$(DEP_SUFFIX): %.cpp 
ifneq ($(OSGNODEPSREBUILD),1)
	$(win_make_depend)
else
	@echo "# Skipping dependency $(@F) from $(<F) "
endif

$(OBJDIR)/%$(DEP_SUFFIX): %.c 
ifneq ($(OSGNODEPSREBUILD),1)
	$(win_make_depend)
else
	@echo "# Skipping dependency $(@F) from $(<F) "
endif
endif

ifeq ($(OS_BASE), irix6.5)
$(OBJDIR)/%$(DEP_SUFFIX): %.cpp
ifneq ($(OSGNODEPSREBUILD),1)
	$(irix_make_depend)
else
	@echo "# Skipping dependency $(@F) from $(<F) "
endif

$(OBJDIR)/%$(DEP_SUFFIX): %.c
ifneq ($(OSGNODEPSREBUILD),1)
	$(irix_make_depend)
else
	@echo "# Skipping dependency $(@F) from $(<F) "
endif
endif

ifeq ($(OS_BASE), linux-gnu)
$(OBJDIR)/%$(DEP_SUFFIX): %.cpp
ifneq ($(OSGNODEPSREBUILD),1)
	$(linux_make_depend)
else
	@echo "# Skipping dependency $(@F) from $(<F) "
endif
$(OBJDIR)/%$(DEP_SUFFIX): %.c
ifneq ($(OSGNODEPSREBUILD),1)
	$(linux_make_depend)
else
	@echo "# Skipping dependency $(@F) from $(<F) "
endif
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
SO_INIT_FLAGS = $(LINKER_INIT_FLAG) -Wl,osgInitSharedObject$(PACKAGE_NAME)
else
SO_INIT_FLAGS =
endif
endif

$(PROJ)SUBPRELINKPAR :=

ifeq ($(OS_BASE), irix6.5)
ifneq ($($(PROJ)SUBPARJOBS),)
ifneq ($($(PROJ)SUBPARJOBS),0)
$(PROJ)SUBPRELINKPAR = -J $($(PROJ)SUBPARJOBS)
endif
endif
endif

ifneq ($(SUB_SO),)
SubLib: $(LIB_DEPS) $(SUB_SO) 
	@echo "LASTDBG=$(DBG)" > .lastdbg

$(SUB_SO): $(LIBS_DEP) $(LIB_QTTARGET_CPP) $(LIB_OBJECTS) 
	@echo $(LIB_OBJECTS) $(AR_FLAGS) $(SUB_SO)
	$(LD_SHARED) $($(PROJ)SUBPRELINKPAR) $(LD_OUTOPT)$(LD_OUTSPACE)$(SUB_SO) \
		$(LIBPATHS) $(call cnvSubDirsUnix2Win,$(LIB_OBJECTS)) $(LIBS) 		 \
		$(SO_INIT_FLAGS) $(LD_FLAGS)

$(LIB_QT_TARGET)
$(LIB_QTTARGET_DEPS): $(LIB_QTTARGET_CPP)

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
	@echo Tests done

$(LIB_TESTQT_TARGET)

ifeq ($(IN_TEST_DIR),1)
$(LIB_TESTQTTARGET_DEPS): $(LIB_TESTQTTARGET_CPP)

list: 
	@echo 
	@echo "	available test cases :"
	@echo "	======================\n"
	@for file in $(TEST_TARGETS_LIST); do	\
		echo "		gmake $$file";         	\
	done
	@echo 
	@echo 
endif

#########################################################################
# Automatic Targets Flex
#########################################################################

ifneq ($(LIB_FLEXTARGET_CPP),)
$(OBJDIR)/%.lex.cpp: %.l
	$(FLEX) -l -P$(call flex_int,$<) $<
	@cat lex.$(call flex_int,$<).c | 								\
		sed -e 's/\(yy\)\(text_ptr\)/$(call flex_int,$<)\2/g'		\
		> $(OBJDIR)/$(call flex_ext,$<).lex.cpp
	@-rm lex.$(call flex_int,$<).c

$(LIB_FLEXTARGET_CPP) : $(LIB_FLEXSOURCES)
endif

#########################################################################
# Automatic Targets Bison
#########################################################################

ifneq ($(LIB_BISONTARGET_CPP),)

$(OBJDIR)/%.tab.cpp: %.y
	$(BISON) -d -v -p$(call bison_int,$<) -b$(call bison_int,$<) $<
	mv $(call bison_int,$<).tab.c  $(OBJDIR)/$(call bison_ext,$<).tab.cpp
	mv $(call bison_int,$<).tab.h            $(call bison_ext,$<).tab.h
	mv $(call bison_int,$<).output $(OBJDIR)/$(call bison_ext,$<).output

$(LIB_BISONTARGET_CPP): $(LIB_BISONSOURCES)

$(LIB_BISONTARGET_DEPS): $(LIB_BISONTARGET_CPP)

endif


#########################################################################
# Normal lib Targets
#########################################################################

ifneq ($(IN_TEST_DIR),1)
dbg: DBG := dbg
dbg: SubLib
	@echo "LASTDBG=dbg" > .lastdbg


opt: DBG := opt
opt: SubLib
	@echo "LASTDBG=dbg" > .lastdbg
else
dbg:
	@echo "LASTDBG=dbg" > .lastdbg
opt:
	@echo "LASTDBG=dbg" > .lastdbg
endif

#########################################################################
# depend
#########################################################################

depend_i: $(LIB_DEPS)

depend: DepClean depend_i

#########################################################################
# clean
#########################################################################

commonclean:
	-rm -f core                       2>/dev/null
	-rm -f *.pure                     2>/dev/null
	-rm -f *.idb                      2>/dev/null
	-rm -f *.pdb                      2>/dev/null
	-rm -f *.core                     2>/dev/null
	-rm -f *.stackdump                2>/dev/null
	-rm -f *.h                        2>/dev/null
	-rm -f .lastdbg                   2>/dev/null
	-rm -f $(OBJDIR)/*$(OBJ_SUFFIX)   2>/dev/null
	-rm -f $(OBJDIR)/*_moc.cpp        2>/dev/null
	-rm -f $(OBJDIR)/*.lex.cpp        2>/dev/null
	-rm -f $(OBJDIR)/*.tab.cpp        2>/dev/null
	-rm -f $(OBJDIR)/*.tab.h          2>/dev/null
	-rm -f $(OBJDIR)/*.output         2>/dev/null
ifneq ($(II_FILESDIR),)
	-rm -rf  $(OBJDIR)/$(II_FILESDIR)  2>/dev/null
endif

dbgclean: DBG := dbg
dbgclean: commonclean

optclean: DBG := opt
optclean: commonclean

clean: commonclean


#########################################################################
# Clean
#########################################################################

.PHONY: commonClean

commonClean : commonclean DepClean
	-rm -f $(LIBDIR)/*$(SO_SUFFIX)  2>/dev/null
	-rm -f $(LIBDIR)/*$(LIB_SUFFIX) 2>/dev/null
	-rm -f $(LIBDIR)/*.exp          2>/dev/null
	-rm -f $(LIBDIR)/*.ilk          2>/dev/null
	-rm -f $(LIBDIR)/*.map          2>/dev/null
	-rm -f $(LIBDIR)/*.pdb          2>/dev/null
	-rm -f so_locations             2>/dev/null

dbgClean: DBG := dbg
dbgClean: OBJDIR := $(OBJDIR_BASE)-$(DBG)
dbgClean: LIBDIR := $(LIBDIR_BASE)-$(DBG)
dbgClean: commonClean
	@echo "Done dbgClean"

optClean: DBG := opt
optClean: OBJDIR := $(OBJDIR_BASE)-$(DBG)
optClean: LIBDIR := $(LIBDIR_BASE)-$(DBG)
optClean: commonClean
	@echo "Done optClean"

Clean: commonClean

distclean: 
	@$(SUB_MAKE) dbgClean 
	@$(SUB_MAKE) optClean

#########################################################################
# DepClean
#########################################################################

commonDepClean:
	-rm -f $(OBJDIR)/*.d 2>/dev/null

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
