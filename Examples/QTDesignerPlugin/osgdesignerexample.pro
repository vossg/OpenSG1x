unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}
FORMS	 = osgdesignerexampleform.ui
TEMPLATE =app
CONFIG	+= qt warn_on debug thread

win32:QMAKE_CXXFLAGS += $$system(bash osg-config --cflags QT)  
win32:LIBS           += $$system(bash osg-config --libs QT)

unix:QMAKE_CXXFLAGS  += $$system(osg-config --cflags QT)  
unix:LIBS            += $$system(osg-config --libs QT)

#LIBS     += -lGLU -lOSGBase -lOSGSystem -lOSGWindowQT
LANGUAGE  = C++
