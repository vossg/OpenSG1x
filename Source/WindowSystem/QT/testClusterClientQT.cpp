// Simple QT cluster client
// usage:
// testClusterServerQT pipe0 -g320,200,0,0
// testClusterClientQT pipe0

#include <iostream>

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
#include <OSGClusterWindow.h>
#include <OSGMultiDisplayWindow.h>
#include <OSGSolidBackground.h>

OSG_USING_NAMESPACE

// ClusterClientGLWidget

class ClusterClientGLWidget : public QGLWidget
{
public:
    
    ClusterClientGLWidget( QGLFormat f, QWidget *parent=0, const char *name=0 );
    virtual ~ClusterClientGLWidget();

    SimpleSceneManager *getManager(void);
    PassiveWindowPtr getWindow(void);
    void setClusterWindow(const ClusterWindowPtr &cwin);

protected:
    
    void initializeGL();
    void resizeGL( int, int );
    void paintGL();
    void mousePressEvent( QMouseEvent *ev );
    void mouseMoveEvent( QMouseEvent *ev );
    void mouseReleaseEvent( QMouseEvent *ev );
    void wheelEvent( QWheelEvent *ev );

    SimpleSceneManager  *_mgr;
    PassiveWindowPtr    _pwin;
    ClusterWindowPtr    _cwin;
};

ClusterClientGLWidget::ClusterClientGLWidget( QGLFormat f, QWidget *parent, const char *name )
     : QGLWidget( f, parent, name ),
    _mgr(NULL),
    _pwin(NullFC),
    _cwin(NullFC)
{
    setAutoBufferSwap(false);
    _mgr = new SimpleSceneManager;
    _pwin = PassiveWindow::create();
    _mgr->setWindow(_pwin);
}

ClusterClientGLWidget::~ClusterClientGLWidget(void)
{
    delete _mgr;
    subRefCP(_pwin);
}

SimpleSceneManager *ClusterClientGLWidget::getManager(void)
{
    return _mgr;
}

PassiveWindowPtr ClusterClientGLWidget::getWindow(void)
{
    return _pwin;
}

void ClusterClientGLWidget::setClusterWindow(const ClusterWindowPtr &cwin)
{
    _cwin = cwin;
}

void ClusterClientGLWidget::initializeGL()
{
    _pwin->init();
}

void ClusterClientGLWidget::resizeGL( int width, int height )
{
    _mgr->resize(width,height);
}

void ClusterClientGLWidget::paintGL()
{
    // we don't need to render the client window this is already done
    // in _cwin->render() but only when the client window is set via setClientWindow()
    //_mgr->redraw();
    // update the camera.
    _mgr->getNavigator()->updateCameraTransformation();
    
    try
    {
        _cwin->render((RenderAction *) _mgr->getAction());
        Thread::getCurrentChangeList()->clearAll();
    }
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        std::cout << e.what() << std::endl;
        exit(0);
    }
    swapBuffers();
}

void ClusterClientGLWidget::mousePressEvent( QMouseEvent *ev )
{
    UInt32 button;
    
    switch ( ev->button() ) 
    {
        case LeftButton:  button = SimpleSceneManager::MouseLeft;   break;
        case MidButton:   button = SimpleSceneManager::MouseMiddle; break;
        case RightButton: button = SimpleSceneManager::MouseRight;  break;
        default:          return;
    }
    _mgr->mouseButtonPress(button, ev->x(), ev->y());
    updateGL();
}

void ClusterClientGLWidget::mouseReleaseEvent( QMouseEvent *ev )
{
    UInt32 button;
    
    switch ( ev->button() ) 
    {
        case LeftButton:  button = SimpleSceneManager::MouseLeft;   break;
        case MidButton:   button = SimpleSceneManager::MouseMiddle; break;
        case RightButton: button = SimpleSceneManager::MouseRight;  break;
        default:          return;
    }
    _mgr->mouseButtonRelease(button, ev->x(), ev->y());
    updateGL();
}

void ClusterClientGLWidget::mouseMoveEvent( QMouseEvent *ev )
{
    _mgr->mouseMove(ev->x(), ev->y());
    updateGL();
}

void ClusterClientGLWidget::wheelEvent( QWheelEvent *ev )
{
    _mgr->mouseButtonPress(ev->delta() > 0 ? SimpleSceneManager::MouseUp
                                          : SimpleSceneManager::MouseDown, 
                          ev->x(), ev->y());
    
    ev->accept();
    updateGL();
}

// -------------------

int main( int argc, char **argv )
{
    ChangeList::setReadWriteDefault();
    osgInit(argc,argv);
    
    // clear changelist from prototypes
    OSG::Thread::getCurrentChangeList()->clearAll();
    
    QApplication::setColorSpec( QApplication::ManyColor );
    QApplication a( argc, argv );

    if ( !QGLFormat::hasOpenGL() )
    {
        qWarning( "This system has no OpenGL support. Exiting." );
        return -1;
    }
    
    // parse command line
    
    std::string connectionType = "StreamSock";
    std::string serviceAddress;
    std::vector<char *> filenames;
    
    for(int i=1;i<argc;++i)
    {
        if(strlen(argv[i])>1 && argv[i][0]=='-')
        {
            switch(argv[i][1])
            {
                case 'b':
                    serviceAddress.assign(argv[i]+2);
                    break;
                case 'f':
                    filenames.push_back(argv[i]+2);
                    break;
                case 'm':
                    connectionType="Multicast";
                    break;
                case 'h':
                    std::cout << "testClusterClientQT [servername]+ [-f<filename>]* [-m]? [-b]? [-h]?" 
                              << std::endl;
                    std::cout << "-m  use multicast" << std::endl;
                    std::cout << "-b  service address" << std::endl;
                    std::cout << "-h  help" << std::endl << std::endl;
                    std::cout << "e.g. testClusterClientQT pipe0 -ftie.wrl" << std::endl << std::endl;
                    return 0;
            }
        }
    }
    
    ClusterClientGLWidget w(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer | QGL::Rgba |
                             QGL::DirectRendering));

    // create the scene
    NodePtr scene = Node::create();
    GroupPtr g = Group::create();
    beginEditCP(scene);
        scene->setCore(g);
    endEditCP(scene);
    
    if(!filenames.empty())
    {
        beginEditCP(scene);
            for(int i = 0; i < filenames.size(); ++i)
            {
                NodePtr file = SceneFileHandler::the().read(filenames[i]);
                if(file != NullFC);
                    scene->addChild(file);
            }
        endEditCP(scene);
    }
    
    if(scene->getNChildren() == 0)
    {
        scene = makeTorus(.5, 3, 16, 16);
    }

    w.getManager()->setRoot(scene);
    w.getManager()->showAll();
    
    a.setMainWidget( &w );

    ViewportPtr clientvp = w.getWindow()->getPort()[0];
    
    // create the viewports for the cluster just a simple one ...
    ViewportPtr vp1 = Viewport::create();
    beginEditCP(vp1);
        vp1->setCamera    (w.getManager()->getCamera());
        vp1->setBackground(clientvp->getBackground());
        vp1->setRoot      (clientvp->getRoot());
        vp1->setSize      (0,0, 1,1);
    endEditCP(vp1);
    
    // create multi display cluster window
    int rows = 1;
    MultiDisplayWindowPtr clusterWindow = MultiDisplayWindow::create();
    
    beginEditCP(clusterWindow);
        // set servers
        for(int i=1;i<argc;i++)
        {
            if(argv[i][0]!='-' && 
               (argv[i][0]<'0' || argv[i][0]>'9'))
            {
                clusterWindow->getServers().push_back(argv[i]);
            }
        }

        clusterWindow->setHServers(clusterWindow->getServers().size()/rows);
        clusterWindow->setVServers(rows);
        clusterWindow->setInterleave(0);
        clusterWindow->setConnectionType(connectionType);
        clusterWindow->setSize(w.width(), w.height());
        clusterWindow->addPort(vp1);
        if(!serviceAddress.empty())
            clusterWindow->setServiceAddress(serviceAddress);
        clusterWindow->setClientWindow(w.getWindow());
    endEditCP(clusterWindow);

    clusterWindow->init();

    w.setClusterWindow(clusterWindow);
    w.show();
    
    bool r = 0;
    try
    {
        r = a.exec();
    }
    
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        SLOG << e.what() << std::endl;
    }
    
    return r;
}
