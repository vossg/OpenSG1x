/****************************************************************************
** Form interface generated from reading ui file 'OSGSceneView_qt.ui'
**
** Created: Fr 10. Nov 18:13:09 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.5   edited Aug 31 12:13 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef OSGSCENEVIEW_H
#define OSGSCENEVIEW_H

#include <qvariant.h>
#include <qwidget.h>
#include <qpopupmenu.h>
#include <qaction.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGQOSGWidgetFactory.h>
#include <OpenSG/OSGQFieldContainerEditor_qt.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <list>
#include <fstream>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QSplitter;
class QListView;
class QListViewItem;
class QFrame;
class QVBox;
class QLabel;
class OpenSGWidget;

class OSGSceneView : public QWidget
{
    Q_OBJECT

public:
    OSGSceneView( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~OSGSceneView();

    QSplitter* mainSplitter;
    QListView* treeListView;
    QFrame* frame6;
    QSplitter* _fceditor_splitter;
    QVBox* _render_frame;
    QFrame* _fc_frame;
    QLabel* textLabel1;
    QFrame* _fceditor_frame;

    void selectItem(OSG::NodePtr node);

public slots:
    virtual void addListItem( osg::NodePtr node, QListViewItem * parentItem );
    virtual void init();
    virtual void destroyView();
    virtual void setRootNode( osg::NodePtr root );
    virtual void setActiveNode( osg::NodePtr node );
    virtual void setActiveNodeFromListItem( QListViewItem * item );
    virtual void createView( osg::NodePtr node );
    virtual void setStatistics( bool val );
    virtual void updateGL( void );
    virtual void deleteNode( osg::NodePtr node );
    virtual void popupTreeMenu( QListViewItem * parentItem );
    virtual void menuHandler( int id );
    virtual void addFile(osg::NodePtr parent, const QString &);
    virtual void insertFromFile( osg::NodePtr parent );
    virtual void exportToFile( osg::NodePtr node );
    virtual void rebuild();
    virtual void setOcclusionCullingMode(int mode);
    virtual void setShadowMode(int mode);
    virtual void setHeadlight(bool);
    virtual void showAll();
    virtual void showObj();
    virtual void editedFC();

protected:
    QListViewItem *activeTreeItem;
    QListViewItem *rootTreeItem;
    QString filter;
    osg::NodePtr activeNode;
    QPopupMenu *treePopupMenu;
    osg::NodePtr rootNode;
    OSG::QFieldContainerEditor *_fceditor;
    OpenSGWidget *_gl;

    QVBoxLayout* OSGSceneViewLayout;
    QVBoxLayout* frame6Layout;
    QVBoxLayout* _fc_frameLayout;

protected slots:
    virtual void languageChange();

};

#endif // OSGSCENEVIEW_H
