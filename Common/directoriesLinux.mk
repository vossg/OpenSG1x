
SOFTDIR              = /usr/Software

INCLUDE_SYSTEM		 = /usr/include

GCC_VERSION          = 2.95.3

GCC_BASEDIR          = $(SOFTDIR)/gcc/$(GCC_VERSION)

INCLUDE_SYSTEM_CC 	 = $(GCC_BASEDIR)/include/g++-3

GCC_ARCH             = $(PROC)-pc-linux-gnu

GCC_DIR              = $(GCC_BASEDIR)/lib/gcc-lib/$(GCC_ARCH)/$(GCC_VERSION)

GCC_BIN              = $(GCC_BASEDIR)/bin

INCLUDE_COMPILER     = $(GCC_DIR)/include

QTDIR                = $(SOFTDIR)/qt/qt-2.1.1
INCLUDE_QT           = $(QTDIR)/include
LINK_QT              = $(QTDIR)/lib

