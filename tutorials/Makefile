# trivial makefile for OpenSG tutorials

SYSTEM := $(shell uname)

# set the path to the OpenSG root directory here
OSGPOOL := ..

# the path where GLUT is found
GLUTPATH := /igd/a4/software/$(SYSTEM)

# use debug or opt libs?
DBG := dbg

# you need to copy the options from compiling the library right now
# we'll have an 'opensg-config' similiar to 'glib-config', but it's not here yet 
# and picking the options out of the OpenSG makefiles is hairy :(
# You need to make the libs and 'make install' before trying to compile this

include common.$(SYSTEM)

TUTS :=  $(wildcard [0-9][0-9]*.cpp) 
PROGS := $(TUTS:.cpp=) 
	
# program dependencies

default:	$(PROGS)


# make rules

.PHONY: clean Clean
                  
clean:
	rm -fr *.o ii_files
                        
Clean: clean
	rm -fr $(PROGS) 

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) -o $@ $< $(LD_FLAGS)

%: %.cpp
	$(CC) $(CCFLAGS) $< $(LD_FLAGS) -o $@ 
