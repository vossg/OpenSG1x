/*!
 * \class OSGAXPlugin
 * \brief
 * \author Andreas Zieringer
 */

// ./OpenSGax.exe -dumpidl OpenSGax.idl -version 1.0
// midl /nologo OpenSGax.idl /tlb OpenSGax.tlb

#include <sstream>

// Qt stuff
#include <qapplication.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qvbox.h>
#include <qpushbutton.h>
#include <qstringlist.h>
#include <qdragobject.h>
#include <qdir.h>
#include <qcursor.h>
#include <qobjectlist.h>
#include <objsafe.h>
#include <qdir.h>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGFresnelMaterial.h>

#include "OSGAXPlugin.h"

OSG_USING_NAMESPACE

// *************************
// Qt OpenSG render widget.
// *************************

OpenSGWidget::OpenSGWidget( QGLFormat f, QWidget *parent, const char *name )
     : QGLWidget( f, parent, name ),
    _mgr(NULL),
    _pwin(NullFC),
    _render_wireframe(false),
    _render_statistic(false),
    _fullscreen(false),
    _parent(NULL)
{
    setAcceptDrops(true);
    setAutoBufferSwap(false);
    setFocusPolicy(QWidget::StrongFocus);
    
    _mgr = new SimpleSceneManager;
    _pwin = PassiveWindow::create();
    addRefCP(_pwin);
    
    _mgr->setWindow(_pwin);
    _mgr->setClickCenter(false);
}

OpenSGWidget::~OpenSGWidget()
{
    if(_mgr != NULL)
        delete _mgr;
    
    if(_pwin != NullFC)
    {
        // remove all viewports
        beginEditCP(_pwin);
            while(_pwin->getPort().size() > 0)
            {
                ViewportPtr vp = _pwin->getPort()[0];
                _pwin->subPort(vp);
            }
        endEditCP(_pwin);
        
        subRefCP(_pwin);
    }
}

SimpleSceneManager *OpenSGWidget::getManager(void)
{
    return _mgr;
}

void OpenSGWidget::initializeGL()
{
    _pwin->init();
    
    makeCurrent();

    // some manual init, will be moved into StateChunks later
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    if(format().accum())
        glClearAccum(0.0, 0.0, 0.0, 0.0);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderAction *ract = (RenderAction *) _mgr->getAction();
    
    if(ract != NULL)
    {
        ract->setSortTrans(true);
        ract->setZWriteTrans(true);
    }

    _mgr->useOpenSGLogo();

    emit initializedGL();
}

void OpenSGWidget::resizeGL( int width, int height )
{
    _mgr->resize(width, height);
}

void OpenSGWidget::paintGL()
{
    _mgr->redraw();
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
    _mgr->mouseButtonPress(button, ev->x(), ev->y());
    updateGL();
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

    _mgr->mouseButtonRelease(button, ev->x(), ev->y());
    updateGL();
}

void OpenSGWidget::mouseMoveEvent( QMouseEvent *ev )
{
    _mgr->mouseMove(ev->x(), ev->y());
    updateGL();
}

void OpenSGWidget::wheelEvent( QWheelEvent *ev )
{
    _mgr->mouseButtonPress(ev->delta() > 0 ? SimpleSceneManager::MouseDown
                                          : SimpleSceneManager::MouseUp, 
                              ev->x(), ev->y());

    ev->accept();
    updateGL();
}

/*!
 * \brief Drag enter event.
 * \param event
 */
void OpenSGWidget::dragEnterEvent(QDragEnterEvent *e)
{
    if(!strcmp(e->format(), "text/uri-list"))
    {
        e->accept(true);
    }
    else
    {
        e->accept(false);
    }
}

/*!
 * \brief Drop event, accepts urls
 * \param event
 */
void OpenSGWidget::dropEvent(QDropEvent *e)
{
    if(!strcmp(e->format(), "text/uri-list"))
    {
        QStringList list;

        if(QUriDrag::decodeLocalFiles(e, list))
        {
            emit droppedFiles(list); 
        }
    }
}

/*!
 * \brief Drop event, accepts urls
 * \param event
 */
void OpenSGWidget::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
        case Key_F1:
            emit toggleTools();
        break;
        case Key_F5:
            _mgr->showAll();
            updateGL();
        break;
        case Key_F10:
            setHeadlightEnabled(!isHeadlightEnabled());
        break;
        case Key_F11:
            toggleWireframe();
        break;
        case Key_F12:
            toggleStatistic();
        break;
        case Key_Space:
            toggleFullScreen();
        break;
    }
}

void OpenSGWidget::toggleWireframe(void)
{
    _render_wireframe = !_render_wireframe;

    if(_render_wireframe)
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
            
    updateGL();
}

void OpenSGWidget::setHeadlightEnabled(bool s)
{
    if(s)
        _mgr->turnHeadlightOn();
    else
        _mgr->turnHeadlightOff();
    
    updateGL();

    emit changedHeadlight(s);
}

bool OpenSGWidget::isHeadlightEnabled(void)
{
    return _mgr->getHeadlightState();
}

void OpenSGWidget::toggleStatistic(void)
{
    _render_statistic = !_render_statistic;
    _mgr->setStatistics(_render_statistic);
    updateGL();
}

void OpenSGWidget::toggleFullScreen(void)
{
    _fullscreen = !_fullscreen;

    // on ATI cards this leads to render bugs, a much slower but safe way
    // is to create a new render widget with the right window flags and
    // destroy the old one.

    if(_fullscreen)
    {
        _parent = parentWidget();
        QPoint p(0, 0);
        reparent(NULL, WStyle_Customize | WStyle_NoBorder |
                 Qt::WStyle_StaysOnTop, p, true);
        setFocus();
        resize(QApplication::desktop()->size());
        updateGL();
    }
    else
    {
        QPoint p(0, 0);
        reparent(_parent, 0, p, true);
        setFocus();
        updateGL();
    }
}

// ****************************
// AXPlugin
// ****************************

OSGAXPlugin::OSGAXPlugin(QWidget *parent, const char *name) :
        QWidget(parent, name),
        _main(NULL),
        _tools(NULL),
        _gl_container(NULL),
        _gl(NULL),
        _root(NullFC),
        _show_tools(true),
        _headlight(NULL)
{
    // When we register the server with "OpenSGax.exe -regserver"
    // the OSGAXPlugin instance is created directly
    // without entering the main. This would crash because osgInit was not called.
    // Also it doesn't make much sense to create a render widget if we just want to
    // register the plugin ;-)
    
    if(OSG::GlobalSystemState != Running)
        return;

    setAcceptDrops(true);

    _main = new QVBox(this);
    //_main->setMinimumSize(640, 512);
    
    _main->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    _main->setSpacing(2);

    QVBoxLayout *vl = new QVBoxLayout(this);
    vl->addWidget(_main);
    
    _gl_container = new QVBox(_main);
    
    // create render widget.
    _gl = new OpenSGWidget(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer |
                                     QGL::Rgba | QGL::DirectRendering), _gl_container);

    connect(_gl, SIGNAL(droppedFiles(const QStringList &)), this,
            SLOT(droppedFiles(const QStringList &)));
    connect(_gl, SIGNAL(initializedGL()), this, SLOT(initializedGL()));

    // tool bar.
    _tools = new QHBox(_main);
    _tools->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setShowTools(false);
    
    connect(_gl, SIGNAL(toggleTools()), this, SLOT(toggleTools()));
    
    // add show all button
    QPushButton *show_all = new QPushButton("ShowAll", _tools);
    connect(show_all, SIGNAL(clicked()), this, SLOT(showAll()));
    
    _headlight = new QPushButton("Headlight", _tools);
    _headlight->setToggleButton(true);
    connect(_headlight, SIGNAL(toggled(bool)), this, SLOT(toggledHeadlight(bool)));
    _headlight->blockSignals(true);
    _headlight->setOn(true);
    _headlight->blockSignals(false);
    
    connect(_gl, SIGNAL(changedHeadlight(bool)), this, SLOT(changedHeadlight(bool)));
    
    // create root node.
    _root = Node::create();
    GroupPtr group = Group::create();
    beginEditCP(_root);
        _root->setCore(group);
    endEditCP(_root);

    // create a default scene
    NodePtr scene = makeTorus(.5, 3, 64, 64);
    
    // add a FresnelMaterial
    UChar8 imgdata[] = {  255,0,0,128,  0,255,0,128,  0,0,255,255,  255,255,255,255 };
    ImagePtr img = Image::create();
    beginEditCP(img);
        img->set( Image::OSG_RGBA_PF, 2, 2, 1, 1, 1, 0, imgdata );
    endEditCP(img);

    FresnelMaterialPtr fmat = FresnelMaterial::create();
    beginEditCP(fmat);
        fmat->setAmbient(Color3f(0.1, 0.1, 0.2));
        fmat->setDiffuse(Color3f(0.2, 0.2, 0.8));
        fmat->setSpecular(Color3f(0.8, 0.8, 0.8));
        fmat->setShininess(100);
        fmat->setImage(img);
    endEditCP(fmat);

    GeometryPtr geo = GeometryPtr::dcast(scene->getCore());
    if(geo != NullFC)
    {
        beginEditCP(geo);
            geo->setMaterial(fmat);
        endEditCP(geo);
    }

    beginEditCP(_root);
        _root->addChild(scene);
    endEditCP(_root);
        
    _gl->getManager()->setRoot(_root);
    _gl->getManager()->showAll();
    _gl->updateGL();
}

OSGAXPlugin::~OSGAXPlugin()
{
    if(_root != NullFC)
    {
        destroyScene();
        subRefCP(_root);
    }
}

void OSGAXPlugin::destroyScene(void)
{
    if(_root == NullFC)
        return;

    beginEditCP(_root);
    while(_root->getNChildren() > 0)
        _root->subChild(_root->getChild(0));
    endEditCP(_root);
    _gl->updateGL();
}

NodePtr OSGAXPlugin::load(const QString &filename)
{
    QString fname = QDir::convertSeparators(filename);
    QApplication::setOverrideCursor(QCursor(Qt::waitCursor));
    NodePtr scene = SceneFileHandler::the().read(fname.latin1(), NULL);
    QApplication::restoreOverrideCursor();
    
    if(scene != NullFC)
    {
        beginEditCP(_root);
            _root->addChild(scene);
        endEditCP(_root);
    }
    else
    {
        QString text;
        text.sprintf("Couldn't load '%s'!", fname.latin1());
        QMessageBox::warning(this, "OSGAXPlugin", text);
    }
    
    _gl->getManager()->showAll();
    _gl->updateGL();

    return scene;
}

void OSGAXPlugin::setShowTools(bool s)
{
    _show_tools = s;
    if(_show_tools)
        _tools->show();
    else
        _tools->hide();
}

QString OSGAXPlugin::getSrc(void) const
{
    return QString("");
}

void OSGAXPlugin::setSrc(const QString &src)
{
    //QString path = QDir::currentDirPath();
    //QMessageBox::warning(NULL, "OSGAXPlugin::setSrc", src);
    
    // Destroy old scene
    destroyScene();

    load(src);
}

QString OSGAXPlugin::getFrom(void) const
{
    Navigator *nav = _gl->getManager()->getNavigator();
    if(nav == NULL)
        return QString("");
    
    Pnt3f from = nav->getFrom();
    std::stringstream fromstr;
    fromstr << from;
    return QString(fromstr.str().c_str());
}

void OSGAXPlugin::setFrom(const QString &fromstr)
{
    Navigator *nav = _gl->getManager()->getNavigator();
    if(nav == NULL)
        return;
    
    Pnt3f from;
    from.setValueFromCString(fromstr);
    
    nav->setFrom(from);
    _gl->updateGL();
}

QString OSGAXPlugin::getAt(void) const
{
    Navigator *nav = _gl->getManager()->getNavigator();
    if(nav == NULL)
        return QString("");
    
    Pnt3f at = nav->getAt();
    std::stringstream atstr;
    atstr << at;
    return QString(atstr.str().c_str());
}

void OSGAXPlugin::setAt(const QString &atstr)
{
    Navigator *nav = _gl->getManager()->getNavigator();
    if(nav == NULL)
        return;
    
    Pnt3f at;
    at.setValueFromCString(atstr);
    
    nav->setAt(at);
    _gl->updateGL();
}

QString OSGAXPlugin::getUp(void) const
{
    Navigator *nav = _gl->getManager()->getNavigator();
    if(nav == NULL)
        return QString("");
    
    Vec3f up = nav->getUp();
    std::stringstream upstr;
    upstr << up;
    return QString(upstr.str().c_str());
}

void OSGAXPlugin::setUp(const QString &upstr)
{
    Navigator *nav = _gl->getManager()->getNavigator();
    if(nav == NULL)
        return;
    
    Vec3f up;
    up.setValueFromCString(upstr);
    
    nav->setUp(up);
    _gl->updateGL();
}

QString OSGAXPlugin::getNear(void) const
{
    CameraPtr cam = _gl->getManager()->getWindow()->getPort()[0]->getCamera();

    Real32 nearp = cam->getNear();

    std::stringstream nearstr;
    nearstr << nearp;

    return QString(nearstr.str().c_str());
}

void OSGAXPlugin::setNear(const QString &nearstr)
{
    CameraPtr cam = _gl->getManager()->getWindow()->getPort()[0]->getCamera();

    beginEditCP(cam);
        cam->setNear(nearstr.toFloat());
    endEditCP(cam);

    _gl->updateGL();
}

QString OSGAXPlugin::getFar(void) const
{
    CameraPtr cam = _gl->getManager()->getWindow()->getPort()[0]->getCamera();

    Real32 farp = cam->getFar();

    std::stringstream farstr;
    farstr << farp;

    return QString(farstr.str().c_str());
}

void OSGAXPlugin::setFar(const QString &farstr)
{
    CameraPtr cam = _gl->getManager()->getWindow()->getPort()[0]->getCamera();

    beginEditCP(cam);
        cam->setFar(farstr.toFloat());
    endEditCP(cam);

    _gl->updateGL();
}

QString OSGAXPlugin::getMotionFactor(void) const
{
    return QString("");
    /*
    Navigator *nav = _gl->getManager()->getNavigator();
    if(nav == NULL)
        return QString("");
    
    Real32 mf = nav->getMotionFactor();
    std::stringstream mfstr;
    mfstr << mf;
    return QString(mfstr.str().c_str());
    */
}

void OSGAXPlugin::setMotionFactor(const QString &mfstr)
{
    Navigator *nav = _gl->getManager()->getNavigator();
    if(nav == NULL)
        return;

    nav->setMotionFactor(mfstr.toFloat());
    _gl->updateGL();
}

void OSGAXPlugin::about(void)
{
    QMessageBox::warning(NULL, "OSGAXPlugin", "OpenSG ActiveX Render Plugin");
}

void OSGAXPlugin::initializedGL(void)
{
    // create a gradient background.
    GradientBackgroundPtr gback = GradientBackground::create();
    beginEditCP(gback, GradientBackground::LineFieldMask);
        gback->clearLines();
        gback->addLine(Color3f(0.7, 0.7, 0.8), 0);
        gback->addLine(Color3f(0.0, 0.1, 0.3), 1);
    endEditCP(gback, GradientBackground::LineFieldMask);

    WindowPtr win = _gl->getManager()->getWindow();
    beginEditCP(win);
        for(int i=0;i<win->getPort().size();++i)
        {
            ViewportPtr vp = win->getPort()[i];
            beginEditCP(vp);
                vp->setBackground(gback);
            endEditCP(vp);
        }
    endEditCP(win);
}

void OSGAXPlugin::showAll(void)
{
    _gl->getManager()->showAll();
    _gl->updateGL();
}

void OSGAXPlugin::toggledHeadlight(bool s)
{
    _gl->setHeadlightEnabled(s);
}

void OSGAXPlugin::changedHeadlight(bool s)
{
    _headlight->blockSignals(true);
    _headlight->setOn(s);
    _headlight->blockSignals(false);
}

void OSGAXPlugin::droppedFiles(const QStringList &files)
{
    // Destroy old scene
    destroyScene();

    for(QStringList::ConstIterator it = files.begin(); it != files.end(); ++it)
        NodePtr scene = load((*it));

    _gl->getManager()->showAll();
    _gl->updateGL();
}

void OSGAXPlugin::toggleTools(void)
{
    OSGAXPlugin::setShowTools(!_show_tools);
}


// --------------------------------------------------


class ObjectSafetyImpl : public QAxAggregated, 
    public IObjectSafety
{
public:
    ObjectSafetyImpl() {}

    long queryInterface( const QUuid &iid, void **iface )
    {
        *iface = 0;
        if(iid == IID_IObjectSafety)
            *iface = (IObjectSafety*)this;
        else
            return E_NOINTERFACE;
        
        AddRef();
        return S_OK;
    }

    QAXAGG_IUNKNOWN;

    HRESULT WINAPI GetInterfaceSafetyOptions( REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions )
    {
        *pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA | INTERFACESAFE_FOR_UNTRUSTED_CALLER;
        *pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA | INTERFACESAFE_FOR_UNTRUSTED_CALLER;
        return S_OK;
    }
    
    HRESULT WINAPI SetInterfaceSafetyOptions( REFIID riid, DWORD pdwSupportedOptions, DWORD pdwEnabledOptions )
    {
        return S_OK;
    }
};

QAxAggregated *OSGAXPlugin::createAggregate()
{
    return new ObjectSafetyImpl();
}
