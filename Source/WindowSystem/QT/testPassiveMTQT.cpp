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
#include <vector>

#if defined(Q_CC_MSVC)
#pragma warning(disable:4305) // init: truncation from const double to float
#endif

#include <OSGConfig.h>
#include <OSGSceneFileHandler.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGGradientBackground.h>
#include <OSGThread.h>
#include <OSGThreadManager.h>

OSG_USING_NAMESPACE

class OpenSGWidget;

static OpenSGWidget *_render_widget = NULL;
static ThreadBase   *_main_thread = NULL;
static Barrier      *_sync_barrier = NULL;
static Thread       *_render_thread = NULL;
static bool         _do_quit = false;
static bool         _quit = false;
static GeometryPtr _geo = NullFC;

static UInt32 _size = 0;
static std::vector<std::vector<Real32> > _surf;
static std::vector<std::vector<Real32> > _force;
static std::vector<std::vector<Real32> > _veloc;
static std::vector<std::vector<Real32> > _surfo;

#define SQRTOFTWOINV 1.0f / 1.414213562f

// This is needed to make doneCurrent() public.
class OpenSGGLContext : public QGLContext
{
public:
    OpenSGGLContext::OpenSGGLContext(const QGLFormat &format, QPaintDevice *device) :
            QGLContext(format, device)
    {
    }

    virtual OpenSGGLContext::~OpenSGGLContext()
    {
    }

    virtual void OpenSGGLContext::doneCurrent(void)
    {
        QGLContext::doneCurrent();
    }
};

class OpenSGWidget : public QGLWidget
{
public:
    OpenSGWidget( QGLFormat f, QWidget *parent=0, const char *name=0 );
    
    SimpleSceneManager *getManager(void);
    bool isInitialized(void);
    virtual void makeCurrent(void);
    virtual void doneCurrent(void);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL(void);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);
    void closeEvent(QCloseEvent *e);

    SimpleSceneManager *mgr;
    PassiveWindowPtr    pwin;
    bool                _initialized;
};

OpenSGWidget::OpenSGWidget( QGLFormat f, QWidget *parent, const char *name )
     : QGLWidget( f, parent, name )
{
    setAutoBufferSwap(false);
    setContext(new OpenSGGLContext(f, this));

    mgr = new SimpleSceneManager;
    pwin = PassiveWindow::create();
    mgr->setWindow(pwin);
}

SimpleSceneManager *OpenSGWidget::getManager(void)
{
    return mgr;
}

bool OpenSGWidget::isInitialized(void)
{
    return _initialized;
}

void OpenSGWidget::makeCurrent(void)
{
    if(Thread::getCurrent() == _main_thread)
    {
        //printf("OpenSGWidget::makeCurrent from main thread!\n");
        // when the render thread is not running yet and while initializing
        // the gl widget we have to call makeCurrent() for the main thread!
        if(_render_thread != NULL)
            return;
    }
    QGLWidget::makeCurrent();
}

void OpenSGWidget::doneCurrent(void)
{
    ((OpenSGGLContext *) context())->doneCurrent();
}

void OpenSGWidget::initializeGL()
{
    pwin->init();

    // create a gradient background.
    GradientBackgroundPtr gback = GradientBackground::create();
    beginEditCP(gback, GradientBackground::LineFieldMask);
        gback->clearLines();
        gback->addLine(Color3f(0.7, 0.7, 0.8), 0);
        gback->addLine(Color3f(0.0, 0.1, 0.3), 1);
    endEditCP(gback, GradientBackground::LineFieldMask);

    beginEditCP(pwin);
        for(int i=0;i<pwin->getPort().size();++i)
        {
            ViewportPtr vp = pwin->getPort()[i];
            beginEditCP(vp);
                vp->setBackground(gback);
            endEditCP(vp);
        }
    endEditCP(pwin);

    _initialized = true;
}

void OpenSGWidget::resizeGL(int width, int height)
{
    mgr->resize(width, height);
}

void OpenSGWidget::paintGL()
{
    if(Thread::getCurrent() == _main_thread)
    {
        //printf("OpenSGWidget::paintGL from main thread!\n");
        return;
    }
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

void OpenSGWidget::mouseMoveEvent(QMouseEvent *ev)
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

void OpenSGWidget::closeEvent(QCloseEvent *e)
{
    QGLWidget::closeEvent(e);
    _do_quit = true;
}

// ---------------------------

static void renderThread(void *)
{
    while(!_quit)
    {
        // sync
        _sync_barrier->enter(2);
        // merge the changes into our aspect
        _main_thread->getChangeList()->apply();
        _sync_barrier->enter(2);

        _render_widget->updateGL();
        Thread::getCurrentChangeList()->clearAll();
    }
}

static void initWave(void)
{
    _size = (int) sqrt((float) _geo->getPositions()->getSize());

    _surf.resize(_size);
    for(UInt32 i=0;i<_size;++i)
        _surf[i].resize(_size);
    
    _force.resize(_size);
    for(UInt32 i=0;i<_size;++i)
        _force[i].resize(_size);
    
    _veloc.resize(_size);
    for(UInt32 i=0;i<_size;++i)
        _veloc[i].resize(_size);
    
    _surfo.resize(_size);
    for(UInt32 i=0;i<_size;++i)
        _surfo[i].resize(_size);

    GeoPositions3fPtr pos = GeoPositions3fPtr::dcast(_geo->getPositions());
    MFPnt3f *p = pos->getFieldPtr();

    beginEditCP(pos);
    {
        int c = 0;

        for(int i=0;i<_size;i++)
        {
            for(int j=0;j<_size;j++)
                _surfo[i][j] = (*p)[c++][2];
        }
    }
    endEditCP(pos);
}

static void startWave(int x, int y, Real32 hw)
{
    if(x == -1 || y == -1)
    {
        x = _size/2;
        y = _size/2;
    }

    _surf[x][y] = hw;
    _surf[x][y+1] = hw;
    _surf[x+1][y] = hw;
    _surf[x+1][y+1] = hw;
}

static void resetWave(void)
{
    for(int i=0; i<_size; i++)
    for(int j=0; j<_size; j++)
    {
        _surf[i][j] = 0.0f;
        _force[i][j] = 0.0f;
        _veloc[i][j] = 0.0f;
    }
}

static void calcWave(void)
{
    int i,j;
    float d;

    for(i=0; i<_size; ++i)
    {
        for(j=0; j<_size; ++j)
        {
            _force[i][j] = 0.0f;
        }
    }

    for(i=1; i<_size-1; ++i)
    {
        for(j=1; j<_size-1; ++j)
        {
            d=_surf[i][j]-_surf[i][j-1];
            _force[i][j] -= d;
            _force[i][j-1] += d;
    
            d=_surf[i-1][j]-_surf[i-1][j];
            _force[i][j] -= d;
            _force[i-1][j] += d;
    
            d=_surf[i][j]-_surf[i][j+1];
            _force[i][j] -= d;
            _force[i][j+1] += d;
    
            d=_surf[i][j]-_surf[i+1][j];
            _force[i][j] -= d;
            _force[i+1][j] += d;
    
            d=(_surf[i][j]-_surf[i+1][j+1])*SQRTOFTWOINV;
            _force[i][j] -= d;
            _force[i+1][j+1] += d;
    
            d=(_surf[i][j]-_surf[i-1][j-1])*SQRTOFTWOINV;
            _force[i][j] -= d;
            _force[i-1][j-1] += d;
    
            d=(_surf[i][j]-_surf[i+1][j-1])*SQRTOFTWOINV;
            _force[i][j] -= d;
            _force[i+1][j-1] += d;
    
            d=(_surf[i][j]-_surf[i+1][j-1])*SQRTOFTWOINV;
            _force[i][j] -= d;
            _force[i+1][j-1] += d;
        }
    }

    float dt = 0.002f;
    for(i=0; i<_size; ++i)
    {
        for(j=0; j<_size; j++)
            _veloc[i][j] += _force[i][j] * dt;
    }

    for(i=0; i<_size; ++i)
    {
        for(j=0; j<_size; ++j)
        {
            _surf[i][j] += _veloc[i][j];

            //if(_surf[i][j] > 0)
            _surf[i][j] -= _surf[i][j]/_size;
        }
    }
}

static void updateGeometry(GeometryPtr geo)
{
    GeoPositions3fPtr pos = GeoPositions3fPtr::dcast(geo->getPositions());
    // p->setValue() is faster than pos->setValue()
    MFPnt3f *p = pos->getFieldPtr();
    beginEditCP(pos);
    int c = 0;
        for(int i=0;i<_size;++i)
        {
            for(int j=0;j<_size;++j)
            {
                Pnt3f &pp = (*p)[c++];
                pp[2] = _surfo[i][j] + _surf[i][j];
            }
        }
    endEditCP(pos);
}

static void calcVertexNormals(GeometryPtr geo)
{
    GeoNormals3fPtr norms = GeoNormals3fPtr::dcast(geo->getNormals());
    GeoPositions3fPtr pos = GeoPositions3fPtr::dcast(geo->getPositions());

    MFPnt3f *p = pos->getFieldPtr();
    MFVec3f *n = norms->getFieldPtr();

    beginEditCP(norms);

    Vec3f a, b, c;
    int l = 0;
        for(int i=0; i<_size; ++i)
        {
            for(int j=0; j<_size; ++j)
            {
                int m = i*_size+j;

                if (i!=_size-1 && j!=_size-1)
                {
                    a = (*p)[l+m+1] - (*p)[l+m];
                    b = (*p)[l+m+_size] - (*p)[l+m];
                }
                else
                {
                    a = (*p)[l+m-1] - (*p)[l+m];
                    
                    int index = l+m-_size;
                    if(index < 0)
                        index += norms->getSize();
                    
                    b = (*p)[index] - (*p)[l+m];
                }

                c = a.cross(b);
                c.normalize();
        
                if (i==0 && j==_size-1)
                {
                    a = (*p)[l+m-1] - (*p)[l+m];
                    b = (*p)[l+m+_size] - (*p)[l+m];
        
                    c = a.cross(b);
                    c.normalize();
                    c.negate();
                }

                if (i==_size-1 && j==0)
                {
                    a = (*p)[l+m-_size] - (*p)[l+m];
                    b = (*p)[l+m+1] - (*p)[l+m];
        
                    c = a.cross(b);
                    c.normalize();
                }
                (*n)[l+m] = c;
            }
        }
        l += _size*_size;
    endEditCP(norms);
}

static void mainThread(void)
{
    // do some animation in the main thread.
    static Real64 t = 0.0;

    if(OSG::getSystemTime() - t > 2.0)
    {
        // create a wave in the center of the plane.
        startWave(-1, -1, 0.1);
        t = OSG::getSystemTime();
    }

    calcWave();
    updateGeometry(_geo);
    calcVertexNormals(_geo);
}

int main( int argc, char **argv )
{
    ChangeList::setReadWriteDefault();
    osgInit(argc,argv);

    _main_thread = Thread::getCurrent();
    _sync_barrier = Barrier::get("RenderBarrier");

    QApplication::setColorSpec( QApplication::CustomColor );
    QApplication a( argc, argv );

    if(!QGLFormat::hasOpenGL())
    {
        qWarning( "This system has no OpenGL support. Exiting." );
        return -1;
    }
    
    _render_widget = new OpenSGWidget(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer | QGL::Rgba |
                                      QGL::DirectRendering));

    NodePtr scene = makePlane(1.0, 1.0, 50, 50);

    MaterialChunkPtr matc = MaterialChunk::create();
    beginEditCP(matc);
        matc->setAmbient(Color4f(0.3, 0.3, 0.3, 1.0));
        matc->setDiffuse(Color4f(0.2, 0.2, 0.8, 1.0));
        matc->setSpecular(Color4f(0.6, 0.6, 0.6, 1.0));
        matc->setShininess(100);
    endEditCP(matc);
    
    ChunkMaterialPtr cmat = ChunkMaterial::create();
    beginEditCP(cmat);
        cmat->addChunk(matc);
    endEditCP(cmat);
    
    _geo = GeometryPtr::dcast(scene->getCore());
    beginEditCP(_geo);
        _geo->setDlistCache(false);
        _geo->setMaterial(cmat);
    endEditCP(_geo);

    initWave();
    resetWave();


    _render_widget->getManager()->setRoot(scene);
    _render_widget->getManager()->showAll();
    _render_widget->getManager()->getNavigator()->setFrom(Pnt3f(1.0f, -1.0f, 1.0f));
    _render_widget->getManager()->getNavigator()->setUp(Vec3f(0.0f, 0.0f, 1.0f));
    
    a.setMainWidget(_render_widget);
    _render_widget->show();
    while(!_render_widget->isInitialized())
        qApp->processEvents();

    // The gl widget is initialized in the main thread!
    // Without the doneCurrent() the next makeCurrent() call in the render thread
    // doesn't work because qt thinks that the context is already current but this
    // was in the main thread ...
    _render_widget->doneCurrent();

    // start render thread
    _render_thread = dynamic_cast<Thread *>(ThreadManager::the()->getThread("RenderThread"));
    _render_thread->runFunction(renderThread, 1, NULL);
    
    // main loop
    while(!_quit)
    {
        mainThread();

        // sync
        _sync_barrier->enter(2);
        if(_do_quit)
            _quit = true;
        _sync_barrier->enter(2);
        
        _main_thread->getChangeList()->clearAll();

        qApp->processEvents();
    }

    Thread::join(_render_thread);
    return 0;
}

