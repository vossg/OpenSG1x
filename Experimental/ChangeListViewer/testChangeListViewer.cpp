
#include <qapplication.h>
#include <qmainwindow.h>
#include <OSGConfig.h>
#include <OSGQGLManagedWidget_qt.h>
#include <OSGChangeListViewer_qt.h>
#include <OSGSceneFileHandler.h>
#include <OSGThread.h>

OSG_USING_NAMESPACE

int main( int argc, char ** argv )
{
    osgInit(argc,argv);
    
    QApplication app(argc, argv);
    ChangeListViewer* clView;
    OSGQGLManagedWidget glWidget;
    NodePtr root;
    int retCode = 1; 
    
    app.connect( &app, SIGNAL( lastWindowClosed() ), 
                 &app, SLOT( quit() ) );
    
    //create the ChangeListViewer widget.
    clView = new ChangeListViewer(app.mainWidget());
    app.setMainWidget(clView);

    if (argc > 1)
    {
        root = SceneFileHandler::the().read(argv[1]);
    }
    else
    {
        SWARNING << "USAGE: " << argv[0] << " <scenefile>" << endl;
        root = Node::create();
    }
    
    if (root == NullFC)
    {
        FFATAL (( "Couldn't load %s", argv[1]));
    }
    else
    {
        glWidget.getManager().setRoot(root);
        glWidget.getManager().showAll();
        glWidget.show();

        //make ChangeListViewer visible and give it a CL to display
        clView->show();
        clView->setChangeList(Thread::getCurrent()->getChangeList());

        retCode = app.exec();
    }
  
    osgExit();
    return retCode;
}
