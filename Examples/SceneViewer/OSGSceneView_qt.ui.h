/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/

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
    _fullscreenAction = NULL;
    _fullscreen = false;

    int i, n;
    QPopupMenu *menu;
    std::list<const char *> suffixList;
    std::list<const char *>::iterator sI;
    
    // init the class variables
    rootTreeItem = 0;
    activeTreeItem = 0;

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
void OSGSceneView::setActiveNode( OSG::NodePtr node )
{
    activeNode = node;

    if(_gl != NULL)
        _gl->getManager().setHighlight(node);

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

//////////////////////////////////////////////////////////////////
// createView: create a new OpenSG 3D view                      //
//////////////////////////////////////////////////////////////////
void OSGSceneView::createView(OSG::NodePtr node)
{
    if(node == OSG::NullFC)
        return;

    _gl = new OSG::OSGQGLManagedWidget(_render_frame, "OSG View");
    _gl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *l = new QVBoxLayout(_render_frame);
    l->addWidget(_gl);

    _gl->getManager().setRoot( node );
    _gl->getManager().setStatistics(false);
    _gl->getManager().showAll();
    _gl->getManager().useOpenSGLogo();
    _gl->getManager().setHighlight(activeNode);
    // _gl->showFullScreen();
    OSG::RenderAction *ract = (OSG::RenderAction *) _gl->getManager().getAction();
    ract->setLocalLights(true);
    ract->setCorrectTwoSidedLighting(true);

    // create a show viewport with a gradient color background.
    OSG::ShadowViewportPtr svp = OSG::ShadowViewport::create();
    OSG::GradientBackgroundPtr   gbg = OSG::GradientBackground::create();

    OSG::beginEditCP(gbg);
        gbg->addLine(OSG::Color3f(0.7, 0.7, 0.8), 0);
        gbg->addLine(OSG::Color3f(0.0, 0.1, 0.3), 1);
    OSG::endEditCP(gbg);

    // Shadow viewport
    OSG::beginEditCP(svp);
        svp->setCamera(_gl->getManager().getCamera());
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
    OSG::WindowPtr win = _gl->getManager().getWindow();
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

    _gl->getManager().getNavigator()->setViewport(svp);

    _gl->show();
}

//////////////////////////////////////////////////////////////////
// setStatistics: change statistics settings                    //
//////////////////////////////////////////////////////////////////
void OSGSceneView::setStatistics(bool val)
{
    if(_gl != NULL)
    {
        _gl->getManager().setStatistics(val);

        if(val)
        {
            // customize the statistic.
            OSG::WindowPtr win = _gl->getManager().getWindow();
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
        return;

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

//////////////////////////////////////////////////////////////////
// insertFromFile: loads a new scene                            //
//////////////////////////////////////////////////////////////////
void OSGSceneView::insertFromFile( OSG::NodePtr parent )
{
    OSG::NodePtr node;
    std::list<QWidget*>::iterator wI;
    OSG::OSGQGLManagedWidget *w;
    QListViewItem *parentItem;
    QString fName = QFileDialog::getOpenFileName ( QString::null,
                                                 filter,
                                                 this,
                                                 "Open Scene Dialog",
                                                 "Choose a scene" );
    if(!fName.isEmpty())
    {

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

        node = OSG::SceneFileHandler::the().read(fName);
        if (node != OSG::NullFC) 
        {
            parent->addChild(node);
            if ((parent == rootNode) && (rootNode->getNChildren() == 1))
            {
                if(_gl != NULL)
                    _gl->getManager().showAll();
            }
            parentItem = (parent == rootNode) ? rootTreeItem : activeTreeItem;
            if(parentItem == NULL)
                parentItem = rootTreeItem;
            addListItem(node,parentItem);
            updateGL();
        }
    }
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
    OSG::WindowPtr win = _gl->getManager().getWindow();
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
    updateGL();
    updateGL();
}

void OSGSceneView::setOcclusionCullingMode(int mode)
{
    if(_gl == NULL)
        return;

    OSG::RenderAction *ra = (OSG::RenderAction *) _gl->getManager().getAction();
    ra->setOcclusionCulling(mode > 0);
    ra->setOcclusionCullingMode(mode);
    updateGL();
}

void OSGSceneView::setHeadlight(bool s)
{
    _gl->getManager().setHeadlight(s);
    updateGL();
}

void OSGSceneView::editedFC(void)
{
    updateGL();
}

void OSGSceneView::toggleFullscreen(void)
{
    _fullscreen = !_fullscreen;

    if(_fullscreen)
    {
        QPoint p(0, 0);
        ((QWidget *)_gl)->reparent(NULL, p, true);
        _gl->showFullScreen();
        _gl->setFocus();
        _fullscreenAction = new QAction(_gl, "fullscreenAction");
        _fullscreenAction->setText(QString::null);
        _fullscreenAction->setAccel(tr("Space"));
        connect(_fullscreenAction, SIGNAL(activated()), this, SLOT(toggleFullscreen()));
        updateGL();
    }
    else
    {
        delete _fullscreenAction;
        _fullscreenAction = NULL;
        QPoint p(0, 0);
        ((QWidget *)_gl)->reparent(_render_frame, p, true);
        _gl->showNormal();
        _gl->resize(_render_frame->width(), _render_frame->height());
        _gl->setFocus();
        updateGL();
    }
}
