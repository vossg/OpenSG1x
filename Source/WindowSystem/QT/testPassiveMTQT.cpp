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
#include <OSGGradientBackground.h>
#include <OSGThread.h>
#include <OSGThreadManager.h>
#include <OSGSHLChunk.h>

OSG_USING_NAMESPACE

class OpenSGWidget;

static OpenSGWidget *_render_widget = NULL;
static ThreadBase   *_main_thread = NULL;
static Barrier      *_sync_barrier = NULL;
static Thread       *_render_thread = NULL;
static bool         _quit = false;
static SHLChunkPtr  _shl = NullFC;

// vertex shader program for 
static std::string _vp_program =
"varying vec3 DiffuseColor;\n"
"varying vec3 SpecularColor;\n"
"\n"
"void main(void)\n"
"{\n"
"	vec3 LightColor = vec3(1.0);\n"
"	vec3 Specular	= vec3(1.0);\n"
"	vec3 Ambient	= vec3(0.2);\n"
"	float Kd		= 0.3;\n"
"\n"
"	vec3 LightPosition = gl_LightSource[0].position.xyz;\n"
"\n"
"	vec3 ecPosition	= vec3(gl_ModelViewMatrix * gl_Vertex);\n"
"\n"
"	vec3 tnorm		= normalize(gl_NormalMatrix * gl_Normal);\n"
"\n"
"	vec3 lightVec	= normalize(LightPosition - ecPosition);\n"
"\n"
"	vec3 hvec		= normalize(lightVec - ecPosition);\n"
"\n"
"	float spec		= clamp(dot(hvec, tnorm), 0.0, 1.0);\n"
"	spec			= pow(spec, 16.0);\n"
"\n"
"	DiffuseColor	= LightColor * vec3(Kd * dot(lightVec, tnorm));\n"
"	DiffuseColor	= clamp(Ambient + DiffuseColor, 0.0, 1.0);\n"
"	SpecularColor	= clamp((LightColor * Specular * spec), 0.0 ,1.0);\n"
"\n"
"	gl_TexCoord[0]	= gl_MultiTexCoord0;\n"
"	gl_Position		= ftransform();\n"
"}\n";


// fragment shader program for
static std::string _fp_program =
"varying vec3 DiffuseColor;\n"
"varying vec3 SpecularColor;\n"
"\n"
"uniform vec2 Scale;\n"
"uniform vec2 Threshold;\n"
"uniform vec3 SurfaceColor;\n"
"\n"
"void main (void)\n"
"{\n"
"	float ss = fract(gl_TexCoord[0].s * Scale.s);\n"
"	float tt = fract(gl_TexCoord[0].t * Scale.t);\n"
"\n"
"	if ((ss > Threshold.s) && (tt > Threshold.t))\n"
"		discard;\n"
"\n"
"	vec3 finalColor = SurfaceColor * DiffuseColor + SpecularColor;\n"
"	gl_FragColor = vec4(finalColor, 1.0);\n"
"}\n";

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
    // just to make it public ...
    QGLWidget::doneCurrent();
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
    _quit = true;
}

// ---------------------------

void renderThread(void *)
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

void mainThread(void)
{
    // do some animation in the main thread.
    static float scale = 10.0f;

    beginEditCP(_shl, SHLChunk::ParametersFieldMask);
        _shl->setUniformParameter("Scale", Vec2f(scale, scale / 8.0f));
    endEditCP(_shl, SHLChunk::ParametersFieldMask);
    
    scale += 0.01f;
    if(scale > 100.0f)
        scale = 10.0f;
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

    NodePtr scene = makeTorus(.5, 3, 128, 128);
    
    // share the chunk
    _shl = SHLChunk::create();
    beginEditCP(_shl);
        _shl->setVertexProgram(_vp_program);
        _shl->setFragmentProgram(_fp_program);
        _shl->setUniformParameter("Scale", Vec2f(20.0f, 20.0f));
        _shl->setUniformParameter("Threshold", Vec2f(0.7f, 0.7f));
        _shl->setUniformParameter("SurfaceColor", Vec3f(1.0f, 1.0f, 1.0f));
    endEditCP(_shl);
    
    ChunkMaterialPtr cmat = ChunkMaterial::create();
    beginEditCP(cmat);
        cmat->addChunk(_shl);
    endEditCP(cmat);
    
    GeometryPtr geo = GeometryPtr::dcast(scene->getCore());
    beginEditCP(geo);
        geo->setMaterial(cmat);
    endEditCP(geo);

    _render_widget->getManager()->setRoot(scene);
    _render_widget->getManager()->showAll();
    
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
        _sync_barrier->enter(2);
        
        _main_thread->getChangeList()->clearAll();

        qApp->processEvents();
    }

    // sync
    _sync_barrier->enter(2);
    _sync_barrier->enter(2);
    Thread::join(_render_thread);

    return 0;
}
