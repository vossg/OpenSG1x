
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
    OSG::osgInit(argc,argv);

    int retCode = -1;
    QApplication qapp( argc, argv );

    QGLFormat::setDefaultFormat(QGLFormat(QGL::DirectRendering | 
                                          QGL::DoubleBuffer    |  
                                          QGL::DepthBuffer     |
                                          QGL::Rgba            ));
    
  OSG::OSGQGLManagedWidget widget;
  OSG::NodePtr root;
  
  qapp.connect( &qapp, SIGNAL  ( lastWindowClosed() ), 
                &qapp, SLOT    ( quit() ) );

  if (argc > 1)
    {
      root = OSG::SceneFileHandler::the().read(argv[1]);

      if (root == OSG::NullFC)
        {
OSG::NodePtr scene = OSG::makeTorus(.5, 1, 8, 8);
OSG::NodePtr scene2 = OSG::makeTorus(.1, 2, 10, 12);

OSG::NodePtr grn = OSG::Node::create();
OSG::GroupPtr gr = OSG::Group::create();

OSG::beginEditCP(grn, OSG::Node::CoreFieldMask | OSG::Node::ChildrenFieldMask );
grn->setCore(gr);
grn->addChild(scene);
grn->addChild(scene2);
OSG::endEditCP  (grn, OSG::Node::CoreFieldMask | OSG::Node::ChildrenFieldMask );
widget.getManager().setRoot(grn);
        }

      else
        {       

widget.getManager().setRoot(root);
        }
    }
  else
    {
      FFATAL (( "%s usage: %s 'sceneFileName'\n", argv[0], argv[0] ));
    }

  widget.getManager().showAll();
  widget.show();
  retCode = qapp.exec();
  
  OSG::osgExit();

  return retCode;
}
