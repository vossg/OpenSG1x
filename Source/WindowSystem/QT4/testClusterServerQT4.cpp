// Simple QT cluster server.
// usage:
// testClusterServerQT pipe0 -g320,200,0,0
// testClusterClientQT pipe0

#include <stdlib.h>
#include <string>

#include <QApplication>
#include <QGLWidget>
#include <QMouseEvent>
#include <QDesktopWidget>

#include <OSGConfig.h>
#include <OSGBaseFunctions.h>
#include <OSGNode.h>
#include <OSGLog.h>
#include <OSGClusterServer.h>
#include <OSGRenderAction.h>
#include <OSGOSGWriter.h>
#include <OSGViewport.h>
#include <OSGWindow.h>
#include <OSGPassiveWindow.h>
#include <OSGRenderAction.h>


OSG_USING_NAMESPACE

static bool _exit_app = false;


// cluster qt render widget

class ClusterServerGLWidget : public QGLWidget
{

public:

    ClusterServerGLWidget(const QGLFormat &f, QWidget *parent = 0, const QGLWidget *share = 0, Qt::WFlags flags = 0);
    virtual ~ClusterServerGLWidget(void);

    void setServer(ClusterServer *server);
    PassiveWindowPtr getWindow(void);
    RenderAction *getRenderAction(void);
    bool isInitialized(void);

protected:

    virtual void initializeGL(void);
    virtual void paintGL(void);
    virtual void resizeGL(int w, int h);
    virtual void keyPressEvent(QKeyEvent *e);

private:

    PassiveWindowPtr       _window;
    RenderAction           *_ract;
    ClusterServer          *_server;
    bool                   _initialized;
};


ClusterServerGLWidget::ClusterServerGLWidget(const QGLFormat &f, QWidget *parent, const QGLWidget *share, Qt::WFlags flags) :
    QGLWidget(f, parent, 0, share, flags),
    _window(NullFC),
    _ract(NULL),
    _server(NULL),
    _initialized(false)
{
    setAutoBufferSwap(false);

    setCursor(QCursor(Qt::BlankCursor));
    
    _ract = RenderAction::create();
    _ract->setSortTrans(true);
    _ract->setZWriteTrans(true);

    _window = PassiveWindow::create();
    setFocus();
}
    
ClusterServerGLWidget::~ClusterServerGLWidget(void)
{
    // Destroys the QTWindow and its gl context!
    subRefCP(_window);
}
    
void ClusterServerGLWidget::setServer(ClusterServer *server)
{
    _server = server;
}

PassiveWindowPtr ClusterServerGLWidget::getWindow(void)
{
    return _window;
}

RenderAction *ClusterServerGLWidget::getRenderAction(void)
{
    return _ract;
}

bool ClusterServerGLWidget::isInitialized(void)
{
    return _initialized;
}

void ClusterServerGLWidget::initializeGL(void)
{
    _window->init();
    makeCurrent();
    _window->activate(); // and activate it
    
    // some manual init, will be moved into StateChunks later
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _initialized = true;
}

void ClusterServerGLWidget::paintGL(void)
{
    if(_server == NULL)
        return;
    
    makeCurrent();
    
    //_window->frameInit();
    _server->render(_ract);
    swapBuffers();
    //_window->frameExit();
    Thread::getCurrentChangeList()->clearAll();
}

void ClusterServerGLWidget::resizeGL(int w, int h)
{
    if(!_window->isResizePending())
    {
        _window->resize(w, h);
        _window->resizeGL();
    }
}

void ClusterServerGLWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Q)
    {
        _exit_app = true;
    }
}

// --------------------------------

int main(int argc, char **argv)
{
    ClusterServer   *server = NULL;
    ClusterServerGLWidget *window = NULL;
    UInt32          servicePort=8437;
    std::string     serviceGroup="224.245.211.234";
    
    bool running = false;
    bool exitOnError = false;

    // QT init
    QApplication::setColorSpec(QApplication::ManyColor);
    QApplication    *app = new QApplication(argc, argv);

    if(!QGLFormat::hasOpenGL())
    {
        qWarning("This system has no OpenGL support. Exiting.");
        return -1;
    }

    app->connect(app, SIGNAL(lastWindowClosed()), app, SLOT(quit()));

    // init OSG
    ChangeList::setReadWriteDefault();
    osgLog().setLogLevel(LOG_WARNING);
    osgInit(argc, argv);

    char *name              = "ClusterServer";
    char *connectionType    = "StreamSock";
    bool noborder           = true;
    std::string address     = "";
    int width=-1,height=300,x=0,y=0;
    bool stereobuffer = false;

    for(int i=1;i<argc;i++)
    {
        if(strlen(argv[i])>1 && argv[i][0]=='-')
        {
            switch(argv[i][1])
            {
                case 'm':
                    connectionType="Multicast";
                    break;
                case 'w':
                    noborder = false;
                    break;
                case 'e':
                    exitOnError=true;
                    break;
                case 'a':
                    address=&(argv[i][2]);
                    break;
                case 'g':
                    if(sscanf(&(argv[i][2]),"%d,%d,%d,%d",
                              &width,&height,&x,&y)!=4)
                    {
                        SWARNING << "Wrong args in -g. Use -gw,h,x,y"
                                 << std::endl;
                        exit(0);
                    }
                    break;
                case 'p':
                    if(argv[i][2] != '\0')
                        servicePort=atoi(argv[i]+2);
                    else
                        servicePort=atoi(argv[++i]);
                    break;
                case 'j':
                    if(argv[i][2] != '\0')
                        serviceGroup=argv[i]+2;
                    else
                        serviceGroup=argv[++i];
                    break;
                case 's':
                    stereobuffer = true;
                    break;
                case 'h':
                    std::cout << "testClusterServerQT "
                              << "-m "
                              << "-w "
                              << "-e "
                              << "-gw,h,x,y "
                              << "-aAddress "
                              << "-j group "
                              << "-p servicePort "
                              << std::endl;
                    std::cout << "-m        use multicast" << std::endl;
                    std::cout << "-w        enables window border" << std::endl;
                    std::cout << "-e        exit after closed connection"
                              << std::endl;
                    std::cout << "-g        geometry" << std::endl;
                    std::cout << "-a Address Server network address"
                              << std::endl;
                    std::cout << "-s        active stereo" << std::endl;
                    return 0;
            }
        }
        else
            name=argv[i];
    }

    try
    {
        if(stereobuffer)
        {
            window = new ClusterServerGLWidget(QGLFormat(QGL::DirectRendering | QGL::DoubleBuffer |
                                            QGL::DepthBuffer | QGL::Rgba | QGL::StereoBuffers),
                                            NULL, NULL, noborder ? Qt::WStyle_Customize  | Qt::WStyle_NoBorder | Qt::WStyle_StaysOnTop : 0);
        }
        else
        {
            window = new ClusterServerGLWidget(QGLFormat(QGL::DirectRendering | QGL::DoubleBuffer |
                                            QGL::DepthBuffer | QGL::Rgba), NULL, NULL,
                                            noborder ? Qt::WStyle_Customize  | Qt::WStyle_NoBorder | Qt::WStyle_StaysOnTop : 0);
        }
    
        if(stereobuffer && !window->format().stereo())
            SWARNING << "OpenGL stereo is not available!" << std::endl;
    
        if(width == -1)// fullscreen
        {
            const QRect screen = qApp->desktop()->screenGeometry(qApp->desktop()->screenNumber(window));
    
            x = screen.topLeft().x();
            y = screen.topLeft().y();
            width = screen.size().width();
            height = screen.size().height();
        }

        server = new ClusterServer(window->getWindow(), name,
                                   connectionType, address,
                                   servicePort, serviceGroup);
    
        window->setServer(server);
    
        server->start();
        running=true;
    
        window->move(x, y);
        window->resize(width, height);
        window->raise();
        window->show();
        // needed for the XServer!
        window->move(x, y);
        window->show();
        window->raise();

        _exit_app = false;
        while(!_exit_app)
        {
            if(!running)
            {
                server->start();
                running=true;
                window->show();
                window->raise();
            }
            app->processEvents(0);
            try
            {
                window->updateGL();
            }
            catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
            {
                if(exitOnError)
                {
                    SLOG << e.what() << std::endl;
                    try
                    {
                        delete server;
                    }
                    catch(...)
                    {
                    }
                    osgExit();
                    exit(0);
                }
                else
                {
                    // try to restart server
                    try
                    {
                        server->stop();
                    }
                    catch(...)
                    {
                    }
                    running=false;
                    window->hide();
                }
            }
        }
    }

    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        SLOG << e.what() << std::endl;
        delete server;
        osgExit();
        return 0;
    }
    
    delete server;
    osgExit();
    
    return 0;
}
