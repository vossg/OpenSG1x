CC = /home/michael/redhat/usr/bin/gcc
MAYA_DIR = /usr/aw/maya4.5
MAYA_PLUGINS = $(MAYA_DIR)/bin/plug-ins
MAYA_LIB = $(MAYA_DIR)/lib
OSG-CONFIG = /home/michael/install/OpenSG-gcc2.96/bin/osg-config
IFLAGS = -Wall -DLINUX -D_BOOL -I. -I$(MAYA_DIR)/include `$(OSG-CONFIG) --cflags System Contrib`
LFLAGS = -L$(MAYA_LIB) -lOpenMayaAnim -lOpenMaya `$(OSG-CONFIG) --libs System Contrib` #-lOpenMayaUI -lOpenMayaAnim -lOpenMayaFX -lImage

OpenSG_exporter.so: maya_exporter.o 
	$(CC) -shared -o $@ $(IFLAGS) $^ $(LFLAGS)

%.o: %.cc
	$(CC) -c -fPIC -o $@ $(IFLAGS) $<

%.o: %.cpp
	$(CC) -c -fPIC -o $@ $(IFLAGS) $<

clean:
	-rm OpenSG_exporter.so

install:
	cp -upf OpenSG_exporter.so $(MAYA_PLUGINS)
