/****************************************************************************
** Form interface generated from reading ui file 'OSGChangeListViewer_qt.ui'
**
** Created: Thu Mar 21 09:58:17 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef CHANGELISTVIEWER_H
#define CHANGELISTVIEWER_H

#include <qvariant.h>
#include <OSGChangeList.h>
#include <OSGConfig.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QListView;
class QListViewItem;
class QPushButton;
class QSplitter;
class QTable;
class ColorTableItem;

class ChangeListViewer : public QWidget
{ 
    Q_OBJECT

public:
    ChangeListViewer( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ChangeListViewer();

    QPushButton* UpdateButton;
    QPushButton* CloseButton;
    QSplitter* Splitter2;
    QListView* FCListView;
    QTable* FCDetailView;


public slots:
    virtual void updateFCList();
    virtual void setActiveFC( QListViewItem * activeItem );
    virtual void setChangeList( osg::ChangeList * list );
    virtual void displayDynFieldAtt( OSG::FieldContainerPtr fcPtr, OSG::BitVector changeMask, bool allFlag=true);
    virtual void displayFC(OSG::FieldContainerPtr fcPtr, OSG::BitVector changeMask, bool allFlag=true);
    virtual void init();

protected:
    QGridLayout* ChangeListViewerLayout;
    QHBoxLayout* LayoutHBox;

    QListViewItem* _destroyedRoot;
    QListViewItem* _createdRoot;
    QListViewItem* _subrefRoot;
    QListViewItem* _addrefRoot;
    QListViewItem* _changedRoot;
    osg::ChangeList* _changeList;
    osg::UInt32 _numAspects;
    QColor _changedColor;
    QColor _normalColor;
};

#endif // CHANGELISTVIEWER_H
