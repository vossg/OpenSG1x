# trivial makefile for OpenSG tutorials

# set the path to the OpenSG root directory here
OSGPOOL := ..

# you need to copy the options from compiling the library right now
# we'll have an 'opensg-config' similiar to 'glib-config', but it's not here yet 
# and picking the options out of the OpenSG makefiles is hairy :(
# You need to make the libs and 'make install' before trying to compile this

include common.$(shell uname)

PROGS := 01hello 02move 03share 04geometry 05indexgeometry \
         06multiindexgeometry 07loading 08parloading
                        
clean:
	rm -fr $(PROGS) *.o ii_files
	
# program dependencies

default:	$(PROGS)

01hello:				01hello.o 
02move:					02move.o 
03share:				03share.o 
04geometry:				04geometry.o 
05indexgeometry:		05indexgeometry.o 
06multiindexgeometry:   06multiindexgeometry.o 
07loading:				07loading.o 
08parloading:			08parloading.o 



# make rules

%.o: %.cpp
	echo $(SYSTEM)
	echo $(CC) $(CCFLAGS)
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) -o $@ $< $(LD_FLAGS)
