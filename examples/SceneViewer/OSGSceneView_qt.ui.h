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
  const char *coreTypeName, *notSet = "Not set";

  if (node != osg::NullFC) 
    {
      if (parentItem)
        listItem = new TreeViewItem (parentItem,node);
      else
        rootTreeItem = listItem = new TreeViewItem (treeListView,node);

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
        }

      listItem->setText(0, node->getType().getCName());
      listItem->setText(1, coreTypeName);
      listItem->setText(2, qstr);
      
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
  list<const char *> suffixList;
  list<const char *>::iterator sI;

  // init the class variables
  rootTreeItem = 0;
  activeTreeItem = 0;
  
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
  osg::SceneFileHandler::the().getSuffixList(suffixList);
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
void OSGSceneView::destroy()
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
  osg::MFFieldContainerPtr* mfFieldPtr;
  QString qval;

  activeNode = node;
  
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
              mfFieldPtr = dynamic_cast<osg::MFFieldContainerPtr*>(fieldPtr);
              if ( mfFieldPtr )
                qval.setNum(mfFieldPtr->getSize());
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
              qval.setNum(fDesc->getFieldMask());
              fieldsTable->setText(i,col,qval);
              
            }

          // node type name
          row = 0;
          infoTable->setText(row,0,node->getType().getCName());
          
          // node core type name
          row++;
          infoTable->setText(row,0,core->getType().getCName());

          // core used count
          row++;
          qval.setNum(core->getParents().size());
          infoTable->setText(row,0,qval);
        }
    } 
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

  if ((viewList.size() < maxViewNum) && (node != osg::NullFC))
    {
      widget = new osg::OSGQGLManagedWidget(0,"OSG View");    
      viewList.push_back(widget);
      connect ( widget, SIGNAL ( closed     (QWidget *) ),
                this,   SLOT   ( removeView (QWidget *) ) );
           widget->getManager().setRoot( node );
      widget->getManager().showAll();
      // widget->getManager().useOpenSGLogo();
      widget->show();
    }  
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
  std::list<QWidget*>::iterator wI;
  QWidget *w;
  
  for (wI = viewList.begin(); wI != viewList.end(); ++wI)
    if ((w = *wI))
      w->close();
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
  osg::OSGWriter *writer;
  ofstream outStream;
  // shout we use the global filer ?!?
  QString filter = "OpenSG Scene file (*.osg)";
  QString fName = QFileDialog::getSaveFileName ( QString::null,
                                                 filter,
                                                 this,
                                                 "Save Scene Dialog",
                                                 "Choose/Create a scene" );
  if (!fName.isEmpty())
    {
      outStream.open(fName);
      if (outStream)
        {
          writer = new osg::OSGWriter( outStream, 4);
          writer->write(node);
          delete writer;
        }
    }
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
