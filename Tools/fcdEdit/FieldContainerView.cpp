/****************************************************************************
** Form implementation generated from reading ui file 'FieldContainerView.ui'
**
** Created: Wed Mar 28 15:00:06 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "FieldContainerView.h"

#include <qcombobox.h>
#include <qframe.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistbox.h>
#include <qmultilineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a FieldContainerView which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
FieldContainerView::FieldContainerView( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "FieldContainerView" );
    resize( 811, 588 ); 
    setCaption( tr( "OpenSG Field Container editor" ) );
    FieldContainerViewLayout = new QVBoxLayout( this ); 
    FieldContainerViewLayout->setSpacing( 6 );
    FieldContainerViewLayout->setMargin( 11 );

    Layout6 = new QHBoxLayout; 
    Layout6->setSpacing( 6 );
    Layout6->setMargin( 0 );

    GroupBox1 = new QGroupBox( this, "GroupBox1" );
    GroupBox1->setTitle( tr( "Field Container" ) );
    QWhatsThis::add(  GroupBox1, tr( "Pointer Field Types" ) );
    GroupBox1->setColumnLayout(0, Qt::Vertical );
    GroupBox1->layout()->setSpacing( 0 );
    GroupBox1->layout()->setMargin( 0 );
    GroupBox1Layout = new QVBoxLayout( GroupBox1->layout() );
    GroupBox1Layout->setAlignment( Qt::AlignTop );
    GroupBox1Layout->setSpacing( 6 );
    GroupBox1Layout->setMargin( 11 );

    GroupBox17 = new QGroupBox( GroupBox1, "GroupBox17" );
    GroupBox17->setTitle( tr( "Type" ) );
    GroupBox17->setColumnLayout(0, Qt::Vertical );
    GroupBox17->layout()->setSpacing( 0 );
    GroupBox17->layout()->setMargin( 0 );
    GroupBox17Layout = new QGridLayout( GroupBox17->layout() );
    GroupBox17Layout->setAlignment( Qt::AlignTop );
    GroupBox17Layout->setSpacing( 6 );
    GroupBox17Layout->setMargin( 11 );

    TextLabel2 = new QLabel( GroupBox17, "TextLabel2" );
    TextLabel2->setText( tr( "Name:" ) );

    GroupBox17Layout->addWidget( TextLabel2, 0, 0 );

    TextLabel3 = new QLabel( GroupBox17, "TextLabel3" );
    TextLabel3->setText( tr( "Parent:" ) );

    GroupBox17Layout->addWidget( TextLabel3, 1, 0 );

    TextLabel1 = new QLabel( GroupBox17, "TextLabel1" );
    TextLabel1->setText( tr( "Library:" ) );

    GroupBox17Layout->addWidget( TextLabel1, 2, 0 );

    nodeParentInput = new QLineEdit( GroupBox17, "nodeParentInput" );

    GroupBox17Layout->addWidget( nodeParentInput, 1, 1 );

    nodeNameInput = new QLineEdit( GroupBox17, "nodeNameInput" );

    GroupBox17Layout->addWidget( nodeNameInput, 0, 1 );

    nodeLibraryInput = new QLineEdit( GroupBox17, "nodeLibraryInput" );

    GroupBox17Layout->addWidget( nodeLibraryInput, 2, 1 );

    TextLabel1_4 = new QLabel( GroupBox17, "TextLabel1_4" );
    TextLabel1_4->setText( tr( "PFTypes:" ) );

    GroupBox17Layout->addWidget( TextLabel1_4, 3, 0 );

    pointerFieldTypesCombo = new QComboBox( FALSE, GroupBox17, "pointerFieldTypesCombo" );
    QToolTip::add(  pointerFieldTypesCombo, tr( "Pointer Field Types" ) );

    GroupBox17Layout->addWidget( pointerFieldTypesCombo, 3, 1 );
    GroupBox1Layout->addWidget( GroupBox17 );

    GroupBox7 = new QGroupBox( GroupBox1, "GroupBox7" );
    GroupBox7->setTitle( tr( "Description" ) );
    GroupBox7->setColumnLayout(0, Qt::Vertical );
    GroupBox7->layout()->setSpacing( 0 );
    GroupBox7->layout()->setMargin( 0 );
    GroupBox7Layout = new QVBoxLayout( GroupBox7->layout() );
    GroupBox7Layout->setAlignment( Qt::AlignTop );
    GroupBox7Layout->setSpacing( 6 );
    GroupBox7Layout->setMargin( 11 );

    nodeDescriptionInput = new QMultiLineEdit( GroupBox7, "nodeDescriptionInput" );
    nodeDescriptionInput->setWordWrap( QMultiLineEdit::WidgetWidth );
    GroupBox7Layout->addWidget( nodeDescriptionInput );
    GroupBox1Layout->addWidget( GroupBox7 );
    Layout6->addWidget( GroupBox1 );

    GroupBox3 = new QGroupBox( this, "GroupBox3" );
    GroupBox3->setTitle( tr( "Fields" ) );
    GroupBox3->setColumnLayout(0, Qt::Vertical );
    GroupBox3->layout()->setSpacing( 0 );
    GroupBox3->layout()->setMargin( 0 );
    GroupBox3Layout = new QVBoxLayout( GroupBox3->layout() );
    GroupBox3Layout->setAlignment( Qt::AlignTop );
    GroupBox3Layout->setSpacing( 6 );
    GroupBox3Layout->setMargin( 11 );

    partListBox = new QListBox( GroupBox3, "partListBox" );
    partListBox->setEnabled( TRUE );
    GroupBox3Layout->addWidget( partListBox );

    partFrame = new QFrame( GroupBox3, "partFrame" );
    partFrame->setEnabled( TRUE );
    partFrame->setFrameShape( QFrame::Box );
    partFrame->setFrameShadow( QFrame::Raised );
    partFrameLayout = new QGridLayout( partFrame ); 
    partFrameLayout->setSpacing( 6 );
    partFrameLayout->setMargin( 11 );

    partNameInput = new QLineEdit( partFrame, "partNameInput" );
    partNameInput->setEnabled( TRUE );

    partFrameLayout->addWidget( partNameInput, 0, 1 );

    TextLabel1_2 = new QLabel( partFrame, "TextLabel1_2" );
    TextLabel1_2->setText( tr( "Name:" ) );

    partFrameLayout->addWidget( TextLabel1_2, 0, 0 );

    TextLabel3_2 = new QLabel( partFrame, "TextLabel3_2" );
    TextLabel3_2->setText( tr( "Type:" ) );

    partFrameLayout->addWidget( TextLabel3_2, 1, 0 );

    partTypeCombo = new QComboBox( FALSE, partFrame, "partTypeCombo" );

    partFrameLayout->addWidget( partTypeCombo, 1, 1 );

    partDescriptionInput = new QLineEdit( partFrame, "partDescriptionInput" );

    partFrameLayout->addWidget( partDescriptionInput, 5, 1 );

    TextLabel5 = new QLabel( partFrame, "TextLabel5" );
    TextLabel5->setText( tr( "Description:" ) );

    partFrameLayout->addWidget( TextLabel5, 5, 0 );

    TextLabel4_2 = new QLabel( partFrame, "TextLabel4_2" );
    TextLabel4_2->setText( tr( "DefaultValue:" ) );

    partFrameLayout->addWidget( TextLabel4_2, 4, 0 );

    partDefaultValueInput = new QLineEdit( partFrame, "partDefaultValueInput" );

    partFrameLayout->addWidget( partDefaultValueInput, 4, 1 );

    TextLabel1_3 = new QLabel( partFrame, "TextLabel1_3" );
    TextLabel1_3->setText( tr( "Visibility:" ) );

    partFrameLayout->addWidget( TextLabel1_3, 3, 0 );

    partVisibilityCombo = new QComboBox( FALSE, partFrame, "partVisibilityCombo" );

    partFrameLayout->addWidget( partVisibilityCombo, 3, 1 );

    TextLabel2_2 = new QLabel( partFrame, "TextLabel2_2" );
    TextLabel2_2->setText( tr( "Cardinality:" ) );

    partFrameLayout->addWidget( TextLabel2_2, 2, 0 );

    partCardinalityCombo = new QComboBox( FALSE, partFrame, "partCardinalityCombo" );

    partFrameLayout->addWidget( partCardinalityCombo, 2, 1 );
    GroupBox3Layout->addWidget( partFrame );

    Layout3 = new QHBoxLayout; 
    Layout3->setSpacing( 6 );
    Layout3->setMargin( 0 );

    newPart = new QPushButton( GroupBox3, "newPart" );
    newPart->setText( tr( "New" ) );
    QToolTip::add(  newPart, tr( "create a new node part" ) );
    Layout3->addWidget( newPart );

    deletePart = new QPushButton( GroupBox3, "deletePart" );
    deletePart->setEnabled( TRUE );
    deletePart->setText( tr( "Delete" ) );
    Layout3->addWidget( deletePart );

    clonePart = new QPushButton( GroupBox3, "clonePart" );
    clonePart->setEnabled( TRUE );
    clonePart->setText( tr( "Clone" ) );
    Layout3->addWidget( clonePart );

    upPart = new QPushButton( GroupBox3, "upPart" );
    upPart->setText( tr( "Up" ) );
    Layout3->addWidget( upPart );

    downPart = new QPushButton( GroupBox3, "downPart" );
    downPart->setText( tr( "Down" ) );
    Layout3->addWidget( downPart );
    GroupBox3Layout->addLayout( Layout3 );
    Layout6->addWidget( GroupBox3 );
    FieldContainerViewLayout->addLayout( Layout6 );

    Layout8 = new QHBoxLayout; 
    Layout8->setSpacing( 6 );
    Layout8->setMargin( 0 );

    Layout7 = new QGridLayout; 
    Layout7->setSpacing( 6 );
    Layout7->setMargin( 0 );

    load = new QPushButton( this, "load" );
    load->setText( tr( "Load" ) );

    Layout7->addWidget( load, 0, 2 );

    save = new QPushButton( this, "save" );
    save->setText( tr( "Save" ) );

    Layout7->addWidget( save, 0, 3 );

    PushButton16 = new QPushButton( this, "PushButton16" );
    PushButton16->setText( tr( "Reset Field Types" ) );

    Layout7->addWidget( PushButton16, 1, 1 );

    loadParent = new QPushButton( this, "loadParent" );
    loadParent->setText( tr( "Load parent" ) );

    Layout7->addWidget( loadParent, 1, 2 );

    PushButton15 = new QPushButton( this, "PushButton15" );
    PushButton15->setText( tr( "Load Field Types" ) );

    Layout7->addWidget( PushButton15, 0, 1 );

    writeNodeCode = new QPushButton( this, "writeNodeCode" );
    writeNodeCode->setText( tr( "Write Field Container Base Code" ) );

    Layout7->addWidget( writeNodeCode, 0, 4 );

    PushButton14 = new QPushButton( this, "PushButton14" );
    PushButton14->setText( tr( "New" ) );

    Layout7->addWidget( PushButton14, 0, 0 );

    writeProcCode = new QPushButton( this, "writeProcCode" );
    writeProcCode->setText( tr( "Write Field Container Code" ) );

    Layout7->addWidget( writeProcCode, 1, 4 );

    saveAs = new QPushButton( this, "saveAs" );
    saveAs->setText( tr( "Save as" ) );

    Layout7->addWidget( saveAs, 1, 3 );
    Layout8->addLayout( Layout7 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout8->addItem( spacer );

    Layout4 = new QVBoxLayout; 
    Layout4->setSpacing( 6 );
    Layout4->setMargin( 0 );

    about = new QPushButton( this, "about" );
    about->setText( tr( "About" ) );
    Layout4->addWidget( about );

    exit = new QPushButton( this, "exit" );
    exit->setText( tr( "Exit" ) );
    Layout4->addWidget( exit );
    Layout8->addLayout( Layout4 );
    FieldContainerViewLayout->addLayout( Layout8 );

    // signals and slots connections
    connect( load, SIGNAL( clicked() ), this, SLOT( loadSlot() ) );
    connect( save, SIGNAL( clicked() ), this, SLOT( saveSlot() ) );
    connect( newPart, SIGNAL( clicked() ), this, SLOT( newPartSlot() ) );
    connect( deletePart, SIGNAL( clicked() ), this, SLOT( deletePartSlot() ) );
    connect( clonePart, SIGNAL( clicked() ), this, SLOT( clonePartSlot() ) );
    connect( nodeNameInput, SIGNAL( textChanged(const QString&) ), this, SLOT( nameChanged(const QString &) ) );
    connect( nodeParentInput, SIGNAL( textChanged(const QString&) ), this, SLOT( parentChanged(const QString &) ) );
    connect( partNameInput, SIGNAL( textChanged(const QString&) ), this, SLOT( partNameChanged(const QString &) ) );
    connect( partDefaultValueInput, SIGNAL( textChanged(const QString&) ), this, SLOT( partDefaultValueChanged(const QString &) ) );
    connect( partDescriptionInput, SIGNAL( textChanged(const QString&) ), this, SLOT( partDescriptionChanged(const QString &) ) );
    connect( partVisibilityCombo, SIGNAL( activated(int) ), this, SLOT( partVisibilityChanged(int) ) );
    connect( loadParent, SIGNAL( clicked() ), this, SLOT( loadParentSlot() ) );
    connect( saveAs, SIGNAL( clicked() ), this, SLOT( saveAsSlot() ) );
    connect( exit, SIGNAL( clicked() ), this, SLOT( exitSlot() ) );
    connect( upPart, SIGNAL( clicked() ), this, SLOT( upPartSlot() ) );
    connect( downPart, SIGNAL( clicked() ), this, SLOT( downPartSlot() ) );
    connect( partListBox, SIGNAL( highlighted(int) ), this, SLOT( activePartChanged(int) ) );
    connect( about, SIGNAL( clicked() ), this, SLOT( aboutSlot() ) );
    connect( writeNodeCode, SIGNAL( clicked() ), this, SLOT( writeFieldContainerBaseSlot() ) );
    connect( writeProcCode, SIGNAL( clicked() ), this, SLOT( writeFieldContainerSlot() ) );
    connect( pointerFieldTypesCombo, SIGNAL( activated(int) ), this, SLOT( pointerFieldTypesChanged(int) ) );
    connect( partCardinalityCombo, SIGNAL( activated(int) ), this, SLOT( partCardinalityChanged(int) ) );
    connect( nodeLibraryInput, SIGNAL( textChanged(const QString&) ), this, SLOT( libraryChanged(const QString &) ) );
    connect( partTypeCombo, SIGNAL( activated(int) ), this, SLOT( partTypeChanged(int) ) );
    connect( PushButton14, SIGNAL( clicked() ), this, SLOT( newSlot() ) );
    connect( PushButton15, SIGNAL( clicked() ), this, SLOT( loadFieldTypesSlot() ) );
    connect( PushButton16, SIGNAL( clicked() ), this, SLOT( resetFieldTypesSlot() ) );

    // tab order
    setTabOrder( nodeNameInput, nodeParentInput );
    setTabOrder( nodeParentInput, nodeLibraryInput );
    setTabOrder( nodeLibraryInput, pointerFieldTypesCombo );
    setTabOrder( pointerFieldTypesCombo, partListBox );
    setTabOrder( partListBox, partNameInput );
    setTabOrder( partNameInput, partTypeCombo );
    setTabOrder( partTypeCombo, partCardinalityCombo );
    setTabOrder( partCardinalityCombo, partVisibilityCombo );
    setTabOrder( partVisibilityCombo, partDefaultValueInput );
    setTabOrder( partDefaultValueInput, partDescriptionInput );
    setTabOrder( partDescriptionInput, newPart );
    setTabOrder( newPart, deletePart );
    setTabOrder( deletePart, clonePart );
    setTabOrder( clonePart, upPart );
    setTabOrder( upPart, downPart );
    setTabOrder( downPart, load );
    setTabOrder( load, loadParent );
    setTabOrder( loadParent, save );
    setTabOrder( save, saveAs );
    setTabOrder( saveAs, writeNodeCode );
    setTabOrder( writeNodeCode, writeProcCode );
    setTabOrder( writeProcCode, about );
    setTabOrder( about, exit );
    setTabOrder( exit, nodeDescriptionInput );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
FieldContainerView::~FieldContainerView()
{
    // no need to delete child widgets, Qt does it all for us
}

void FieldContainerView::aboutSlot()
{
    qWarning( "FieldContainerView::aboutSlot(): Not implemented yet!" );
}

void FieldContainerView::activePartChanged(int)
{
    qWarning( "FieldContainerView::activePartChanged(int): Not implemented yet!" );
}

void FieldContainerView::clonePartSlot()
{
    qWarning( "FieldContainerView::clonePartSlot(): Not implemented yet!" );
}

void FieldContainerView::deletePartSlot()
{
    qWarning( "FieldContainerView::deletePartSlot(): Not implemented yet!" );
}

void FieldContainerView::downPartSlot()
{
    qWarning( "FieldContainerView::downPartSlot(): Not implemented yet!" );
}

void FieldContainerView::exitSlot()
{
    qWarning( "FieldContainerView::exitSlot(): Not implemented yet!" );
}

void FieldContainerView::libraryChanged(const QString &)
{
    qWarning( "FieldContainerView::libraryChanged(const QString &): Not implemented yet!" );
}

void FieldContainerView::loadFieldTypesSlot()
{
    qWarning( "FieldContainerView::loadFieldTypesSlot(): Not implemented yet!" );
}

void FieldContainerView::loadParentSlot()
{
    qWarning( "FieldContainerView::loadParentSlot(): Not implemented yet!" );
}

void FieldContainerView::loadSlot()
{
    qWarning( "FieldContainerView::loadSlot(): Not implemented yet!" );
}

void FieldContainerView::nameChanged(const QString &)
{
    qWarning( "FieldContainerView::nameChanged(const QString &): Not implemented yet!" );
}

void FieldContainerView::newPartSlot()
{
    qWarning( "FieldContainerView::newPartSlot(): Not implemented yet!" );
}

void FieldContainerView::newSlot()
{
    qWarning( "FieldContainerView::newSlot(): Not implemented yet!" );
}

void FieldContainerView::resetFieldTypesSlot()
{
    qWarning( "FieldContainerView::resetFieldTypesSlot(): Not implemented yet!" );
}

void FieldContainerView::parentChanged(const QString &)
{
    qWarning( "FieldContainerView::parentChanged(const QString &): Not implemented yet!" );
}

void FieldContainerView::partCardinalityChanged(int)
{
    qWarning( "FieldContainerView::partCardinalityChanged(int): Not implemented yet!" );
}

void FieldContainerView::partDefaultValueChanged(const QString &)
{
    qWarning( "FieldContainerView::partDefaultValueChanged(const QString &): Not implemented yet!" );
}

void FieldContainerView::partDescriptionChanged(const QString &)
{
    qWarning( "FieldContainerView::partDescriptionChanged(const QString &): Not implemented yet!" );
}

void FieldContainerView::partNameChanged(const QString &)
{
    qWarning( "FieldContainerView::partNameChanged(const QString &): Not implemented yet!" );
}

void FieldContainerView::partTypeChanged(int)
{
    qWarning( "FieldContainerView::partTypeChanged(int): Not implemented yet!" );
}

void FieldContainerView::partVisibilityChanged(int)
{
    qWarning( "FieldContainerView::partVisibilityChanged(int): Not implemented yet!" );
}

void FieldContainerView::pointerFieldTypesChanged(int)
{
    qWarning( "FieldContainerView::pointerFieldTypesChanged(int): Not implemented yet!" );
}

void FieldContainerView::saveAsSlot()
{
    qWarning( "FieldContainerView::saveAsSlot(): Not implemented yet!" );
}

void FieldContainerView::saveSlot()
{
    qWarning( "FieldContainerView::saveSlot(): Not implemented yet!" );
}

void FieldContainerView::upPartSlot()
{
    qWarning( "FieldContainerView::upPartSlot(): Not implemented yet!" );
}

void FieldContainerView::writeFieldContainerBaseSlot()
{
    qWarning( "FieldContainerView::writeFieldContainerBaseSlot(): Not implemented yet!" );
}

void FieldContainerView::writeFieldContainerSlot()
{
    qWarning( "FieldContainerView::writeFieldContainerSlot(): Not implemented yet!" );
}

