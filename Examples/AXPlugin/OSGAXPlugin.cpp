/*!
 * \class OSGAXPlugin
 * \brief
 * \author Andreas Zieringer
 */

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
    _pwin(NullFC)
{
    setAcceptDrops(true);
    setAutoBufferSwap(false);
    setFocusPolicy(QWidget::StrongFocus);
    
    _mgr = new SimpleSceneManager;
    _pwin = PassiveWindow::create();
    addRefCP(_pwin);
    
    _mgr->setWindow(_pwin);
}

OpenSGWidget::~OpenSGWidget()
{
    if(_mgr != NULL)
        delete _mgr;
    
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

    _mgr->mouseButtonRelease(button, ev->x(), ev->y());
    update();
}

void OpenSGWidget::mouseMoveEvent( QMouseEvent *ev )
{
    _mgr->mouseMove(ev->x(), ev->y());
    update();
}

void OpenSGWidget::wheelEvent( QWheelEvent *ev )
{
    _mgr->mouseButtonPress(ev->delta() > 0 ? SimpleSceneManager::MouseUp
                                          : SimpleSceneManager::MouseDown, 
                              ev->x(), ev->y());

    ev->accept();
    update();
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


// ****************************
// AXPlugin
// ****************************

OSGAXPlugin::OSGAXPlugin(QWidget *parent, const char *name) :
        QWidget(parent, name),
        _main(NULL),
        _tools(NULL),
        _gl(NULL),
        _root(NullFC),
        _show_tools(false)
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
    
    // create render widget.
    _gl = new OpenSGWidget(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer |
                                     QGL::Rgba | QGL::DirectRendering), _main);

    connect(_gl, SIGNAL(droppedFiles(const QStringList &)), this,
            SLOT(droppedFiles(const QStringList &)));
    connect(_gl, SIGNAL(initializedGL()), this, SLOT(initializedGL()));

    // tool bar.
    _tools = new QHBox(_main);
    _tools->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    
    // add show all button
    QPushButton *show_all = new QPushButton("ShowAll", _tools);
    connect(show_all, SIGNAL(clicked()), this, SLOT(showAll()));
    
    QPushButton *headlight = new QPushButton("Headlight", _tools);
    headlight->setToggleButton(true);
    connect(headlight, SIGNAL(toggled(bool)), this, SLOT(toggledHeadlight(bool)));
    headlight->blockSignals(true);
    headlight->setOn(true);
    headlight->blockSignals(false);
    
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
    _gl->update();
}

OSGAXPlugin::~OSGAXPlugin()
{
    destroyScene();
    subRefCP(_root);
}

void OSGAXPlugin::destroyScene(void)
{
    beginEditCP(_root);
    while(_root->getNChildren() > 0)
        _root->subChild(_root->getChild(0));
    endEditCP(_root);
}

NodePtr OSGAXPlugin::load(const QString &filename)
{
    QString fname = QDir::convertSeparators(filename);
    QApplication::setOverrideCursor(QCursor(Qt::waitCursor));
    NodePtr scene = SceneFileHandler::the().read(fname.latin1());
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
    _gl->update();

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
    //QMessageBox::warning(NULL, "bla", path);
    load(src);
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
    _gl->update();
}

void OSGAXPlugin::toggledHeadlight(bool s)
{
    if(s)
        _gl->getManager()->turnHeadlightOn();
    else
        _gl->getManager()->turnHeadlightOff();
    _gl->update();
}

void OSGAXPlugin::droppedFiles(const QStringList &files)
{
    // Destroy old scene
    destroyScene();

    for(QStringList::ConstIterator it = files.begin(); it != files.end(); ++it)
        NodePtr scene = load((*it));

    _gl->getManager()->showAll();
    _gl->update();
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
