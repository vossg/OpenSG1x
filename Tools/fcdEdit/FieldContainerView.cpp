/****************************************************************************
** Form implementation generated from reading ui file 'FieldContainerView.ui'
**
** Created: Sat Feb 16 18:32:33 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "FieldContainerView.h"

#include <qvariant.h>   // first for gcc 2.7.2
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistbox.h>
#include <qmultilineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "FieldContainerView.ui.h"

/* 
 *  Constructs a FieldContainerView which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
FieldContainerView::FieldContainerView( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "FieldContainerView" );
    resize( 856, 671 ); 
    setCaption( trUtf8( "OpenSG Field Container editor" ) );
    FieldContainerViewLayout = new QVBoxLayout( this, 11, 6, "FieldContainerViewLayout"); 

    Layout6 = new QHBoxLayout( 0, 0, 6, "Layout6"); 

    GroupBox1 = new QGroupBox( this, "GroupBox1" );
    GroupBox1->setTitle( trUtf8( "Field Container" ) );
    QWhatsThis::add( GroupBox1, trUtf8( "Pointer Field Types" ) );

    GroupBox7 = new QGroupBox( GroupBox1, "GroupBox7" );
    GroupBox7->setGeometry( QRect( 11, 274, 356, 272 ) ); 
    GroupBox7->setTitle( trUtf8( "Description" ) );
    GroupBox7->setColumnLayout(0, Qt::Vertical );
    GroupBox7->layout()->setSpacing( 6 );
    GroupBox7->layout()->setMargin( 11 );
    GroupBox7Layout = new QVBoxLayout( GroupBox7->layout() );
    GroupBox7Layout->setAlignment( Qt::AlignTop );

    nodeDescriptionInput = new QMultiLineEdit( GroupBox7, "nodeDescriptionInput" );
    nodeDescriptionInput->setWordWrap( QMultiLineEdit::WidgetWidth );
    GroupBox7Layout->addWidget( nodeDescriptionInput );

    GroupBox17 = new QGroupBox( GroupBox1, "GroupBox17" );
    GroupBox17->setGeometry( QRect( 11, 23, 356, 245 ) ); 
    GroupBox17->setTitle( trUtf8( "Type" ) );

    TextLabel2 = new QLabel( GroupBox17, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 11, 23, 73, 25 ) ); 
    TextLabel2->setText( trUtf8( "Name:" ) );

    TextLabel3 = new QLabel( GroupBox17, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 11, 83, 73, 25 ) ); 
    TextLabel3->setText( trUtf8( "Parent:" ) );

    TextLabel1 = new QLabel( GroupBox17, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 11, 143, 73, 25 ) ); 
    TextLabel1->setText( trUtf8( "Library:" ) );

    nodeParentInput = new QLineEdit( GroupBox17, "nodeParentInput" );
    nodeParentInput->setGeometry( QRect( 90, 83, 255, 25 ) ); 

    nodeNameInput = new QLineEdit( GroupBox17, "nodeNameInput" );
    nodeNameInput->setGeometry( QRect( 90, 23, 255, 25 ) ); 

    nodeLibraryInput = new QLineEdit( GroupBox17, "nodeLibraryInput" );
    nodeLibraryInput->setGeometry( QRect( 90, 143, 255, 25 ) ); 

    TextLabel1_4 = new QLabel( GroupBox17, "TextLabel1_4" );
    TextLabel1_4->setGeometry( QRect( 11, 174, 73, 27 ) ); 
    TextLabel1_4->setText( trUtf8( "PFTypes:" ) );

    pointerFieldTypesCombo = new QComboBox( FALSE, GroupBox17, "pointerFieldTypesCombo" );
    pointerFieldTypesCombo->setGeometry( QRect( 90, 174, 255, 27 ) ); 
    QToolTip::add( pointerFieldTypesCombo, trUtf8( "Pointer Field Types" ) );

    structureCombo = new QComboBox( FALSE, GroupBox17, "structureCombo" );
    structureCombo->setGeometry( QRect( 90, 207, 255, 27 ) ); 

    TextLabel1_5 = new QLabel( GroupBox17, "TextLabel1_5" );
    TextLabel1_5->setGeometry( QRect( 11, 207, 73, 27 ) ); 
    TextLabel1_5->setText( trUtf8( "Structure:" ) );

    parentSysComp = new QCheckBox( GroupBox17, "parentSysComp" );
    parentSysComp->setGeometry( QRect( 11, 114, 334, 23 ) ); 
    parentSysComp->setText( trUtf8( "Is Parent a System Component?" ) );
    parentSysComp->setChecked( TRUE );

    sysComp = new QCheckBox( GroupBox17, "sysComp" );
    sysComp->setGeometry( QRect( 11, 54, 180, 23 ) ); 
    sysComp->setText( trUtf8( "System Component?" ) );

    decoratableSwitch = new QCheckBox( GroupBox17, "decoratableSwitch" );
    decoratableSwitch->setGeometry( QRect( 220, 54, 120, 23 ) ); 
    decoratableSwitch->setText( trUtf8( "Decoratable?" ) );
    Layout6->addWidget( GroupBox1 );

    GroupBox3 = new QGroupBox( this, "GroupBox3" );
    GroupBox3->setTitle( trUtf8( "Fields" ) );
    GroupBox3->setColumnLayout(0, Qt::Vertical );
    GroupBox3->layout()->setSpacing( 6 );
    GroupBox3->layout()->setMargin( 11 );
    GroupBox3Layout = new QVBoxLayout( GroupBox3->layout() );
    GroupBox3Layout->setAlignment( Qt::AlignTop );

    partListBox = new QListBox( GroupBox3, "partListBox" );
    partListBox->setEnabled( TRUE );
    GroupBox3Layout->addWidget( partListBox );

    partFrame = new QFrame( GroupBox3, "partFrame" );
    partFrame->setEnabled( TRUE );
    partFrame->setFrameShape( QFrame::Box );
    partFrame->setFrameShadow( QFrame::Raised );
    partFrameLayout = new QGridLayout( partFrame, 1, 1, 11, 6, "partFrameLayout"); 

    TextLabel3_2 = new QLabel( partFrame, "TextLabel3_2" );
    TextLabel3_2->setText( trUtf8( "Type:" ) );

    partFrameLayout->addWidget( TextLabel3_2, 1, 0 );

    partTypeCombo = new QComboBox( FALSE, partFrame, "partTypeCombo" );
    partTypeCombo->setEditable( TRUE );

    partFrameLayout->addWidget( partTypeCombo, 1, 1 );

    TextLabel2_2 = new QLabel( partFrame, "TextLabel2_2" );
    TextLabel2_2->setText( trUtf8( "Cardinality:" ) );

    partFrameLayout->addWidget( TextLabel2_2, 2, 0 );

    TextLabel1_2 = new QLabel( partFrame, "TextLabel1_2" );
    TextLabel1_2->setText( trUtf8( "Name:" ) );

    partFrameLayout->addWidget( TextLabel1_2, 0, 0 );

    TextLabel4_2 = new QLabel( partFrame, "TextLabel4_2" );
    TextLabel4_2->setText( trUtf8( "DefaultValue:" ) );

    partFrameLayout->addWidget( TextLabel4_2, 6, 0 );

    partCardinalityCombo = new QComboBox( FALSE, partFrame, "partCardinalityCombo" );

    partFrameLayout->addWidget( partCardinalityCombo, 2, 1 );

    partNameInput = new QLineEdit( partFrame, "partNameInput" );
    partNameInput->setEnabled( TRUE );

    partFrameLayout->addWidget( partNameInput, 0, 1 );

    TextLabel2_3 = new QLabel( partFrame, "TextLabel2_3" );
    TextLabel2_3->setText( trUtf8( "Access:" ) );

    partFrameLayout->addWidget( TextLabel2_3, 3, 0 );

    TextLabel1_3 = new QLabel( partFrame, "TextLabel1_3" );
    TextLabel1_3->setText( trUtf8( "Visibility:" ) );

    partFrameLayout->addWidget( TextLabel1_3, 4, 0 );

    TextLabel3_3 = new QLabel( partFrame, "TextLabel3_3" );
    TextLabel3_3->setText( trUtf8( "Header:" ) );

    partFrameLayout->addWidget( TextLabel3_3, 5, 0 );

    partAccessCombo = new QComboBox( FALSE, partFrame, "partAccessCombo" );

    partFrameLayout->addWidget( partAccessCombo, 3, 1 );

    partVisibilityCombo = new QComboBox( FALSE, partFrame, "partVisibilityCombo" );

    partFrameLayout->addWidget( partVisibilityCombo, 4, 1 );

    partIncludeInput = new QLineEdit( partFrame, "partIncludeInput" );

    partFrameLayout->addWidget( partIncludeInput, 5, 1 );

    partDefaultValueInput = new QLineEdit( partFrame, "partDefaultValueInput" );

    partFrameLayout->addWidget( partDefaultValueInput, 6, 1 );

    partDescriptionInput = new QLineEdit( partFrame, "partDescriptionInput" );

    partFrameLayout->addWidget( partDescriptionInput, 8, 1 );

    TextLabel5 = new QLabel( partFrame, "TextLabel5" );
    TextLabel5->setText( trUtf8( "Description:" ) );

    partFrameLayout->addWidget( TextLabel5, 8, 0 );

    TextLabel1_6 = new QLabel( partFrame, "TextLabel1_6" );
    TextLabel1_6->setText( trUtf8( "DefaultHeader:" ) );

    partFrameLayout->addWidget( TextLabel1_6, 7, 0 );

    partDefaultHeaderInput = new QLineEdit( partFrame, "partDefaultHeaderInput" );

    partFrameLayout->addWidget( partDefaultHeaderInput, 7, 1 );
    GroupBox3Layout->addWidget( partFrame );

    Layout3 = new QHBoxLayout( 0, 0, 6, "Layout3"); 

    newPart = new QPushButton( GroupBox3, "newPart" );
    newPart->setText( trUtf8( "New" ) );
    QToolTip::add( newPart, trUtf8( "create a new node part" ) );
    Layout3->addWidget( newPart );

    deletePart = new QPushButton( GroupBox3, "deletePart" );
    deletePart->setEnabled( TRUE );
    deletePart->setText( trUtf8( "Delete" ) );
    Layout3->addWidget( deletePart );

    clonePart = new QPushButton( GroupBox3, "clonePart" );
    clonePart->setEnabled( TRUE );
    clonePart->setText( trUtf8( "Clone" ) );
    Layout3->addWidget( clonePart );

    upPart = new QPushButton( GroupBox3, "upPart" );
    upPart->setText( trUtf8( "Up" ) );
    Layout3->addWidget( upPart );

    downPart = new QPushButton( GroupBox3, "downPart" );
    downPart->setText( trUtf8( "Down" ) );
    Layout3->addWidget( downPart );
    GroupBox3Layout->addLayout( Layout3 );
    Layout6->addWidget( GroupBox3 );
    FieldContainerViewLayout->addLayout( Layout6 );

    Layout7 = new QHBoxLayout( 0, 0, 6, "Layout7"); 

    Layout6_2 = new QGridLayout( 0, 1, 1, 0, 6, "Layout6_2"); 

    writeNodeCode = new QPushButton( this, "writeNodeCode" );
    writeNodeCode->setText( trUtf8( "Write Field Container Base Code" ) );

    Layout6_2->addWidget( writeNodeCode, 0, 4 );

    writeProcCode = new QPushButton( this, "writeProcCode" );
    writeProcCode->setText( trUtf8( "Write Field Container Code" ) );

    Layout6_2->addWidget( writeProcCode, 1, 4 );

    saveAs = new QPushButton( this, "saveAs" );
    saveAs->setText( trUtf8( "Save as" ) );

    Layout6_2->addWidget( saveAs, 1, 3 );

    load = new QPushButton( this, "load" );
    load->setText( trUtf8( "Load" ) );

    Layout6_2->addWidget( load, 0, 1 );

    save = new QPushButton( this, "save" );
    save->setText( trUtf8( "Save" ) );

    Layout6_2->addWidget( save, 0, 3 );

    PushButton15 = new QPushButton( this, "PushButton15" );
    PushButton15->setText( trUtf8( "Reset Field Types" ) );

    Layout6_2->addWidget( PushButton15, 0, 2 );

    PushButton16 = new QPushButton( this, "PushButton16" );
    PushButton16->setText( trUtf8( "Load Field Types" ) );

    Layout6_2->addWidget( PushButton16, 1, 2 );

    loadParent = new QPushButton( this, "loadParent" );
    loadParent->setText( trUtf8( "Load parent" ) );

    Layout6_2->addWidget( loadParent, 1, 1 );

    PushButton14 = new QPushButton( this, "PushButton14" );
    PushButton14->setText( trUtf8( "New" ) );

    Layout6_2->addWidget( PushButton14, 0, 0 );
    Layout7->addLayout( Layout6_2 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout7->addItem( spacer );

    Layout4 = new QVBoxLayout( 0, 0, 6, "Layout4"); 

    about = new QPushButton( this, "about" );
    about->setText( trUtf8( "About" ) );
    Layout4->addWidget( about );

    exit = new QPushButton( this, "exit" );
    exit->setText( trUtf8( "Exit" ) );
    Layout4->addWidget( exit );
    Layout7->addLayout( Layout4 );
    FieldContainerViewLayout->addLayout( Layout7 );

    // signals and slots connections
    connect( load, SIGNAL( clicked() ), this, SLOT( loadSlot() ) );
    connect( save, SIGNAL( clicked() ), this, SLOT( saveSlot() ) );
    connect( newPart, SIGNAL( clicked() ), this, SLOT( newPartSlot() ) );
    connect( deletePart, SIGNAL( clicked() ), this, SLOT( deletePartSlot() ) );
    connect( clonePart, SIGNAL( clicked() ), this, SLOT( clonePartSlot() ) );
    connect( nodeNameInput, SIGNAL( textChanged(const QString&) ), this, SLOT( nameChanged(const QString&) ) );
    connect( nodeParentInput, SIGNAL( textChanged(const QString&) ), this, SLOT( parentChanged(const QString&) ) );
    connect( partNameInput, SIGNAL( textChanged(const QString&) ), this, SLOT( partNameChanged(const QString&) ) );
    connect( partDefaultValueInput, SIGNAL( textChanged(const QString&) ), this, SLOT( partDefaultValueChanged(const QString&) ) );
    connect( partDescriptionInput, SIGNAL( textChanged(const QString&) ), this, SLOT( partDescriptionChanged(const QString&) ) );
    connect( partVisibilityCombo, SIGNAL( activated(int) ), this, SLOT( partVisibilityChanged(int) ) );
    connect( loadParent, SIGNAL( clicked() ), this, SLOT( loadParentSlot() ) );
    connect( saveAs, SIGNAL( clicked() ), this, SLOT( saveAsSlot() ) );
    connect( exit, SIGNAL( clicked() ), this, SLOT( exitSlot() ) );
    connect( upPart, SIGNAL( clicked() ), this, SLOT( upPartSlot() ) );
    connect( downPart, SIGNAL( clicked() ), this, SLOT( downPartSlot() ) );
    connect( partListBox, SIGNAL( highlighted(int) ), this, SLOT( activePartChanged(int) ) );
    connect( about, SIGNAL( clicked() ), this, SLOT( aboutSlot() ) );
    connect( writeNodeCode, SIGNAL( clicked() ), this, SLOT( writeFieldContainerBaseSlot() ) );
    connect( pointerFieldTypesCombo, SIGNAL( activated(int) ), this, SLOT( pointerFieldTypesChanged(int) ) );
    connect( partCardinalityCombo, SIGNAL( activated(int) ), this, SLOT( partCardinalityChanged(int) ) );
    connect( nodeLibraryInput, SIGNAL( textChanged(const QString&) ), this, SLOT( libraryChanged(const QString&) ) );
    connect( PushButton14, SIGNAL( clicked() ), this, SLOT( newSlot() ) );
    connect( PushButton15, SIGNAL( clicked() ), this, SLOT( resetFieldTypesSlot() ) );
    connect( PushButton16, SIGNAL( clicked() ), this, SLOT( loadFieldTypesSlot() ) );
    connect( structureCombo, SIGNAL( activated(int) ), this, SLOT( structureChanged(int) ) );
    connect( partAccessCombo, SIGNAL( activated(int) ), this, SLOT( partAccessChanged(int) ) );
    connect( partIncludeInput, SIGNAL( textChanged(const QString&) ), this, SLOT( partIncludeChanged(const QString&) ) );
    connect( partDefaultHeaderInput, SIGNAL( textChanged(const QString&) ), this, SLOT( partDefaultHeaderChanged(const QString&) ) );
    connect( sysComp, SIGNAL( stateChanged(int) ), this, SLOT( sysCompChanged(int) ) );
    connect( parentSysComp, SIGNAL( stateChanged(int) ), this, SLOT( parentSysCompChanged(int) ) );
    connect( partTypeCombo, SIGNAL( textChanged(const QString&) ), this, SLOT( partTypeChanged(const QString&) ) );
    connect( decoratableSwitch, SIGNAL( stateChanged(int) ), this, SLOT( decoratableSwitch_stateChanged(int) ) );
    connect( writeProcCode, SIGNAL( stateChanged(int) ), this, SLOT( writeFieldContainerSlot(int) ) );

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

