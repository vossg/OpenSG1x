// little example on how to use OpenSG with a standard QT OpenGL widget
// should be independent of QT version, and might also be used as an example
// on how ot integrate OpenSG into other windowing toolkits

// The only thing lost by doing it like this is the ability to separate the
// rendering and interface threads. If you need that you will have to 
// use the real OpenSG QT widget.

// It is ASAP (as simple as possible ;), and thus probably not a good example 
// for style, but I hope it's good enough to see what's going on.

// This code is based on the QT opengl/gear example.

#include <qgl.h>
#include <qapplication.h>
#include <math.h>

#if defined(Q_CC_MSVC)
#pragma warning(disable:4305) // init: truncation from const double to float
#endif

#include <OSGConfig.h>
#include <OSGSceneFileHandler.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>

OSG_USING_NAMESPACE


class OpenSGWidget : public QGLWidget
{
public:
    OpenSGWidget( QGLFormat f, QWidget *parent=0, const char *name=0 );
    
    SimpleSceneManager *getManager(void);
protected:
    void initializeGL();
    void resizeGL( int, int );
    void paintGL();
    void mousePressEvent( QMouseEvent *ev );
    void mouseMoveEvent( QMouseEvent *ev );
    void mouseReleaseEvent( QMouseEvent *ev );
    void wheelEvent( QWheelEvent *ev );

    SimpleSceneManager *mgr;
    PassiveWindowPtr    pwin;
};

OpenSGWidget::OpenSGWidget( QGLFormat f, QWidget *parent, const char *name )
     : QGLWidget( f, parent, name )
{
    setAutoBufferSwap(false);
    mgr = new SimpleSceneManager;
    pwin = PassiveWindow::create();
    mgr->setWindow(pwin);
}

SimpleSceneManager *OpenSGWidget::getManager(void)
{
    return mgr;
}


void OpenSGWidget::initializeGL()
{
    pwin->init();   
}

void OpenSGWidget::resizeGL( int width, int height )
{
    mgr->resize(width,height);
}

void OpenSGWidget::paintGL()
{
    mgr->redraw();
    swapBuffers();
}

void OpenSGWidget::mousePressEvent( QMouseEvent *ev )
{
    UInt32 button;
    
    switch ( ev->button() ) 
    {
        case LeftButton:  button = SimpleSceneManager::MouseLeft;   break;
        case MidButton:   button = SimpleSceneManager::MouseMiddle; break;
        case RightButton: button = SimpleSceneManager::MouseRight;  break;
        default:          return;
    }
    mgr->mouseButtonPress(button, ev->x(), ev->y());
    update();
}

void OpenSGWidget::mouseReleaseEvent( QMouseEvent *ev )
{
    UInt32 button;
    
    switch ( ev->button() ) 
    {
        case LeftButton:  button = SimpleSceneManager::MouseLeft;   break;
        case MidButton:   button = SimpleSceneManager::MouseMiddle; break;
        case RightButton: button = SimpleSceneManager::MouseRight;  break;
        default:          return;
    }
    mgr->mouseButtonRelease(button, ev->x(), ev->y());
    update();
}

void OpenSGWidget::mouseMoveEvent( QMouseEvent *ev )
{
    mgr->mouseMove(ev->x(), ev->y());
    update();
}

void OpenSGWidget::wheelEvent( QWheelEvent *ev )
{
    mgr->mouseButtonPress(ev->delta() > 0 ? SimpleSceneManager::MouseUp
                                          : SimpleSceneManager::MouseDown, 
                          ev->x(), ev->y());
    
    ev->accept();
    update();
}


int main( int argc, char **argv )
{
    osgInit(argc,argv);
    
    QApplication::setColorSpec( QApplication::CustomColor );
    QApplication a( argc, argv );

    if ( !QGLFormat::hasOpenGL() ) {
	qWarning( "This system has no OpenGL support. Exiting." );
	return -1;
    }
    
    OpenSGWidget w(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer | QGL::Rgba |
                             QGL::DirectRendering));

    // create the scene
    NodePtr scene;
    
    if(argc > 1)
    {
        scene = Node::create();
        GroupPtr g = Group::create();
        
        beginEditCP(scene);
        scene->setCore(g);
        
        for(UInt16 i = 1; i < argc; ++i)
            scene->addChild(SceneFileHandler::the().read(argv[i]));
        
        endEditCP(scene);
    }
    else
    {
        scene = makeTorus(.5, 3, 16, 16);
    }

    w.getManager()->setRoot(scene);
    w.getManager()->showAll();
    
    a.setMainWidget( &w );
    w.show();
    return a.exec();
}
