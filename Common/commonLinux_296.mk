
include $(OSGPOOL)/$(OSGCOMMON)/commonLinux.mk

#LIBCIO = -lCio

WARNINGS := -Wall -W   -Wpointer-arith 						\
		    -Wcast-qual -Wcast-align   -Wconversion   		\
			-Wsign-compare -Winline -Wfloat-equal -Wpacked	\
			-Wunreachable-code  

#-Wpadded -Wshadow
#-Wwrite-string -Wdisabled-optimization
