/****************************************************************************
** Form implementation generated from reading ui file 'OSGChangeListViewer_qt.ui'
**
** Created: Thu Mar 21 09:58:35 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "OSGChangeListViewer_qt.h"

#include <qvariant.h>   // first for gcc 2.7.2
#include <OSGAttachment.h>
#include <OSGBaseTypes.h>
#include <OSGFieldContainerType.h>
#include <OSGFieldDescription.h>
#include <OSGLog.h>
#include <OSGNode.h>
#include <OSGThreadManager.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qtable.h>
#include "OSGChangeListViewer_qt_moc.cpp"
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "OSGChangeListViewer_qt.ui.h"

/* 
 *  Constructs a ChangeListViewer which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ChangeListViewer::ChangeListViewer( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "ChangeListViewer" );
    resize( 640, 480 ); 
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 200, 100 ) );
    setBaseSize( QSize( 640, 4800 ) );
    setCaption( trUtf8( "Change List Viewer" ) );
    ChangeListViewerLayout = new QGridLayout( this, 1, 1, 11, 6, "ChangeListViewerLayout"); 

    LayoutHBox = new QHBoxLayout( 0, 0, 26, "LayoutHBox"); 

    UpdateButton = new QPushButton( this, "UpdateButton" );
    UpdateButton->setText( trUtf8( "Update" ) );
    LayoutHBox->addWidget( UpdateButton );

    CloseButton = new QPushButton( this, "CloseButton" );
    CloseButton->setText( trUtf8( "Close" ) );
    LayoutHBox->addWidget( CloseButton );

    ChangeListViewerLayout->addLayout( LayoutHBox, 1, 0 );

    Splitter2 = new QSplitter( this, "Splitter2" );
    Splitter2->setOrientation( QSplitter::Horizontal );

    FCListView = new QListView( Splitter2, "FCListView" );
    FCListView->addColumn( trUtf8( "FC Name" ) );
    FCListView->header()->setClickEnabled( FALSE, FCListView->header()->count() - 1 );
    FCListView->addColumn( trUtf8( "FC Type" ) );
    FCListView->header()->setClickEnabled( FALSE, FCListView->header()->count() - 1 );
    FCListView->setResizePolicy( QScrollView::Manual );
    FCListView->setVScrollBarMode( QListView::Auto );
    FCListView->setDragAutoScroll( FALSE );
    FCListView->setSelectionMode( QListView::Single );
    FCListView->setAllColumnsShowFocus( TRUE );
    FCListView->setItemMargin( 1 );
    FCListView->setRootIsDecorated( TRUE );
    FCListView->setResizeMode( QListView::AllColumns );

    FCDetailView = new QTable( Splitter2, "FCDetailView" );
    FCDetailView->setResizePolicy( QTable::Default );
    FCDetailView->setNumRows( 0 );
    FCDetailView->setNumCols( 0 );
    FCDetailView->setReadOnly( TRUE );
    FCDetailView->setSelectionMode( QTable::NoSelection );

    ChangeListViewerLayout->addWidget( Splitter2, 0, 0 );

    // signals and slots connections
    connect( CloseButton, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( FCListView, SIGNAL( selectionChanged(QListViewItem*) ), this, SLOT( setActiveFC(QListViewItem*) ) );
    connect( UpdateButton, SIGNAL( clicked() ), this, SLOT( updateFCList() ) );
    init();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
ChangeListViewer::~ChangeListViewer()
{
    // no need to delete child widgets, Qt does it all for us
}

