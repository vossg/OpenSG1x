# This Makefile will compile the OpenSGWidget application (2nd tutorial in qt.dox)
# The first totorial has to be compiled by hand (see qt.dox)


# define the kind of library you have installed ('dbg' or 'opt')
LIBTYPE = opt

C++ = g++

CCFLAGS = -D_GNU_SOURCE -DQT_CLEAN_NAMESPACE -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_JPG -DOSG_WITH_PNG -D_OSG_HAVE_CONFIGURED_H_ -DQT_NO_XINERAMA -DQT_NO_XRENDER -DQT_NO_XFTFREERYPE -D_QT_NO_XKB -DQT_NO_SM_SUPPORT -DQT_NO_IMAGEIO_MNG -DQT_NO_IMAGEIO_JPEG -DQT_NO_STYLE_AQUA -DQT_NO_STYE_MAC -DQT_NO_STYLE_INTERLACE -DQT_NO_STYLE_COMPACT -use_readonly_const -ftemplate-depth-100 -Wno-deprecated -pipe -funroll-loops 
LDFLAGS = -L/usr/local/lib/$(LIBTYPE) -L/usr/qt/3/lib -L/usr/X11R6/lib -Wall
LIBS = -lOSGSystem -lOSGBase -lglut -lGLU -lGL -lXmu -lXi -lXt -lqt -lpthread -ldl
DEBUG = -c -O3
INCLUDE = /usr/qt/3/include

SOURCES = OpenSGWidget.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = OSGWidget

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(C++) $(LDFLAGS) $(LIBS) $(OBJECTS) -o $@

.cpp.o:
	$(C++) $(CCFLAGS) -I$(INCLUDE) $(DEBUG) $< -o $@

clean:
	rm -rf *.o OSGWidget

