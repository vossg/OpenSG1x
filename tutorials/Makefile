# trivial makefile for OpenSG tutorials

# set the path to the OpenSG root directory here
OSGPOOL := ..

# you need to copy the options from compiling the library right now
# we'll have an 'opensg-config' similiar to 'glib-config', but it's not here yet 
# and picking the options out of the OpenSG makefiles is hairy :(
# You need to make the libs and 'make install' before trying to compile this

SYSTEM := `uname`

CC := CC

CCFLAGS :=	-DQT_CLEAN_NAMESPACE -DOSG_WITH_GLUT -DOSG_WITH_QT \
			-D_OSG_HAVE_CONFIGURED_H_ -D__sgi -D__EDG__ -D_STANDARD_C_PLUS_PLUS  \
			-n32 -mips3 -xansi  -use_readonly_const -no_auto_include \
			-LANG:ansi-for-init-scope=on -LANG:restrict -LANG:exceptions=ON \
			-LANG:std  -g -INLINE:none  -c  \
			-I$(OSGPOOL)/Builds/mips-sgi-irix6.5-CC/include \
			-I/igd/a4/software/IRIX/include \
			-I/usr/include -I.

LD_FLAGS :=  -n32 -mips3  -g   \
			-L$(OSGPOOL)/Builds/mips-sgi-irix6.5-CC/lib/dbg  \
			-L/igd/a4/software/IRIX/lib   \
			-lOSGWindowGLUT -lOSGSystem  -lOSGBase  \
			-lglut  -lGLU -lGL -lXmu -lXi -lXt -lX11  -lCio -lm

# program dependencies

default:	01hello 02move 03share 04simplegeometry

01hello:      01hello.o 
02move:       02move.o 
03share:      03share.o 
04geometry:   04geometry.o 
05indexgeometry:   05indexgeometry.o 
06multiindexgeometry:   06multiindexgeometry.o 



# make rules

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) -o $@ $< $(LD_FLAGS)
