/****************************************************************************
** Form interface generated from reading ui file 'OSGSceneView_qt.ui'
**
** Created: Sat Aug 17 23:51:33 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef OSGSCENEVIEW_H
#define OSGSCENEVIEW_H

#include <qvariant.h>
#include <OpenSG/OSGNode.h>
#include <list>
#include <qpopupmenu.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QGroupBox;
class QListView;
class QListViewItem;
class QSplitter;
class QTable;

class OSGSceneView : public QWidget
{ 
    Q_OBJECT

public:
    OSGSceneView( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~OSGSceneView();

    QSplitter* mainSplitter;
    QSplitter* Splitter3;
    QGroupBox* GroupBox1;
    QListView* treeListView;
    QSplitter* Splitter5;
    QGroupBox* GroupBox3;
    QTable* infoTable;
    QGroupBox* GroupBox5;
    QTable* fieldsTable;


public slots:
    virtual void addListItem( osg::NodePtr node, QListViewItem * parentItem );
    virtual void init();
    virtual void destroyView();
    virtual void setRootNode( osg::NodePtr root );
    virtual void setActiveNode( osg::NodePtr node );
    virtual void setActiveNodeFromListItem( QListViewItem * item );
    virtual void createView( osg::NodePtr node );
    virtual void setStatistics( bool val );
    virtual void updateAllViews( void );
    virtual void closeAllViews( void );
    virtual void deleteNode( osg::NodePtr node );
    virtual void popupTreeMenu( QListViewItem * parentItem );
    virtual void menuHandler( int id );
    virtual void insertFromFile( osg::NodePtr parent );
    virtual void exportToFile( osg::NodePtr node );
    virtual void rebuild();
    virtual void removeView( QWidget * object );

protected:
    QHBoxLayout* OSGSceneViewLayout;
    QHBoxLayout* GroupBox1Layout;
    QHBoxLayout* GroupBox3Layout;
    QHBoxLayout* GroupBox5Layout;

    QListViewItem *activeTreeItem;
    QListViewItem *rootTreeItem;
    QString filter;
    osg::NodePtr activeNode;
    QPopupMenu *treePopupMenu;
    osg::NodePtr rootNode;
    std::list<QWidget *> viewList;
    bool statState;
};

#endif // OSGSCENEVIEW_H
