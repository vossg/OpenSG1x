
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

#include <OSGNode.h>
#include <OSGSimpleGeometry.h>
#include <OSGGroup.h>

int main( int argc, char ** argv )
{
  osg::osgInit(argc,argv);

  int retCode = -1;
  QApplication qapp( argc, argv );
  osg::OSGQGLManagedWidget widget;
  osg::NodePtr root;
  
  qapp.connect( &qapp, SIGNAL  ( lastWindowClosed() ), 
                &qapp, SLOT    ( quit() ) );

  if (argc > 1)
    {
      root = osg::SceneFileHandler::the().read(argv[1]);
      if (root == osg::NullFC)
        {
          FFATAL (( "Couldn't load %s", argv[1]));
        }
      else
        {       
osg::NodePtr scene = osg::makeTorus(.5, 1, 8, 8);
osg::NodePtr scene2 = osg::makeTorus(.1, 2, 10, 12);

osg::NodePtr grn = osg::Node::create();
osg::GroupPtr gr = osg::Group::create();

osg::beginEditCP(grn, osg::Node::CoreFieldMask | osg::Node::ChildrenFieldMask );
grn->setCore(gr);
grn->addChild(scene);
grn->addChild(scene2);
osg::endEditCP  (grn, osg::Node::CoreFieldMask | osg::Node::ChildrenFieldMask );

widget.getManager().setRoot(grn);
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
