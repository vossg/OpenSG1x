#!gmake

include Common/common.mk

# map some common targets into the Builds/ directory for the current system
# NOTE: this will fail if there are multiple directories for one system (i.e.
# if multiple compilers have been used)

default:
	$(MAKE) -C Builds/${BUILD_ENV}* 
        
opt:
	$(MAKE) -C Builds/${BUILD_ENV}* opt

install:
	cd Builds/${BUILD_ENV}* && $(MAKE) install

clean:
	cd Builds/${BUILD_ENV}* && $(MAKE) clean

ctags:
	ctags -R --c-types=+c --totals -h +.inl --langmap=c++:.h.hpp.cpp.cxx.inl .

etags:
	etags -R --c-types=+c --totals -h +.inl --langmap=c++:.h.hpp.cpp.cxx.inl .

help: 
	@echo "Most targets are only supported inside the Builds/* directories!"
	@echo "Go there and type 'make help' to get a list of possible targets."
	@echo
	@echo "Targets supported on this level:"
	@echo "================================"
	@echo 
	@echo "fcdToBase    run through the tree and regenerate all the Base sources"
	@echo "<default>    go into the Builds directory and call $(MAKE)"
	@echo "install      go into the Builds directory and call $(MAKE) install"
	@echo "clean        go into the Builds directory and call $(MAKE) clean"
	@echo "ctags        create tags file using ctags"
	@echo "etags        create tags file using etags"
	@echo "userdoc      create the HMTL version of the user-level docs"
	@echo "userstarter  create the PS/PDF version of the user-level docs"
	@echo "extdoc       create the HMTL version of the extender-level docs"
	@echo "extstarter   create the PS/PDF version of the extender-level docs"
	@echo "devdoc       create the HMTL version of the developer-level docs"
	@echo "devstarter   create the PS/PDF version of the developer-level docs"
	@echo "alldocs      all of the above docs"


# doc targets

doc: userdoc

alldocs: userdoc extdoc devdoc userstarter extstarter devstarter

userdoc:
	cd Doc && make userdoc

extdoc:
	cd Doc && make extdoc

devdoc:
	cd Doc && make devdoc

userstarter:
	cd Doc && make userstarter

extstarter:
	cd Doc && make extstarter

devstarter:
	cd Doc && make devstarter

# utility targets

fcdToBase:
	@CURRDIR=`pwd`;															\
	FCDEDIT=$${CURRDIR}/Tools/fcdEdit/fcdEdit;								\
	for i in `find .														\
		\( -type d \( -name CVS -o -name Test -o -name Builds -o			\
		   -name Tools -o -name examples -o -name '*/.*' \) -prune \) 		\
		-o -type f -name '*\.fcd' -print` ;									\
	do																		\
		echo $$i ;															\
		cd `dirname $$i` ;													\
		$$FCDEDIT -b `basename $$i`;										\
		cd $$CURRDIR ;														\
	done;																	\
