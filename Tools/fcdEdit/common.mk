######################################################################
### Common Makefile Declarations, Johannes Behr 1997,98,99  ##########
######################################################################

### System dependences ###############################################
OS := $(shell echo `uname`)
OS_TYPE := $(shell echo `uname`_`uname -r`_`uname -p`)

#-- SUNOS ------------------------------------------------------------
ifeq ($(OS),SunOS)
	GCCHOME = /hgdv/software/gcc/SunOS_5.7_sparc
#	GCCHOME = /usr/local
  GCC     = $(GCCHOME)/bin/gcc
  GCXX    = $(GCCHOME)/bin/g++
  GCXXINC = -I$(GCCHOME)/include/g++-3 
  #GCXXINC = -I$(GCCHOME)/include/g++-3 -I$(GCCHOME)/lib/gcc-lib/sparc-sun-solaris2.7/2.95.2/include
  GCFLAGS = -c -o $@ -D_REENTRANT -D$(OS)_OS -Wall -fPIC -ffast-math -funroll-loops -frtti -ansi -Wno-unknown-pragmas -I. -D __EXTENSIONS__
  ifeq ($(TEMPDB),YES)
	  GCFLAGS += -fno-implicit-templates
  endif
  GLD     = $(GCCHOME)/bin/g++
	GSO     = $(GCCHOME)/bin/gcc -shared

	NCCHOME =  /solaris/WorkShop5.0/SUNWspro/SC5.0
	NCC			= $(NCCHOME)/bin/cc
	NCXX		= $(NCCHOME)/bin/CC 
	NCXXINC = -I$(NCCHOME)/include/CC -I$(NCCHOME)/include/CCios \
						-I$(NCCHOME)/include/cc 
	NCFLAGS = -c -o $@ -D$(OS)_OS -DNATIVE_CC -DSTL_NAMESPACE -mt
	NLD			= CC

	STRIP   = strip
	LINK    = ln -s
	LEX     = /solaris/bin/flex -dLst
#	YACC    = yacc
	YACC    = /hgdv/software/gnu/SunOS5/bin/bison
	MOC			= moc
	PURIFY  = /hgdv/software/purify/SunOS5/purify
	DFLAG		= -g -DDEBUG_BIN # -frepo
	OPTFLAG =	#-O6
	LDFLAGS = -o $(SYSTARGET)
	SYSTMP	= ./
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
	AEIINC  = -I$(PPOOL)/include/aei -DAEI_LIB
	AEILIB  = -L$(PPOOL)/lib/$(OS) -laei$(LIBSUF)
	JNIINC  = -I/usr/java/include -I/usr/java/include/solaris -DJNI_LIB
	JNILIB  = 
	TIFFINC = -I$(PPOOL)/include/tiff -DTIFF_LIB
	TIFFLIB = -L$(PPOOL)/lib/$(OS) -ltiff
	GIFINC  = -I$(PPOOL)/include/GIF -DGIF_LIB
	GIFLIB  = -L$(PPOOL)/lib/$(OS) -lGIF$(LIBSUF)
	PNGINC  = -I$(PPOOL)/include/png -DPNG_LIB
	PNGLIB  = -L$(PPOOL)/lib/$(OS) -lpng
	XMLINC  = -I$(PPOOL)/include/xml -DXML_LIB
	XMLLIB  = -L$(PPOOL)/lib/$(OS) -lxml$(LIBSUF)
	ECMAINC	= -I$(PPOOL)/include/js -I$(PPOOL)/include/js/SunOS5.7_DBG.OBJ -DECMA_LIB
	ECMALIB	= -L$(PPOOL)/lib/$(OS) -ljs -lfdm
	VORINC  = -I$(PPOOL)/include/voronoi -D VORONOI_LIB
	VORLIB  = -L$(PPOOL)/lib/$(OS) -lvor$(LIBSUF)
	NMINC   = -I$(PPOOL)/include/newmat
	NMLIB   = -L$(PPOOL)/lib/$(OS) -lnewmat$(LIBSUF)
	COMINC  = -I$(PPOOL)/include
  COMLIB  = -L$(PPOOL)/lib/$(OS) -lcompress$(LIBSUF)
	DYNINC  = -I$(PPOOL)/include/dynamid -DDYNAMID_LIB
	DYNLIB  = -L$(PPOOL)/lib/$(OS) -lDYNAMID$(LIBSUF)
	HERINC  = -I$(PPOOL)/include/hermes -DHERMES_LIB
	HERLIB  = -L$(PPOOL)/lib/$(OS) -lhermes$(LIBSUF) 
	HER2INC = -I$(PPOOL)/include/hermes2 -DHERMES2_LIB
	HER2LIB = -L$(PPOOL)/lib/$(OS) -lhermes2$(LIBSUF) 
	XINC 		= -isystem /usr/openwin/include -D X_LIB
	#XINC 		= -I/usr/openwin/include/ -D X_LIB
	XLIB  	= -R/usr/openwin/lib -L/usr/openwin/lib -lXmu  -lXext -lXt -lXi -lX11
	XPMINC 	= -I$(PPOOL)/include -D XPM_LIB
	XPMLIB 	= -R$(PPOOL)/lib/$(OS) -lXpm
	MINC 		=	-I/usr/dt/include 
	MLIB		= -R/usr/dt/lib -L/usr/dt/lib -lXm 
	QTINC		=	-I$(QTDIR)/include -D QT_LIB
	QTLIB		= -L$(QTDIR)/lib -lqt
	QGLINC	=	-I$(QTDIR)/include -D QGL_LIB
	QGLLIB	= -L$(QTDIR)/lib -lqgl
	PMINC   = -I$(PPOOL)/include/pmesh -D PMESH_LIB
	PMLIB   = -I$(PPOOL)/lib/$(OS) -lpmesh$(LIBSUF)
	ABINC   = -I$(PPOOL)/include/abase -D ABASE_LIB
	ABLIB 	= -R$(PPOOL)/lib/$(OS) -labase$(LIBSUF)
	TIINC   = -I$(PPOOL)/include/texImage -D TEXIMAGE_LIB 
	TILIB   = -R$(PPOOL)/lib/$(OS) -ltexImage$(LIBSUF)
	GSINC   = -I$(PPOOL)/include/geoShape -D GEOSHAPE_LIB 
	GSLIB   = -R$(PPOOL)/lib/$(OS) -lgeoShape$(LIBSUF)
	ACFINC  = -I$(PPOOL)/include/appConfig -D APPCONFIG_LIB
	ACFLIB  = -L$(PPOOL)/lib/$(OS) -lappConfig$(LIBSUF)
	OGLINC	= -isystem /usr/openwin/include -DSUN_OGL -DOPENGL_LIB
	OGLLIB	= -R/usr/openwin/lib -L/usr/openwin/lib -lGLU -lGL
	OGLWINC = -I/usr/openwin/include 
	OGLWLIB = -L/usr/openwin/lib -lGLw
	LUGINC 	= -I/igd/a7/imaging/public/include/lug
	LUGLIB 	= -L/igd/a7/imaging/public/lib
	TTFINC  = -I/$(PPOOL)/include/freetype -D TTF_LIB
	TTFLIB  = -L/$(PPOOL)/lib/$(OS) -lttf
	TMINC   = -I/$(PPOOL)/include/textMaker -D TEXTMAKER_LIB
	TMLIB   = -L/$(PPOOL)/lib/$(OS) -ltextMaker$(LIBSUF)
	GLTTINC = -I/$(PPOOL)/include/gltt -D GLTT_LIB
	GLTTLIB = -L$(PPOOL)/lib/$(OS) -lgltt$(LIBSUF)
	GLUTINC = -I$(PPOOL)/include -D GLUT_LIB
	GLUTLIB = $(PPOOL)/lib/$(OS)/libglut-sm.a
	S3INC = -I$(PPOOL)/include/s3 -D S3_LIB
	S3LIB = -L$(PPOOL)/lib/$(OS) -ls3$(LIBSUF)
	HIDINC  = -I$(PPOOL)/include/hid -D HID_LIB
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
	MEDINC  = -I$(PPOOL)/include/medusa -D MEDUSA_LIB
	MEDLIB  = -L$(POOL)/lib/$(OS) -lmedusa$(LIBSUF)
	MICOINC = -I$(PPOOL)/opt/mico/inst/$(OS)/include -D MICO_LIB
	MICOLIB = -L $(PPOOL)/opt/mico/inst/$(OS)/lib -lmico2.3.1 -lmicocoss2.3.1
	THRINC  = 
	THRLIB  = -lpthread 
	LOGINC  = -I$(PPOOL)/include/log
	LOGLIB  = -L$(PPOOL)/lib/$(OS) -llog$(LIBSUF)
endif
#-- HP-UX ------------------------------------------------------------
ifeq ($(OS),HP-UX)
  GCC     = gcc
  GCXX    = g++
  GCXXINC = 
  GCFLAGS = -c -o $@ -D$(OS)_OS -Wall -pedantic -DGNU_CC \
						-frtti -I. 
  ifeq ($(TEMPDB),YES)
	  GCFLAGS += -fno-implicit-templates
  endif
  GLD     = $(GCCHOME)/SunOS_5.5_sparc/bin/g++

	NCC			= /opt/aCC/bin/aCC 
	NCXX		= /opt/aCC/bin/aCC 
	NCXXINC = -I.
  NCFLAGS = -c -o $@ -D HP_OS -D NATIVE_CC 
	NLD			= /opt/aCC/bin/aCC 

	STRIP   = strip
	LINK    = ln -s

	PURIFY	= /hgdv/software/purify/SunOS5/purify
	LEX     = flex -dLst
	YACC    = bison
	MOC			= $(QTDIR)/bin/moc
	PURIFY  = /hgdv/software/purify/SunOS5/purify
	DFLAG		= -g -DDEBUG_BIN
	OPTFLAG =	
	LDFLAGS = -o $(SYSTARGET)
	SYSTMP	= ./
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
	JPEGINC = -I$(PPOOL)/include/jpeg
	JPEGLIB = -L$(PPOOL)/lib/jpeg -ljpeg
	TIFFINC = -I$(PPOOL)/include/tiff -D TIFF_LIB
	TIFFLIB = -L$(PPOOL)/lib/$(OS) -ltiff
	GIFINC  = -I/$(PPOOL)/include/GIF
	GIFLIB  = -L/$(PPOOL)/lib/$(OS) -lGIF$(LIBSUF)
	XMLINC  = -I$(PPOOL)/include/xml -DXML_LIB
	XMLLIB  = -L$(PPOOL)/lib/$(OS) -lxml$(LIBSUF)
	NMINC   = -I$(PPOOL)/include/newmat
	NMLIB   = -L$(PPOOL)/lib/$(OS) -lnewmat$(LIBSUF)
	COMINC  = -I$(PPOOL)/include
  COMLIB  = -L$(PPOOL)/lib/$(OS) -lcompress$(LIBSUF)
	XINC 		= -I/usr/openwin/include -D X_LIB 
	XLIB  	= -L/usr/lib/X11R6 -L/usr/lib/X11R5 -lXt -lXext -lX11
	MINC 		=	-I/usr/dt/include 
	MLIB		= -R/usr/dt/lib -L/usr/dt/lib -lXm 
	QTINC		=	-I$(QTDIR)/include
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
	S3INC = -I$(PPOOL)/include/s3 -D S3_LIB
	S3LIB = -L$(PPOOL)/lib/$(OS) -ls3$(LIBSUF)
	HIDINC  = -I$(PPOOL)/include/hid -D HID_LIB
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
  GCFLAGS = -c -o $@ -D$(OS)_OS -DARCH=3 -Wall -pedantic -DGNU_CC	
  ifeq ($(TEMPDB),YES)
	  GCFLAGS += -fno-implicit-templates
  endif
	GLD			= $(GCCHOME)/bin/g++
	GLIBDIR  = lib

	NCC			= cc
	NCXX		= /usr/bin/CC
	NCXXINC = -I/usr/include/CC
  NCFLAGS = -c -o $@ -D$(OS)_OS -DARCH=3 -DNATIVE_CC -n32 -LANG:bool=ON -LANG:std -woff 1107,1682 
	NLD			= CC 
	NLIBDIR = lib

	STRIP   = strip
	LINK    = ln -s
	LEX     = flex -dLst
	YACC    = /sgi/gnu2.7.2/bin/bison
	MOC			= $(QTDIR)/bin/moc
	DFLAG		= -g -DDEBUG_BIN
	OPTFLAG =	-O2 
	LDFLAGS = -o $(SYSTARGET) 
	SYSTMP	= ./
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
	QTINC		=	-I$(QTDIR)/include
	QTLIB		= -L$(QTDIR)/$(LIBDIR) -lqt -lCio
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
	S3INC = -I$(PPOOL)/include/s3 -D S3_LIB
	S3LIB = -L$(PPOOL)/lib/$(OS) -ls3$(LIBSUF)
	HIDINC  = -I$(PPOOL)/include/hid -D HID_LIB
	HIDLIB  = -L$(PPOOL)/lib/$(OS) -lhid$(LIBSUF)
	GLUTINC = -I$(PPOOL)/include -D GLUT_LIB
	GLUTLIB = -I$(PPOOL)/lib/$(OS) -lglut
#	GLUTINC = -I/usr/include
#	GLUTLIB = -I/usr/$(LIBDIR) -lglut
	CAMINC  = -I/usr/include -DCAMERA_LIB
	CAMLIB  = -I/usr/lib -lvl
#	OIINC		= -I/opt/Inventor/include
#	OILIB		= -L/opt/Inventor/lib -lInventorXt -lInventor
	OIINC		= -I/usr/include
	OILIB		= -L/usr/$(LIBDIR) -lInventor -lInventorXt
	MEDINC  = -I$(PPOOL)/include/medusa -D MEDUSA_LIB
	MEDLIB  = -L$(POOL)/lib/$(OS) -lmedusa$(LIBSUF) 
	THRINC  = 
	THRLIB  = -lpthread 
endif
#-- SGI --------------------------------------------------------------
ifeq ($(OS),IRIX64)
	GCCHOME	= $(GCCPATH)
	#GCCHOME	= /hgdv/software/gcc-2.8.1/IRIX64_6.2_mips
	GCC 		= $(GCCHOME)/bin/gcc 
	GCXX 		= $(GCCHOME)/bin/g++ 
#	GCXXINC	= -I$(GCCHOME)/lib/g++-include
	GCXXINC	= 
  GCFLAGS = -c -o $@ -D$(OS)_OS -Wall -pedantic -DGNU_CC -frtti -DRTTI 
  ifeq ($(TEMPDB),YES)
	  GCFLAGS += -fno-implicit-templates
  endif
	GLD 		= $(GCCHOME)/bin/g++ -LANG:std
	GLIBDIR = lib32

	NCC 		= cc
	NCXX 		= CC -LANG:std -ptused -signed
	#NCXX 		= CC -LANG:std -ptused
	NCFLAGS = -LANG:std -ptused -c -o $@ -D$(OS)_OS -DNATIVE_CC -n32 \
						-woff 3303,1355,1107
	NLD			= CC -n32 -LANG:std -ptused
#	NLD			= CC -n32 -LANG:std -ptused
	NLIBDIR = lib32

	STRIP   = strip
	LINK    = ln -s
	LEX     = flex -dLst
	YACC    = /sgi/gnu2.7.2/bin/bison
	MOC			= $(QTDIR)/bin/moc
	DFLAG		= -g -DDEBUG_BIN
	OPTFLAG =
	LDFLAGS = -o $(SYSTARGET) 
	SYSTMP	= ./
	XDEBUGER	=	ddd
	EDIT		= xemacs
	XTERM		= xterm
	BINSET  = touch

	OBJSUF  = o
	BINSUF  =

	EXINC 	= -I$(PPOOL)/include
	EXLIB 	= -L$(PPOOL)/lib/$(OS)/$(LIBDIR)
	SYSINC  = 
	SYSLIB  = -lm
	#STLINC  = -I/igd/a4/op2010/Software/SGI/stdlib
	#STLLIB  = -L/igd/a4/op2010/Software/SGI/stdlib -lCio
	STLINC  = 
	STLLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lCio
 
	ACEINC  = -I$(PPOOL)/include/ace/version_4.6 ACE_LIB
	ACELIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lACE$(LIBSUF)
	SMANINC  = -I$(PPOOL)/include/sman -DSOCKETMAN_LIB
	SMANLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lsman
	COMINC  = -I$(PPOOL)/include
  COMLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lcompress$(LIBSUF)
	HERINC  = -I$(PPOOL)/include/hermes -DHERMES_LIB
	HERLIB  = -I$(PPOOL)/lib/$(OS)/$(LIBDIR) -lhermes$(LIBSUF) -lmedusa$(LIBSUF) 
	HER2INC  = -I$(PPOOL)/include/hermes2 -DHERMES2_LIB
	HER2LIB  = -I$(PPOOL)/lib/$(OS)/$(LIBDIR) -lhermes2$(LIBSUF) -lmedusa$(LIBSUF) 

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
	XMLINC  = -I$(PPOOL)/include/xml -DXML_LIB
	XMLLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lxml$(LIBSUF)
	ECMAINC	= -I$(PPOOL)/include/js -I$(PPOOL)/include/js/IRIX6.5_DBG.OBJ -DECMA_LIB
	ECMALIB	= -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -ljs -lfdm -lm
	XINC 		= -I/usr/include/X11 -D X_LIB
	XLIB  	= -L/usr/$(LIBDIR) -lXmu -lXext -lXt -lXi -lX11
	MINC 		=	-I/usr/include/X11 
	MLIB		= -L/usr/lib32 -lXm 
	QTINC		=	-I$(QTDIR)/include
	QTLIB		= -L$(QTDIR)/lib -lqt
	CAMINC  = -I/usr/include -DCAMERA_LIB
	CAMLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lcamera -L/usr/$(LIBDIR) -lvl
	#ANIMINC = -I$(PPOOL)/include/ANIM -D ANIM_LIB
	#ANIMLIB = -L$(PPOOL)/lib/$(OS) -lANIM$(LIBSUF) -lvic$(LIBSUF) -lMPEG$(LIBSUF)
	ANIMINC = -I$(PPOOL)/src/mpeg_play -D ANIM_LIB
	ANIMLIB = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lMPEG$(LIBSUF) -lpthread
	DYNINC  = -I$(PPOOL)/include/dynamid -DDYNAMID_LIB
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
	#OGLINC	= -I/usr/tmp/mesa/include -DMESA_OGL -DOPENGL_LIB
	#OGLLIB	= -L/usr/tmp/mesa/$(LIBDIR) -lMesaGLU -lMesaGL
	PMINC   = -I$(PPOOL)/include/pmesh -D PMESH_LIB
	PMLIB   = -I$(PPOOL)/lib/$(OS)/$(LIBDIR) -lpmesh$(LIBSUF)
	ABINC   = -I$(PPOOL)/include/abase -DABASE_LIB
	ABLIB 	= -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -labase$(LIBSUF)
	TIINC   = -I$(PPOOL)/include/texImage -D TEXIMAGE_LIB 
	TILIB   = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -ltexImage$(LIBSUF)
	GSINC   = -I$(PPOOL)/include/geoShape -D GEOSHAPE_LIB 
	GSLIB   = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lgeoShape$(LIBSUF)
	ACFINC  = -I$(PPOOL)/include/appConfig -D APPCONFIG_LIB
	ACFLIB  = -L$(PPOOL)/lib/$(OS) -lappConfig$(LIBSUF)
	OIINC   = -I/usr/include -D INVENTOR_LIB
	OILIB		= -L/usr/$(LIBDIR) -lInventor 
	TTFINC  = -I/$(PPOOL)/include/freetype -D TTF_LIB
	TTFLIB  = -L/$(PPOOL)/lib/$(OS)/$(LIBDIR) -lttf -lGLU
	TMINC   = -I/$(PPOOL)/include/textMaker -D TEXTMAKER_LIB
	TMLIB   = -L/$(PPOOL)/lib/$(OS)/$(LIBDIR) -ltextMaker$(LIBSUF)
	GLTTINC = -I/$(PPOOL)/include/gltt -D GLTT_LIB
	GLTTLIB = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lgltt
	GLUTINC = -I$(PPOOL)/include -D GLUT_LIB
	GLUTLIB = -L/$(PPOOL)/lib/IRIX/$(LIBDIR) -lglut-sm-nfa
	S3INC = -I$(PPOOL)/include/s3 -D S3_LIB
	S3LIB = -L$(PPOOL)/lib/$(OS) -ls3$(LIBSUF)
	HIDINC  = -I$(PPOOL)/include/hid -D HID_LIB
	HIDLIB  = -L$(PPOOL)/lib/$(OS) -lhid$(LIBSUF)
	OPTINC  = -I/usr/include -D OPTIMIZER_LIB
	OPTLIB  = -L/usr/lib32 -lop_sp -lopGUI_sp -lcosmo3d
	MEDINC  = -I$(PPOOL)/include/medusa -D MEDUSA_LIB
	MEDLIB  = -L$(POOL)/lib/$(OS)/$(LIBDIR) -lmedusa$(LIBSUF) 
	THRINC  = 
	THRLIB  = -lpthread 
	LOGINC  = -I$(PPOOL)/include/log
	LOGLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -llog$(LIBSUF)
endif
#-- Linux -----------------------------------------------------------
ifeq ($(OS),Linux)
	GCC 		= gcc
	GCXX 		= g++
  GCFLAGS = -c -o $@ -D$(OS)_OS -Wall -fPIC -ffast-math -funroll-loops -frtti -Wno-unknown-pragmas -I.
  ifeq ($(TEMPDB),YES)
	  GCFLAGS += -fno-implicit-templates
  endif
	GLD			= gcc
	GSO     = gcc -shared

	NCC 		= gcc
	NCXX 		= g++
  NCFLAGS = -c -o $@ -D$(OS)_OS -Wall -fPIC -ffast-math -funroll-loops -frtti -Wno-unknown-pragmas -I.
  ifeq ($(TEMPDB),YES)
	  GCFLAGS += -fno-implicit-templates
  endif
	NLD			= gcc
	NSO     = $(GCCHOME)/bin/gcc -shared

	STRIP   = strip
	LINK    = ln -s
	LEX     = flex -dLst
	YACC    = bison
	MOC			= $(QTDIR)/bin/moc
	DFLAG		= -g -DDEBUG_BIN
	OPTFLAG =	-O2
	LDFLAGS = -o $(SYSTARGET) 
	SYSTMP	= ./
	XDEBUGER	=	ddd
	EDIT		= xemacs
	XTERM		= rxvt
	BINSET  = touch

	OBJSUF  = o
	BINSUF  =

	EXINC 	= 
	EXLIB 	= -L$(PPOOL)/lib/$(OS)
	SYSINC  = -I$(PPOOL)/include
	SYSLIB  =  -lstdc++ -lm
	STLINC  = 

	TIFFINC = -I/usr/include -D TIFF_LIB
	TIFFLIB = -L/usr/lib -ltiff
	JPEGINC = -I$(PPOOL)/include/jpeg -DJPEG_LIB
	AEIINC  = -I$(PPOOL)/include/aei -DAEI_LIB
	AEILIB  = -L$(PPOOL)/lib/$(OS) -laei$(LIBSUF)
	JPEGLIB = -L/usr/lib/jpeg -ljpeg
	GIFINC  = -I/$(PPOOL)/include/GIF -DGIF_LIB
	GIFLIB  = -L/$(PPOOL)/lib/$(OS) -lGIF$(LIBSUF)
	XPPINC  = -I$(PPOOL)/include/xmlpp -DXMLPP_LIB
	XPPLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lxmlpp$(LIBSUF)
	XMLINC  = -I$(PPOOL)/include/xml -DXML_LIB
	XMLLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lxml$(LIBSUF)
	XINC 		=
	XLIB	 	= -L/usr/X11R6/lib -lXmu -lXext -lXt -lSM -lICE -lXi -lX11
	MINC 		=	-I/usr/X11R6/include 
	MLIB		= -L/usr/X11R6/lib -lXm 
	QTINC		=	-I$(QTDIR)/include
	QTLIB		= -L$(QTDIR)/lib -lqt
	VORINC  = -I$(PPOOL)/include/voronoi -D VORONOI_LIB
	VORLIB  = -L$(PPOOL)/lib/$(OS) -lvor$(LIBSUF)
	NMINC   = -I$(PPOOL)/include/newmat
	NMLIB   = -L$(PPOOL)/lib/$(OS) -lnewmat$(LIBSUF)
	TMINC   = -I/$(PPOOL)/include/textMaker -D TEXTMAKER_LIB
	TMLIB   = -L/$(PPOOL)/lib/$(OS) -ltextMaker$(LIBSUF)
	PMINC   = -I$(PPOOL)/include/pmesh -D PMESH_LIB
	PMLIB   = -I$(PPOOL)/lib/$(OS) -lpmesh$(LIBSUF)
	OGLINC	= -I/usr/X11R6/include  -DMESA_OGL -DOPENGL_LIB
	OGLLIB	= -L/usr/X11R6/lib -lGLU -lGL
	#OGLLIB	= -L/usr/X11R6/lib -lMesaGLU -lMesaGL
  CAMINC   = -I$(PPOOL)/include -DCAMERA_LIB
  CAMLIB   = -L$(PPOOL)/lib/$(OS) -lcamera 
	OIINC   = -I/opt/OpenInventor/include
	OILIB		= -L/opt/OpenInventor/lib -lInventorXt -lInventor -limage
	TTFINC  = -I/$(PPOOL)/include -D TTF_LIB
	TTFLIB  = -L/$(PPOOL)/lib/$(OS) -lttf
	HERINC  = -I$(PPOOL)/include/hermes -DHERMES_LIB
	#HERLIB  = -L$(PPOOL)/lib/$(OS) -lhermes$(LIBSUF)
	HERLIB  = -I$(PPOOL)/lib/$(OS) -lhermes$(LIBSUF) -lmedusa$(LIBSUF) 
	HER2INC  = -I$(PPOOL)/include/hermes2 -DHERMES2_LIB
	HER2LIB  = -I$(PPOOL)/lib/$(OS) -lhermes2$(LIBSUF) -lmedusa$(LIBSUF) 
	COMINC  = -I$(PPOOL)/include
  COMLIB  = -L$(PPOOL)/lib/$(OS) -lcompress$(LIBSUF)
	DYNINC  = -I$(PPOOL)/include/dynamid -DDYNAMID_LIB
	DYNLIB  = -L$(PPOOL)/lib/$(OS) -lDYNAMID$(LIBSUF)
	TTFINC  = -I/$(PPOOL)/include/freetype -D TTF_LIB
	TTFLIB  = -L/$(PPOOL)/lib/$(OS) -lttf
	GLTTINC = -I/$(PPOOL)/include/gltt -D GLTT_LIB
	GLTTLIB = -L$(PPOOL)/lib/$(OS) -lgltt$(LIBSUF)
	ABINC   = -I$(PPOOL)/include/abase -DABASE_LIB
	ABLIB 	= -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -labase$(LIBSUF)
	TIINC   = -I$(PPOOL)/include/texImage -D TEXIMAGE_LIB 
	TILIB   = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -ltexImage$(LIBSUF)
	GSINC   = -I$(PPOOL)/include/geoShape -D GEOSHAPE_LIB 
	GSLIB   = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -lgeoShape$(LIBSUF)
	ACFINC  = -I$(PPOOL)/include/appConfig -D APPCONFIG_LIB
	ACFLIB  = -L$(PPOOL)/lib/$(OS) -lappConfig$(LIBSUF)
	GLUTINC = -I$(PPOOL)/include -D GLUT_LIB
	GLUTLIB = -L$(PPOOL)/lib/$(OS) -lglut-sm
	S3INC = -I$(PPOOL)/include/s3 -D S3_LIB
	S3LIB = -L$(PPOOL)/lib/$(OS) -ls3$(LIBSUF)
	HIDINC  = -I$(PPOOL)/include/hid -D HID_LIB
	HIDLIB  = -L$(PPOOL)/lib/$(OS) -lhid$(LIBSUF)
	OGLWINC = -I/usr/X11/include 
	OGLWLIB = -L/usr/X11/lib -lMesaGLwM
	MEDINC  = -I$(PPOOL)/include/medusa -D MEDUSA_LIB
	MEDLIB  = -L$(POOL)/lib/$(OS) -lmedusa$(LIBSUF) 
	THRINC  = 
	THRLIB  = -lpthread 
	LOGINC  = -I$(PPOOL)/include/log
	LOGLIB  = -L$(PPOOL)/lib/$(OS)/$(LIBDIR) -llog$(LIBSUF)
endif
#-- NT --------------------------------------------------------------
ifeq ($(findstring WIN,$(OS)),WIN)

	QTDIR := q:\\packages\\qt-2.3
	OS		= WIN32
	GCC 		= gcc
	GCXX 		= g++
  GCFLAGS = -c -o $@ -D$(OS)_OS -Wall -pedantic -ID:\include -DGNU_CC	
	GLD			= g++

	NCC 		= cl
	NCXX 		= cl
	NCFLAGS	= /c /Fd"c:\tmp\test.pdb" /Fo"$@" /D "ANSI_STL" /D "NT_OS" /D "NATIVE_CC" \
						/D "__i386__"  /D "WIN32" /D "_WIN32" /D "_MBCS" \
						/D "_WINDOWS" /D "__ANSI_CPP__" /nologo \
						/D XMLPP_NOEXPORTS

	NLD	= link /DEBUG /libpath:"V:/lib/NT" /libpath:"f:\Program Files\Microsoft Visual Studio\VC98\Lib" /NODEFAULTLIB:LIBC 

	STRIP   = upx
	LINK    = cp
	LEX     = flex -dLst
	YACC    = bison
	MOC			= $(QTDIR)/bin/moc

	DFLAG	  = -DDEBUG_BIN /GR /GX /ZI /Zi /Yd /W1 /MTd
	OPTFLAG = /GR /GX /W3 /G6 /O2 /Ogityb2 /Gs /MT 
	#OPTFLAG = /GR /GM /W1 /G6 /Ot /O2 /GR /MT
	#OPTFLAG = /GR /GX /W1 /G6 /Ot /O2 /GR /MT

	LDFLAGS = /nologo /subsystem:console /incremental:yes /machine:I386 \
						/pdb:"$(TARGET).pdb" /out:"$(SYSTARGET)" 

	SYSTMP	= 
	XDEBUGER	=	ddd
	EDIT		= xemacs
	XTERM		= bash 
	BINSET  = touch

	OBJSUF  = obj
	BINSUF  = .exe

	EXINC 	= -I "V:\include" -I "V:\include\NT" -I "V:\include" -I"f:\Program Files\Microsoft Visual Studio\VC98\Include"
	EXLIB 	= /libpath:"V:\lib\NT"
	SYSINC  = 
	SYSLIB  = kernel32.lib user32.lib gdi32.lib winspool.lib \
						comdlg32.lib advapi32.lib shell32.lib winmm.lib \
						ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib 

#						/NODEFAULTLIB:LIBC 

	NETINC  = 
	NETLIB  = ws2_32.lib 
	STLINC  = -D STL_NAMESPACE 
#	STLINC  = -D "OS_WIN_NT_4_0" -I "V:\include\ospace" -I "V:\include\ospace\ospace\stl" -D "OS_STL" /D STL_HSUFFIX 
#	STLLIB  = std-2.0.1-vc5.0.lib std-2.0.1-vc5.0-mt.lib std-2.0.1-vc5.0-uss.lib std-2.0.1-vc5.0-mt-uss.lib 
	#STLINC  = -I "V:\include\stlport" /D "STLPORT_STL" /D "STL_NAMESPACE"
	#STLLIB  = 
	PMINC   = -I "V:\include\pmesh" /D PMESH_LIB
	PMLIB   = pmesh.lib
	ABINC   = -I "V:\include\abase" /D ABASE_LIB
	ABLIB 	= abase.lib
	TIINC   = -I "V:\include\texImage" /D TEXIMAGE_LIB 
	TILIB   = texImage.lib
	VORINC  = -I "V:\include\voronoi" -D VORONOI_LIB
	VORLIB  = vor.lib
	AEIINC  = -I "V:\include\aei" /D AEI_LIB
	AEILIB  = aei.lib
	NMINC   = -I "V:\include\newmat" 
	NMLIB   = newmat.lib
	GSINC   = -I "V:\include\geoShape" /D GEOSHAPE_LIB 
	GSLIB   = geoShape.lib
	ACFINC  = -I "V:\include\appConfig" /D APPCONFIG_LIB
	ACFLIB  = appConfig.lib
	ACEINC  = -I "V:\include\ace\version_4.5"
	ACELIB  = aced.lib
	DYNINC  = -I "V:\include\dynamid" /D DYNAMID_LIB
	DYNLIB  = dynamid.lib
	COMINC  = -I "V:\include" /D COMPRESS_LIB
  COMLIB  = compress.lib
#	ECMAINC = -I "U:\homes\pdaehne_vc8\js" /D ECMA_LIB
	ECMAINC	= -I "V:\include\js" /D ECMA_LIB
	ECMALIB	= js32.lib
	VIDEOBUFFERINC   = -I "V:\include\videobuffer" /D VIDEOBUFFER_LIB
	VIDEOBUFFERLIB 	= videoBuffer.lib
	XINC 		=
	XLIB	 	= 
	MINC 		=	
	MLIB		= 
	DXINC   = -I "V:\include\directX" /D DIRECTX_LIB
	DXLIB   = /libpath:"V:/lib/NT/directX" dsound.lib dinput.lib dxguid.lib
	COMINC  = -I "V:\include\include"
  COMLIB  = compress.lib
	TTFINC  = -I "V:\include\freetype" /D TTF_LIB
	TTFLIB  = freetype.lib
	TMINC   = -I "V:\include\textMaker" /D TEXTMAKER_LIB
	TMLIB   = textMaker.lib
	S3INC   = -I "V:\include\s3" /D S3_LIB
	S3LIB   = s3.lib
	HIDINC  = -I "V:\include\hid" /D HID_LIB
	HIDLIB  = hid.lib
	GSINC   = -I "V:\include\geoShape" /D GEOSHAPE_LIB 
	GSLIB   = geoShape.lib
	SMANINC  = -I "V:\include\sman" /D SOCKETMAN_LIB
	SMANLIB  = -lsman
	HERINC  = -I "V:\include\hermes" /D HERMES_LIB
	HERLIB  = hermes.lib
	HER2INC = -I "V:\include\hermes2" /D HERMES2_LIB
	HER2LIB = hermes2.lib medusa.lib
	MEDINC  = -I "V:\include\medusa" -D MEDUSA_LIB
	MEDLIB  = medusa.lib
	GIFINC  = -I "V:\include\GIF" /D GIF_LIB
	GIFLIB  = GIF.lib
	XMLINC  = -I "V:\include\xml" /D XML_LIB
	XMLLIB  = xml.lib
	TIFFINC  = -I "V:\include\tiff" /D TIFF_LIB
	TIFFLIB  = tiff.lib
	JPEGINC = -I "V:\include\jpeg" /D JPEG_LIB
	JPEGLIB = libjpeg.lib
	PNGINC  = -I "V:\include\png" /D PNG_LIB
	PNGLIB  = libpng.lib
	ZINC     = -I "V:\include\zlib" /D Z_LIB
	ZLIB     = zlib.lib
	A3DINC  = -I "V:\include\a3d" -D A3D_LIB
	A3DLIB  = ia3dutil.lib
	QTINC		=	-I "$(QTDIR)\\include"
	QTLIB		= /libpath:"$(QTDIR)\lib"  qt230.lib
	GLTTINC = -I "V:\include\gltt" /D GLTT_LIB
	GLTTLIB = gltt.lib 
	OGLINC	= /D OPENGL_LIB
	OGLLIB	= opengl32.lib glu32.lib 
	GLUTINC =  /D GLUT_LIB
	GLUTLIB = /libpath:"V:/lib/NT" glut32.lib 
	#GLUTLIB = /libpath:"V:/lib/NT" glut32-sm.lib mg_spacemouse.lib
endif
ifeq ($(TMPBIN),YES)
	SYSTARGET = $(SYSTMP)$(TARGET).$(USER)_$(SYSDEP)$(BINSUF)
	TARGETLNK = $(SYSTMP)$(TARGET).$(USER)$(BINSUF)
else
	SYSTARGET = ./$(TARGET).$(SYSDEP)$(BINSUF)
	TARGETLNK = ./$(TARGET).$(BINSUF)
endif
######################################################################

### Document Dir #####################################################
DOCDIR = $(PPOOL)/doc/src/$(TARGET)
######################################################################

### Compiler and Linker ##############################################
ifeq ($(CC_$(OS)),GNU_CC)
	CC = $(GCC)
	CXX = $(GCXX)
	CXXINC = $(GCXXINC)
	LD = $(GLD)
	SOLD = $(GSO)
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
	LD = $(NLD)
	SOLD = $(NSO)
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

### Production flag (degug/optimize) #################################
ifeq ($(DEBUG),YES)
	PROFLAG = $(DFLAG) $(PROFLAG_$(OS))
	BINSET = touch
else
	PROFLAG = $(OPTFLAG) $(PROFLAG_$(OS))
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
ifeq ($(OPENGL_PAK),YES)
	INCS += $(OGLINC)
	LIBS += $(OGLLIB)
  ifeq ($(QT_PAK),YES)
    LIBS += $(QTOGLLIB)
  endif
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
ifeq ($(OSGBASE_PAK),YES)
	INCS += -I $(OSGROOT)/Base
	LIBS += -L $(OSGROOT)/lib/$(OS) -lBase
endif
ifeq ($(OSG_LOG_PAK),YES)
	INCS += -I $(OSGROOT)/Log
	LIBS += -L $(OSGROOT)/lib/$(OS) -lLog
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
ifeq ($(HERMES2_PAK),YES)
	INCS += $(HER2INC)
	LIBS += $(HER2LIB)
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
ifeq ($(APPCONFIG_PAK),YES)
	INCS += $(ACFINC)
	LIBS += $(ACFLIB)
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

### Compiler and linker flags ########################################
CFLAGS = $(PROFLAG) $(SCFLAGS) $(INCS)
CXXFLAGS = $(PROFLAG) $(SCFLAGS) $(INCS)
######################################################################

### Object and source files ##########################################
HEADERS := $(shell test -f declist.mk && cat declist.mk)
SOURCES := $(shell test -f implist.mk && cat implist.mk)
BINOBJS := $(shell test -f objlist.$(SYSDEP).mk && cat objlist.$(SYSDEP).mk)
LIBOBJS := $(shell test -f objlist.$(SYSDEP).mk && sed < objlist.$(SYSDEP).mk 's/main\.[a-zA-Z_0-9]*\.o//g')
######################################################################

### TARGET build rules ###############################################
:%.o
	@echo "AAA"

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
	$(QTDIR)/bin/uic -o $@ $<

%.cpp: %.ui
	$(QTDIR)/bin/uic -i $*.h -o $@ $<

moc_%.cpp: %.h
	$(MOC) -f$< $< -o $@

%.$(SYSDEP).o: %.cc
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.cxx
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.cpp
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.C
	$(CXX) $(CXXFLAGS) $<

%.$(SYSDEP).o: %.c
	$(CC) $(CXXFLAGS) $<

%.pp: %.cpp
	$(CXX) -E $(CXXFLAGS) $<

######################################################################

### File lists #######################################################
lists: declist implist objlist 
	$(MAKE) depend 

declist:
	@echo "make declist.mk"
	@rm -rf declist.mk
	@for i in *.ui ;\
	do \
	    echo $$i | sed 's/.ui/.h/g' > declist.mk ; \
	done
	@echo *.[hH] *.hh *.hxx *.ui " " | \
	sed 's/\*\.[a-zA-Z]* //g' | \
	cat >> declist.mk

implist:
	@echo "make implist.mk"
	@rm -rf implist.mk
	@grep -l Q_OBJECT *.[hH] | sed -e 's/^/moc_/g' -e 's/.[hH]/.cpp/' >> implist.mk
	@for i in *.ui ;\
	do \
	    echo $$i | sed -e 's/^/moc_/g' -e 's/.ui/.cpp/g' >> implist.mk ; \
	    echo $$i | sed -e 's/.ui/.cpp/g' >> implist.mk ; \
	done
	@echo *.y *.l *.c *.C *.cc *.cxx *.cpp " " | \
	sed 's/\*\.[a-zA-Z]* //g' | \
	cat >> implist.mk

objlist: implist.mk
	@echo "make objlist.$(SYSDEP).mk"
	@rm -rf objlist.$(SYSDEP).mk
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

depend: implist.mk $(shell test -f implist.mk && cat implist.mk) declist.mk $(shell test -f declist.mk && cat declist.mk)
	@echo "make deplist.$(SYSDEP).mk"
	@makedepend 2>/dev/null $(INCS) $(shell cat implist.mk) \
	-f - | sed 's/\.o/\.$(SYSDEP)\.o/' > deplist.$(SYSDEP).mk

######################################################################

### Commands #########################################################
all: 
	$(MAKE) lists 
	$(MAKE) $(TARGET)$(BINSUF)

uinstall: $(SYSTARGET)
	$(STRIP) $(SYSTARGET)
	cp $(SYSTARGET) $(HOME)/bin/$(OS)/$(TARGET)$(BINSUF)

install: $(SYSTARGET)
	$(STRIP) $(SYSTARGET)
	cp $(SYSTARGET) $(PPOOL)/bin/$(OS)/$(TARGET)$(BINSUF)

lib: $(LIBOBJS)
	rm -rf lib$(TARGET)$(LIBSUF).a
	ar ruv lib$(TARGET)$(LIBSUF).a $(LIBOBJS)

slib: $(LIBOBJS)
	rm -rf lib$(TARGET)$(LIBSUF).so
	$(SOLD) -o lib$(TARGET)$(LIBSUF).so $(LIBOBJS)

ulibinstall: lib
	mv lib$(TARGET)$(LIBSUF).a $(HOME)/lib/$(OS)/$(LIBDIR)

libinstall: lib
	mv lib$(TARGET)$(LIBSUF).a $(PPOOL)/lib/$(OS)/$(LIBDIR)

slibinstall: slib
	mv lib$(TARGET)$(LIBSUF).so $(PPOOL)/lib/$(OS)/$(LIBDIR)


includelink:
	ln -s $(PWD) $(PPOOL)/include/$(TARGET)

clean:
	-rm -f *.$(SYSDEP).o *.$(SYSDEP)*_pure_* *.bak *.swp *~ *% \#*\# 
	-rm -f $(TARGET)$(BINSUF) $(SYSTARGET)

mrProper: clean
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

-include deplist.$(SYSDEP).mk
