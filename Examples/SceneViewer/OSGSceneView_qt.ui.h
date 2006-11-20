/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/

extern OSGMainView *_main_view;
static OSGSceneView *_sceneView = NULL;

// ---------------------------------------------------
// OpenSG opengl render widget using a passive window.
// ---------------------------------------------------
class OpenSGWidget : public QGLWidget
{
public:

    OpenSGWidget( QGLFormat f, QWidget *parent=0, const char *name=0 ) :
        QGLWidget( f, parent, name ),
        _mgr(NULL),
        _pwin(OSG::NullFC),
        _render_wireframe(false),
        _render_statistic(false),
        _fullscreen(false),
        _parent(NULL),
        _initialized_gl(false)
    {
        setAcceptDrops(true);
        setAutoBufferSwap(false);
        setFocusPolicy(QWidget::StrongFocus);
        
        _mgr = new OSG::SimpleSceneManager;
        _pwin = OSG::PassiveWindow::create();
        addRefCP(_pwin);
        
        _mgr->setWindow(_pwin);
        _mgr->setClickCenter(false);
    }

    virtual ~OpenSGWidget()
    {
        if(_mgr != NULL)
        delete _mgr;
    
        if(_pwin != OSG::NullFC)
        {
            // remove all viewports
            OSG::beginEditCP(_pwin);
                while(_pwin->getPort().size() > 0)
                {
                    OSG::ViewportPtr vp = _pwin->getPort()[0];
                    _pwin->subPort(vp);
                }
            OSG::endEditCP(_pwin);
            OSG::subRefCP(_pwin);
        }
    }

    OSG::SimpleSceneManager *getManager(void)
    {
        return _mgr;
    }

    void toggleWireframe(void)
    {
        _render_wireframe = !_render_wireframe;

        if(_render_wireframe)
                glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
                
        updateGL();
    }

    void setHeadlightEnabled(bool s)
    {
        if(s)
            _mgr->turnHeadlightOn();
        else
            _mgr->turnHeadlightOff();
        
        updateGL();
    
        //emit changedHeadlight(s);
    }

    bool isHeadlightEnabled(void)
    {
        return _mgr->getHeadlightState();
    }

    void toggleStatistic(void)
    {
        _render_statistic = !_render_statistic;
        _mgr->setStatistics(_render_statistic);
        updateGL();
    }

    void toggleFullScreen(void)
    {
        _fullscreen = !_fullscreen;

        if(_fullscreen)
        {
            _parent = parentWidget();
            QPoint p(0, 0);
            ((QWidget *)this)->reparent(NULL, p, true);
            showFullScreen();
            setFocus();
            updateGL();
        }
        else
        {
            QPoint p(0, 0);
            ((QWidget *)this)->reparent(_parent, p, true);
            showNormal();
            resize(_parent->width(), _parent->height());
            setFocus();
            updateGL();
        }
    }

protected:

    virtual void initializeGL()
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

        OSG::RenderAction *ract = (OSG::RenderAction *) _mgr->getAction();

        if(ract != NULL)
        {
            ract->setSortTrans(true);
            //ract->setZWriteTrans(true);
            ract->setLocalLights(true);
            ract->setCorrectTwoSidedLighting(true);
            ract->setOcclusionCullingThreshold(0);
        }
    
        if(!_initialized_gl)
        {
            // this should be done only once, switching to fullscreen mode will
            // call initializeGL()!
            _mgr->useOpenSGLogo();
            //emit initializedGL();

            // create a show viewport with a gradient color background.
            OSG::ShadowViewportPtr svp = OSG::ShadowViewport::create();
            OSG::GradientBackgroundPtr   gbg = OSG::GradientBackground::create();
        
            OSG::beginEditCP(gbg);
                gbg->addLine(OSG::Color3f(0.7, 0.7, 0.8), 0);
                gbg->addLine(OSG::Color3f(0.0, 0.1, 0.3), 1);
            OSG::endEditCP(gbg);
        
            // Shadow viewport
            OSG::beginEditCP(svp);
                svp->setCamera(_mgr->getCamera());
                svp->setBackground(gbg);
                svp->setSize(0, 0, 1, 1);
                //svp->setOffFactor(4.0);
                //svp->setOffBias(8.0);
                //used to set global shadow intensity, ignores shadow intensity from light sources if != 0.0
                //svp->setGlobalShadowIntensity(0.8);
                svp->setMapSize(1024);
                svp->setShadowMode(OSG::ShadowViewport::NO_SHADOW);
                //ShadowSmoothness used for PCF_SHADOW_MAP and VARIANCE_SHADOW_MAP, defines Filter Width. Range can be 0.0 ... 1.0.
                //ShadowSmoothness also used to define the light size for PCSS_SHADOW_MAP
                svp->setShadowSmoothness(0.5);
                svp->setAutoSearchForLights(true);
                //svp->setMapAutoUpdate(true);
            OSG::endEditCP(svp);
        
            // that's a bit tricky replace the viewport in the simple scene manager with our own.
            OSG::NodePtr internal_root = OSG::NullFC;
            OSG::ImageForegroundPtr foreground = OSG::NullFC;
            OSG::WindowPtr win = _mgr->getWindow();
            OSG::beginEditCP(win);
                for(int i=0;i<win->getPort().size();++i)
                {
                    OSG::ViewportPtr vp = win->getPort()[i];
                    if(internal_root == OSG::NullFC)
                    {
                        internal_root = vp->getRoot();
                        if(vp->getForegrounds().size() > 0)
                            foreground = OSG::ImageForegroundPtr::dcast(vp->getForegrounds()[0]);
                    }
                    subRefCP(vp);
                }
                win->getPort().clear();
                win->addPort(svp);
            OSG::endEditCP(win);
        
            OSG::beginEditCP(svp, OSG::Viewport::RootFieldMask |
                             OSG::Viewport::ForegroundsFieldMask);
                if(internal_root != OSG::NullFC)
                    svp->setRoot(internal_root);
                if(foreground != OSG::NullFC)
                    svp->getForegrounds().push_back(foreground);
            OSG::endEditCP(svp, OSG::Viewport::RootFieldMask |
                           OSG::Viewport::ForegroundsFieldMask);

            _mgr->getNavigator()->setViewport(svp);
        }

        _initialized_gl = true;
    }

    virtual void resizeGL(int width, int height)
    {
        _mgr->resize(width, height);
    }

    virtual void paintGL()
    {
        _mgr->redraw();
        swapBuffers();
    }

    virtual void mousePressEvent( QMouseEvent *ev )
    {
        OSG::UInt32 button;

        switch(ev->button())
        {
            case LeftButton:
                button = OSG::SimpleSceneManager::MouseLeft;
            break;
            case MidButton:
                button = OSG::SimpleSceneManager::MouseMiddle;
            break;
            case RightButton:
                button = OSG::SimpleSceneManager::MouseRight;
            break;
            default:
                return;
        }
        _mgr->mouseButtonPress(button, ev->x(), ev->y());

        // object picking via shift and left mouse button.
        if(ev->button() == LeftButton &&
           ev->state() & ShiftButton)
        {
            OSG::Line l = _mgr->calcViewRay(ev->x(), ev->y());

            OSG::IntersectAction *act = OSG::IntersectAction::create();
            act->setLine(l);
            act->apply(_mgr->getRoot());

            if (act->didHit() && _sceneView != NULL)
            {
                _sceneView->setActiveNode(act->getHitObject());
                _sceneView->selectItem(act->getHitObject());
            }
            delete act;
        }

        updateGL();
    }

    virtual void mouseMoveEvent( QMouseEvent *ev )
    {
        _mgr->mouseMove(ev->x(), ev->y());
        updateGL();
    }

    virtual void mouseReleaseEvent( QMouseEvent *ev )
    {
        OSG::UInt32 button;

        switch ( ev->button() ) 
        {
            case LeftButton:
                button = OSG::SimpleSceneManager::MouseLeft;
            break;
            case MidButton:
                button = OSG::SimpleSceneManager::MouseMiddle;
            break;
            case RightButton:
                button = OSG::SimpleSceneManager::MouseRight;
            break;
            default:
                return;
        }

        _mgr->mouseButtonRelease(button, ev->x(), ev->y());

        OSG::RenderAction *ract = (OSG::RenderAction *) _mgr->getAction();
        if(ract != NULL && ract->getOcclusionCulling())
        {
            updateGL();
            updateGL();
        }
        updateGL();
    }

    virtual void wheelEvent( QWheelEvent *ev )
    {
        _mgr->mouseButtonPress(ev->delta() > 0 ? OSG::SimpleSceneManager::MouseDown
                                          : OSG::SimpleSceneManager::MouseUp, 
                              ev->x(), ev->y());

        ev->accept();
        updateGL();
    }

    virtual void dragEnterEvent(QDragEnterEvent *e)
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

    virtual void dropEvent(QDropEvent *e)
    {
        if(!strcmp(e->format(), "text/uri-list"))
        {
            QStringList list;
            if(QUriDrag::decodeLocalFiles(e, list))
            {
                for(QStringList::Iterator it = list.begin();it != list.end();++it)
                    _sceneView->addFile(OSG::NullFC, *it);
            }
            _sceneView->showAll();
        }
    }

    virtual void keyPressEvent(QKeyEvent *e)
    {
        switch(e->key())
        {
            case Key_F5:
                _mgr->showAll();
                updateGL();
            break;
            case Key_F10:
                _main_view->headlight->setOn(!_main_view->headlight->isOn());
            break;
            case Key_F11:
                toggleWireframe();
            break;
            case Key_F12:
                _main_view->statistic->setOn(!_main_view->statistic->isOn());
            break;
            case Key_Space:
                toggleFullScreen();
            break;
        }
    }


    OSG::SimpleSceneManager  *_mgr;
    OSG::PassiveWindowPtr    _pwin;

    bool _render_wireframe;
    bool _render_statistic;
    bool _fullscreen;
    QWidget *_parent;
    bool _initialized_gl;
};

//////////////////////////////////////////////////////////////////
// TreeViewItem:  listView item which holds a link to a node    //
//////////////////////////////////////////////////////////////////
class TreeViewItem : public QListViewItem
{
public:

    OSG::NodePtr _node;

    TreeViewItem (QListView *parent, OSG::NodePtr node)
        : QListViewItem(parent), _node(node) {}

    TreeViewItem (QListViewItem *parent, OSG::NodePtr node)
        : QListViewItem(parent), _node(node) {}

    ~TreeViewItem (void) {}
};

//////////////////////////////////////////////////////////////////
// MenuID: enum for popup menu entry id                         //
//////////////////////////////////////////////////////////////////
enum MenuID { DELETE_MID, INSERT_MID, EXPORT_MID };

//////////////////////////////////////////////////////////////////
// addListItem: used to create the tree view recursiv           //
//////////////////////////////////////////////////////////////////
void OSGSceneView::addListItem( OSG::NodePtr node, QListViewItem *parentItem )
{
    if(node == OSG::NullFC)
        return;

    QListViewItem *listItem;

    if (parentItem)
        listItem = new TreeViewItem (parentItem, node);
    else
        rootTreeItem = listItem = new TreeViewItem (treeListView, node);

    const char *nodeName = OSG::getName(node);
    OSG::NodeCorePtr core = node->getCore();

    // get item name
    QString iname;
    if(nodeName != NULL)
    {
        iname = nodeName;
    }
    else
    {
        if(core != OSG::NullFC)
            iname = core->getType().getCName();
        else
            iname = node->getType().getCName();
    }

    // add shared value to name.
    OSG::UInt32 cparents = core->getParents().size();
    if(cparents > 1)
    {
        iname += " (";
        iname += QString::number(cparents);
        iname += ")";
    }

    listItem->setText(0, iname);

    OSG::Int32 n = node->getNChildren();
    for(OSG::Int32 i = 0; i < n; i++)
        addListItem (node->getChild(i), listItem);
}

//////////////////////////////////////////////////////////////////
// init: called by the widget constructor                       //
//////////////////////////////////////////////////////////////////
void OSGSceneView::init()
{
    _sceneView = this;

    // init the class variables
    rootTreeItem = 0;
    activeTreeItem = 0;
    activeNode = OSG::NullFC;
    _gl = NULL;
    _fceditor = NULL;

    int i, n;
    QPopupMenu *menu;
    std::list<const char *> suffixList;
    std::list<const char *>::iterator sI;

    // create tree popup menu
    menu = new QPopupMenu (this, "treeMenu");

    menu->insertItem("Insert", this, SLOT(menuHandler(int)),0,INSERT_MID);
    menu->insertItem("Export", this, SLOT(menuHandler(int)),0,EXPORT_MID);
    menu->insertSeparator();
    menu->insertItem("Delete", this, SLOT(menuHandler(int)),0,DELETE_MID);
    treePopupMenu = menu;

    // create filter for import/export dialog
    OSG::SceneFileHandler::the().getSuffixList(suffixList, 1 /*SceneFileType::OSG_READ_SUPPORTED*/);
    filter = "Scene File";
    filter += " (";
    for (sI = suffixList.begin(); sI != suffixList.end(); sI++) 
    {
        filter += " *.";
        filter += *sI;
    }
    filter += ")"; 

    _fceditor_splitter->setResizeMode(_render_frame, QSplitter::Stretch);
    _fceditor_splitter->setResizeMode(_fc_frame, QSplitter::FollowSizeHint);

    _fceditor = new OSG::QFieldContainerEditor(_fceditor_frame, "FCEditor");
    _fceditor->setReadOnly(false);
    _fceditor->show();

    QHBoxLayout *l = new QHBoxLayout(_fceditor_frame);
    l->addWidget(_fceditor);

    connect(_fceditor, SIGNAL(valueChanged(UInt32, UInt32)), this, SLOT(editedFC()));
}

//////////////////////////////////////////////////////////////////
// destory: called by the widget destructor                     //
//////////////////////////////////////////////////////////////////
void OSGSceneView::destroyView()
{
}

//////////////////////////////////////////////////////////////////
// init: method to set the root node                            //
//////////////////////////////////////////////////////////////////
void OSGSceneView::setRootNode( OSG::NodePtr root )
{
    rootNode = root;
    rebuild();
}

//////////////////////////////////////////////////////////////////
// setActiveNode: sets the active node and rebuilds the views   //
//////////////////////////////////////////////////////////////////
void OSGSceneView::setActiveNode(OSG::NodePtr node)
{
    activeNode = node;

    if(_gl != NULL)
        _gl->getManager()->setHighlight(node);

    // fcdEditor
    if(node != OSG::NullFC) 
    {
        OSG::NodeCorePtr core = node->getCore();
        if (core != OSG::NullFC)
            _fceditor->setFieldContainer(core);
        else
            _fceditor->setFieldContainer(OSG::NullFC);
    }
    else
    {
        _fceditor->setFieldContainer(OSG::NullFC);
    }

    updateGL();
}

//////////////////////////////////////////////////////////////////
// setActiveNodeFromListItem: set the act. node from tree item  //
//////////////////////////////////////////////////////////////////
void OSGSceneView::setActiveNodeFromListItem(QListViewItem *item)
{
    TreeViewItem *treeItem = dynamic_cast<TreeViewItem*>(item);

    if (treeItem)
    {
        setActiveNode(treeItem->_node);
        activeTreeItem = item;
    }
    else
    {
        setActiveNode(OSG::NullFC);
        activeTreeItem = NULL;
    }
}

void OSGSceneView::selectItem(OSG::NodePtr node)
{
    if(node == OSG::NullFC)
        return;

    QListViewItemIterator it(treeListView);
    
    // iterate through all items of the listview
    for(; it.current(); ++it)
    {
        TreeViewItem *treeItem = (TreeViewItem *) it.current();
        if(treeItem->_node == node)
        {
            treeListView->setSelected(treeItem, true);
            treeListView->ensureItemVisible(treeItem);
            return;
        }
    }
}

//////////////////////////////////////////////////////////////////
// createView: create a new OpenSG 3D view                      //
//////////////////////////////////////////////////////////////////
void OSGSceneView::createView(OSG::NodePtr node)
{
    if(node == OSG::NullFC)
        return;

    _gl = new OpenSGWidget(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer |
                                     QGL::Rgba | QGL::DirectRendering),
                                     _render_frame, "OSG View");

    _gl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    _gl->getManager()->setRoot( node );
    _gl->getManager()->setStatistics(false);
    _gl->getManager()->showAll();
    _gl->getManager()->useOpenSGLogo();
    _gl->getManager()->setHighlight(activeNode);
    _gl->show();
}

//////////////////////////////////////////////////////////////////
// setStatistics: change statistics settings                    //
//////////////////////////////////////////////////////////////////
void OSGSceneView::setStatistics(bool val)
{
    if(_gl != NULL)
    {
        _gl->getManager()->setStatistics(val);
        if(val)
        {
            // customize the statistic.
            OSG::WindowPtr win = _gl->getManager()->getWindow();
            for(int i=0;i<win->getPort().size();++i)
            {
                OSG::ViewportPtr vp = win->getPort()[i];
                for(int j=0;j<vp->getForegrounds().size();++j)
                {
                    OSG::SimpleStatisticsForegroundPtr sf =
                        OSG::SimpleStatisticsForegroundPtr::dcast(vp->getForegrounds()[j]);
                    if(sf != OSG::NullFC)
                    {
                        sf->setColor(OSG::Color4f(1.0f,1.0f,1.0f,1.0f));
                        sf->setBgColor(OSG::Color4f(0.0f,0.0f,1.0f,0.5f));
                        sf->setBorderColor(OSG::Color4f(1.0f,1.0f,1.0f,1.0f));
                        sf->setBorderOffset(OSG::Vec2f(4.0f, 4.0f));
                        sf->setTextMargin(OSG::Vec2f(8.0f, 8.0f));
                        break;
                    }
                }
            }
        }
    }

    updateGL();
}

//////////////////////////////////////////////////////////////////
// updateGL: redraws all OpenSG views                     //
//////////////////////////////////////////////////////////////////
void OSGSceneView::updateGL(void)
{
    if(_gl != NULL)
        _gl->updateGL();
}

//////////////////////////////////////////////////////////////////
// deleteNode: deletes a subtree                                //
//////////////////////////////////////////////////////////////////
void OSGSceneView::deleteNode(OSG::NodePtr node)
{
    if(node == OSG::NullFC)
        node = rootNode;

    TreeViewItem *item = dynamic_cast<TreeViewItem*>(activeTreeItem);

    if(node == rootNode)
    {
        beginEditCP(node);
            while(node->getNChildren() > 0)
                node->subChild(0);
        endEditCP(node);
        rebuild();
    }
    else
    {
        OSG::NodePtr pnode = node->getParent();
        beginEditCP(pnode);
            pnode->subChild(node);
        endEditCP(pnode);
        if(item != NULL && (item->_node == node))
        {
            delete activeTreeItem;
            activeTreeItem = 0;
        }
        else
            rebuild();
    }

    updateGL();
}

//////////////////////////////////////////////////////////////////
// popupTreeMenu: shows the tree menu at the current mouse pos  //
//////////////////////////////////////////////////////////////////
void OSGSceneView::popupTreeMenu( QListViewItem *parentItem )
{
    treePopupMenu->exec(QCursor::pos());
}

//////////////////////////////////////////////////////////////////
// menuHandler: handles the popup menu events                   //
//////////////////////////////////////////////////////////////////
void OSGSceneView::menuHandler( int id )
{
    switch (id)
    {
        case DELETE_MID:
            deleteNode(activeNode);
        break;
        case INSERT_MID: 
            insertFromFile(activeNode);
        break;
        case EXPORT_MID:
            exportToFile(activeNode);
        break;
    }
}

void OSGSceneView::addFile(OSG::NodePtr parent, const QString &fName)
{
    if(fName.isEmpty())
        return;

    if(parent == OSG::NullFC)
        parent = rootNode;

    // Hack as qt returns a screwed up windows path
#ifdef WIN32
    for(int ui = 0; ui < fName.length(); ui++)
    {
        if(fName[ui] == '/')
        {
            fName[ui] = '\\';
        }
    }
#endif

    OSG::NodePtr node = OSG::SceneFileHandler::the().read(fName);
    if (node != OSG::NullFC) 
    {
        parent->addChild(node);
        if ((parent == rootNode) && (rootNode->getNChildren() == 1))
        {
            if(_gl != NULL)
                _gl->getManager()->showAll();
        }
        QListViewItem *parentItem = (parent == rootNode) ? rootTreeItem : activeTreeItem;
        if(parentItem == NULL)
            parentItem = rootTreeItem;
        addListItem(node,parentItem);
    }
}

//////////////////////////////////////////////////////////////////
// insertFromFile: loads a new scene                            //
//////////////////////////////////////////////////////////////////
void OSGSceneView::insertFromFile(OSG::NodePtr parent)
{
    QString fName = QFileDialog::getOpenFileName ( QString::null,
                                                 filter,
                                                 this,
                                                 "Open Scene Dialog",
                                                 "Choose a scene" );

    addFile(parent, fName);
    updateGL();
}

//////////////////////////////////////////////////////////////////
// exportFromFile: saves a (sub)tree                            //
//////////////////////////////////////////////////////////////////
void OSGSceneView::exportToFile( OSG::NodePtr node )
{
    // shout we use the global filer ?!?
    QString filter = "OpenSG Binary Scene file (*.osb *.wrl *.bin)";
    QString fName = QFileDialog::getSaveFileName(QString::null,
                                                 filter,
                                                 this,
                                                 "Save Scene Dialog",
                                                 "Choose/Create a scene" );

    if(!fName.isEmpty())
        OSG::SceneFileHandler::the().write(node, fName.latin1());
}

//////////////////////////////////////////////////////////////////
// rebuild: loads a new scene                                   //
//////////////////////////////////////////////////////////////////
void OSGSceneView::rebuild()
{
    treeListView->clear();

    addListItem(rootNode,0); 
    setActiveNode(OSG::NullFC);
    activeTreeItem = NULL;
}

//////////////////////////////////////////////////////////////////
// remove the given view from the list                          //
//////////////////////////////////////////////////////////////////

void OSGSceneView::setShadowMode(int mode)
{
    if(_gl == NULL)
        return;

    updateGL();
    OSG::WindowPtr win = _gl->getManager()->getWindow();
    for(int i=0;i<win->getPort().size();++i)
    {
        OSG::ShadowViewportPtr svp = OSG::ShadowViewportPtr::dcast(win->getPort()[i]);
        if(svp != OSG::NullFC)
        {
            beginEditCP(svp, OSG::ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(mode);
            endEditCP(svp, OSG::ShadowViewport::ShadowModeFieldMask);
        }
    }

    updateGL();
}

void OSGSceneView::setOcclusionCullingMode(int mode)
{
    if(_gl == NULL)
        return;

    OSG::RenderAction *ra = (OSG::RenderAction *) _gl->getManager()->getAction();
    ra->setOcclusionCulling(mode > 0);
    ra->setOcclusionCullingMode(mode);
    updateGL();
}

void OSGSceneView::setHeadlight(bool s)
{
    if(_gl == NULL)
        return;

    _gl->getManager()->setHeadlight(s);
    updateGL();
}

void OSGSceneView::showAll()
{
    if(_gl == NULL)
        return;

    _gl->getManager()->showAll();
    updateGL();
}

void OSGSceneView::showObj()
{
    if(_gl == NULL)
        return;

    if(activeNode == OSG::NullFC)
        return;

    _gl->getManager()->showAll();

    activeNode->updateVolume();

    OSG::Vec3f min,max;
    activeNode->getVolume().getBounds( min, max );
    OSG::Vec3f d = max - min;

    if(d.length() < OSG::Eps) // Nothing loaded? Use a unity box
    {
        min.setValues(-1.f,-1.f,-1.f);
        max.setValues( 1.f, 1.f, 1.f);
        d = max - min;
    }

    OSG::Real32 dist = OSG::osgMax(d[0],d[1]) / (2 * OSG::osgtan(_gl->getManager()->getCamera()->getFov() / 2.f));
    OSG::Vec3f up(0,1,0);
    OSG::Pnt3f at((min[0] + max[0]) * .5f,(min[1] + max[1]) * .5f,(min[2] + max[2]) * .5f);
    OSG::Pnt3f from=at;
    from[2]+=(dist+fabs(max[2]-min[2])*0.5f); 
    _gl->getManager()->getNavigator()->set(from,at,up);

    updateGL();
}

void OSGSceneView::editedFC(void)
{
    updateGL();
}

