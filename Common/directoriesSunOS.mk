
INCLUDE_SYSTEM		  = /usr/include

GCC_VERSION         = 2.95.2

#GCC_BASEDIR        = $(SOFTDIR)/egcs/$(GCC_VERSION)

GCC_ARCH            = sparc-sun-solaris2.7

GCC_DIR             = $(GCC_BASEDIR)/lib/gcc-lib/$(GCC_ARCH)/$(GCC_VERSION)

GCC_BIN             = $(GCC_BASEDIR)/bin

INCLUDE_COMPILER    = $(GCC_DIR)/include

INCLUDE_SYSTEM_CC	  = $(GCC_BASEDIR)/include/g++-3

INCLUDE_PLATTFORM   = $(GCC_BASEDIR)/$(GCC_ARCH)/include/

#INCLUDE_COMPILER     = $(GCC_BASEDIR)/$(GCC_ARCH)/include

#INCLUDE_STL          = $(SOFTDIR)/STL/include_32
#INCLUDE_STL          = /usr/include
INCLUDE_STL     	    = $(GCC_BASEDIR)/include/g++-3
#INCLUDE_STL     	    = /igd/a4/lib/stl/include_32

LINK_GLUT               = /zgdv/vc9/avalon/lib/SunOS
INCLUDE_GLUT            = /zgdv/vc9/avalon/include
