#
# This is a legacy Makefile. We will replace it with a more OpenSG-style 
# Makefile later, but for now it has to suffice.
# 
# To compile the SceneViewer you need your QTDIR to point to a QT-3.0
# installation. The OSGROOT settings below use an OpenSG installed in the
# Builds hierarchy, if yours is elsewhere call make with make OSGROOT=...
#
# If you have trouble making it, talk to us, we can help. See www.opensg.org
# for details.
#

OSGROOT := $(wildcard ../../Builds/$(shell ../../CommonConf/config.guess)-*)


GCCHOME = /usr
GCCPATH = ${GCCHOME}

### PROJECT ##########################################################
TARGET = osgSceneViewer
PROJINC = -I. # -DOSG_DEBUG
PROJLIB = 
PROBACK = *.ndf
######################################################################

### Build Flags ######################################################
TMPBIN          = NO
DEBUG           = YES
#PURIFYBIN       = YES
#EEFENCE		= YES
#OGLDEBUG       = YES
#TEMPDB          = YES
XRUN		= YES
######################################################################

### System Compiler (GNU_CC/NATIVE_CC) ###############################
CC_Linux  = GNU_CC
CC_SunOS  = GNU_CC
CC_IRIX   = NATIVE_CC
CC_IRIX64 = NATIVE_CC
CC_NT     = NATIVE_CC
######################################################################

### System Flags #####################################################
PRO_FLAG_Linux 	=
PRO_FLAG_SunOS  = 
PRO_FLAG_IRIX   =
PRO_FLAG_IRIX64 = 
PRO_FLAG_NT     =
######################################################################

### Package Declarations #############################################
#PERSONAL_PAK    = YES
SYSTEM_PAK      = YES
STL_PAK         = YES
NET_PAK         = YES
THREAD_PAK      = YES
OSG_DBG_PAK     = YES
OSG_BASE_PAK    = YES
OSG_SYSTEM_PAK  = YES
#OSG_WINDOW_GLUT_PAK  = YES
OSG_WINDOW_QT_PAK  = YES
#OSG_WINDOW_X_PAK  = YES
QT_PAK  = YES
OPENGL_PAK      = YES
GLUT_PAK        = NO
TIFF_PAK        = YES
JPEG_PAK        = YES
######################################################################

### Common Makefile Declarations #####################################
######################################################################
### Common Makefile Declarations, Johannes Behr 1997,98,99  ##########
######################################################################

### System dependences ###############################################
OS := $(shell echo `uname`)
OS_TYPE := $(shell echo `uname`_`uname -r`_`uname -p`)
#-- SUNOS ------------------------------------------------------------
ifeq ($(OS),SunOS)
	GCCHOME = /hgdv/software/gcc/SunOS_5.7_sparc
	GCC     = $(GCCHOME)/bin/gcc
	GCXX    = $(GCCHOME)/bin/g++
	GCXXINC = -I$(GCCHOME)/include/g++-3 
	GCFLAGS = -c -o $@ -D_REENTRANT -Wall -fPIC -ffast-math -funroll-loops -frtti -ansi -Wno-unknown-pragmas -D__EXTENSIONS__
	ifeq ($(TEMPDB),YES)
		GCFLAGS += -fno-implicit-templates
	endif
	GLD     = $(GCCHOME)/bin/g++
	GSO     = $(GCCHOME)/bin/gcc -shared
	NCCHOME =  /solaris/WorkShop5.0/SUNWspro/SC5.0
	NCC     = $(NCCHOME)/bin/cc
	NCXX    = $(NCCHOME)/bin/CC 
	NCXXINC = -I$(NCCHOME)/include/CC -I$(NCCHOME)/include/CCios -I$(NCCHOME)/include/cc
	NCFLAGS = -c -o $@ -mt
	NLD     = CC
	NSO     =

	STRIP   = strip
	AR      = ar ruv 
	LINK    = ln -s
	QTDIR   = /opt/qt
	LEX     = /solaris/bin/flex -dLst
#	YACC    = yacc
	YACC    = /hgdv/software/gnu/SunOS5/bin/bison
	MOC     = $(QTDIR)/bin/moc
	UIC     = $(QTDIR)/bin/uic
	PURIFY  = /hgdv/software/purify/SunOS5/purify
	DFLAG   = -g -D DEBUG
	OPTFLAG = -D NDEBUG
	LDFLAGS = -o $(SYSTARGET)
	SYSTMP	= /tmp/
	XDEBUGER	=	ddd
	EDIT		= xemacs
	XTERM		= rxvt
	BINSET  = touch
	OBJSUF	= o
	BINSUF  =

	EXINC 	= -I$(PPOOL)/include 
	EXLIB 	= -L$(PPOOL)/lib/$(OS)
	SYSINC  = 
  SYSLIB  =  -lm -lposix4
	STLINC  = 
	STLLIB  = 

	NETINC  = 
	NETLIB  = -lresolv -lsocket -lnsl
	#NETLIB  = -lsocket -lnsl
# NETLIB  = -lsocket -lxnet
	#ACEINC  = -I/var/tmp/ACE_wrappers
	#ACEINC  = -I$(PPOOL)/include/ace/version_4.6
	#ACELIB  = -R$(PPOOL)/lib/$(OS) -L$(PPOOL)/lib/$(OS) -lACE$(LIBSUF)
	#ACEINC  = -I/var/tmp/ACE_wrappers -D ACE_LIB
	#ACELIB  = -L/var/tmp/ACE_wrappers/ace -lACE
	ZINC     = -I$(PPOOL)/include/zlib -DZ_LIB
	ZLIB     = -L$(PPOOL)/lib/$(OS) -lz
	SMANINC  = -I$(PPOOL)/include/sman -DSOCKETMAN_LIB
	SMANLIB  = -L$(PPOOL)/lib/$(OS) -lsman
	JPEGINC = -I$(PPOOL)/include/jpeg -DJPEG_LIB
	JPEGLIB = -L$(PPOOL)/lib/jpeg -ljpeg
	AEIINC  = -DAEI_LIB
	AEILIB  = -L$(PPOOL)/lib/$(OS) -laei$(LIBSUF)
	JNIINC  = -I/usr/java/include -I/usr/java/include/solaris -DJNI_LIB
	JNILIB  = 
	TIFFINC = -I$(PPOOL)/include/tiff -DTIFF_LIB
	TIFFLIB = -L$(PPOOL)/lib/$(OS) -ltiff
	GIFINC  = -I$(PPOOL)/include/GIF -DGIF_LIB
	GIFLIB  = -L$(PPOOL)/lib/$(OS) -lGIF$(LIBSUF)
	PNGINC  = -I$(PPOOL)/include/png -DPNG_LIB
	PNGLIB  = -L$(PPOOL)/lib/$(OS) -lpng
	XMLINC  = -D XML_LIB
	XMLLIB  = -L$(PPOOL)/lib/$(OS) -lxml$(LIBSUF)
	ECMAINC	= -I$(PPOOL)/include/js -I$(PPOOL)/include/js/SunOS5.7_DBG.OBJ -DECMA_LIB
	ECMALIB	= -L$(PPOOL)/lib/$(OS) -ljs -lfdm
	VORINC  = -I$(PPOOL)/include/voronoi -D VORONOI_LIB
	VORLIB  = -L$(PPOOL)/lib/$(OS) -lvor$(LIBSUF)
	NMINC   = -I$(PPOOL)/include/newmat
	NMLIB   = -L$(PPOOL)/lib/$(OS) -lnewmat$(LIBSUF)
	COMINC  = -I$(PPOOL)/include
  COMLIB  = -L$(PPOOL)/lib/$(OS) -lcompress$(LIBSUF)
	DYNINC  = -DDYNAMID_LIB
	DYNLIB  = -L$(PPOOL)/lib/$(OS) -lDYNAMID$(LIBSUF)
	HERINC  = -DHERMES_LIB
	HERLIB  = -L$(PPOOL)/lib/$(OS) -lhermes$(LIBSUF) 
	XINC 		= -isystem /usr/openwin/include -D X_LIB
	#XINC 		= -I/usr/openwin/include/ -D X_LIB
	XLIB  	= -R/usr/openwin/lib -L/usr/openwin/lib -lXmu  -lXext -lXt -lXi -lX11
	XPMINC 	= -I$(PPOOL)/include -D XPM_LIB
	XPMLIB 	= -R$(PPOOL)/lib/$(OS) -lXpm
	MINC 		=	-I/usr/dt/include 
	MLIB		= -R/usr/dt/lib -L/usr/dt/lib -lXm 
	QTINC		=	-I$(PPOOL)/include/qt -D QT_LIB -DQT_CLEAN_NAMESPACE
	QTLIB		= -L$(PPOOL)/lib/$(OS) -lqt
	QGLINC	=	-I$(QTDIR)/include -D QGL_LIB
	QGLLIB	= -L$(QTDIR)/lib -lqgl
	PMINC   = -D PMESH_LIB
	PMLIB   = -I$(PPOOL)/lib/$(OS) -lpmesh$(LIBSUF)
	ABINC   = -D ABASE_LIB
	ABLIB 	= -R$(PPOOL)/lib/$(OS) -labase$(LIBSUF)
	TIINC   = -D TEXIMAGE_LIB 
	TILIB   = -R$(PPOOL)/lib/$(OS) -ltexImage$(LIBSUF)
	GSINC   = -D GEOSHAPE_LIB 
	GSLIB   = -R$(PPOOL)/lib/$(OS) -lgeoShape$(LIBSUF)
	CONFINC = -D CONFIG_LIB
	CONFLIB = -L$(PPOOL)/lib/$(OS) -lconfig$(LIBSUF)
	OGLINC	= -isystem /usr/openwin/include -DSUN_OGL -DOPENGL_LIB
	OGLLIB	= -R/usr/openwin/lib -L/usr/openwin/lib -lGLU -lGL
	OGLWINC = -I/usr/openwin/include 
	OGLWLIB = -L/usr/openwin/lib -lGLw
	LUGINC 	= -I/igd/a7/imaging/public/include/lug
	LUGLIB 	= -L/igd/a7/imaging/public/lib
	TTFINC  = -I/$(PPOOL)/include/freetype -D TTF_LIB
	TTFLIB  = -L/$(PPOOL)/lib/$(OS) -lttf
	TMINC   = -D TEXTMAKER_LIB
	TMLIB   = -L/$(PPOOL)/lib/$(OS) -ltextMaker$(LIBSUF)
	GLTTINC = -I/$(PPOOL)/include/gltt -D GLTT_LIB
	GLTTLIB = -L$(PPOOL)/lib/$(OS) -lgltt$(LIBSUF)
	GLUTINC = -I$(PPOOL)/include -DGLUT_LIB
	GLUTLIB = $(PPOOL)/lib/$(OS)/libglut-sm.a
	S3INC = -D S3_LIB
	S3LIB = -L$(PPOOL)/lib/$(OS) -ls3$(LIBSUF)
	HIDINC  = -D HID_LIB
	HIDLIB  = -L$(PPOOL)/lib/$(OS) -lhid$(LIBSUF)
	ESDINC  = -I$(PPOOL)/include/esd -D ESOUND_LIB
	ESDLIB  = -L/zgdv/vc9/avalon/lib/$(OS) -lesd -laudiofile
	#ANIMINC = -I$(PPOOL)/include/ANIM -D ANIM_LIB
	#ANIMLIB = -L$(PPOOL)/lib/$(OS) -lANIM$(LIBSUF) -lvic$(LIBSUF) -lMPEG$(LIBSUF)
	ANIMINC = -I$(PPOOL)/src/mpeg_play -D ANIM_LIB
	ANIMLIB = -L$(PPOOL)/lib/$(OS) -lMPEG$(LIBSUF)
  CAMINC   = -I$(PPOOL)/include -DCAMERA_LIB
  CAMLIB   = -L$(PPOOL)/lib/$(OS) -lcamera \
	 -L/opt/SUNWits/Graphics-sw/xil/lib -lxil    
	#OIINC   = -I/usr1/OpenInventor2.1.1-1/include
	#OILIB   = -L/usr1/OpenInventor2.1.1-1/lib/InventorDebug  -lInventor 
	MEDINC  = -D MEDUSA_LIB
	MEDLIB  = -L$(POOL)/lib/$(OS) -lmedusa$(LIBSUF)
	MICOINC = -I$(PPOOL)/opt/mico/inst/$(OS)/include -D MICO_LIB
	MICOLIB = -L $(PPOOL)/opt/mico/inst/$(OS)/lib -lmico2.3.1 -lmicocoss2.3.1
	THRINC  = 
	THRLIB  = -lpthread 
	LOGINC  = -D LOG_LIB
	LOGLIB  = -L$(PPOOL)/lib/$(OS) -llog$(LIBSUF)
endif
#-- HP-UX ------------------------------------------------------------
ifeq ($(OS),HP-UX)
  GCC     = gcc
  GCXX    = g++
  GCXXINC = 
  GCFLAGS = -c -o $@ -Wall -pedantic -frtti
  ifeq ($(TEMPDB),YES)
	  GCFLAGS += -fno-implicit-templates
  endif
  GLD     = $(GCCHOME)/SunOS_5.5_sparc/bin/g++

	NCC			= /opt/aCC/bin/aCC 
	NCXX		= /opt/aCC/bin/aCC 
	NCXXINC = -I.
  NCFLAGS = -c -o $@
	NLD			= /opt/aCC/bin/aCC 

	STRIP   = strip
	LINK    = ln -s

	LEX     = flex -dLst
	YACC    = bison
	MOC     = $(QTDIR)/bin/moc
	PURIFY  = /hgdv/software/purify/SunOS5/purify
	DFLAG   = -g -D DEBUG
	OPTFLAG = -D NDEBUG
	LDFLAGS = -o $(SYSTARGET)
	SYSTMP	= /tmp/
	XDEBUGER	=	ddd
	EDIT		= xemacs
	XTERM		= rxvt
	BINSET  = touch
	OBJSUF	= o
	BINSUF  =

	EXINC 	= -I$(PPOOL)/include
	EXLIB 	= -L$(PPOOL)/lib/$(OS)
	SYSINC  = 
  SYSLIB  = 

	NETINC  = 
	NETLIB  = -lsocket -lnsl
# NETLIB  = -lsocket -lxnet
	AEIINC  = -DAEI_LIB
	AEILIB  = -L$(PPOOL)/lib/$(OS) -laei$(LIBSUF)
	JPEGINC = -I$(PPOOL)/include/jpeg
	JPEGLIB = -L$(PPOOL)/lib/jpeg -ljpeg
	TIFFINC = -I$(PPOOL)/include/tiff -D TIFF_LIB
	TIFFLIB = -L$(PPOOL)/lib/$(OS) -ltiff
	GIFINC  = -I/$(PPOOL)/include/GIF
	GIFLIB  = -L/$(PPOOL)/lib/$(OS) -lGIF$(LIBSUF)
	XMLINC  = -D XML_LIB
	XMLLIB  = -L$(PPOOL)/lib/$(OS) -lxml$(LIBSUF)
	NMINC   = -I$(PPOOL)/include/newmat
	NMLIB   = -L$(PPOOL)/lib/$(OS) -lnewmat$(LIBSUF)
	COMINC  = -I$(PPOOL)/include
  COMLIB  = -L$(PPOOL)/lib/$(OS) -lcompress$(LIBSUF)
	XINC 		= -I/usr/openwin/include -D X_LIB 
	XLIB  	= -L/usr/lib/X11R6 -L/usr/lib/X11R5 -lXt -lXext -lX11
	MINC 		=	-I/usr/dt/include 
	MLIB		= -R/usr/dt/lib -L/usr/dt/lib -lXm 
	QTINC		=	-I$(QTDIR)/include  -DQT_CLEAN_NAMESPACE
	QTLIB		= -L$(QTDIR)/lib -lqt
	OGLINC	= -I/opt/graphics/OpenGL/include -DHP_OGL -DOPENGL_LIB
	OGLLIB	= -L/opt/graphics/OpenGL/lib -lGLU -lGL
	OGLWINC = -I/usr/openwin/include 
	OGLWLIB = -L/usr/openwin/lib -lGLw
	LUGINC 	= -I/igd/a7/imaging/public/include/lug
	LUGLIB 	= -L/igd/a7/imaging/public/lib
	TTFINC  = -I/$(PPOOL)/include 
	TTFLIB  = -L/$(PPOOL)/lib/$(OS) -lttf
	GLUTINC = -I$(PPOOL)/include -D GLUT_LIB
	GLUTLIB = $(PPOOL)/lib/$(OS)/libglut-sm.a
	S3INC = -D S3_LIB
	S3LIB = -L$(PPOOL)/lib/$(OS) -ls3$(LIBSUF)
	HIDINC  = -D HID_LIB
	HIDLIB  = -L$(PPOOL)/lib/$(OS) -lhid$(LIBSUF)
	GLTTINC = -I/$(PPOOL)/include/gltt 
	GLTTLIB = -L$(PPOOL)/lib/$(OS) -lgltt
  CAMINC   = -I$(PPOOL)/include -DCAMERA_LIB
  CAMLIB   = -L$(PPOOL)/lib/$(OS) -lcamera \
	 -L/opt/SUNWits/Graphics-sw/xil/lib -lxil    
	OIINC   = -I/usr1/OpenInventor2.1.1-1/include
	OILIB   = -L/usr1/OpenInventor2.1.1-1/lib  -lInventor -lInventorXt
endif
#-- SGI --------------------------------------------------------------
ifeq ($(OS),IRIX)
	GCCHOME = /hgdv/software/gnu/IRIX6
	GCC 		= $(GCCHOME)/bin/gcc
	GCXX 		= $(GCCHOME)/bin/g++
	GCXXINC	= -I$(GCCHOME)/lib/g++-include
  GCFLAGS = -c -o $@ -DARCH=3 -Wall -pedantic
  ifeq ($(TEMPDB),YES)
	  GCFLAGS += -fno-implicit-templates
  endif
	GLD			= $(GCCHOME)/bin/g++
	GLIBDIR  = lib

	NCC			= cc
	NCXX		= /usr/bin/CC
	NCXXINC = -I/usr/include/CC
  NCFLAGS = -c -o $@ -DARCH=3 -n32 -LANG:bool=ON -woff 1682
	NLD			= CC 
	NLIBDIR = lib
	NMKDEP  = CC -M

	STRIP   = strip
	LINK    = ln -s
	LEX     = flex -dLst
	YACC    = /sgi/gnu2.7.2/bin/bison
	MOC     = $(QTDIR)/bin/moc
	UIC     = $(QTDIR)/bin/uic
	DFLAG   = -g -D DEBUG
	OPTFLAG = -O2 -D NDEBUG
	LDFLAGS = -o $(SYSTARGET) 
	SYSTMP	= /tmp/
	XDEBUGER	=	ddd
	EDIT		= xemacs
	XTERM		= xterm
	BINSET  = touch

	OBJSUF	= o
	BINSUF  =

	EXINC 	= -I$(PPOOL)/include
	EXLIB 	= -L$(PPOOL)/lib/$(OS)
	SYSINC  = 
	SYSLIB  =
	NMINC   = -I$(PPOOL)/include/newmat
	NMLIB   = -L$(PPOOL)/lib/$(OS) -lnewmat$(LIBSUF)
	COMINC  = -I$(PPOOL)/include
  COMLIB  = -L$(PPOOL)/lib/$(OS) -lcompress$(LIBSUF)
	XINC 		= -I/usr/include/X11 -D X_LIB
	XLIB  	= -L/usr/$(LIBDIR) -lXmu -lXext -lXt -lX11
	MINC 		=	-I/usr/include/X11 
	MLIB		= -L/usr/$(LIBDIR) -lXm 
	QTINC		=	-I$(QTDIR)/include  -DQT_CLEAN_NAMESPACE
	QTLIB		= -L$(QTDIR)/lib -lqt
	QTOGLINC = 
	QTOGLLIB = -lqgl
	OGLINC	= -I/usr/include -DSGI_OGL -DOPENGL -DOPENGL_EXTENSIONS -DOPENGL_LIB
	OGLLIB	= -L/usr/$(LIBDIR) -lGLU -lGL
	OGLWINC = -I/usr/include 
	OGLWLIB = -L/usr/$(LIBDIR) -lGLw
	C3DINC  = -I/usr/include -DCSNORMALSET3S -DCOMPILE_ACTION -ptall -nostdinc
	C3DLIB  = -n32 -L/usr/$(LIBDIR) -lcosmo	-lcscsb -limage -lglut -lm
	SNDINC  = -I/usr/include
	SNDLIB  = -L/usr/lib -laudio -laudiofile
	ESDINC  = -I$(PPOOL)/include/esd -D ESOUND_LIB
	ESDLIB  = -L/zgdv/vc9/avalon/lib/$(OS) -lesd -laudiofile
	S3INC = -D S3_LIB
	S3LIB = -L$(PPOOL)/lib/$(OS) -ls3$(LIBSUF)
	HIDINC  = -D HID_LIB
	HIDLIB  = -L$(PPOOL)/lib/$(OS) -lhid$(LIBSUF)
	AEIINC  = -DAEI_LIB
	AEILIB  = -L$(PPOOL)/lib/$(OS) -laei$(LIBSUF)
	GLUTINC = -I$(PPOOL)/include -D GLUT_LIB
	GLUTLIB = -I$(PPOOL)/lib/$(OS) 
#	GLUTINC = -I/usr/include
#	GLUTLIB = -I/usr/$(LIBDIR) -lglut
	CAMINC  = -I/usr/include -DCAMERA_LIB
	CAMLIB  = -I/usr/lib -lvl
#	OIINC		= -I/opt/Inventor/include
#	OILIB		= -L/opt/Inventor/lib -lInventorXt -lInventor
	OIINC		= -I/usr/include
	OILIB		= -L/usr/$(LIBDIR) -lInventor -lInventorXt
	MEDINC  = -D MEDUSA_LIB
	MEDLIB  = -L$(POOL)/lib/$(OS) -lmedusa$(LIBSUF)
	THRINC  = 
	THRLIB  = -lpthread 
	LOGINC  = -D LOG_LIB
	LOGLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -llog$(LIBSUF)
	OSGINC  = -I$(OSGROOT)/include
	OSGDLIB = -L$(OSGROOT)/lib/dbg
	OSGOLIB = -L$(OSGROOT)/lib/opt
	OSGBASEINC  =
	OSGBASELIB  = -lOSGBase
	OSGSYSINC   = 
	OSGSYSLIB   = -lOSGSystem
	OSGWXINC    = 
	OSGWXLIB    = -lOSGWindowX
	OSGWGLUTINC = -DOSG_WITH_GLUT
	OSGWGLUTLIB = -lOSGWindowGLUT
	OSGWQTINC   = -DOSG_WITH_QT -DQT_NO_XINERAMA -DQT_NO_XRENDER 		\
				  -DQT_NO_XFTFREETYPE 									\
				  -DQT_NO_XKB -DQT_NO_SM_SUPPORT -DQT_NO_IMAGEIO_MNG	\
				  -DQT_NO_IMAGEIO_JPEG -DQT_NO_STYLE_AQUA 				\
				  -DQT_NO_STYLE_MAC -DQT_NO_STYLE_INTERLACE 			\
				  -DQT_NO_STYLE_COMPACT

	OSGWQTLIB   = -lOSGWindowQT
endif
#-- SGI --------------------------------------------------------------
ifeq ($(OS),IRIX64)
	GCCHOME	= $(GCCPATH)
	#GCCHOME	= /hgdv/software/gcc-2.8.1/IRIX64_6.2_mips
	GCC 		= $(GCCHOME)/bin/gcc 
	GCXX 		= $(GCCHOME)/bin/g++ 
#	GCXXINC	= -I$(GCCHOME)/lib/g++-include
	GCXXINC	= 
  GCFLAGS = -c -o $@ -Wall -pedantic -frtti -DRTTI
  ifeq ($(TEMPDB),YES)
	  GCFLAGS += -fno-implicit-templates
  endif
	GLD 		= $(GCCHOME)/bin/g++ -LANG:std
	GLIBDIR = lib32

	NCC 		= cc
	NCXX 		= CC
	NCFLAGS = -LANG:std -ptused -c -o $@ -n32 -woff 3303,1355,1681
	NLD			= CC -n32 -LANG:std -ptused
	NSO     = CC -shared -n32 -LANG:std
	NLIBDIR = lib32
	NMKDEP  = CC -M

	AR      = CC -ar -n32 -o 
	STRIP   = strip
	LINK    = ln -s
	LEX     = flex -dLst
	YACC    = /sgi/gnu2.7.2/bin/bison
	MOC     = $(QTDIR)/bin/moc
	UIC     = $(QTDIR)/bin/uic
	DFLAG   = -g -D DEBUG
	OPTFLAG = -D NDEBUG
	LDFLAGS = -o $(SYSTARGET) 
	SYSTMP	= /tmp/
	XDEBUGER	=	ddd
	EDIT		= xemacs
	XTERM		= xterm
	BINSET  = touch

	OBJSUF  = o
	BINSUF  =

	EXINC 	= -I$(PPOOL)/include -I$(HOME)/include
	EXLIB 	= -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -L$(HOME)/lib/$(OS)/$(LIBDIR)
	SYSINC  = 
	SYSLIB  = -lm
	STLINC  = 
	STLLIB  = 
 
	ACEINC  = -I$(PPOOL)/include/ace/version_4.6 ACE_LIB
	ACELIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lACE$(LIBSUF)
	SMANINC  = -I$(PPOOL)/include/sman -DSOCKETMAN_LIB
	SMANLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lsman
	COMINC  = -I$(PPOOL)/include
  COMLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lcompress$(LIBSUF)
	HERINC  = -DHERMES_LIB
	HERLIB  = -I$(PPOOL)/lib/$(OS)/$(LIBDIR) -lhermes$(LIBSUF)
	AEIINC  = -DAEI_LIB
	AEILIB  = -L$(PPOOL)/lib/$(OS) -laei$(LIBSUF)
#	TIFFINC = -I/usr/include -DTIFF_LIB
#	TIFFLIB = -L/usr/$(LIBDIR) -ltiff
#	JPEGINC = -I/usr/include -DJPEG_LIB
#	JPEGLIB = -L/usr/$(LIBDIR) -ljpeg
	TIFFINC = -DTIFF_LIB
	TIFFLIB = -ltiff
	JPEGINC = -DJPEG_LIB
	JPEGLIB = -ljpeg
	GIFINC  = -I$(PPOOL)/include/GIF -DGIF_LIB
	GIFLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lGIF$(LIBSUF)
	PNGINC  = -I$(PPOOL)/include/png -DPNG_LIB
	PNGLIB  = -L$(PPOOL)/lib/$(OS) -lpng
	ZINC     = -I$(PPOOL)/include/zlib -DZ_LIB
	ZLIB     = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lz
	XMLINC  = -D XML_LIB
	XMLLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lxml$(LIBSUF)
	ECMAINC	= -I$(PPOOL)/include/js -I$(PPOOL)/include/js/IRIX6.5_DBG.OBJ -DECMA_LIB
	ECMALIB	= -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -ljs -lfdm -lm
	XINC 		= -I/usr/include/X11 -D X_LIB
	XLIB  	= -L/usr/$(LIBDIR) -lXmu -lXext -lXt -lXi -lX11
	MINC 		=	-I/usr/include/X11 
	MLIB		= -L/usr/lib32 -lXm 
	QTINC		=	-I$(QTDIR)/include  -DQT_CLEAN_NAMESPACE
	QTLIB		= -L$(QTDIR)/lib -lqt
	QTOGLINC = 
	QTOGLLIB = -lqgl
	CAMINC  = -I/usr/include -DCAMERA_LIB
	CAMLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lcamera -L/usr/$(LIBDIR) -lvl
	#ANIMINC = -I$(PPOOL)/include/ANIM -D ANIM_LIB
	#ANIMLIB = -L$(PPOOL)/lib/$(OS) -lANIM$(LIBSUF) -lvic$(LIBSUF) -lMPEG$(LIBSUF)
	ANIMINC = -I$(PPOOL)/src/mpeg_play -D ANIM_LIB
	ANIMLIB = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lMPEG$(LIBSUF) -lpthread
	DYNINC  = -DDYNAMID_LIB
	DYNLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lDYNAMID$(LIBSUF)
	SNDINC  = -I/usr/include
	SNDLIB  = -L/usr/$(LIBDIR) -laudio -laudiofile
	NMINC   = -I$(PPOOL)/include/newmat
	NMLIB   = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lnewmat$(LIBSUF)
	ESDINC  = -I$(PPOOL)/include/esd -D ESOUND_LIB
	ESDLIB  = -L/zgdv/vc9/avalon/lib/$(OS)/$(LIBDIR) -lesd -laudiofile -laudio
	OGLINC	= -DSGI_OGL -DOPENGL_LIB
	OGLLIB	= -L/usr/$(LIBDIR) -lGLU -lGL
	#OGLINC	= -I/usr/include -DSGI_OGL -DOPENGL_LIB
	#OGLLIB	= -L/usr/$(LIBDIR) -lGLU -lGL
	#OGLINC	= -I/usr/tmp/mesa/include -DOPENGL_LIB
	#OGLLIB	= -L/usr/tmp/mesa/$(LIBDIR) -lMesaGLU -lMesaGL
	PMINC   = -D PMESH_LIB
	PMLIB   = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lpmesh$(LIBSUF)
	ABINC   = -DABASE_LIB
	ABLIB 	= -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -labase$(LIBSUF)
	TIINC   = -D TEXIMAGE_LIB 
	TILIB   = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -ltexImage$(LIBSUF)
	GSINC   = -D GEOSHAPE_LIB 
	GSLIB   = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lgeoShape$(LIBSUF)
	CONFINC = -D CONFIG_LIB
	CONFLIB = -L$(PPOOL)/lib/$(OS) -lconfig$(LIBSUF)
	OIINC   = -I/usr/include -D INVENTOR_LIB
	OILIB		= -L/usr/$(LIBDIR) -lInventor 
	TTFINC  = -I/$(PPOOL)/include/freetype -D TTF_LIB
	TTFLIB  = -L/$(PPOOL)/lib/$(OS)/$(LIBDIR) -lttf -lGLU
	TMINC   = -D TEXTMAKER_LIB
	TMLIB   = -L/$(PPOOL)/lib/$(OS)/$(LIBDIR) -ltextMaker$(LIBSUF)
	GLTTINC = -I/$(PPOOL)/include/gltt -D GLTT_LIB
	GLTTLIB = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lgltt
	GLUTINC = -I$(PPOOL)/include -D GLUT_LIB
	GLUTLIB = -L/$(PPOOL)/lib/IRIX/$(LIBDIR) 
	#GLUTINC = -I/igd/a4/lib/glut-3.7/include -D GLUT_LIB
	#GLUTLIB = -L/igd/a4/lib/glut-3.7/lib -lglut
	S3INC = -D S3_LIB
	S3LIB = -L$(PPOOL)/lib/$(OS) -ls3$(LIBSUF)
	HIDINC  = -D HID_LIB
	HIDLIB  = -L$(PPOOL)/lib/$(OS) -lhid$(LIBSUF)
	OPTINC  = -I/usr/include -D OPTIMIZER_LIB
	OPTLIB  = -L/usr/lib32 -lop_sp -lopGUI_sp -lcosmo3d
	MEDINC  = -D MEDUSA_LIB
	MEDLIB  = -L$(POOL)/lib/$(OS)/$(LIBDIR) -lmedusa$(LIBSUF)
	THRINC  = 
	THRLIB  = -lpthread 
	LOGINC  = -D LOG_LIB
	LOGLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -llog$(LIBSUF)
	OSGINC  = -I$(OSGROOT)/include
	OSGDLIB = -L$(OSGROOT)/lib/dbg
	OSGOLIB = -L$(OSGROOT)/lib/opt
	OSGBASEINC  =
	OSGBASELIB  = -lOSGBase
	OSGSYSINC   = 
	OSGSYSLIB   = -lOSGSystem
	OSGWXINC    = 
	OSGWXLIB    = -lOSGWindowX
	OSGWGLUTINC = -DOSG_WITH_GLUT
	OSGWGLUTLIB = -lOSGWindowGLUT
	OSGWQTINC   = -DOSG_WITH_QT -DQT_NO_XINERAMA -DQT_NO_XRENDER 		\
				  -DQT_NO_XFTFREETYPE 									\
				  -DQT_NO_XKB -DQT_NO_SM_SUPPORT -DQT_NO_IMAGEIO_MNG	\
				  -DQT_NO_IMAGEIO_JPEG -DQT_NO_STYLE_AQUA 				\
				  -DQT_NO_STYLE_MAC -DQT_NO_STYLE_INTERLACE 			\
				  -DQT_NO_STYLE_COMPACT
	OSGWQTLIB   = -lOSGWindowQT
endif
#-- Linux -----------------------------------------------------------
ifeq ($(OS),Linux)
	GCC 		= $(GCCPATH)/bin/g++
	GCXX 		= $(GCCPATH)/bin/g++
  GCFLAGS = -c -o $@ -Wall  -Wno-unknown-pragmas
  ifeq ($(TEMPDB),YES)
	  GCFLAGS += -fno-implicit-templates
  endif
	GLD			= $(GCCPATH)/bin/g++ -Wl,-v 
	GSO     = $(GCCPATH)/bin/gcc -shared -Wl,-v
	GMKDEP  = $(GCXX) -M
#	GMKDEP  = makedepend 2>/dev/null -f-

	NCC 		= g++
	NCXX 		= g++
  NCFLAGS = -c -o $@ -Wall -fPIC -ffast-math -funroll-loops -frtti -Wno-unknown-pragmas
  ifeq ($(TEMPDB),YES)
	  GCFLAGS += -fno-implicit-templates
  endif
	NLD			= gcc
	NSO     = $(GCCHOME)/bin/gcc -shared

	AR      = ar ruv 
	STRIP   = strip
	LINK    = ln -s
	LEX     = flex -dLst
	YACC    = bison
	MOC     = $(QTDIR)/bin/moc
	UIC     = $(QTDIR)/bin/uic
	DFLAG   = -g -D DEBUG
	OPTFLAG = -O2 -D NDEBUG
	LDFLAGS = -o $(SYSTARGET) 
	SYSTMP	= /tmp/
	XDEBUGER	=	ddd
	EDIT		= xemacs
	XTERM		= rxvt
	BINSET  = touch

	OBJSUF  = o
	BINSUF  =

	EXINC 	= -I$(PPOOL)/include -I$(HOME)/include
	EXLIB 	= -L$(PPOOL)/lib/$(OS) -L$(HOME)/lib/$(OS)
	SYSINC  = -I$(PPOOL)/include
	SYSLIB  = -lm
	CPPINC  = 
	CPPLIB  = -lstdc++ 
	STLINC  = 

	TIFFINC = -I/usr/include/tiff -DTIFF_LIB
	TIFFLIB = -L/usr/lib -ltiff
	JPEGINC = -I$(PPOOL)/include/jpeg -DJPEG_LIB
	JPEGLIB = -L/usr/lib/jpeg -ljpeg
	GIFINC  = -I/$(PPOOL)/include/GIF -DGIF_LIB
	GIFLIB  = -lGIF$(LIBSUF)
	PNGINC  = -I$(PPOOL)/include/png -DPNG_LIB
	PNGLIB  = -lpng
	XPPINC  = -I$(PPOOL)/include/xmlpp -DXMLPP_LIB
	XPPLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lxmlpp$(LIBSUF)
	XMLINC  = -D XML_LIB
	XMLLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lxml$(LIBSUF)
	XINC 		=
	XLIB	 	= -L/usr/X11R6/lib -lXmu -lXext -lXt -lSM -lICE -lXi -lX11
	MINC 		=	-I/usr/X11R6/include 
	MLIB		= -L/usr/X11R6/lib -lXm 
	QTINC		=	-I$(QTDIR)/include  -DQT_CLEAN_NAMESPACE
	QTLIB		= -L$(QTDIR)/lib -lqt
	VORINC  = -I$(PPOOL)/include/voronoi -DVORONOI_LIB
	VORLIB  = -L$(PPOOL)/lib/$(OS) -lvor$(LIBSUF)
	NMINC   = -I$(PPOOL)/include/newmat
	NMLIB   = -L$(PPOOL)/lib/$(OS) -lnewmat$(LIBSUF)
	TMINC   = -D TEXTMAKER_LIB
	TMLIB   = -L/$(PPOOL)/lib/$(OS) -ltextMaker$(LIBSUF)
	PMINC   = -D PMESH_LIB
	PMLIB   = -L$(PPOOL)/lib/$(OS) -lpmesh$(LIBSUF)
	FGLINC	= -I/usr/X11R6/include  -DOPENGL_LIB
	FGLLIB	= -L/usr/X11R6/lib -lGLU -lfakeGL
	OGLINC	= -I/usr/X11R6/include  -DOPENGL_LIB
	OGLLIB	= -L/usr/X11R6/lib -lGLU -lGL
	#OGLLIB	= -L/usr/X11R6/lib -lGLU -ldebugGL
	#OGLLIB	= -L/usr/X11R6/lib -lMesaGLU -lMesaGL
  CAMINC   = -I$(PPOOL)/include -DCAMERA_LIB
  CAMLIB   = -L$(PPOOL)/lib/$(OS) -lcamera 
	OIINC   = -I/opt/OpenInventor/include
	OILIB		= -L/opt/OpenInventor/lib -lInventorXt -lInventor -limage
	TTFINC  = -I/$(PPOOL)/include -DTTF_LIB
	TTFLIB  = -L/$(PPOOL)/lib/$(OS) -lttf
	HERINC  = -D HERMES_LIB
	HERLIB  = -L$(PPOOL)/lib/$(OS) -lhermes$(LIBSUF)
	AEIINC  = -DAEI_LIB
	AEILIB  = -L$(PPOOL)/lib/$(OS) -laei$(LIBSUF)
	COMINC  = -I$(PPOOL)/include
  COMLIB  = -L$(PPOOL)/lib/$(OS) -lcompress$(LIBSUF)
	DYNINC  = -DDYNAMID_LIB
	DYNLIB  = -L$(PPOOL)/lib/$(OS) -lDYNAMID$(LIBSUF)
	TTFINC  = -I/$(PPOOL)/include/freetype -DTTF_LIB
	TTFLIB  = -L/$(PPOOL)/lib/$(OS) -lttf
	GLTTINC = -I/$(PPOOL)/include/gltt -DGLTT_LIB
	GLTTLIB = -L$(PPOOL)/lib/$(OS) -lgltt$(LIBSUF)
	ABINC   = -D ABASE_LIB
	ABLIB 	= -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -labase$(LIBSUF)
	TIINC   = -D TEXIMAGE_LIB 
	TILIB   = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -ltexImage$(LIBSUF)
	GSINC   = -D GEOSHAPE_LIB 
	GSLIB   = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lgeoShape$(LIBSUF)
	CONFINC = -D CONFIG_LIB
	CONFLIB = -L$(PPOOL)/lib/$(OS) -lconfig$(LIBSUF)
	GLUTINC = -I$(PPOOL)/include -DGLUT_LIB
	GLUTLIB = -L$(PPOOL)/lib/$(OS) -lglut
	S3INC = -D S3_LIB
	S3LIB = -L$(PPOOL)/lib/$(OS) -ls3$(LIBSUF)
	HIDINC  = -D HID_LIB
	HIDLIB  = -L$(PPOOL)/lib/$(OS) -lhid$(LIBSUF)
	OSGINC  = -I$(OSGROOT)/include
	OSGDLIB = -L$(OSGROOT)/lib/dbg
	OSGOLIB = -L$(OSGROOT)/lib/opt
	OSGBASEINC  =
	OSGBASELIB  = -lOSGBase
	OSGSYSINC   = 
	OSGSYSLIB   = -lOSGSystem
	OSGWXINC    = 
	OSGWXLIB    = -lOSGWindowX
	OSGWGLUTINC = -DOSG_WITH_GLUT
	OSGWGLUTLIB = -lOSGWindowGLUT
	OSGWQTINC   = -DOSG_WITH_QT -DQT_NO_XINERAMA -DQT_NO_XRENDER 		\
				  -DQT_NO_XFTFREETYPE 									\
				  -DQT_NO_XKB -DQT_NO_SM_SUPPORT -DQT_NO_IMAGEIO_MNG	\
				  -DQT_NO_IMAGEIO_JPEG -DQT_NO_STYLE_AQUA 				\
				  -DQT_NO_STYLE_MAC -DQT_NO_STYLE_INTERLACE 			\
				  -DQT_NO_STYLE_COMPACT
	OSGWQTLIB   = -lOSGWindowQT
	OGLWINC = -I/usr/X11/include 
	OGLWLIB = -L/usr/X11/lib -lMesaGLwM
	MEDINC  = -D MEDUSA_LIB
	MEDLIB  = -L$(POOL)/lib/$(OS) -lmedusa$(LIBSUF)
	THRINC  = 
	THRLIB  = -lpthread 
	LOGINC  = -D LOG_LIB
	LOGLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -llog$(LIBSUF)
endif
#-- WIN32 --------------------------------------------------------------
ifeq ($(findstring WIN,$(OS)),WIN)
	OS		= WIN32

	GCCHOME =
	GCC     = gcc
	GCXX    = g++
	GCXXINC =
	GCFLAGS = -c -o $@ -Wall -pedantic
	GMKDEP  = $(GCXX) -M
	GLD     = g++
	GSO     =

	NCCHOME =
	NCC     = cl
	NCXX    = $(NCC)
	NCXXINC = 
	NCFLAGS	= /c /Fd"c:\tmp\test.pdb" /Fo"$@" /GR /GX /w \
	          /D "_CONSOLE"  /D "_MBCS" /D "WIN32" /nologo \
				   /D WINVER=0x0400 /D _WIN32_WINDOWS=0x0410 	      \
				   /D OSG_BUILD_DLL /D OSG_NEW_DLLS \
           /D_OSG_HAVE_CONFIGURED_H_                      \
           /D__INTEL_COMPILER_VERSION=500
#	NMKDEP  = $(NCXX) -QM -nologo

# /D "__i386__" /D "ANSI_STL" /D "__ANSI_CPP__"
	NLD	    = link
	NSO     =

	AR      = ar ruv
	STRIP   = upx
	LINK    = cp
	LEX     = flex -dLst
	YACC    = bison
	MOC     = $(PPOOL)/bin/WIN32/moc
	DFLAG   = /D "DEBUG" /ZI /Zi /MTd
	OPTFLAG = /D "NDEBUG" /G6 /O2 /Ogityb2 /Gs /MT 
	LDFLAGS =  /DEBUG /NOLOGO /INCREMENTAL:YES \
	           /PDB:"$(TARGET).pdb" /OUT:"$(SYSTARGET)" 
	SYSTMP	= C:\\temp\\
	XDEBUGER	=	ddd
	EDIT		= xemacs
	XTERM		= bash 
	BINSET  = touch

	OBJSUF  = obj
	BINSUF  = .exe

	EXINC 	= /I "V:\include" /I "V:\include\WIN32"
	EXLIB 	= /LIBPATH:"c:\Programme\Intel\compiler50\ia32\lib" /LIBPATH:"v:\lib\WIN32"
	#EXLIB 	= /LIBPATH:"V:\lib\WIN32"
	SYSINC  = 
	SYSLIB  = kernel32.lib user32.lib gdi32.lib winspool.lib \
						comdlg32.lib advapi32.lib shell32.lib winmm.lib \
						ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib 

#						/NODEFAULTLIB:LIBC 

	NETINC  = 
	NETLIB  = ws2_32.lib 
	STLINC  = 
#	STLINC  = /D "OS_WIN_NT_4_0" /I "V:\include\ospace" /I "V:\include\ospace\ospace\stl" /D "OS_STL" /D STL_HSUFFIX 
#	STLLIB  = std-2.0.1-vc5.0.lib std-2.0.1-vc5.0-mt.lib std-2.0.1-vc5.0-uss.lib std-2.0.1-vc5.0-mt-uss.lib 
	#STLINC  = /I "V:\include\stlport" /D "STLPORT_STL" /D "STL_NAMESPACE"
	#STLLIB  = 
	PMINC   = /D PMESH_LIB
	PMLIB   = pmesh.lib
	ABINC   = /D ABASE_LIB
	ABLIB 	= abase.lib
	TIINC   = /D TEXIMAGE_LIB 
	TILIB   = texImage.lib
	VORINC  = /I "V:\include\voronoi" /D VORONOI_LIB
	VORLIB  = vor.lib
	AEIINC  = /D AEI_LIB
	AEILIB  = aei.lib
	NMINC   = /I "V:\include\newmat" 
	NMLIB   = newmat.lib
	GSINC   = /D GEOSHAPE_LIB 
	GSLIB   = geoShape.lib
	CONFINC = /D CONFIG_LIB
	CONFLIB = config.lib
	ACEINC  = /I "V:\include\ace\version_4.5"
	ACELIB  = aced.lib
	DYNINC  = /D DYNAMID_LIB
	DYNLIB  = dynamid.lib
	COMINC  = /I "V:\include" /D COMPRESS_LIB
  COMLIB  = compress.lib
#	ECMAINC = /I "U:\homes\pdaehne_vc8\js" /D ECMA_LIB
	ECMAINC	= /I "V:\include\js" /D ECMA_LIB
	ECMALIB	= js32.lib
	VIDEOBUFFERINC   = /D VIDEOBUFFER_LIB
	VIDEOBUFFERLIB 	= videoBuffer.lib
	XINC 		=
	XLIB	 	= 
	MINC 		=	
	MLIB		= 
	DXINC   = /D DIRECTX_LIB #/I "V:\include\directX" /D DIRECTX_LIB
	DXLIB   = dsound.lib dinput.lib dxguid.lib #/libpath:"V:/lib/WIN32/directX" dsound.lib dinput.lib dxguid.lib
	COMINC  = /I "V:\include\include"
  COMLIB  = compress.lib
	TTFINC  = /I "V:\include\freetype" /D TTF_LIB
	TTFLIB  = freetype.lib
	TMINC   = /D TEXTMAKER_LIB
	TMLIB   = textMaker.lib
	S3INC   = /D S3_LIB
	S3LIB   = s3.lib
	HIDINC  = /D HID_LIB
	HIDLIB  = hid.lib
	GSINC   = /I "V:\include\geoShape" /D GEOSHAPE_LIB 
	GSLIB   = geoShape.lib
	SMANINC  = /I "V:\include\sman" /D SOCKETMAN_LIB
	SMANLIB  = -lsman
	HERINC  = /D HERMES_LIB
	HERLIB  = hermes.lib
	MEDINC  = /D MEDUSA_LIB
	MEDLIB  = medusa.lib
	GIFINC  = /I "V:\include\GIF" /D GIF_LIB
	GIFLIB  = GIF.lib
	XMLINC  = /D XML_LIB
	XMLLIB  = xml.lib
	TIFFINC  = /I "V:\include\tiff" /D TIFF_LIB
	TIFFLIB  = tiff.lib
	JPEGINC = /I "V:\include\jpeg" /D JPEG_LIB
	JPEGLIB = libjpeg.lib
	PNGINC  = /I "V:\include\png" /D PNG_LIB
	PNGLIB  = libpng.lib
	ZINC     = /I "V:\include\zlib" /D Z_LIB
	ZLIB     = zlib.lib
	A3DINC  = /I "V:\include\a3d" /D A3D_LIB
	A3DLIB  = ia3dutil.lib
	QTINC		=	/I "V:\include\qt-2.1.1" 
	QTLIB		= /libpath:"D:\qt-1.42\lib" qt.lib 
	GLTTINC = /I "V:\include\gltt" /D GLTT_LIB
	GLTTLIB = gltt.lib 
	OSGINC  = /I "$(OSGROOT)\include"
	OSGDLIB = /libpath:"$(OSGROOT)\lib\dbg"  
	OSGOLIB = /libpath:"$(OSGROOT)\lib\opt"
	OSGBASEINC  =
	OSGBASELIB  = OSGBase.lib
	OSGSYSINC   = 
	OSGSYSLIB   = OSGSystem.lib
	OSGWXINC    = 
	OSGWXLIB    = OSGWindowX.lib
	OSGWGLUTINC = /D OSG_WITH_GLUT
	OSGWGLUTLIB = OSGWindowGLUT.lib
	OSGWQTINC   = -DOSG_WITH_QT -DQT_NO_XINERAMA -DQT_NO_XRENDER 		\
				  -DQT_NO_XFTFREETYPE 									\
				  -DQT_NO_XKB -DQT_NO_SM_SUPPORT -DQT_NO_IMAGEIO_MNG	\
				  -DQT_NO_IMAGEIO_JPEG -DQT_NO_STYLE_AQUA 				\
				  -DQT_NO_STYLE_MAC -DQT_NO_STYLE_INTERLACE 			\
				  -DQT_NO_STYLE_COMPACT
	OSGWQTLIB   = OSGWindowQT.lib
	OGLINC	= /D OPENGL_LIB
	OGLLIB	= opengl32.lib glu32.lib 
	GLUTINC =  /D GLUT_LIB
	GLUTLIB = /libpath:"V:/lib/WIN32" glut32.lib 
endif

######################################################################
ifeq ($(TMPBIN),YES)
	SYSTARGET = $(SYSTMP)$(TARGET).$(USER)_$(SYSDEP)$(BINSUF)
	TARGETLNK = $(SYSTMP)$(TARGET).$(USER)$(BINSUF)
	LIBTARGET = $(SYSTMP)/lib$(TARGET)$(LIBSUF)
else
	SYSTARGET = ./$(TARGET).$(SYSDEP)$(BINSUF)
	TARGETLNK = ./$(TARGET).$(BINSUF)
	LIBTARGET = ./lib$(TARGET)$(LIBSUF)
endif

### Document Dir #####################################################
DOCDIR = $(PPOOL)/doc/src/$(TARGET)
######################################################################

### Compiler and Linker ##############################################
ifeq ($(CC_$(OS)),GNU_CC)
	CC = $(GCC)
	CXX = $(GCXX)
	CXXINC = $(GCXXINC)
	ifeq ($(STATICBIN),YES)
		LD = $(GLD) -Wl,-Bstatic
	else
		LD = $(GLD)
	endif
	SOLD = $(GSO)
	MKDEP = $(GMKDEP)
	SCFLAGS = $(GCFLAGS)
	ifeq ($(DEBUG),YES)
		SYSDEP = $(OS)_GCC_DEB
	else
		SYSDEP = $(OS)_GCC_OPT
	endif
	LIBDIR = $(GLIBDIR)
	LIBSUF = _GCC
	DEBUGER = gdb
else
	CC = $(NCC)
	CXX = $(NCXX)
	CXXINC = $(NCXXINC)
	ifeq ($(STATICBIN),YES)
		LD = $(NLD) -Wl,-Bstatic
	else
		LD = $(NLD)
	endif
	SOLD = $(NSO)
	MKDEP = $(NMKDEP)
	SCFLAGS = $(NCFLAGS)
	ifeq ($(DEBUG),YES)
		SYSDEP = $(OS)_NCC_DEB
	else
		SYSDEP = $(OS)_NCC_OPT
	endif
	LIBDIR = $(NLIBDIR)
	LIBSUF = _NCC
	DEBUGER = dbx
endif
######################################################################

### Production flag (debug/optimize) #################################
ifeq ($(DEBUG),YES)
	PROFLAG = $(DFLAG) $(PROFLAG_$(OS))
	BINSET = touch
else
	PROFLAG = $(OPTFLAG) $(PROFLAG_$(OS))
endif
######################################################################

### Package dependences ##############################################
INCS += $(PROJINC) $(CXXINC) $(EXINC)
LIBS += $(PROJLIB) $(EXLIB)

ifeq ($(OPTIMIZER_PAK),YES)
	INCS += $(OPTINC)
	LIBS += $(OPTLIB)
endif
ifeq ($(COSMO3D_PAK),YES)
	INCS += $(C3DINC)
	LIBS += $(C3DLIB)
endif
ifeq ($(INVENTOR_PAK),YES)
	INCS += $(OIINC)
	LIBS += $(OILIB)
endif
ifeq ($(GLUT_PAK),YES)
	INCS += $(GLUTINC)
	LIBS += $(GLUTLIB)
endif
ifeq ($(GLTT_PAK),YES)
	INCS += $(GLTTINC)
	LIBS += $(GLTTLIB)
endif
ifeq ($(OPENGLWIDGET_PAK),YES)
	INCS += $(OGLWINC)
	LIBS += $(OGLWLIB)
endif
ifeq ($(ANIM_PAK),YES)
	INCS += $(ANIMINC)
	LIBS += $(ANIMLIB)
endif
ifeq ($(QT_PAK),YES)
	INCS += $(QTINC)
	LIBS += $(QTLIB)
endif
ifeq ($(QGL_PAK),YES)
	INCS += $(QGLINC)
	LIBS += $(QGLLIB)
endif
ifeq ($(FAKEGL_PAK),YES)
	INCS += $(FGLINC)
	LIBS += $(FGLLIB)
endif
ifeq ($(OPENGL_PAK),YES)
	INCS += $(OGLINC)
	LIBS += $(OGLLIB)
endif
ifeq ($(MOTIF_PAK),YES)
	INCS += $(MINC)
	LIBS += $(MLIB)
endif
ifeq ($(XPM_PAK),YES)
	INCS += $(XPMINC)
	LIBS += $(XPMLIB)
endif
ifeq ($(XWINDOW_PAK),YES)
	INCS += $(XINC)
	LIBS += $(XLIB)
endif
ifeq ($(ESOUND_PAK),YES)
	INCS += $(ESDINC)
	LIBS += $(ESDLIB)
endif
ifeq ($(SOUND_PAK),YES)
	INCS += $(SNDINC)
	LIBS += $(SNDLIB)
endif
ifeq ($(VORONOI_PAK),YES)
	INCS += $(VORINC)
	LIBS += $(VORLIB)
endif
ifeq ($(NEWMAT_PAK),YES)
	INCS += $(NMINC)
	LIBS += $(NMLIB)
endif
ifeq ($(GEOSHAPE_PAK),YES)
	INCS += $(GSINC)
	LIBS += $(GSLIB)
endif
ifeq ($(TEXIMAGE_PAK),YES)
	INCS += $(TIINC)
	LIBS += $(TILIB)
endif
ifeq ($(PMESH_PAK),YES)
	INCS += $(PMINC)
	LIBS += $(PMLIB)
endif
ifeq ($(TM_PAK),YES)
	INCS += $(TMINC)
	LIBS += $(TMLIB)
endif
ifeq ($(TTF_PAK),YES)
	INCS += $(TTFINC)
	LIBS += $(TTFLIB)
endif
ifeq ($(TIFF_PAK),YES)
	INCS += $(TIFFINC) 
	LIBS += $(TIFFLIB)
endif
ifeq ($(PNG_PAK),YES)
	INCS += $(PNGINC) 
	LIBS += $(PNGLIB)
endif
ifeq ($(JPEG_PAK),YES)
	INCS += $(JPEGINC)
	LIBS += $(JPEGLIB)
endif
ifeq ($(GIF_PAK),YES)
	INCS += $(GIFINC) 
	LIBS += $(GIFLIB)
endif
ifeq ($(CAMERA_PAK),YES)
	INCS += $(CAMINC)
	LIBS += $(CAMLIB)
endif
ifeq ($(ACE_PAK),YES)
	INCS += $(ACEINC)
	LIBS += $(ACELIB)
endif
ifeq ($(SOCKETMAN_PAK),YES)
	INCS += $(SMANINC)
	LIBS += $(SMANLIB)
endif
ifeq ($(JNI_PAK),YES)
	INCS += $(JNIINC)
	LIBS += $(JNILIB)
endif
ifeq ($(NET_PAK),YES)
	INCS += $(NETINC)
	LIBS += $(NETLIB)
endif
ifeq ($(MICO_PAK),YES)
	INCS += $(MICOINC)
	LIBS += $(MICOLIB)
endif
ifeq ($(A3D_PAK),YES)
	INCS += $(A3DINC)
	LIBS += $(A3DLIB)
endif
ifeq ($(STL_PAK),YES)
	INCS += $(STLINC)
	LIBS += $(STLLIB)
endif
ifeq ($(DYNAMID_PAK),YES)
	INCS += $(DYNINC)
	LIBS += $(DYNLIB)
endif
ifeq ($(S3_PAK),YES)
	INCS += $(S3INC)
	LIBS += $(S3LIB)
endif
ifeq ($(HID_PAK),YES)
	INCS += $(HIDINC)
	LIBS += $(HIDLIB)
endif
ifeq ($(DIRECTX_PAK),YES)
	INCS += $(DXINC)
	LIBS += $(DXLIB)
endif
ifeq ($(AVALON_ENGINE_PAK),YES)
	INCS += 
	LIBS += -lavalonEngineNodePool$(LIBSUF)
endif
ifeq ($(AVALON_SCENE_PAK),YES)
	INCS += 
	LIBS += -lavalonSceneNodePool$(LIBSUF)
endif
ifeq ($(AVALON_LOADER_PAK),YES)
	INCS += 
	LIBS += -lavalonLoaderPool$(LIBSUF)
endif
ifeq ($(AVALON_BASE_PAK),YES)
	INCS +=  
	LIBS += -lavalonBase$(LIBSUF)
endif
ifeq ($(OSG_DBG_PAK),YES)
	INCS += $(OSGINC)
	LIBS += $(OSGDLIB)
endif
ifeq ($(OSG_OPT_PAK),YES)
	INCS += $(OSGINC)
	LIBS += $(OSGOLIB)
endif
ifeq ($(OSG_BASE_PAK),YES)
	INCS += $(OSGBASEINC)
	LIBS += $(OSGBASELIB)
endif
ifeq ($(OSG_SYSTEM_PAK),YES)
	INCS += $(OSGSYSINC)
	LIBS += $(OSGSYSLIB)
endif
ifeq ($(OSG_WINDOW_GLUT_PAK),YES)
	INCS += $(OSGWGLUTINC)
	LIBS += $(OSGWGLUTLIB)
endif
ifeq ($(OSG_WINDOW_QT_PAK),YES)
	INCS += $(OSGWQTINC)
	LIBS += $(OSGWQTLIB)
endif
ifeq ($(OSG_WINDOW_X_PAK),YES)
	INCS += $(OSGWXINC)
	LIBS += $(OSGWXLIB)
endif
ifeq ($(ABASE_PAK),YES)
	INCS += $(ABINC)
	LIBS += $(ABLIB)
endif
ifeq ($(AEI_PAK),YES)
	INCS += $(AEIINC)
	LIBS += $(AEILIB)
endif
ifeq ($(HERMES_PAK),YES)
	INCS += $(HERINC)
	LIBS += $(HERLIB)
endif
ifeq ($(MEDUSA_PAK),YES)
	INCS += $(MEDINC)
	LIBS += $(MEDLIB)
endif
ifeq ($(XMLPP_PAK),YES)
	INCS += $(XPPINC) 
	LIBS += $(XPPLIB)
endif
ifeq ($(XML_PAK),YES)
	INCS += $(XMLINC) 
	LIBS += $(XMLLIB)
endif
ifeq ($(CONFIG_PAK),YES)
	INCS += $(CONFINC)
	LIBS += $(CONFLIB)
endif
ifeq ($(LOG_PAK),YES)
	INCS += $(LOGINC)
	LIBS += $(LOGLIB)
endif
ifeq ($(THREAD_PAK),YES)
	INCS += $(THRINC)
	LIBS += $(THRLIB)
endif
ifeq ($(ZLIB_PAK),YES)
	INCS += $(ZINC)
	LIBS += $(ZLIB)
endif
ifeq ($(COMPRESS_PAK),YES)
	INCS += $(COMINC)
	LIBS += $(COMLIB)
endif
ifeq ($(STDCPP_PAK),YES)
	INCS += $(CPPINC)
	LIBS += $(CPPLIB)
endif
ifeq ($(STATIC_STDCPP_PAK),YES)
	INCS += $(CPPINC)
	LIBS += -Wl,-Bstatic $(CPPLIB) -Wl,-Bdynamic
endif
ifeq ($(SYSTEM_PAK),YES)
	INCS += $(SYSINC)
	LIBS += $(SYSLIB)
endif
ifeq ($(PERSONAL_PAK),YES)
	INCS += $(EXTINC)
	LIBS += $(EXTLIB)
endif
ifeq ($(ECMASCRIPT_PAK),YES)
	INCS += $(ECMAINC) 
	LIBS += $(ECMALIB)
endif
ifeq ($(VIDEOBUFFER_PAK),YES)
	INCS += $(VIDEOBUFFERINC) 
	LIBS += $(VIDEOBUFFERLIB)
endif
######################################################################

### debugger #########################################################
ifeq ($(PURIFYBIN),YES)
	LDPREFIX = $(PURIFY)
else
	LDPREFIX =
endif
ifeq ($(EFENCE),YES)
	LIBS += -L$(PPOOL)/lib/$(OS) -lefence
endif
ifeq ($(OGLDEBUG),YES)
	LIBS += -logldebug
endif
######################################################################

### Compiler and linker flags ########################################
CFLAGS = $(PROFLAG) $(SCFLAGS) $(INCS)
CXXFLAGS = $(PROFLAG) $(SCFLAGS) $(INCS)
######################################################################

### Object and source files ##########################################
HEADERS := $(shell cat declist.mk)
SOURCES := $(shell cat implist.mk)
BINOBJS := $(shell cat objlist.$(SYSDEP).mk) 
LIBOBJS := $(shell sed < objlist.$(SYSDEP).mk 's/main\.[a-zA-Z_0-9]*\.o//g')
######################################################################

### TARGET build rules ###############################################
$(TARGET)$(BINSUF): $(SYSTARGET)
	@echo "TARGET:   " $(TARGET)
	@echo "SYSTEM:   " $(SYSDEP)
	@rm -f $(TARGET)$(BINSUF)
	@rm -f $(TARGETLNK)
	@$(LINK) $(SYSTARGET) $(TARGETLNK)
	@$(LINK) $(TARGETLNK) $(TARGET)$(BINSUF)

$(SYSTARGET): $(BINOBJS)
	$(LDPREFIX) $(LD) $(LDFLAGS) $(BINOBJS) $(LIBS)
	$(BINSET) $(SYSTARGET)

######################################################################

### Implicit rules ###################################################
%.cpp: %.y
	$(YACC) -ld $< -o $@

%.cpp: %.l
	$(LEX) $< > $@

%.h: %.ui
	$(UIC) -o $@ $<

%.cpp: %.ui
	$(UIC) -i $*.h -o $@ $<

moc_%.cpp: %.h
	$(MOC) -f$< $< -o $@

%.$(SYSDEP).dep: %.cpp
	@echo "Updating " $@
	$(MKDEP) $(INCS) -I. $< | sed 's/\.o/\.$(SYSDEP)\.o/' > $@

%.$(SYSDEP).o: %.cc
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.cxx
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.cpp %.$(SYSDEP).dep
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.C
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.c
	$(CC) $(CXXFLAGS) $<

%.pp: %.cpp
	$(CXX) -E $(CXXFLAGS) $<

######################################################################

### File lists #######################################################
lists: declist implist objlist depend 

declist:
	@echo "make declist.mk"
	@rm -rf declist.mk
	@echo *.[hH] *.hh *.hxx *.ui " " | \
	sed 's/\*\.[a-zA-Z]* //g' | \
	cat >declist.mk

implist: $(PROSRCS)
	@echo "make implist.mk"
	@rm -rf implist.mk
	@rm -rf moc_*.cpp
	@echo *.y *.l *.c *.C *.cc *.cxx *.cpp " " | \
	sed 's/\*\.[a-zA-Z]* //g' | \
	cat >implist.mk

objlist: implist.mk
	@echo "make objlist.$(SYSDEP).mk"
	@rm -rf objlist.$(SYSDEP).mk
	@grep -l Q_OBJECT *.[hH] | sed 's/^/moc_/g' > objlist.mk
	@cat implist.mk >> objlist.mk
	@cat < objlist.mk | \
	tr '\n' ' ' | \
	sed 's/\.cc/\.$(SYSDEP)\.o/g' | \
	sed 's/\.cxx/\.$(SYSDEP)\.o/g' | \
	sed 's/\.cpp/\.$(SYSDEP)\.o/g' | \
	sed 's/\.[cC]/\.$(SYSDEP)\.o/g' | \
	sed 's/\.[ly]/\.$(SYSDEP)\.o/g' | \
	sed 's/\.[hH]/\.$(SYSDEP)\.o/g' | \
	cat >objlist.$(SYSDEP).mk

deplist.$(SYSDEP).mk:
	@echo "init deplist.$(SYSDEP).mk"
	@echo >deplist.$(SYSDEP).mk ""
	$(MAKE) lists

depend: implist.mk
	@echo "make deplist.$(SYSDEP).mk"
	@echo -n "include " > deplist.$(SYSDEP).mk 
	@cat objlist.$(SYSDEP).mk | \
	sed 's/\.o/.dep/g' | \
	cat >> deplist.$(SYSDEP).mk

######################################################################

### Commands #########################################################
all: $(TARGET)$(BINSUF)

uinstall: $(SYSTARGET)
	$(STRIP) $(SYSTARGET)
	cp $(SYSTARGET) $(HOME)/bin/$(OS)/$(TARGET)$(BINSUF)

install: $(SYSTARGET)
	$(STRIP) $(SYSTARGET)
	cp $(SYSTARGET) $(PPOOL)/bin/$(OS)/$(TARGET)$(BINSUF)

lib: $(LIBOBJS)
	rm -rf $(LIBTARGET).a
	$(AR) $(LIBTARGET).a $(LIBOBJS)

so: $(LIBOBJS)
	rm -rf $(LIBTARGET).so
	$(SOLD) -o $(LIBTARGET).so $(LIBOBJS)

ulibinstall: lib
	mv $(LIBTARGET).a $(HOME)/lib/$(OS)/$(LIBDIR)

libinstall: lib
	mv $(LIBTARGET).a $(PPOOL)/lib/$(OS)/$(LIBDIR)

soinstall: so
	mv $(LIBTARGET).so $(PPOOL)/lib/$(OS)/$(LIBDIR)

usoinstall: so
	mv $(LIBTARGET).so $(HOME)/lib/$(OS)/$(LIBDIR)

incinstall: 
	cp *.h $(PPOOL)/include/$(NAMESPACE)

uincinstall: 
	cp *.h $(HOME)/include/$(NAMESPACE)

soinc: so
	cp *.h $(PPOOL)/include/$(NAMESPACE)
	mv $(LIBTARGET).so $(PPOOL)/lib/$(OS)/$(LIBDIR)

usoinc: so
	cp *.h $(HOME)/include/$(NAMESPACE)
	mv $(LIBTARGET).so $(HOME)/lib/$(OS)/$(LIBDIR)

includelink:
	ln -s $(PWD) $(PPOOL)/include/$(TARGET)

clean:
	-rm -f *.$(SYSDEP).o *.$(SYSDEP)*_pure_* *.bak *.swp *~ *% \#*\# 
	-rm -f $(TARGET)$(BINSUF) $(SYSTARGET)

Clean: clean
	-rm -rf *.o *.mk OOBR* *.dep TAGS tags *.bin
	-rm -rf $(DOCDIR)

run: $(RUN)

xrun: $(SYSTARGET) 
	@echo "RUN: $(SYSTARGET)"
	@$(XTERM) -geometry 80x60+0+0 -bg black -fg green \
	-title '$(SYSTARGET) console' \
	-e $(SYSTARGET) -geometry +200+200

run: $(SYSTARGET)
	@echo "RUN: $(SYSTARGET)"
	$(SYSTARGET) 

strip: $(SYSTARGET)
	@echo "STRIP: $(SYSTARGET)"
	@$(STRIP) $(SYSTARGET)

edit:
	$(EDIT) &

docify:
	mdocify $(HEADERS)

$(DOCDIR):
	mkdir -p $(DOCDIR)

doc: $(DOCDIR)

$(DOCDIR)/tex: doc
	mkdir -p $(DOCDIR)/tex

tex:	$(HEADERS) $(DOCDIR)/tex
	doc++ -t -o $(DOCDIR)/tex/$(TARGET).tex $(HEADERS)

ps: tex
	cd $(DOCDIR)/tex; latex $(TARGET).tex; latex $(TARGET).tex; \
	dvips -o $(TARGET).ps $(TARGET).dvi

$(DOCDIR)/html: doc
	mkdir -p $(DOCDIR)/html

html: $(HEADERS) $(DOCDIR)/html
	doc++ -p -u -H -d $(DOCDIR)/html -b $(HEADERS)

docu: ps html

debug: $(SYSTARGET)
	@echo "DEBUG: $(SYSTARGET)"
	@$(XDEBUGER) --$(DEBUGER) $(SYSTARGET)

count: 
	wc $(HEADERS) $(SOURCES)

tar:
	tar cvf $(TARGET).tar $(HEADERS) $(SOURCES) [Mm]akefile $(PROBACK)

star:
	tar cvf $(TARGET)-src.tar $(HEADERS) $(SOURCES) [Mm]akefile 

tgz: tar
	gzip $(TARGET).tar
	mv $(TARGET).tar $(TARGET).tgz

backup: tar
	mv $(TARGET).tar $(PPOOL)/src/backup

sbackup: star
	mv $(TARGET)-src.tar $(PPOOL)/src/backup

tags: declist.mk implist.mk
	@echo "make tag file"
	@etags -C $(shell cat implist.mk) $(shell cat implist.mk)

######################################################################

include deplist.$(SYSDEP).mk
######################################################################
# DO NOT DELETE

