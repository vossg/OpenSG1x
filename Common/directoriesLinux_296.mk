
SOFTDIR              = /usr/Software
MEDSOFTDIR           = /igd/a4/op2010/Software/Linux

INCLUDE_SYSTEM		  = /usr/include

#EGCS_VERSION         = 2.95.2
EGCS_VERSION         = 2.96

EGCS_BASEDIR         = $(SOFTDIR)/egcs/$(EGCS_VERSION)

INCLUDE_SYSTEM_CC	 	 = $(EGCS_BASEDIR)/include/g++-3

EGCS_ARCH            = $(PROC)-pc-linux

EGCS_DIR             = $(EGCS_BASEDIR)/lib/gcc-lib/$(EGCS_ARCH)/$(EGCS_VERSION)

EGCS_BIN             = $(EGCS_BASEDIR)/bin

INCLUDE_COMPILER     = $(EGCS_DIR)/include

INCLUDE_STL          = $(INCLUDE_SYSTEM_CC)

#LINK_GLUT            
#INCLUDE_GLUT

#LINK_GL
#INCLUDE_GL

LINK_X11             = /usr/X11R6/lib


INCLUDE_STL          = $(MEDSOFTDIR)/stdlib
LINK_STL             = $(MEDSOFTDIR)/stdlib
#/usr/Software/egcs/2.95.2/include/g++-3/