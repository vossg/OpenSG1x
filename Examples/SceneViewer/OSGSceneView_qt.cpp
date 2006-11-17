/****************************************************************************
** Form implementation generated from reading ui file 'OSGSceneView_qt.ui'
**
** Created: Fr 17. Nov 12:30:30 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.5   edited Aug 31 12:13 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "OSGSceneView_qt.h"

#include <qvariant.h>
#include <qfiledialog.h>
#include <qobjectlist.h>
#include <qgl.h>
#include <qvbox.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <qpopupmenu.h>
#include <qdragobject.h>
#include <OpenSG/OSGSFFieldContainerPtr.h>
#include <OpenSG/OSGMFFieldContainerPtr.h>
#include <OpenSG/OSGNodeCore.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGLog.h>
#include <OpenSG/OSGBINWriter.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGShadowViewport.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGSimpleStatisticsForeground.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qheader.h>
#include <qlistview.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "OSGMainView_qt.h"
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
    OSGSceneViewLayout = new QVBoxLayout( this, 2, 6, "OSGSceneViewLayout"); 

    mainSplitter = new QSplitter( this, "mainSplitter" );
    mainSplitter->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)5, 0, 0, mainSplitter->sizePolicy().hasHeightForWidth() ) );
    mainSplitter->setOrientation( QSplitter::Horizontal );

    treeListView = new QListView( mainSplitter, "treeListView" );
    treeListView->addColumn( tr( "Scenegraph" ) );
    treeListView->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)7, 0, 0, treeListView->sizePolicy().hasHeightForWidth() ) );
    treeListView->setRootIsDecorated( TRUE );

    frame6 = new QFrame( mainSplitter, "frame6" );
    frame6->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)5, 0, 0, frame6->sizePolicy().hasHeightForWidth() ) );
    frame6->setFrameShape( QFrame::NoFrame );
    frame6->setFrameShadow( QFrame::Raised );
    frame6Layout = new QVBoxLayout( frame6, 0, 0, "frame6Layout"); 

    _fceditor_splitter = new QSplitter( frame6, "_fceditor_splitter" );
    _fceditor_splitter->setOrientation( QSplitter::Vertical );

    _render_frame = new QVBox( _fceditor_splitter, "_render_frame" );
    _render_frame->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, _render_frame->sizePolicy().hasHeightForWidth() ) );
    _render_frame->setMinimumSize( QSize( 320, 256 ) );
    _render_frame->setFrameShape( QVBox::NoFrame );
    _render_frame->setFrameShadow( QVBox::Raised );

    _fc_frame = new QFrame( _fceditor_splitter, "_fc_frame" );
    _fc_frame->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, _fc_frame->sizePolicy().hasHeightForWidth() ) );
    _fc_frame->setFrameShape( QFrame::NoFrame );
    _fc_frame->setFrameShadow( QFrame::Raised );
    _fc_frameLayout = new QVBoxLayout( _fc_frame, 5, 5, "_fc_frameLayout"); 

    textLabel1 = new QLabel( _fc_frame, "textLabel1" );
    textLabel1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, textLabel1->sizePolicy().hasHeightForWidth() ) );
    textLabel1->setAlignment( int( QLabel::WordBreak | QLabel::AlignCenter ) );
    _fc_frameLayout->addWidget( textLabel1 );

    _fceditor_frame = new QFrame( _fc_frame, "_fceditor_frame" );
    _fceditor_frame->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, _fceditor_frame->sizePolicy().hasHeightForWidth() ) );
    _fceditor_frame->setFrameShape( QFrame::NoFrame );
    _fceditor_frame->setFrameShadow( QFrame::Raised );
    _fc_frameLayout->addWidget( _fceditor_frame );
    frame6Layout->addWidget( _fceditor_splitter );
    OSGSceneViewLayout->addWidget( mainSplitter );
    languageChange();
    resize( QSize(774, 743).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( treeListView, SIGNAL( rightButtonPressed(QListViewItem*,const QPoint&,int) ), this, SLOT( popupTreeMenu(QListViewItem*) ) );
    connect( treeListView, SIGNAL( selectionChanged(QListViewItem*) ), this, SLOT( setActiveNodeFromListItem(QListViewItem*) ) );
    connect( treeListView, SIGNAL( clicked(QListViewItem*) ), this, SLOT( setActiveNodeFromListItem(QListViewItem*) ) );
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
    treeListView->header()->setLabel( 0, tr( "Scenegraph" ) );
    textLabel1->setText( tr( "<b>FCEditor</b>" ) );
}

