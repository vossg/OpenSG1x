/****************************************************************************
** Form implementation generated from reading ui file 'OSGSceneView_qt.ui'
**
** Created: So 17. Aug 15:50:29 2003
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.2.0   edited May 19 14:22 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "OSGSceneView_qt.h"

#include <qvariant.h>
#include <qfiledialog.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <qpopupmenu.h>
#include <OpenSG/OSGSFFieldContainerPtr.h>
#include <OpenSG/OSGMFFieldContainerPtr.h>
#include <OpenSG/OSGNodeCore.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGLog.h>
#include <OpenSG/OSGBINWriter.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qgroupbox.h>
#include <qheader.h>
#include <qlistview.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "OpenSG/OSGQGLManagedWidget_qt.h"
#include "OSGSceneView_qt.ui.h"

/*
 *  Constructs a OSGSceneView as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
OSGSceneView::OSGSceneView( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "OSGSceneView" );
    OSGSceneViewLayout = new QHBoxLayout( this, 2, 6, "OSGSceneViewLayout"); 

    mainSplitter = new QSplitter( this, "mainSplitter" );
    mainSplitter->setFrameShape( QSplitter::MShape );
    mainSplitter->setFrameShadow( QSplitter::MShadow );
    mainSplitter->setOrientation( QSplitter::Horizontal );

    Splitter3 = new QSplitter( mainSplitter, "Splitter3" );
    Splitter3->setOrientation( QSplitter::Horizontal );

    GroupBox1 = new QGroupBox( Splitter3, "GroupBox1" );
    GroupBox1->setColumnLayout(0, Qt::Vertical );
    GroupBox1->layout()->setSpacing( 6 );
    GroupBox1->layout()->setMargin( 2 );
    GroupBox1Layout = new QHBoxLayout( GroupBox1->layout() );
    GroupBox1Layout->setAlignment( Qt::AlignTop );

    treeListView = new QListView( GroupBox1, "treeListView" );
    treeListView->addColumn( tr( "Node Type" ) );
    treeListView->addColumn( tr( "Core Type" ) );
    treeListView->addColumn( tr( "Node Name" ) );
    treeListView->addColumn( tr( "Core Name" ) );
    treeListView->addColumn( tr( "Core USEed" ) );
    treeListView->setRootIsDecorated( TRUE );
    GroupBox1Layout->addWidget( treeListView );

    Splitter5 = new QSplitter( mainSplitter, "Splitter5" );
    Splitter5->setOrientation( QSplitter::Vertical );

    GroupBox3 = new QGroupBox( Splitter5, "GroupBox3" );
    GroupBox3->setColumnLayout(0, Qt::Vertical );
    GroupBox3->layout()->setSpacing( 6 );
    GroupBox3->layout()->setMargin( 2 );
    GroupBox3Layout = new QHBoxLayout( GroupBox3->layout() );
    GroupBox3Layout->setAlignment( Qt::AlignTop );

    infoTable = new QTable( GroupBox3, "infoTable" );
    infoTable->setNumCols( infoTable->numCols() + 1 );
    infoTable->horizontalHeader()->setLabel( infoTable->numCols() - 1, tr( "Value" ) );
    infoTable->setNumRows( infoTable->numRows() + 1 );
    infoTable->verticalHeader()->setLabel( infoTable->numRows() - 1, tr( "Node Type Name" ) );
    infoTable->setNumRows( infoTable->numRows() + 1 );
    infoTable->verticalHeader()->setLabel( infoTable->numRows() - 1, tr( "Node Name" ) );
    infoTable->setNumRows( infoTable->numRows() + 1 );
    infoTable->verticalHeader()->setLabel( infoTable->numRows() - 1, tr( "Core Type Name" ) );
    infoTable->setNumRows( infoTable->numRows() + 1 );
    infoTable->verticalHeader()->setLabel( infoTable->numRows() - 1, tr( "Core Name" ) );
    infoTable->setNumRows( infoTable->numRows() + 1 );
    infoTable->verticalHeader()->setLabel( infoTable->numRows() - 1, tr( "Core USEed count" ) );
    infoTable->setNumRows( 5 );
    infoTable->setNumCols( 1 );
    GroupBox3Layout->addWidget( infoTable );

    GroupBox5 = new QGroupBox( Splitter5, "GroupBox5" );

    fieldsTable = new QTable( GroupBox5, "fieldsTable" );
    fieldsTable->setNumCols( fieldsTable->numCols() + 1 );
    fieldsTable->horizontalHeader()->setLabel( fieldsTable->numCols() - 1, tr( "Name" ) );
    fieldsTable->setNumCols( fieldsTable->numCols() + 1 );
    fieldsTable->horizontalHeader()->setLabel( fieldsTable->numCols() - 1, tr( "Type" ) );
    fieldsTable->setNumCols( fieldsTable->numCols() + 1 );
    fieldsTable->horizontalHeader()->setLabel( fieldsTable->numCols() - 1, tr( "Value" ) );
    fieldsTable->setNumCols( fieldsTable->numCols() + 1 );
    fieldsTable->horizontalHeader()->setLabel( fieldsTable->numCols() - 1, tr( "Cardinality" ) );
    fieldsTable->setNumCols( fieldsTable->numCols() + 1 );
    fieldsTable->horizontalHeader()->setLabel( fieldsTable->numCols() - 1, tr( "ID" ) );
    fieldsTable->setNumCols( fieldsTable->numCols() + 1 );
    fieldsTable->horizontalHeader()->setLabel( fieldsTable->numCols() - 1, tr( "Mask" ) );
    fieldsTable->setGeometry( QRect( 2, 20, 383, 250 ) );
    fieldsTable->setNumRows( 0 );
    fieldsTable->setNumCols( 6 );
    OSGSceneViewLayout->addWidget( mainSplitter );
    languageChange();
    resize( QSize(667, 540).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( treeListView, SIGNAL( rightButtonPressed(QListViewItem*,const QPoint&,int) ), this, SLOT( popupTreeMenu(QListViewItem*) ) );
    connect( treeListView, SIGNAL( selectionChanged(QListViewItem*) ), this, SLOT( setActiveNodeFromListItem(QListViewItem*) ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
OSGSceneView::~OSGSceneView()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void OSGSceneView::languageChange()
{
    setCaption( tr( "Form1" ) );
    GroupBox1->setTitle( tr( "Tree" ) );
    treeListView->header()->setLabel( 0, tr( "Node Type" ) );
    treeListView->header()->setLabel( 1, tr( "Core Type" ) );
    treeListView->header()->setLabel( 2, tr( "Node Name" ) );
    treeListView->header()->setLabel( 3, tr( "Core Name" ) );
    treeListView->header()->setLabel( 4, tr( "Core USEed" ) );
    GroupBox3->setTitle( tr( "Info" ) );
    infoTable->horizontalHeader()->setLabel( 0, tr( "Value" ) );
    infoTable->verticalHeader()->setLabel( 0, tr( "Node Type Name" ) );
    infoTable->verticalHeader()->setLabel( 1, tr( "Node Name" ) );
    infoTable->verticalHeader()->setLabel( 2, tr( "Core Type Name" ) );
    infoTable->verticalHeader()->setLabel( 3, tr( "Core Name" ) );
    infoTable->verticalHeader()->setLabel( 4, tr( "Core USEed count" ) );
    GroupBox5->setTitle( tr( "Fields" ) );
    fieldsTable->horizontalHeader()->setLabel( 0, tr( "Name" ) );
    fieldsTable->horizontalHeader()->setLabel( 1, tr( "Type" ) );
    fieldsTable->horizontalHeader()->setLabel( 2, tr( "Value" ) );
    fieldsTable->horizontalHeader()->setLabel( 3, tr( "Cardinality" ) );
    fieldsTable->horizontalHeader()->setLabel( 4, tr( "ID" ) );
    fieldsTable->horizontalHeader()->setLabel( 5, tr( "Mask" ) );
}

