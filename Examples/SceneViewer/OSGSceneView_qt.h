/****************************************************************************
** Form interface generated from reading ui file 'OSGSceneView_qt.ui'
**
** Created: Fr 15. Aug 10:55:55 2003
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.1.2   edited Dec 19 11:45 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef OSGSCENEVIEW_H
#define OSGSCENEVIEW_H

#include <qvariant.h>
#include <qwidget.h>
#include <qpopupmenu.h>
#include <OpenSG/OSGNode.h>
#include <list>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSplitter;
class QGroupBox;
class QListView;
class QListViewItem;
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
    QListViewItem *activeTreeItem;
    QListViewItem *rootTreeItem;
    QString filter;
    osg::NodePtr activeNode;
    QPopupMenu *treePopupMenu;
    osg::NodePtr rootNode;
    std::list<QWidget *> viewList;
    bool statState;

    QHBoxLayout* OSGSceneViewLayout;
    QHBoxLayout* GroupBox1Layout;
    QHBoxLayout* GroupBox3Layout;
    QHBoxLayout* GroupBox5Layout;

protected slots:
    virtual void languageChange();

};

#endif // OSGSCENEVIEW_H
