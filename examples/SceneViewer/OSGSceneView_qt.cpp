/****************************************************************************
** Form implementation generated from reading ui file 'OSGSceneView_qt.ui'
**
** Created: Mon Oct 15 13:11:26 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "OSGSceneView_qt.h"

#include <qvariant.h>   // first for gcc 2.7.2
#include <OpenSG/OSGLog.h>
#include <OpenSG/OSGMFFieldContainerPtr.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNodeCore.h>
#include <OpenSG/OSGOSGWriter.h>
#include <OpenSG/OSGSFFieldContainerPtr.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <qfiledialog.h>
#include <qgroupbox.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpopupmenu.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qtable.h>
#include "OpenSG/OSGQGLManagedWidget_qt.h"
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "OSGSceneView_qt.ui.h"

/* 
 *  Constructs a OSGSceneView which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
OSGSceneView::OSGSceneView( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "OSGSceneView" );
    resize( 773, 744 ); 
    setCaption( trUtf8( "Form1", "" ) );
    OSGSceneViewLayout = new QHBoxLayout( this ); 
    OSGSceneViewLayout->setSpacing( 6 );
    OSGSceneViewLayout->setMargin( 2 );

    mainSplitter = new QSplitter( this, "mainSplitter" );
    mainSplitter->setFrameShape( QSplitter::MShape );
    mainSplitter->setFrameShadow( QSplitter::MShadow );
    mainSplitter->setOrientation( QSplitter::Horizontal );

    Splitter3 = new QSplitter( mainSplitter, "Splitter3" );
    Splitter3->setOrientation( QSplitter::Horizontal );

    GroupBox1 = new QGroupBox( Splitter3, "GroupBox1" );
    GroupBox1->setTitle( trUtf8( "Tree", "" ) );
    GroupBox1->setColumnLayout(0, Qt::Vertical );
    GroupBox1->layout()->setSpacing( 0 );
    GroupBox1->layout()->setMargin( 0 );
    GroupBox1Layout = new QHBoxLayout( GroupBox1->layout() );
    GroupBox1Layout->setAlignment( Qt::AlignTop );
    GroupBox1Layout->setSpacing( 6 );
    GroupBox1Layout->setMargin( 2 );

    treeListView = new QListView( GroupBox1, "treeListView" );
    treeListView->addColumn( trUtf8( "Node Type", "" ) );
    treeListView->addColumn( trUtf8( "Core Type", "" ) );
    treeListView->addColumn( trUtf8( "Core USEed", "" ) );
    treeListView->setRootIsDecorated( TRUE );
    GroupBox1Layout->addWidget( treeListView );

    Splitter5 = new QSplitter( mainSplitter, "Splitter5" );
    Splitter5->setOrientation( QSplitter::Vertical );

    GroupBox3 = new QGroupBox( Splitter5, "GroupBox3" );
    GroupBox3->setTitle( trUtf8( "Info", "" ) );
    GroupBox3->setColumnLayout(0, Qt::Vertical );
    GroupBox3->layout()->setSpacing( 0 );
    GroupBox3->layout()->setMargin( 0 );
    GroupBox3Layout = new QHBoxLayout( GroupBox3->layout() );
    GroupBox3Layout->setAlignment( Qt::AlignTop );
    GroupBox3Layout->setSpacing( 6 );
    GroupBox3Layout->setMargin( 2 );

    infoTable = new QTable( GroupBox3, "infoTable" );
    infoTable->setNumCols( infoTable->numCols() + 1 );    infoTable->horizontalHeader()->setLabel( infoTable->numCols() - 1, trUtf8( "Value", "" ) );
    infoTable->setNumRows( infoTable->numRows() + 1 );    infoTable->verticalHeader()->setLabel( infoTable->numRows() - 1, trUtf8( "Node Type Name", "" ) );
    infoTable->setNumRows( infoTable->numRows() + 1 );    infoTable->verticalHeader()->setLabel( infoTable->numRows() - 1, trUtf8( "Core Type Name", "" ) );
    infoTable->setNumRows( infoTable->numRows() + 1 );    infoTable->verticalHeader()->setLabel( infoTable->numRows() - 1, trUtf8( "Core USEed count", "" ) );
    infoTable->setNumRows( 3 );
    infoTable->setNumCols( 1 );
    GroupBox3Layout->addWidget( infoTable );

    GroupBox5 = new QGroupBox( Splitter5, "GroupBox5" );
    GroupBox5->setTitle( trUtf8( "Fields", "" ) );
    GroupBox5->setColumnLayout(0, Qt::Vertical );
    GroupBox5->layout()->setSpacing( 0 );
    GroupBox5->layout()->setMargin( 0 );
    GroupBox5Layout = new QHBoxLayout( GroupBox5->layout() );
    GroupBox5Layout->setAlignment( Qt::AlignTop );
    GroupBox5Layout->setSpacing( 6 );
    GroupBox5Layout->setMargin( 2 );

    fieldsTable = new QTable( GroupBox5, "fieldsTable" );
    fieldsTable->setNumCols( fieldsTable->numCols() + 1 );    fieldsTable->horizontalHeader()->setLabel( fieldsTable->numCols() - 1, trUtf8( "Name", "" ) );
    fieldsTable->setNumCols( fieldsTable->numCols() + 1 );    fieldsTable->horizontalHeader()->setLabel( fieldsTable->numCols() - 1, trUtf8( "Type", "" ) );
    fieldsTable->setNumCols( fieldsTable->numCols() + 1 );    fieldsTable->horizontalHeader()->setLabel( fieldsTable->numCols() - 1, trUtf8( "Value", "" ) );
    fieldsTable->setNumCols( fieldsTable->numCols() + 1 );    fieldsTable->horizontalHeader()->setLabel( fieldsTable->numCols() - 1, trUtf8( "Cardinality", "" ) );
    fieldsTable->setNumCols( fieldsTable->numCols() + 1 );    fieldsTable->horizontalHeader()->setLabel( fieldsTable->numCols() - 1, trUtf8( "ID", "" ) );
    fieldsTable->setNumCols( fieldsTable->numCols() + 1 );    fieldsTable->horizontalHeader()->setLabel( fieldsTable->numCols() - 1, trUtf8( "Mask", "" ) );
    fieldsTable->setNumRows( 0 );
    fieldsTable->setNumCols( 6 );
    GroupBox5Layout->addWidget( fieldsTable );
    OSGSceneViewLayout->addWidget( mainSplitter );

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
    destroy();
    // no need to delete child widgets, Qt does it all for us
}

