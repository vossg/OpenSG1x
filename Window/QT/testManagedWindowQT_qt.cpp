
#ifdef __sgi
#pragma set woff 1375
#endif

#include <qapplication.h>

#ifdef __sgi
#pragma reset woff 1375
#endif

#include <OSGConfig.h>
#include <OSGSceneFileHandler.h>
#include <OSGQGLManagedWidget_qt.h>

int main( int argc, char ** argv )
{
  osg::osgInit(argc,argv);

  int retCode = -1;
  QApplication qapp( argc, argv );
  osg::OSGQGLManagedWidget widget;
  osg::NodePtr root;
  

  if (argc > 1)
    {
      root = osg::SceneFileHandler::the().read(argv[1]);
      if (root == osg::NullFC)
        {
          FFATAL (( "Couldn't load %s", argv[1]));
        }
      else
        {
          widget.getManager().setRoot(root);
          widget.getManager().showAll();
          widget.show();
          retCode = qapp.exec();
        }
    }
  else
    {
      FFATAL (( "%s usage: %s 'sceneFileName'\n", argv[0], argv[0] ));
    }
  
  osg::osgExit();

  return retCode;
}
