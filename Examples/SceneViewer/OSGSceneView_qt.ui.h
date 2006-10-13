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
class TreeViewItem : public QListViewItem {
public:

  osg::NodePtr _node;

  TreeViewItem (QListView *parent, osg::NodePtr node)
    : QListViewItem(parent), _node(node) {;}

  TreeViewItem (QListViewItem *parent, osg::NodePtr node)
    : QListViewItem(parent), _node(node) {;}

  ~TreeViewItem (void) {;}

};

//////////////////////////////////////////////////////////////////
// MenuID: enum for popup menu entry id                         //
//////////////////////////////////////////////////////////////////
enum MenuID { VIEW_MID, DELETE_MID, INSERT_MID, EXPORT_MID };

//////////////////////////////////////////////////////////////////
// addListItem: used to create the tree view recursiv           //
//////////////////////////////////////////////////////////////////
void OSGSceneView::addListItem( osg::NodePtr node, QListViewItem *parentItem )
{
  osg::Int32 i,n;
  osg::NodeCorePtr core;
  QListViewItem *listItem;
  QString qstr;
  const char *nodeName, *coreName, *coreTypeName, *notSet = "Not set";
  
  if (node != osg::NullFC) 
    {
      if (parentItem)
        listItem = new TreeViewItem (parentItem,node);
      else
        rootTreeItem = listItem = new TreeViewItem (treeListView,node);

      nodeName = osg::getName(node);
      if (nodeName == NULL)
        nodeName = notSet;
      
      core = node->getCore();
      if (core == osg::NullFC)
        {
          coreTypeName = notSet;
          qstr.setNum(0);
        }
      else
        {
          coreTypeName = core->getType().getCName();
          qstr.setNum(core->getParents().size());
          listItem->setText(2, qstr);

          coreName = osg::getName(core);
          if (coreName == NULL)
            coreName = notSet;
        }
      
      listItem->setText(0, node->getType().getCName());
      listItem->setText(1, coreTypeName);
      listItem->setText(2, nodeName);
      listItem->setText(3, coreName);
      listItem->setText(4, qstr);
      
      n = node->getNChildren();
      for ( i = 0; i < n; i++)
        addListItem (node->getChild(i),listItem);
    }
}

//////////////////////////////////////////////////////////////////
// init: called by the widget constructor                       //
//////////////////////////////////////////////////////////////////
void OSGSceneView::init()
{
  int i, n;
  QPopupMenu *menu;
  std::list<const char *> suffixList;
  std::list<const char *>::iterator sI;

  // init the class variables
  rootTreeItem = 0;
  activeTreeItem = 0;
  statState = false;
  
  // create tree popup menu
  menu = new QPopupMenu (this, "treeMenu");
  // not yet
  // menu->insertItem("View",   this, SLOT(menuHandler(int)),0,VIEW_MID);
  menu->insertItem("Insert", this, SLOT(menuHandler(int)),0,INSERT_MID);
  menu->insertItem("Export", this, SLOT(menuHandler(int)),0,EXPORT_MID);
  menu->insertSeparator();
  menu->insertItem("Delete", this, SLOT(menuHandler(int)),0,DELETE_MID);
  treePopupMenu = menu;
  
  // init the fields table
  n = fieldsTable->numCols();
  fieldsTable->setLeftMargin( 0 );
  fieldsTable->verticalHeader()->hide();
  for (i = 0; i < n; i++)
    fieldsTable->setColumnStretchable (i , true );

  // init the info table
  infoTable->setColumnStretchable (0 , true );

  // create filter for import/export dialog
  osg::SceneFileHandler::the().getSuffixList(suffixList, 1 /*SceneFileType::OSG_READ_SUPPORTED*/);
  filter = "Scene File";
  filter += " (";
  for (sI = suffixList.begin(); sI != suffixList.end(); sI++) 
    {
      filter += " *.";
      filter += *sI;
    }
  filter += ")"; 
}

//////////////////////////////////////////////////////////////////
// destory: called by the widget destructor                     //
//////////////////////////////////////////////////////////////////
void OSGSceneView::destroyView()
{
  ;
}

//////////////////////////////////////////////////////////////////
// init: method to set the root node                            //
//////////////////////////////////////////////////////////////////
void OSGSceneView::setRootNode( osg::NodePtr root )
{
  rootNode = root;
    
  rebuild();
}

//////////////////////////////////////////////////////////////////
// setActiveNode: sets the active node and rebuilds the views   //
//////////////////////////////////////////////////////////////////
void OSGSceneView::setActiveNode( osg::NodePtr node )
{
  int i, row,col;
  osg::NodeCorePtr core;
  osg::FieldDescription* fDesc;
  osg::Field* fieldPtr;
  std::string val;
  osg::SFFieldContainerPtr* sfFieldPtr;
  osg::MFFieldContainerPtr* mfFieldPtr;
  QString qval;
  std::list<QWidget*>::iterator wI;
  osg::OSGQGLManagedWidget *w;
  osg::NamePtr namePtr;
 
  activeNode = node;
	
  for (wI = viewList.begin(); wI != viewList.end(); ++wI)
    if ((w = dynamic_cast<osg::OSGQGLManagedWidget*>(*wI)))
      {
				std::cerr << "update one manager" << std::endl;
				w->getManager().setHighlight(node);
			}
   
  if (node != osg::NullFC) 
    {
      core = node->getCore();

      if (core != osg::NullFC)
        {
          row = core->getType().getNumFieldDescs();
          fieldsTable->setNumRows(row);

          // set the fieldsTable values
          for ( i = 0; i < row; ++i )
            {
              fDesc = core->getType().getFieldDescription(i+1);
              fieldPtr = core->getField(i+1);
              
              // Name
              col = 0;
              fieldsTable->setText(i,col, fDesc->getCName());
              
              // Type
              col++;
              fieldsTable->setText(i,col, fieldPtr->getType().getCName());
              
              // Value
              col++;
              if ( strstr(fieldPtr->getType().getContentType().getCName(),
                         "Ptr"))
                if (fieldPtr->getCardinality() == osg::FieldType::SINGLE_FIELD)
                  {
                    sfFieldPtr = (osg::SFFieldContainerPtr*)(fieldPtr);
                    if (sfFieldPtr->getValue() == osg::NullFC)
                      qval = "unset";
                    else
                      qval = "set";
                  }
                else
                  {
                    mfFieldPtr = (osg::MFFieldContainerPtr*)(fieldPtr);
                    qval.setNum(mfFieldPtr->size());
                  }
              else
                {
                  fieldPtr->getValueByStr(val);
                  qval = val.c_str();
                }
              fieldsTable->setText(i,col,qval);
              
              // Cardinality
              col++;
              if (fieldPtr->getCardinality() == osg::FieldType::MULTI_FIELD )
                qval = "Multi";
              else
                qval = "Single";
              fieldsTable->setText(i,col,qval);
              
              // ID
              col++;
              qval.setNum(fDesc->getFieldId());
              fieldsTable->setText(i,col,qval);
              
              // mask
              col++;
              qval.setNum((unsigned long)(fDesc->getFieldMask()));
              fieldsTable->setText(i,col,qval);
              
            }

          // node type name
          row = 0;
          infoTable->setText(row,0,node->getType().getCName());
          
          // node name
          row++;
          namePtr = osg::NamePtr::dcast(node->findAttachment(osg::Name::getClassType().getGroupId()));
          if (namePtr == osg::NullFC)
            qval = "";
          else
            qval = namePtr->getFieldPtr()->getValue().c_str();
          infoTable->setText(row,0,qval);

          // node core type name
          row++;
          infoTable->setText(row,0,core->getType().getCName());

          // node name
          row++;
          namePtr = osg::NamePtr::dcast(core->findAttachment(osg::Name::getClassType().getGroupId()));
          if (namePtr == osg::NullFC)
            qval = "";
          else
            qval = namePtr->getFieldPtr()->getValue().c_str();
          infoTable->setText(row,0,qval);

          // core used count
          row++;
          qval.setNum(core->getParents().size());
          infoTable->setText(row,0,qval);
        }
    } 
	updateAllViews();
}

//////////////////////////////////////////////////////////////////
// setActiveNodeFromListItem: set the act. node from tree item  //
//////////////////////////////////////////////////////////////////
void OSGSceneView::setActiveNodeFromListItem( QListViewItem *item )
{
  TreeViewItem *treeItem = dynamic_cast<TreeViewItem*>(item);
  
  if (treeItem)
    {    
      setActiveNode(treeItem->_node);
      activeTreeItem = item;
    }
}

//////////////////////////////////////////////////////////////////
// createView: create a new OpenSG 3D view                      //
//////////////////////////////////////////////////////////////////
void OSGSceneView::createView( osg::NodePtr node )
{
    osg::OSGQGLManagedWidget *widget;
    unsigned maxViewNum = 1; // TODO; will be removed/increased

    if((viewList.size() < maxViewNum) && (node != osg::NullFC))
    {
        widget = new osg::OSGQGLManagedWidget(0,"OSG View");
        widget->getManager().setRoot( node );
        widget->getManager().setStatistics( statState );
        widget->getManager().showAll();
        widget->getManager().useOpenSGLogo();
        widget->getManager().setHighlight(activeNode);
        // widget->showFullScreen();
        osg::RenderAction *ract = (osg::RenderAction *) widget->getManager().getAction();
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
            svp->setCamera(widget->getManager().getCamera());
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
        OSG::WindowPtr win = widget->getManager().getWindow();
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

        widget->getManager().getNavigator()->setViewport(svp);

        viewList.push_back(widget);
        connect ( widget, SIGNAL ( closed     (QWidget *) ),
                this,   SLOT   ( removeView (QWidget *) ) );
        widget->show();
    }
}

//////////////////////////////////////////////////////////////////
// setStatistics: change statistics settings                    //
//////////////////////////////////////////////////////////////////
void OSGSceneView::setStatistics(bool val)
{
    std::list<QWidget*>::iterator wI;
    osg::OSGQGLManagedWidget *w;

    statState = val;
    
    for (wI = viewList.begin(); wI != viewList.end(); ++wI)
    {
        if ((w = dynamic_cast<osg::OSGQGLManagedWidget*>(*wI)))
            w->getManager().setStatistics(val);
    }
    updateAllViews();
}

//////////////////////////////////////////////////////////////////
// updateAllViews: redraws all OpenSG views                     //
//////////////////////////////////////////////////////////////////
void OSGSceneView::updateAllViews(void)
{
  std::list<QWidget*>::iterator wI;
  QGLWidget *w;
  
  for (wI = viewList.begin(); wI != viewList.end(); ++wI)
    if ((w = dynamic_cast<QGLWidget*>(*wI)))
      w->updateGL();
}

//////////////////////////////////////////////////////////////////
// closeAllViews: close all views                               //
//////////////////////////////////////////////////////////////////
void OSGSceneView::closeAllViews(void)
{
	while (viewList.empty() == false)
		viewList.front()->close();
}

//////////////////////////////////////////////////////////////////
// deleteNode: deletes a subtree                                //
//////////////////////////////////////////////////////////////////
void OSGSceneView::deleteNode(osg::NodePtr node)
{
  TreeViewItem *item = dynamic_cast<TreeViewItem*>(activeTreeItem);

  if (node != osg::NullFC)
    if (node == rootNode)
      {
        while (node->getNChildren())
          node->subChild(0);
        rebuild();
      }
    else
      {
        node->getParent()->subChild(node);
        if (item && (item->_node == node))
          {
            delete activeTreeItem;
            activeTreeItem = 0;
          }
        else
          rebuild();
      }

  updateAllViews();
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
    case VIEW_MID:
      createView(activeNode);
      break;
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
void OSGSceneView::insertFromFile( osg::NodePtr parent )
{
  osg::NodePtr node;
  std::list<QWidget*>::iterator wI;
  osg::OSGQGLManagedWidget *w;
  QListViewItem *parentItem;
  QString fName = QFileDialog::getOpenFileName ( QString::null,
                                                 filter,
                                                 this,
                                                 "Open Scene Dialog",
                                                 "Choose a scene" );
  if (!fName.isEmpty())
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
        
      node = osg::SceneFileHandler::the().read(fName);
      if (node != osg::NullFC) 
        {
          parent->addChild(node);
          if ((parent == rootNode) && (rootNode->getNChildren() == 1))
            {
              for (wI = viewList.begin(); wI != viewList.end(); ++wI)
                if ((w = dynamic_cast<osg::OSGQGLManagedWidget*>(*wI)))
                  w->getManager().showAll();
            }
          parentItem = (parent == rootNode) ? rootTreeItem : activeTreeItem;
          addListItem(node,parentItem);
          updateAllViews();
        }
    }
}

//////////////////////////////////////////////////////////////////
// exportFromFile: saves a (sub)tree                            //
//////////////////////////////////////////////////////////////////
void OSGSceneView::exportToFile( osg::NodePtr node )
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
  setActiveNode(rootNode);
  activeTreeItem = rootTreeItem;
}

//////////////////////////////////////////////////////////////////
// remove the given view from the list                          //
//////////////////////////////////////////////////////////////////
void OSGSceneView::removeView( QWidget *object )
{
  FDEBUG (("OSGSceneView::removeView() called\n"));

  viewList.remove(object);
}

void OSGSceneView::setShadowMode(int mode)
{
    std::list<QWidget*>::iterator wI;
    osg::OSGQGLManagedWidget *w;

    updateAllViews();
    for (wI = viewList.begin(); wI != viewList.end(); ++wI)
    {
        if((w = dynamic_cast<osg::OSGQGLManagedWidget*>(*wI)))
        {
            OSG::WindowPtr win = w->getManager().getWindow();
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
        }
    }
    updateAllViews();
    updateAllViews();
    updateAllViews();
}

void OSGSceneView::setOcclusionCullingMode(int mode)
{
    std::list<QWidget*>::iterator wI;
    osg::OSGQGLManagedWidget *w;

    for (wI = viewList.begin(); wI != viewList.end(); ++wI)
    {
        if((w = dynamic_cast<osg::OSGQGLManagedWidget*>(*wI)))
        {
            OSG::RenderAction *ra = (OSG::RenderAction *) w->getManager().getAction();
            ra->setOcclusionCulling(mode > 0);
            ra->setOcclusionCullingMode(mode);
        }
    }
    updateAllViews();
}

void OSGSceneView::setHeadlight(bool s)
{
    std::list<QWidget*>::iterator wI;
    osg::OSGQGLManagedWidget *w;

    for(wI = viewList.begin(); wI != viewList.end(); ++wI)
    {
        if((w = dynamic_cast<osg::OSGQGLManagedWidget*>(*wI)))
            w->getManager().setHeadlight(s);
    }
    updateAllViews();
}
